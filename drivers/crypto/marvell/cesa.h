#ifndef __MARVELL_CESA_H__
#define __MARVELL_CESA_H__

#include <crypto/algapi.h>
#include <crypto/hash.h>
#include <crypto/internal/hash.h>

#include <linux/crypto.h>

#define CESA_ENGINE_OFF(i)			(((i) * 0x2000))

#define CESA_TDMA_BYTE_CNT			0x800
#define CESA_TDMA_SRC_ADDR			0x810
#define CESA_TDMA_DST_ADDR			0x820
#define CESA_TDMA_NEXT_ADDR			0x830

#define CESA_TDMA_CONTROL			0x840
#define CESA_TDMA_DST_BURST			GENMASK(2, 0)
#define CESA_TDMA_DST_BURST_32B			3
#define CESA_TDMA_DST_BURST_128B		4
#define CESA_TDMA_OUT_RD_EN			BIT(4)
#define CESA_TDMA_SRC_BURST			GENMASK(8, 6)
#define CESA_TDMA_SRC_BURST_32B			(3 << 6)
#define CESA_TDMA_SRC_BURST_128B		(4 << 6)
#define CESA_TDMA_CHAIN				BIT(9)
#define CESA_TDMA_BYTE_SWAP			BIT(11)
#define CESA_TDMA_NO_BYTE_SWAP			BIT(11)
#define CESA_TDMA_EN				BIT(12)
#define CESA_TDMA_FETCH_ND			BIT(13)
#define CESA_TDMA_ACT				BIT(14)

#define CESA_TDMA_CUR				0x870
#define CESA_TDMA_ERROR_CAUSE			0x8c8
#define CESA_TDMA_ERROR_MSK			0x8cc

#define CESA_TDMA_WINDOW_BASE(x)		(((x) * 0x8) + 0xa00)
#define CESA_TDMA_WINDOW_CTRL(x)		(((x) * 0x8) + 0xa04)

#define CESA_IVDIG(x)				(0xdd00 + ((x) * 4) +	\
						 (((x) < 5) ? 0 : 0x14))

#define CESA_SA_CMD				0xde00
#define CESA_SA_CMD_EN_CESA_SA_ACCL0		BIT(0)
#define CESA_SA_CMD_EN_CESA_SA_ACCL1		BIT(1)
#define CESA_SA_CMD_DISABLE_SEC			BIT(2)

#define CESA_SA_DESC_P0				0xde04

#define CESA_SA_DESC_P1				0xde14

#define CESA_SA_CFG				0xde08
#define CESA_SA_CFG_STOP_DIG_ERR		GENMASK(1, 0)
#define CESA_SA_CFG_DIG_ERR_CONT		0
#define CESA_SA_CFG_DIG_ERR_SKIP		1
#define CESA_SA_CFG_DIG_ERR_STOP		3
#define CESA_SA_CFG_CH0_W_IDMA			BIT(7)
#define CESA_SA_CFG_CH1_W_IDMA			BIT(8)
#define CESA_SA_CFG_ACT_CH0_IDMA		BIT(9)
#define CESA_SA_CFG_ACT_CH1_IDMA		BIT(10)
#define CESA_SA_CFG_MULTI_PKT			BIT(11)
#define CESA_SA_CFG_PARA_DIS			BIT(13)

#define CESA_SA_ACCEL_STATUS			0xde0c
#define CESA_SA_ST_ACT_0			BIT(0)
#define CESA_SA_ST_ACT_1			BIT(1)

/*
 * CESA_SA_FPGA_INT_STATUS looks like a FPGA leftover and is documented only
 * in Errata 4.12. It looks like that it was part of an IRQ-controller in FPGA
 * and someone forgot to remove  it while switching to the core and moving to
 * CESA_SA_INT_STATUS.
 */
#define CESA_SA_FPGA_INT_STATUS			0xdd68
#define CESA_SA_INT_STATUS			0xde20
#define CESA_SA_INT_AUTH_DONE			BIT(0)
#define CESA_SA_INT_DES_E_DONE			BIT(1)
#define CESA_SA_INT_AES_E_DONE			BIT(2)
#define CESA_SA_INT_AES_D_DONE			BIT(3)
#define CESA_SA_INT_ENC_DONE			BIT(4)
#define CESA_SA_INT_ACCEL0_DONE			BIT(5)
#define CESA_SA_INT_ACCEL1_DONE			BIT(6)
#define CESA_SA_INT_ACC0_IDMA_DONE		BIT(7)
#define CESA_SA_INT_ACC1_IDMA_DONE		BIT(8)
#define CESA_SA_INT_IDMA_DONE			BIT(9)
#define CESA_SA_INT_IDMA_OWN_ERR		BIT(10)

