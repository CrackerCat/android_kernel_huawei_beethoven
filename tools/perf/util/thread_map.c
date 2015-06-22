#include <dirent.h>
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "strlist.h"
#include <string.h>
#include "asm/bug.h"
#include "thread_map.h"
#include "util.h"

/* Skip "." and ".." directories */
static int filter(const struct dirent *dir)
{
	if (dir->d_name[0] == '.')
		return 0;
	else
		return 1;
}

static struct thread_map *thread_map__realloc(struct thread_map *map, int nr)
{
	size_t size = sizeof(*map) + sizeof(map->map[0]) * nr;

	return realloc(map, size);
}

#define thread_map__alloc(__nr) thread_map__realloc(NULL, __nr)

struct thread_map *thread_map__new_by_pid(pid_t pid)
{
	struct thread_map *threads;
	char name[256];
	int items;
	struct dirent **namelist = NULL;
	int i;

	sprintf(name, "/proc/%d/task", pid);
	items = scandir(name, &namelist, filter, NULL);
	if (items <= 0)
		return NULL;

	threads = thread_map__alloc(items);
	if (threads != NULL) {
		for (i = 0; i < items; i++)
			thread_map__set_pid(threads, i, atoi(namelist[i]->d_name));
		threads->nr = items;
		atomic_set(&threads->refcnt, 1);
	}

	for (i=0; i<items; i++)
		zfree(&namelist[i]);
	free(namelist);

	return threads;
}

struct thread_map *thread_map__new_by_tid(pid_t tid)
{
	struct thread_map *threads = thread_map__alloc(1);

	if (threads != NULL) {
		thread_map__set_pid(threads, 0, tid);
		threads->nr = 1;
		atomic_set(&threads->refcnt, 1);
	}

	return threads;
}

struct thread_map *thread_map__new_by_uid(uid_t uid)
{
	DIR *proc;
	int max_threads = 32, items, i;
	char path[256];
	struct dirent dirent, *next, **namelist = NULL;
	struct thread_map *threads = thread_map__alloc(max_threads);

	if (threads == NULL)
		goto out;

	proc = opendir("/proc");
	if (proc == NULL)
		goto out_free_threads;

	threads->nr = 0;
	atomic_set(&threads->refcnt, 1);

	while (!readdir_r(proc, &dirent, &next) && next) {
		char *end;
		bool grow = false;
		struct stat st;
		pid_t pid = strtol(dirent.d_name, &end, 10);

		if (*end) /* only interested in proper numerical dirents */
			continue;

		snprintf(path, sizeof(path), "/proc/%s", dirent.d_name);

		if (stat(path, &st) != 0)
			continue;

		if (st.st_uid != uid)
			continue;

		snprintf(path, sizeof(path), "/proc/%d/task", pid);
		items = scandir(path, &namelist, filter, NULL);
		if (items <= 0)
			goto out_free_closedir;

		while (threads->nr + items >= max_threads) {
			max_threads *= 2;
			grow = true;
		}

		if (grow) {
			struct thread_map *tmp;

			tmp = realloc(threads, (sizeof(*threads) +
						max_threads * sizeof(pid_t)));
			if (tmp == NULL)
				goto out_free_namelist;

			threads = tmp;
		}

		for (i = 0; i < items; i++) {
			thread_map__set_pid(threads, threads->nr + i,
					    atoi(namelist[i]->d_name));
		}

		for (i = 0; i < items; i++)
			zfree(&namelist[i]);
		free(namelist);

		threads->nr += items;
	}

out_closedir:
	closedir(proc);
out:
	return threads;

out_free_threads:
	free(threads);
	return NULL;

out_free_namelist:
	for (i = 0; i < items; i++)
		zfree(&namelist[i]);
	free(namelist);

out_free_closedir:
	zfree(&threads);
	goto out_closedir;
}

struct thread_map *thread_map__new(pid_t pid, pid_t tid, uid_t uid)
{
	if (pid != -1)
		return thread_map__new_by_pid(pid);

	if (tid == -1 && uid != UINT_MAX)
		return thread_map__new_by_uid(uid);

	return thread_map__new_by_tid(tid);
}

