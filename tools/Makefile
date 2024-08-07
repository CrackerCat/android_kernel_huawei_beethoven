# Some of the tools (perf) use same make variables
# as in kernel build.
export srctree=
export objtree=

include scripts/Makefile.include

help:
	@echo 'Possible targets:'
	@echo ''
	@echo '  acpi       - ACPI tools'
	@echo '  cgroup     - cgroup tools'
	@echo '  cpupower   - a tool for all things x86 CPU power'
	@echo '  firewire   - the userspace part of nosy, an IEEE-1394 traffic sniffer'
	@echo '  hv         - tools used when in Hyper-V clients'
	@echo '  lguest     - a minimal 32-bit x86 hypervisor'
	@echo '  perf       - Linux performance measurement and analysis tool'
	@echo '  selftests  - various kernel selftests'
	@echo '  turbostat  - Intel CPU idle stats and freq reporting tool'
	@echo '  usb        - USB testing tools'
	@echo '  virtio     - vhost test module'
	@echo '  net        - misc networking tools'
	@echo '  vm         - misc vm tools'
	@echo '  x86_energy_perf_policy - Intel energy policy tool'
	@echo '  tmon       - thermal monitoring and tuning tool'
	@echo ''
	@echo 'You can do:'
	@echo ' $$ make -C tools/ <tool>_install'
	@echo ''
	@echo '  from the kernel command line to build and install one of'
	@echo '  the tools above'
	@echo ''
	@echo '  $$ make tools/all'
	@echo ''
	@echo '  builds all tools.'
	@echo ''
	@echo '  $$ make tools/install'
	@echo ''
	@echo '  installs all tools.'
	@echo ''
	@echo 'Cleaning targets:'
	@echo ''
	@echo '  all of the above with the "_clean" string appended cleans'
	@echo '    the respective build directory.'
	@echo '  clean: a summary clean target to clean _all_ folders'

acpi: FORCE
	$(call descend,power/$@)

cpupower: FORCE
	$(call descend,power/$@)

cgroup firewire hv guest usb virtio vm net: FORCE
	$(call descend,$@)

liblockdep: FORCE
	$(call descend,lib/lockdep)

libapi: FORCE
	$(call descend,lib/api)

# The perf build does not follow the descend function setup,
# invoking it via it's own make rule.
PERF_O   = $(if $(O),$(O)/tools/perf,)

perf: FORCE
	$(Q)mkdir -p $(PERF_O) .
	$(Q)$(MAKE) --no-print-directory -C perf O=$(PERF_O) subdir=

selftests: FORCE
	$(call descend,testing/$@)

turbostat x86_energy_perf_policy: FORCE
	$(call descend,power/x86/$@)

tmon: FORCE
	$(call descend,thermal/$@)

freefall: FORCE
	$(call descend,laptop/$@)

all: acpi cgroup cpupower hv firewire lguest \
		perf selftests turbostat usb \
		virtio vm net x86_energy_perf_policy \
		tmon freefall

acpi_install:
	$(call descend,power/$(@:_install=),install)

cpupower_install:
	$(call descend,power/$(@:_install=),install)

cgroup_install firewire_install hv_install lguest_install perf_install usb_install virtio_install vm_install net_install:
	$(call descend,$(@:_install=),install)

selftests_install:
	$(call descend,testing/$(@:_clean=),install)

turbostat_install x86_energy_perf_policy_install:
	$(call descend,power/x86/$(@:_install=),install)

tmon_install:
	$(call descend,thermal/$(@:_install=),install)

install: acpi_install cgroup_install cpupower_install hv_install firewire_install lguest_install \
		perf_install selftests_install turbostat_install usb_install \
		virtio_install vm_install net_install x86_energy_perf_policy_install \
		tmon_install freefall_install

acpi_clean:
	$(call descend,power/acpi,clean)

cpupower_clean:
	$(call descend,power/cpupower,clean)

cgroup_clean hv_clean firewire_clean lguest_clean usb_clean virtio_clean vm_clean net_clean:
	$(call descend,$(@:_clean=),clean)

liblockdep_clean:
	$(call descend,lib/lockdep,clean)

libapi_clean:
	$(call descend,lib/api,clean)

perf_clean:
	$(call descend,$(@:_clean=),clean)

selftests_clean:
	$(call descend,testing/$(@:_clean=),clean)

turbostat_clean x86_energy_perf_policy_clean:
	$(call descend,power/x86/$(@:_clean=),clean)

tmon_clean:
	$(call descend,thermal/tmon,clean)

clean: acpi_clean cgroup_clean cpupower_clean hv_clean firewire_clean lguest_clean \
		perf_clean selftests_clean turbostat_clean usb_clean virtio_clean \
		vm_clean net_clean x86_energy_perf_policy_clean tmon_clean

.PHONY: FORCE