#define CESA_SA_INT_MSK				0xde24

#define CESA_SA_DESC_CFG_OP_MAC_ONLY		0
#define CESA_SA_DESC_CFG_OP_CRYPT_ONLY		1
#define CESA_SA_DESC_CFG_OP_MAC_CRYPT		2
#define CESA_SA_DESC_CFG_OP_CRYPT_MAC		3
#define CESA_SA_DESC_CFG_OP_MSK			GENMASK(1, 0)
#define CESA_SA_DESC_CFG_MACM_SHA256		(1 << 4)
#define CESA_SA_DESC_CFG_MACM_HMAC_SHA256	(3 << 4)
#define CESA_SA_DESC_CFG_MACM_MD5		(4 << 4)
#define CESA_SA_DESC_CFG_MACM_SHA1		(5 << 4)
#define CESA_SA_DESC_CFG_MACM_HMAC_MD5		(6 << 4)
#define CESA_SA_DESC_CFG_MACM_HMAC_SHA1		(7 << 4)
#define CESA_SA_DESC_CFG_MACM_MSK		GENMASK(6, 4)
#define CESA_SA_DESC_CFG_CRYPTM_DES		(1 << 8)
#define CESA_SA_DESC_CFG_CRYPTM_3DES		(2 << 8)
#define CESA_SA_DESC_CFG_CRYPTM_AES		(3 << 8)
#define CESA_SA_DESC_CFG_CRYPTM_MSK		GENMASK(9, 8)
#define CESA_SA_DESC_CFG_DIR_ENC		(0 << 12)
#define CESA_SA_DESC_CFG_DIR_DEC		(1 << 12)
#define CESA_SA_DESC_CFG_CRYPTCM_ECB		(0 << 16)
#define CESA_SA_DESC_CFG_CRYPTCM_CBC		(1 << 16)
#define CESA_SA_DESC_CFG_CRYPTCM_MSK		BIT(16)
#define CESA_SA_DESC_CFG_3DES_EEE		(0 << 20)
#define CESA_SA_DESC_CFG_3DES_EDE		(1 << 20)
#define CESA_SA_DESC_CFG_AES_LEN_128		(0 << 24)
#define CESA_SA_DESC_CFG_AES_LEN_192		(1 << 24)
#define CESA_SA_DESC_CFG_AES_LEN_256		(2 << 24)
#define CESA_SA_DESC_CFG_AES_LEN_MSK		GENMASK(25, 24)
#define CESA_SA_DESC_CFG_NOT_FRAG		(0 << 30)
#define CESA_SA_DESC_CFG_FIRST_FRAG		(1 << 30)
#define CESA_SA_DESC_CFG_LAST_FRAG		(2 << 30)
#define CESA_SA_DESC_CFG_MID_FRAG		(3 << 30)
#define CESA_SA_DESC_CFG_FRAG_MSK		GENMASK(31, 30)

/*
 * /-----------\ 0
 * | ACCEL CFG |	4 * 8
 * |-----------| 0x20
 * | CRYPT KEY |	8 * 4
 * |-----------| 0x40
 * |  IV   IN  |	4 * 4
 * |-----------| 0x40 (inplace)
 * |  IV BUF   |	4 * 4
 * |-----------| 0x80
 * |  DATA IN  |	16 * x (max ->max_req_size)
 * |-----------| 0x80 (inplace operation)
 * |  DATA OUT |	16 * x (max ->max_req_size)
 * \-----------/ SRAM size
 */

/*
 * Hashing memory map:
 * /-----------\ 0
 * | ACCEL CFG |        4 * 8
 * |-----------| 0x20
 * | Inner IV  |        8 * 4
 * |-----------| 0x40
 * | Outer IV  |        8 * 4
 * |-----------| 0x60
 * | Output BUF|        8 * 4
 * |-----------| 0x80
 * |  DATA IN  |        64 * x (max ->max_req_size)
 * \-----------/ SRAM size
 */

#define CESA_SA_CFG_SRAM_OFFSET			0x00
#define CESA_SA_DATA_SRAM_OFFSET		0x80

#define CESA_SA_CRYPT_KEY_SRAM_OFFSET		0x20
#define CESA_SA_CRYPT_IV_SRAM_OFFSET		0x40

#define CESA_SA_MAC_IIV_SRAM_OFFSET		0x20
#define CESA_SA_MAC_OIV_SRAM_OFFSET		0x40
#define CESA_SA_MAC_DIG_SRAM_OFFSET		0x60

