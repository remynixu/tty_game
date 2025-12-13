#include "block.h"

/*
 * IMPLEMENTATION
 *
 * A block is a memory format used by this library for allocating and freeing
 * memory for the user. It has a header and a payload.
 *
 * The header has:
 * - Status             - Could be "free" or "given", free if available for
 *                        allocation, given if used by user. Also located at the
 *                        start of the block.
 * - Payload size       - The size of the payload in bytes, might be inaccurate
 *                        due to alignments considered when making a block.
 * - Next block pointer - The pointer to the next first byte of the next block,
 *                        needed because chaining blocks together like a linked
 *                        list is easier to track, but note that the user can
 *                        change this purpose.
 * The payload has:
 * - Memory             - A counted amount of raw bytes, aligned by the value of
 *                        size_t.
 */

/*
 * Abbreviated terms:
 * alloc| allocate
 * pos	| position
 * str	| string
 * buf	| buffer
 * fmt	| format
 * blk	| block
 * sz	| size
 * c	| char
 * b	| byte
 * t	| type
 */



/*
 * Header managers!
 */

enum header_status{
	FREE = 0x1,
	GIVEN
};

struct header{
	enum header_status status;
	size_t magic; /* >:) */
	size_t payload_sz;
	struct header *next;
};

#if BIT_SYSTEM == 16
#define MAGIC_VALUE	"rn"
#elif BIT_SYSTEM == 32
#define MAGIC_VALUE	"remy"
#elif BIT_SYSTEM == 64
#define MAGIC_VALUE	"remynixu"
#endif /* MAGIC_VALUE */

static struct header mkheader(enum header_status status,
		size_t payload_sz, struct header *next){
	struct header header;
	header.status = status;
	header.magic = MAGIC_VALUE;
	header.payload_sz = payload_sz;
	header.next = next;
	return header;
}

static struct header *_to_header_ptr(void *blk){
	return blk;
}



/*
 * Helper functions for getting info about a block.
 */

static size_t payload_sz_to_sz(size_t payload_sz){
	return payload_sz + sizeof(struct header);
}

static size_t _payload_sz(void *blk){
	return _to_header_ptr(blk)->payload_sz;
}

static size_t _sz(void *blk){
	return payload_sz_to_sz(_payload_sz(blk));
}



/*
 * API Functions.
 */

static int _payload_sz_align(size_t payload_sz){
	return payload_sz + (payload_sz % sizeof(size_t));
}

void *blkfmt(void *buf, size_t sz){
	struct header *header_pos;
	size_t payload_sz;
	size_t aligned_payload_sz;
	if(sz < sizeof(struct header))
		return NULL;
	payload_sz = sz - sizeof(struct header);
	header_pos = _to_header_ptr(buf);
	*header_pos = mkheader(FREE, payload_sz, NULL);
	return buf;
}

void *blksplit(void *blk, size_t payload_sz, enum blksplit_mode how){
	struct header *blk1_header = _to_header_ptr(blk);
	struct header *blk2_header = NULL;
	size_t blk1_payload_sz = 0;
	enum header_status status = 0;
	struct header *next = NULL;
	if(_to_header_ptr(blk)->status & GIVEN)
		return NULL;
	if(blk1_header->payload_sz <= payload_sz)
		return NULL;
	blk1_payload_sz = blk1_header->payload_sz - payload_sz;
	blk1_payload_sz = _payload_sz_align(blk1_payload_sz);
	blk2_header = (char *)blk1_header + payload_sz_to_sz(blk1_payload_sz);
	status = FREE;
	if(how & GIVEBLK2)
		status = GIVEN;
	next = NULL;
	if(how & KEEPLINK)
		next = blk1_header->next;
	if(how & LINK2TO1)
		next = blk1_header;
	*blk2_header = mkheader(status, payload_sz, next);
	status = FREE;
	if(how & GIVEBLK1)
		status = GIVEN;
	next = NULL;
	if(how & KEEPLINK)
		next = blk2_header->next;
	if(how & LINK1TO2)
		next = blk2_header;
	*blk1_header = mkheader(status, blk1_payload_sz, next);
	return (void *)blk2_header;
}

int blkcheck(void *blk){
	struct header *header = _to_header_ptr(blk);
	return header->magic == MAGIC_VALUE;
}
