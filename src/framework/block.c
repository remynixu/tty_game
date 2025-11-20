#include "block.h"

/*
 * Standard function copies.
 */

void *blk_memcpy(void *dest, void *src, blk_size_t sz){
	char *__dest = dest;
	char *__src = src;
	blk_size_t i = 0;
	for(; i < sz; i++)
		__dest[i] = __src[i];
	return dest;
}

void *blk_memset(void *dest, char src, blk_size_t sz){
	char *__dest = dest;
	blk_size_t i = 0;
	for(; i < sz; i++)
		__dest[i] = src;
	return dest;
}

/*
 * A block consists of:
 * - header
 *   - payload size
 *   - flags
 * - payload
 */

void __no_effect(void){
	return;
}

/*
 * Errors for users.
 */

enum _err{
	_ERR_FAILURE = -1,
	_ERR_NOERROR,
	_ERR_BADARGS,
	_ERR_LACKMEM
}_err = _ERR_NOERROR;

static enum _err _geterr(void){
	return _err;
}

static void _seterr(enum _err err){
	_err = err;
}

int blkerr(void){
	return _geterr();
}

char *blk_strerror(void){
	static char errstr[4][16] = {
		"Unknown Failure",
		"No Block Errors",
		"Bad Instruction",
		"Short of Memory"
	};
	return errstr[_geterr() + 1];
}

/*
 * The header is consistent, hence why it's a struct.
 */

struct _hdr{
	blk_size_t fl;
	blk_size_t pyld_sz;
	struct _hdr *next;
};

/*
 * Flags are used for status checks.
 */

enum _flag{
	_FL_FREE = 1 << 0,
	_FL_GIVEN = 1 << 1,
	_FL_MAGIC = 0xA << 3
};

static char mkfl(enum _flag hint){
	return hint | _FL_MAGIC;
}

static struct _hdr mkhdr(blk_size_t pyld_sz, enum _flag fl, struct _hdr *next){
	struct _hdr hdr;
	hdr.fl = fl;
	hdr.pyld_sz = pyld_sz;
	hdr.next = next;
	return hdr;
}

static struct _hdr *_tohdr(void *blk){
	return blk;
}

static blk_size_t sizeof_hdr(void){
	return sizeof(struct _hdr);
}

/*
 * The payload is found after the header, it's size is varied because we don't
 * know how many bytes the user will request.
 */

static blk_size_t _pyld_sz(void *blk){
	return _tohdr(blk)->pyld_sz;
}

static blk_size_t _sz_to_pyld_sz(blk_size_t sz){
	return sz - sizeof_hdr();
}

#define _sztopsz(sz)	_sz_to_pyld_sz(sz)

static blk_size_t _pyld_sz_to_sz(blk_size_t pyld_sz){
	return pyld_sz + sizeof_hdr();
}

#define _psztosz(psz)	_pyld_sz_to_sz(psz)

static blk_size_t _sz(void *blk){
	return _psztosz(_pyld_sz(blk));
}

/* Needs to be supplied a pointer because of C90 standard :P */

#define for_each_blk(ptr)	for(; _tohdr(ptr); (ptr) = _tohdr(ptr)->next)

static blk_size_t _sz_all(void *blk){
	blk_size_t sz = 0;
	for_each_blk(blk)
		sz += _sz(blk);
	return sz;
}

/*
 * We also need to track the amount of blocks, and the list's size is varied,
 * which is why we will use a linked list.
 */

static void *_ldhdr(void *dest, struct _hdr *hdr){
	struct _hdr *__dest = dest;
	*__dest = *hdr;
	return __dest;
}

static int _sz_ok(blk_size_t sz){
	return sz > sizeof_hdr();
}

void *blkfmt(void *buf, blk_size_t sz){
	struct _hdr hdr = mkhdr(_sztopsz(sz), mkfl(_FL_FREE), NULL);
	if(!buf)
		goto err;
	if(!_sz_ok(sz))
		goto err;
	blk_memset(buf, 0, sz);
	_seterr(_ERR_NOERROR);
	return _ldhdr(buf, &hdr);
err:
	_seterr(_ERR_BADARGS);
	return NULL;
}

static void _print(char *str, int (*putchar_fn)(int)){
	for(; *str; str++)
		putchar_fn(*str);
}

static void __dump_byte(char c, int (*putchar_fn)(int)){
	int is_flag = (c & (char)(255 << 2)) == _FL_MAGIC;
	if(is_flag)
		_print("\001\033[31;40m", putchar_fn);
	dump_byte(c, putchar_fn);
	if(is_flag)
		_print("\033[0m\002", putchar_fn);
}

void dump_byte(char c, int (*putchar_fn)(int)){
	int i = (sizeof(c) * 8) - 1;
	int is_flag = (c & (char)(255 << 2)) == _FL_MAGIC;
	char bit_char;
	for(; i > -1; i--){
		bit_char = ((c & (1 << i)) && 1) + '0';
		putchar_fn(bit_char);
	}
	putchar_fn(' ');
}

static void _dump_byte_ln(char *bytes, int (*putchar_fn)(int), blk_size_t len){
	for(; len; len--, bytes++)
		__dump_byte(*bytes, putchar_fn);
}

void blkdump(void *blk, int (*putchar_fn)(int), blk_size_t ln_len){
	char *__blk = blk;
	blk_size_t i = 0;
	blk_size_t sz = _sz_all(blk);
	for(; i < sz; i += ln_len, __blk += ln_len){
		_dump_byte_ln(__blk, putchar_fn, ln_len);
		putchar_fn('\n');
	}
}

/*
 * To allocate from a block, it'll be split into two - one for the requested
 * memory, and another remainder for other allocations.
 */

static void *_next(void *blk){
	return (char *)blk + _sz(blk);
}

static void *__blkalloc(void *blk, blk_size_t pyld_sz){
	struct _hdr hint1;
	struct _hdr hint2;
	void *blk1;
	void *blk2;
	hint1 = mkhdr(_pyld_sz(blk) - _psztosz(pyld_sz), mkfl(_FL_FREE), NULL);
	hint2 = mkhdr(pyld_sz, mkfl(_FL_GIVEN), _tohdr(blk)->next);
	blk1 = _ldhdr(blk, &hint1);
	blk2 = _ldhdr(_next(blk1), &hint2);
	_tohdr(blk1)->next = blk2;
	return blk2;
}

/*
 * TODO:
 * - Segfault at miscalculated memory to be taken.
 */

void *blkalloc(void *blk, blk_size_t sz){
	if(!blk){
		_seterr(_ERR_BADARGS);
		goto err;
	}
	if(_psztosz(sz) > _sz(blk)){
		_seterr(_ERR_LACKMEM);
		goto err;
	}
	_seterr(_ERR_NOERROR);
	return __blkalloc(blk, sz);
err:
	return NULL;
}

/* We must also find a suitable block to split. */

/*
 * To mitigate fragmentation, we merge some mergeable blocks.
 */
