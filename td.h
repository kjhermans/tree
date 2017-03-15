/*
** Copyright 2015 K.J. Hermans (kees@pink-frog.com)
** This code is part of simpledbm, an API to a dbm on a finite resource.
** License: BSD
*/

#ifndef _TD_H_
#define _TD_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _DEBUG
#include <stdio.h>
#endif
#include <string.h>

#include "td_types.h"

/**
 * Flags for td_init_* like functions.
 * \def TDFLG_MUSTEXIST
 * Indicates that, on opening, the resource must be encountered in an
 * initialized state.
 * \def TDFLG_DUPLKEYS
 * Indicates that you allow multiple values be stored undef the same key.
 * This implies a (potentially) random result on a normal td_get(), and
 * full retrieval only using a cursor.  This flag can also be omitted on
 * initialization, and instead be given during an individual td_put()
 * function call.  Note: When both TDFLG_DUPLKEYS and TDFLG_NOOVERWRITE
 * are given, TDFLG_DUPLKEYS 'wins' and a duplicate storage is made.
 * \def TDFLG_EXTEND
 * Indicates that extension of the resource should be possible.
 * Requires that the 'realloc' member of the td structure is filled with
 * a valid function pointer.
 * \def TDFLG_ALLOCTDT
 * Indicates that tdt_t pointers passed to the API that are elegible for
 * filling in, and that are set to { NULL, 0 }, may be allocated using the
 * memory-allocation function in the td_t structure.
 * This flag can also be omitted on initialization, and instead be given
 * during an individual call to td_get(), td_del(), td_pop(), tdc_nxt(),
 * tdc_prv() and tdc_get().
 * Requires that the 'realloc' member of the td structure is filled with
 * a valid function pointer.
 * \def TDFLG_NOOVERWRITE
 * Indicates that, during a put operation, existing keys may
 * not be overwritten.  This flag can also be omitted on initialization,
 * and instead be given during an individual td_put() function call.
 * Note: When both TDFLG_DUPLKEYS and TDFLG_NOOVERWRITE are given,
 * DFLG_DUPLKEYS 'wins' and a duplicate storage is made.
 * \def TDFLG_WIPEDELETED
 * Indicates that any chunk must be overwritten with zero bytes when
 * discarded.
 * \def TDFLG_DELETEALL
 * The key is interpreted as partially, but exactly, matching, and every
 * instance of it is deleted. Supplied value pointers will be ignored.
 */
#define TDFLG_MUSTEXIST   (1<<0)
#define TDFLG_DUPLKEYS    (1<<1)
#define TDFLG_EXTEND      (1<<2)
#define TDFLG_ALLOCTDT    (1<<3)
#define TDFLG_NOOVERWRITE (1<<4)
#define TDFLG_WIPEDELETED (1<<5)
#define TDFLG_DELETEALL   (1<<6)
#define TDFLG_CHECKSUM    (1<<7)
#define TDFLG_SPARSE      (1<<8)

/*
 * Initializes a btree structure inside a fixed memory buffer.
 * \param td Non-NULL pointer to an uninitialized btree structure.
 * \param flags Bits from TDFLG_* flags.
 * \param mem Pointer to memory buffer to contain the btree.
 * \param size Size of the buffer.
 * \return Zero on success, or any of the TDERR_* values on error.
 */
int td_init_mem(td_t* td, unsigned flags, void* mem, unsigned size);

/*
 * Initializes a btree structure using a user-provided file descriptor.
 * \param td Non-NULL pointer to an uninitialized btree structure.
 * \param flags Bits from TDFLG_* flags.
 * \param fd Valid filedescriptor.
 * \return Zero on success, or any of the TDERR_* values on error.
 */
int td_init_fd(td_t* td, unsigned flags, int fd);

/*
 * Initializes a btree structure inside dynamic memory.
 * \param td Non-NULL pointer to an uninitialized btree structure.
 * \param flags Bits from TDFLG_* flags.
 * \return Zero on success, or any of the TDERR_* values on error.
 */
