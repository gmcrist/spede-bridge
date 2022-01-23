/*   include/spede/sys/mman.h
 *	@(#)mman.h	1.1   01/26/01
 *	Provides interface to mmap()
 */

#ifndef _SPEDE_SYS_MMAN_H
#define _SPEDE_SYS_MMAN_H

#include <spede/sys/types.h>
#include <spede/sys/bits.h>		/* For BIT() macro */

/*
 * Protections are chosen from these bits, or-ed together.
 * Note - not all implementations literally provide all possible
 * combinations.  PROT_WRITE is often implemented as (PROT_READ |
 * PROT_WRITE) and (PROT_EXECUTE as PROT_READ | PROT_EXECUTE).
 * However, no implementation will permit a write to succeed
 * where PROT_WRITE has not been set.  Also, no implementation will
 * allow any access to succeed where prot is specified as PROT_NONE.
 */
#define	PROT_READ	BIT(0)		/* pages can be read */
#define	PROT_WRITE	BIT(1)		/* pages can be written */
#define	PROT_EXEC	BIT(2)		/* pages can be executed */
#define	PROT_USER	BIT(3)		/* pages are user accessable */

#define	PROT_NONE	0x0		/* pages cannot be accessed */

/* sharing types:  must choose either SHARED or PRIVATE */
#define	MAP_SHARED	1		/* share changes */
#define	MAP_PRIVATE	2		/* changes are private */
#define	MAP_TYPE	0xf		/* mask for share type */

/* other flags to mmap() (or-ed in to MAP_SHARED or MAP_PRIVATE) */
#define	MAP_FIXED	BIT(4)		/* user assigns address */
#define	MAP_NORESERVE	BIT(5)		/* don't reserve needed swap area */

/* these flags are used by memcntl() */
#define	PROC_TEXT	(PROT_EXEC | PROT_READ)
#define	PROC_DATA	(PROT_READ | PROT_WRITE | PROT_EXEC)
#define	SHARED		0x10
#define	PRIVATE		0x20
#define	VALID_ATTR  (PROT_READ|PROT_WRITE|PROT_EXEC|SHARED|PRIVATE)

/* -------------------------------------------------------------- */

extern void *	mmap(void *, size_t, int, int, int UNUSED, off_t);
extern int 	munmap(caddr_t, size_t);

extern char *	_spede_alloc_frame(void);

/* mmap() failure value */
#define	MAP_FAILED	((void *) -1)

/*  To map physical memory, ala /dev/kmem: */
#define MMAP_FD_DEV_KMEM 	0


extern char *	_topPhysicalMemory;	/* How far we'll up frames are alloc'ed */
extern BOOL	_mmap_report;		/* TRUE displays diagnostic megs */

#endif