static struct thread_map *thread_map__new_by_pid_str(const char *pid_str)
{
	struct thread_map *threads = NULL, *nt;
	char name[256];
	int items, total_tasks = 0;
	struct dirent **namelist = NULL;
	int i, j = 0;
	pid_t pid, prev_pid = INT_MAX;
	char *end_ptr;
	struct str_node *pos;
	struct strlist *slist = strlist__new(false, pid_str);

	if (!slist)
		return NULL;

	strlist__for_each(pos, slist) {
		pid = strtol(pos->s, &end_ptr, 10);

		if (pid == INT_MIN || pid == INT_MAX ||
		    (*end_ptr != '\0' && *end_ptr != ','))
			goto out_free_threads;

		if (pid == prev_pid)
			continue;

		sprintf(name, "/proc/%d/task", pid);
		items = scandir(name, &namelist, filter, NULL);
		if (items <= 0)
			goto out_free_threads;

		total_tasks += items;
		nt = thread_map__realloc(threads, total_tasks);
		if (nt == NULL)
			goto out_free_namelist;

		threads = nt;

		for (i = 0; i < items; i++) {
			thread_map__set_pid(threads, j++, atoi(namelist[i]->d_name));
			zfree(&namelist[i]);
		}
		threads->nr = total_tasks;
		free(namelist);
	}

out:
	strlist__delete(slist);
	if (threads)
		atomic_set(&threads->refcnt, 1);
	return threads;

out_free_namelist:
	for (i = 0; i < items; i++)
		zfree(&namelist[i]);
	free(namelist);

out_free_threads:
	zfree(&threads);
	goto out;
}

struct thread_map *thread_map__new_dummy(void)
{
	struct thread_map *threads = thread_map__alloc(1);

	if (threads != NULL) {
		thread_map__set_pid(threads, 0, -1);
		threads->nr = 1;
		atomic_set(&threads->refcnt, 1);
	}
	return threads;
}

static struct thread_map *thread_map__new_by_tid_str(const char *tid_str)
{
	struct thread_map *threads = NULL, *nt;
	int ntasks = 0;
	pid_t tid, prev_tid = INT_MAX;
	char *end_ptr;
	struct str_node *pos;
	struct strlist *slist;

	/* perf-stat expects threads to be generated even if tid not given */
	if (!tid_str)
		return thread_map__new_dummy();

	slist = strlist__new(false, tid_str);
	if (!slist)
		return NULL;

	strlist__for_each(pos, slist) {
		tid = strtol(pos->s, &end_ptr, 10);

		if (tid == INT_MIN || tid == INT_MAX ||
		    (*end_ptr != '\0' && *end_ptr != ','))
			goto out_free_threads;

		if (tid == prev_tid)
			continue;

		ntasks++;
		nt = thread_map__realloc(threads, ntasks);

		if (nt == NULL)
			goto out_free_threads;

		threads = nt;
		thread_map__set_pid(threads, ntasks - 1, tid);
		threads->nr = ntasks;
	}
out:
	if (threads)
		atomic_set(&threads->refcnt, 1);
	return threads;

out_free_threads:
	zfree(&threads);
	goto out;
}

struct thread_map *thread_map__new_str(const char *pid, const char *tid,
				       uid_t uid)
{
	if (pid)
		return thread_map__new_by_pid_str(pid);

	if (!tid && uid != UINT_MAX)
		return thread_map__new_by_uid(uid);

	return thread_map__new_by_tid_str(tid);
}

static void thread_map__delete(struct thread_map *threads)
{
	if (threads) {
		WARN_ONCE(atomic_read(&threads->refcnt) != 0,
			  "thread map refcnt unbalanced\n");
		free(threads);
	}
}

struct thread_map *thread_map__get(struct thread_map *map)
{
	if (map)
		atomic_inc(&map->refcnt);
	return map;
}

void thread_map__put(struct thread_map *map)
{
	if (map && atomic_dec_and_test(&map->refcnt))
		thread_map__delete(map);
}

size_t thread_map__fprintf(struct thread_map *threads, FILE *fp)
{
	int i;
	size_t printed = fprintf(fp, "%d thread%s: ",
				 threads->nr, threads->nr > 1 ? "s" : "");
	for (i = 0; i < threads->nr; ++i)
		printed += fprintf(fp, "%s%d", i ? ", " : "", thread_map__pid(threads, i));

	return printed + fprintf(fp, "\n");
}
