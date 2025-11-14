#include "block.h"

/*
 * A block consists of:
 * - header
 *   - payload size
 *   - flags
 * - payload
 */

struct _hdr{
	blk_size_t pyld_sz;
	blk_size_t fl;
	struct _hdr *next;
};

/*
 * The header is consistent, hence why it's a struct.
 *
 * The payload is found after the header, it's size is varied because we don't
 * know how many bytes the user will request.
 *
 * We also need to track the amount of blocks, and the list's size is varied,
 * which is why we will use a linked list.
 */

#define _pyld_pos(blk)	((struct _hdr *)(blk) + 1)

static blk_size_t _sz_to_pyldsz(blk_size_t sz){
	return sz - sizeof(struct _hdr);
}

static blk_size_t _pyldsz_to_sz(blk_size_t pyld_sz){
	return pyld_sz + sizeof(struct _hdr);
}

#define FL_FREE		(1 << 0)
#define FL_GIVEN	(1 << 1)

static void *ldhdr(void *buf, struct _hdr *hint){
	struct _hdr *hdr_pos = buf;
	*hdr_pos = *hint;
	return hdr_pos;
}

void *blkfmt(void *buf, blk_size_t sz){
	struct _hdr hint = {
		0,
		FL_FREE,
		NULL
	};
	hint.pyld_sz = _sz_to_pyldsz(sz);
	return ldhdr(buf, &hint);
}

/*
 * To allocate from a block, it'll be split into two - one for the requested
 * memory, and another remainder for other allocations.
 */

static struct _hdr *_tohdr(void *blk){
	return blk;
}

#define _pyldsz(blk)	_tohdr(blk)->pyld_sz
#define _sz(blk)	_pyldsz_to_sz(_pyldsz(blk))
#define _next_pos(blk)	((char *)(blk) + _sz(blk))

static struct _hdr sethdr(blk_size_t pyld_sz, blk_size_t fl, struct _hdr *next){
	struct _hdr hdr;
	hdr.pyld_sz = pyld_sz;
	hdr.fl = fl;
	hdr.next = next;
	return hdr;
}

/*
 * Expected that 'sz' is less than _sz('blk').
 */

static void *_split(void **blk, blk_size_t sz, blk_size_t fl1, blk_size_t fl2){
	struct _hdr hint1 = sethdr(sz, fl1, NULL);
	struct _hdr hint2 = sethdr(_sz(blk) - sz, fl2, NULL);
	void *blk1 = *blk;
	void *blk2;
	blk1 = ldhdr(*blk, &hint1);
	*blk = _next_pos(*blk);
	blk2 = ldhdr(*blk, &hint2);
	_tohdr(blk1)->next = blk2; /* currently contemplating double pointers */
	return blk1;
}

/* We must also find a suitable block to split. */

static void *_find(struct _hdr *head, blk_size_t fl){
	struct _hdr *curr = head;
	for(; curr->next != NULL; curr = curr->next){
		if(curr->fl & fl)
			break;
	}
	return curr;
}

static void *__blkalloc(void *blk, blk_size_t pyld_sz){
	blk = _find(blk, FL_FREE);
	return _split(&blk, pyld_sz + sizeof(struct _hdr), FL_GIVEN, FL_FREE);
}

void *blkalloc(void *blk, blk_size_t sz){
	if(sz > _sz(blk))
		return NULL;
	return _pyld_pos(__blkalloc(blk, sz));
}

/*
 * To mitigate fragmentation, we merge some mergeable blocks.
 */

static void *_merge(void *blk1, void *blk2){
	return blkfmt(blk1, _sz(blk1) + _sz(blk2));
}

#define _merge_ok(blk)	(_tohdr(_next_pos(blk))->fl & FL_FREE)

static int defrag_once(struct _hdr *head){
	void *blk = _find(head, FL_FREE);
	int merge_cnt = 0;
	for(; blk; blk = _find(head, FL_FREE)){
		if(!_merge_ok(blk))
			continue;
		_merge(blk, _next_pos(blk));
		merge_cnt++;
	}
	return merge_cnt;
}

static void defrag(struct _hdr *head){
	while(defrag_once(head));
}

#define _hdr_pos(ptr)	((struct _hdr *)(ptr) - 1)

void blkfree(void *blk, void *ptr){
	void *blk1 = _hdr_pos(ptr);
	blkfmt(blk1, _sz(blk1));
}