#define CESA_SA_DESC_CRYPT_DATA(offset)					\
	cpu_to_le32((CESA_SA_DATA_SRAM_OFFSET + (offset)) |		\
		    ((CESA_SA_DATA_SRAM_OFFSET + (offset)) << 16))

#define CESA_SA_DESC_CRYPT_IV(offset)					\
	cpu_to_le32((CESA_SA_CRYPT_IV_SRAM_OFFSET + (offset)) |	\
		    ((CESA_SA_CRYPT_IV_SRAM_OFFSET + (offset)) << 16))

#define CESA_SA_DESC_CRYPT_KEY(offset)					\
	cpu_to_le32(CESA_SA_CRYPT_KEY_SRAM_OFFSET + (offset))

#define CESA_SA_DESC_MAC_DATA(offset)					\
	cpu_to_le32(CESA_SA_DATA_SRAM_OFFSET + (offset))
#define CESA_SA_DESC_MAC_DATA_MSK		GENMASK(15, 0)

#define CESA_SA_DESC_MAC_TOTAL_LEN(total_len)	cpu_to_le32((total_len) << 16)
#define CESA_SA_DESC_MAC_TOTAL_LEN_MSK		GENMASK(31, 16)

#define CESA_SA_DESC_MAC_SRC_TOTAL_LEN_MAX	0xffff

#define CESA_SA_DESC_MAC_DIGEST(offset)					\
	cpu_to_le32(CESA_SA_MAC_DIG_SRAM_OFFSET + (offset))
#define CESA_SA_DESC_MAC_DIGEST_MSK		GENMASK(15, 0)

#define CESA_SA_DESC_MAC_FRAG_LEN(frag_len)	cpu_to_le32((frag_len) << 16)
#define CESA_SA_DESC_MAC_FRAG_LEN_MSK		GENMASK(31, 16)

#define CESA_SA_DESC_MAC_IV(offset)					\
	cpu_to_le32((CESA_SA_MAC_IIV_SRAM_OFFSET + (offset)) |		\
		    ((CESA_SA_MAC_OIV_SRAM_OFFSET + (offset)) << 16))

#define CESA_SA_SRAM_SIZE			2048
#define CESA_SA_SRAM_PAYLOAD_SIZE		(cesa_dev->sram_size - \
						 CESA_SA_DATA_SRAM_OFFSET)

#define CESA_SA_DEFAULT_SRAM_SIZE		2048
#define CESA_SA_MIN_SRAM_SIZE			1024

#define CESA_SA_SRAM_MSK			(2048 - 1)

#define CESA_MAX_HASH_BLOCK_SIZE		64
#define CESA_HASH_BLOCK_SIZE_MSK		(CESA_MAX_HASH_BLOCK_SIZE - 1)

/**
 * struct mv_cesa_sec_accel_desc - security accelerator descriptor
 * @config:	engine config
 * @enc_p:	input and output data pointers for a cipher operation
 * @enc_len:	cipher operation length
 * @enc_key_p:	cipher key pointer
 * @enc_iv:	cipher IV pointers
 * @mac_src_p:	input pointer and total hash length
 * @mac_digest:	digest pointer and hash operation length
 * @mac_iv:	hmac IV pointers
 *
 * Structure passed to the CESA engine to describe the crypto operation
 * to be executed.
 */
struct mv_cesa_sec_accel_desc {
	u32 config;
	u32 enc_p;
	u32 enc_len;
	u32 enc_key_p;
	u32 enc_iv;
	u32 mac_src_p;
	u32 mac_digest;
	u32 mac_iv;
};

/**
 * struct mv_cesa_blkcipher_op_ctx - cipher operation context
 * @key:	cipher key
 * @iv:		cipher IV
 *
 * Context associated to a cipher operation.
 */
struct mv_cesa_blkcipher_op_ctx {
	u32 key[8];
	u32 iv[4];
};

/**
 * struct mv_cesa_hash_op_ctx - hash or hmac operation context
 * @key:	cipher key
 * @iv:		cipher IV
 *
 * Context associated to an hash or hmac operation.
 */
struct mv_cesa_hash_op_ctx {
	u32 iv[16];
	u32 hash[8];
};

/**
 * struct mv_cesa_op_ctx - crypto operation context
 * @desc:	CESA descriptor
 * @ctx:	context associated to the crypto operation
 *
 * Context associated to a crypto operation.
 */
struct mv_cesa_op_ctx {
	struct mv_cesa_sec_accel_desc desc;
	union {
		struct mv_cesa_blkcipher_op_ctx blkcipher;
		struct mv_cesa_hash_op_ctx hash;
	} ctx;
};

