/*  spede/unistd.h	Misc functions, like UNIX's <unitstd.h>
 *	@(#)unistd.h	1.4 06/08/00
 */

#ifndef __SPEDE_UNISTD_H
#define __SPEDE_UNISTD_H

#include <spede/sys/cdefs.h>
#include <spede/sys/types.h>

__BEGIN_DECLS


/**
 *	Adds "delta" bytes to the "top of heap memory" break line.
 *	"delta" can be negative to lower the break line (very
 *	dangerous, though).  Initially, the break line is set just
 *	above the end of the data area (bss in C programs).  This is
 *	done by a call to brk() by the C startup code.
 *
 *	<P> The system variable _topHeapMemory is the max break value.
 *
 *	@param delta (in) bytes to change break by.
 *	@return  Prior break pointer, or (char *)-1 if an error.
 */
extern char *	sbrk __P(( int delta ));

extern int	brk( void * enddata );

/*  sbrk()'s HARD limit. */
extern char    *_topHeapMemory;

/*  Display the free nodes of malloc() -- for debugging.
 *	'flags' is unused right now.
 */
extern void	_malloc_walk_heap(int flags, void (*outfunc)(const char *));

/**
 *	Terminate the program.  Doesn't close files, doesn't call
 *	"atexit" handlers.  Calls GDBexit() and then FlamingExit().
 */
NEVER_RETURNING  _exit(int status);


/* ------------------------------------------------------------------ */

/**
 *	Two routines to control the DES encryption.
 *	<P> Warning: You cannot export code for DES from USA.
 *	For setkey() provides access to the hashing routine
 *	used by encrypt().
 *
 *	@param key (in) pointer to 64 bytes of only 1 or 0 values.
 */
extern void	setkey(const char * key);

/**
 *	The "edflag" controls whether block contains plaintext (0)
 *	or encoded bits (1).
 *
 *	@param block (inout) pointer to 64 with values of only 1 or 0.
 *	@param edflag (in) 0 then encode, 1 for decode.
 */
extern void	encrypt(char block[64], int edflag);

/**
 *	Take a string and encode using "salt". The first eight bytes
 *	of "key" is altered. And "salt" only the first two characters
 *	are used, which should be "[a-z]A-Z0-9./]" for a one of 4096
 *	variations in the hashing algorithm.
 *
 *	@param key (in) 8 bytes to encode.
 *	@param salt (in) 2 chars to perturb the algorithm.
 *	@return Pointer to 10 bytes, the first two are copied from "salt",
 *		the next 8 are encoded form of "key".
 */
extern char *	crypt(const char * key, const char * salt);


__END_DECLS

#endif