int td_init_malloc(td_t* td, unsigned flags);
int td_init_chunk(td_t* td, unsigned flags, int fd, unsigned off, unsigned siz);
int td_init_mmap(td_t* td, unsigned flags, int fd, unsigned off, unsigned siz);
int td_open(td_t*, char*, unsigned tdflags, unsigned openflags, unsigned mode);

/*
 * Closes the btree, wherever it is stored.
 * \param td Non-NULL pointer to initialized btree structure.
 */
void td_exit(td_t* td);

/* 
 * Converts a char* string to a key.
 * \param tdt Pointer to an uninitialized tdt. When NULL, a valid
 * tdt will be returned.
 * \param string Zero terminated string.
 * \returns A valid tdt.
 */
tdt_t tdt_string(tdt_t* tdt, char* string);

/*
 * Creates a valid tdt.
 * \param tdt Pointer to an uninitialized tdt. When NULL, a valid
 * tdt will be returned.
 * \param mem Pointer to a memory buffer, which will be read or written
 * by various functions.
 * \param size Size of the memory buffer.
 * \returns A valid tdt.
 */
tdt_t tdt_init(tdt_t* tdt, void* mem, unsigned size);

/*
 * Get a value from the btree by providing a key.
 * \param td Non-NULL pointer to initialized btree structure.
 * \param key Non-NULL pointer to initialized tdt_t.
 * \param value Pointer to initialized tdt_t. May be NULL, in which case
 * the return value of this function indicates existence of a key only.
 * \param flags Bits from TDFLG_* flags.
 * \returns Zero on success (key is found), TDERR_NOTFOUND when the key
 * hasn't been found, or any other error.
 */
int td_get(td_t* td, const tdt_t* key, tdt_t* value, unsigned flags);

/*
 * Put a value into the btree by providing a key and a value.
 * \param td Non-NULL pointer to initialized btree structure.
 * \param key Non-NULL pointer to initialized tdt_t.
 * \param value Non-NULL pointer to initialized tdt_t.
 * \param flags Bits from TDFLG_* flags.
 * \return Zero on success, or any of the TDERR_* values on error.
 */
int td_put(td_t* td, const tdt_t* key, const tdt_t* value, unsigned flags);

/*
* Variant of td_put(). Puts the same value into the btree under
* multiple keys. The elipsis is a list of tdt_t pointers representing keys.
*/
int td_put_keys
  (td_t* td, const tdt_t* value, unsigned flags, unsigned nkeys, ...);

/*
 * Delete a value from the btree by providing a key.
 * \param td Non-NULL pointer to initialized btree structure.
 * \param key Non-NULL pointer to initialized tdt_t.
 * \param value Pointer to initialized tdt_t. May be non-NULL, in which case
 * the deleted value is returned.
 * \param flags Bits from TDFLG_* flags.
 * \returns Zero on success (key is found), TDERR_NOTFOUND when the key
 * hasn't been found, or any other error.
 */
int td_del(td_t* td, const tdt_t* key, tdt_t* value, unsigned flags);

/*
 * Pop a value from the btree.
 * \param td Non-NULL pointer to initialized btree structure.
 * \param key Pointer to initialized tdt_t. May be NULL, in which case
 * the return value of this function indicates existence of a key only.
 * \param value Pointer to initialized tdt_t. May be NULL, in which case
 * the return value of this function indicates existence of a value only.
 * \param flags Bits from TDFLG_* flags.
 * \returns Zero on success (key is found), TDERR_NOTFOUND at EOF, or
 * any other error.
 */
int td_pop(td_t* td, tdt_t* key, tdt_t* value, unsigned flags);

typedef int(*rmwfnc_t)(td_t*,const tdt_t* key, tdt_t* value, void* arg);

int td_rmw
  (
    td_t* td,
    const tdt_t* key,
    tdt_t* value,
    unsigned flags,
    rmwfnc_t callback,
    void* arg
  );

/*
 * Cursor functionality.
 * Mutations to the dbm during cursor iteration invalidate the cursor; any
 * peration on a cursor will yield the TDERR_INVAL error immediately when
 * this happens.
 */

/**
 * \def TDCFLG_PARTIAL
 * Allow for partial matches, that is, when the key given is smaller than,
 * but up its size equal to the key found, it's considered a match.
 * \def TDCFLG_EXACT
 * Matches of the cursor movement must be exact, or fail with TDERR_NOTFOUND.
 * Mind that partial matches _are_ considered exact matches when
 * TDCFLG_PARTIAL has been set.
 */