struct mv_cesa_engine;

/**
 * struct mv_cesa_caps - CESA device capabilities
 * @engines:		number of engines
 * @cipher_algs:	supported cipher algorithms
 * @ncipher_algs:	number of supported cipher algorithms
 * @ahash_algs:		supported hash algorithms
 * @nahash_algs:	number of supported hash algorithms
 *
 * Structure used to describe CESA device capabilities.
 */
struct mv_cesa_caps {
	int nengines;
	struct crypto_alg **cipher_algs;
	int ncipher_algs;
	struct ahash_alg **ahash_algs;
	int nahash_algs;
};

/**
 * struct mv_cesa_dev - CESA device
 * @caps:	device capabilities
 * @regs:	device registers
 * @sram_size:	usable SRAM size
 * @lock:	device lock
 * @queue:	crypto request queue
 * @engines:	array of engines
 *
 * Structure storing CESA device information.
 */
struct mv_cesa_dev {
	const struct mv_cesa_caps *caps;
	void __iomem *regs;
	struct device *dev;
	unsigned int sram_size;
	spinlock_t lock;
	struct crypto_queue queue;
	struct mv_cesa_engine *engines;
};

/**
 * struct mv_cesa_engine - CESA engine
 * @id:			engine id
 * @regs:		engine registers
 * @sram:		SRAM memory region
 * @sram_dma:		DMA address of the SRAM memory region
 * @lock:		engine lock
 * @req:		current crypto request
 * @clk:		engine clk
 * @zclk:		engine zclk
 * @max_req_len:	maximum chunk length (useful to create the TDMA chain)
 * @int_mask:		interrupt mask cache
 * @pool:		memory pool pointing to the memory region reserved in
 *			SRAM
 *
 * Structure storing CESA engine information.
 */
struct mv_cesa_engine {
	int id;
	void __iomem *regs;
	void __iomem *sram;
	dma_addr_t sram_dma;
	spinlock_t lock;
	struct crypto_async_request *req;
	struct clk *clk;
	struct clk *zclk;
	size_t max_req_len;
	u32 int_mask;
	struct gen_pool *pool;
};

/**
 * struct mv_cesa_req_ops - CESA request operations
 * @prepare:	prepare a request to be executed on the specified engine
 * @process:	process a request chunk result (should return 0 if the
 *		operation, -EINPROGRESS if it needs more steps or an error
 *		code)
 * @step:	launch the crypto operation on the next chunk
 * @cleanup:	cleanup the crypto request (release associated data)
 */
struct mv_cesa_req_ops {
	void (*prepare)(struct crypto_async_request *req,
			struct mv_cesa_engine *engine);
	int (*process)(struct crypto_async_request *req, u32 status);
	void (*step)(struct crypto_async_request *req);
	void (*cleanup)(struct crypto_async_request *req);
};

/**
 * struct mv_cesa_ctx - CESA operation context
 * @ops:	crypto operations
 *
 * Base context structure inherited by operation specific ones.
 */
struct mv_cesa_ctx {
	const struct mv_cesa_req_ops *ops;
};

/**
 * struct mv_cesa_hash_ctx - CESA hash operation context
 * @base:	base context structure
 *
 * Hash context structure.
 */
struct mv_cesa_hash_ctx {
	struct mv_cesa_ctx base;
};

/**
 * struct mv_cesa_hash_ctx - CESA hmac operation context
 * @base:	base context structure
 * @iv:		initialization vectors
 *
 * HMAC context structure.
 */
struct mv_cesa_hmac_ctx {
	struct mv_cesa_ctx base;
	u32 iv[16];
};

/**
 * enum mv_cesa_req_type - request type definitions
 * @CESA_STD_REQ:	standard request
 */
enum mv_cesa_req_type {
	CESA_STD_REQ,
};

/**
 * struct mv_cesa_req - CESA request
 * @type:	request type
 * @engine:	engine associated with this request
 */
struct mv_cesa_req {
	enum mv_cesa_req_type type;
	struct mv_cesa_engine *engine;
};

/**
 * struct mv_cesa_ablkcipher_std_req - cipher standard request
 * @base:	base information
 * @op:		operation context
 * @offset:	current operation offset
 * @size:	size of the crypto operation
 */
struct mv_cesa_ablkcipher_std_req {
	struct mv_cesa_req base;
	struct mv_cesa_op_ctx op;
	unsigned int offset;
	unsigned int size;
	bool skip_ctx;
};

/**
 * struct mv_cesa_ablkcipher_req - cipher request
 * @req:	type specific request information
 * @src_nents:	number of entries in the src sg list
 * @dst_nents:	number of entries in the dest sg list
 */