#define TDCFLG_PARTIAL  (1<<9)
#define TDCFLG_EXACT    (1<<10)

/*
 * Initializes a cursor.
 * \param td Non-NULL pointer to initialized btree structure.
 * \param tdc Non-NULL pointer to uninitialized cursor structure.
 * \return Zero on success, or any of the TDERR_* values on error.
 */
int tdc_init(td_t* td, tdc_t* tdc);

int tdc_first(tdc_t* tdc);

/*
 * Moves an initialized cursor to or near a key.
 * \param tdc Non-NULL pointer to an initialized cursor structure.
 * \return Zero on success, or any of the TDERR_* values on error.
 */
int tdc_mov(tdc_t* tdc, const tdt_t* key, unsigned flags);

/*
 * Moves the cursor to the next position.
 * \param tdc Non-NULL pointer to an initialized cursor structure.
 * \return Zero on success, or any of the TDERR_* values on error.
 */
int tdc_nxt(tdc_t* tdc, tdt_t* key, tdt_t* value, unsigned flags);

/*
 * Moves the cursor to the previous position.
 * \param tdc Non-NULL pointer to an initialized cursor structure.
 * \return Zero on success, or any of the TDERR_* values on error.
 */
int tdc_prv(tdc_t* tdc, tdt_t* key, tdt_t* value, unsigned flags);

/*
 * Gets key and value at the current position of the cursor.
 * \param tdc Non-NULL pointer to an initialized cursor structure.
 * \return Zero on success, or any of the TDERR_* values on error.
 */
int tdc_get(tdc_t* tdc, tdt_t* key, tdt_t* value, unsigned flags);

/*
 * Replaces the value at the current position of the cursor.
 * \param tdc Non-NULL pointer to an initialized cursor structure.
 * \return Zero on success, or any of the TDERR_* values on error.
 */
int tdc_rpl(tdc_t* tdc, const tdt_t* value, unsigned flags);

/*
 * Debugging.  Will push a description of the current structure to stderr.
 * \return Zero on success, or any of the TDERR_* values on error.
 */
int td_debug(td_t* td);

/**
 * Verifies the entire dbm. If it returns a fatal error, the dbm
 * should not be used.
 */
extern
int td_verify
  (td_t* td, int fix);

/**
 * Wipes the entire db.
 */
extern
int td_wipe
  (td_t* td);

/*
 * Errors.
 * In general: > 0 is recoverable; < 0 is not; 0 is success throughout the API
 */

/**
 * \def TDERR_SPACE
 * is returned when the dbm is not extendable, or cannot
 * be extended, and the requested storage size cannot be had.
 * \def TDERR_DUP
 * is returned when one puts a value, the key is already
 * present and TDFLG_NOOVERWRITE is set.
 * \def TDERR_INVAL
 * is returned when a cursor has become stale.
 * \def TDERR_NOTFOUND
 * is returned when a desired key is not found.
 * \def TDERR_BOUNDS
 * is returned when a read or write operation tried
 * to exceed the dbm's resource's bounds.
 * \def TDERR_LOCK
 * is returned when obtaining or releasing a lock failed.
 * \def TDERR_IO
 * is returned when an I/O operation failed.
 * \def TDERR_INIT
 * is returned when initializing the dbm failed.
 * \def TDERR_NOMEM
 * is returned when obtaining memory failed.
 */
#define TDERR_CHECKSUM 5
#define TDERR_SPACE    4
#define TDERR_DUP      3
#define TDERR_INVAL    2
#define TDERR_NOTFOUND 1
#define TDERR_BOUNDS  -1
#define TDERR_LOCK    -2
#define TDERR_IO      -3
#define TDERR_INIT    -4
#define TDERR_NOMEM   -5
#define TDERR_STRUCT  -6

#define TDERR_IS_FATAL(__r) ((__r)<0)

extern int td_compare
  (td_t* td, const tdt_t* key1, const tdt_t* key2, int partial, void* arg);

#ifdef __cplusplus
}
#endif

#endif