struct mv_cesa_ablkcipher_req {
	union {
		struct mv_cesa_req base;
		struct mv_cesa_ablkcipher_std_req std;
	} req;
	int src_nents;
	int dst_nents;
};

/**
 * struct mv_cesa_ahash_std_req - standard hash request
 * @base:	base information
 * @offset:	current operation offset
 */
struct mv_cesa_ahash_std_req {
	struct mv_cesa_req base;
	unsigned int offset;
};

/**
 * struct mv_cesa_ahash_req - hash request
 * @req:		type specific request information
 * @cache:		cache buffer
 * @cache_ptr:		write pointer in the cache buffer
 * @len:		hash total length
 * @src_nents:		number of entries in the scatterlist
 * @last_req:		define whether the current operation is the last one
 *			or not
 * @state:		hash state
 */
struct mv_cesa_ahash_req {
	union {
		struct mv_cesa_req base;
		struct mv_cesa_ahash_std_req std;
	} req;
	struct mv_cesa_op_ctx op_tmpl;
	u8 *cache;
	unsigned int cache_ptr;
	u64 len;
	int src_nents;
	bool last_req;
	__be32 state[8];
};

/* CESA functions */

extern struct mv_cesa_dev *cesa_dev;

static inline void mv_cesa_update_op_cfg(struct mv_cesa_op_ctx *op,
					 u32 cfg, u32 mask)
{
	op->desc.config &= cpu_to_le32(~mask);
	op->desc.config |= cpu_to_le32(cfg);
}

static inline u32 mv_cesa_get_op_cfg(struct mv_cesa_op_ctx *op)
{
	return le32_to_cpu(op->desc.config);
}

static inline void mv_cesa_set_op_cfg(struct mv_cesa_op_ctx *op, u32 cfg)
{
	op->desc.config = cpu_to_le32(cfg);
}

static inline void mv_cesa_adjust_op(struct mv_cesa_engine *engine,
				     struct mv_cesa_op_ctx *op)
{
	u32 offset = engine->sram_dma & CESA_SA_SRAM_MSK;

	op->desc.enc_p = CESA_SA_DESC_CRYPT_DATA(offset);
	op->desc.enc_key_p = CESA_SA_DESC_CRYPT_KEY(offset);
	op->desc.enc_iv = CESA_SA_DESC_CRYPT_IV(offset);
	op->desc.mac_src_p &= ~CESA_SA_DESC_MAC_DATA_MSK;
	op->desc.mac_src_p |= CESA_SA_DESC_MAC_DATA(offset);
	op->desc.mac_digest &= ~CESA_SA_DESC_MAC_DIGEST_MSK;
	op->desc.mac_digest |= CESA_SA_DESC_MAC_DIGEST(offset);
	op->desc.mac_iv = CESA_SA_DESC_MAC_IV(offset);
}

static inline void mv_cesa_set_crypt_op_len(struct mv_cesa_op_ctx *op, int len)
{
	op->desc.enc_len = cpu_to_le32(len);
}

static inline void mv_cesa_set_mac_op_total_len(struct mv_cesa_op_ctx *op,
						int len)
{
	op->desc.mac_src_p &= ~CESA_SA_DESC_MAC_TOTAL_LEN_MSK;
	op->desc.mac_src_p |= CESA_SA_DESC_MAC_TOTAL_LEN(len);
}

static inline void mv_cesa_set_mac_op_frag_len(struct mv_cesa_op_ctx *op,
					       int len)
{
	op->desc.mac_digest &= ~CESA_SA_DESC_MAC_FRAG_LEN_MSK;
	op->desc.mac_digest |= CESA_SA_DESC_MAC_FRAG_LEN(len);
}

static inline void mv_cesa_set_int_mask(struct mv_cesa_engine *engine,
					u32 int_mask)
{
	if (int_mask == engine->int_mask)
		return;

	writel(int_mask, engine->regs + CESA_SA_INT_MSK);
	engine->int_mask = int_mask;
}

static inline u32 mv_cesa_get_int_mask(struct mv_cesa_engine *engine)
{
	return engine->int_mask;
}

int mv_cesa_queue_req(struct crypto_async_request *req);

/* Algorithm definitions */

extern struct ahash_alg mv_sha1_alg;
extern struct ahash_alg mv_ahmac_sha1_alg;

extern struct crypto_alg mv_cesa_ecb_aes_alg;
extern struct crypto_alg mv_cesa_cbc_aes_alg;

#endif /* __MARVELL_CESA_H__ */
