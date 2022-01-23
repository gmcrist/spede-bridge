/*   spede/util.h   Misc util functions.        bwitt, May 1999
 *   %W%   %G%
 */
/*
 *  For ASM() macro, #include <spede/flames.h>
 *
 *	Includes a not-really-standard functions.  It comes from
 *	the BSD world, which define it in <strings.h>.  Not in
 *	<string.h> to keep it pure.
 *		ffs - find least significant non-zero bit.
 *
 *	#include <spede/machine/trap.h>	 -- For "struct trap_frame".
 *  A reduced version of "trap.h" is handed out to the class.  However
 *	this file declares a trap_dump() routine.  Change: if "trap.h"
 *	has already been included, then trap_dump() is declared.
 *	Otherwise it is not.	(bwitt, March 2000)
 *
 *	dec2000 	Moved bzero() to <spede/string.h>
 */

#ifndef __SPEDE_UTIL_H
#define __SPEDE_UTIL_H

#include <spede/sys/cdefs.h>
#include <spede/string.h>
#include <spede/flames.h>	/* For ASM() macro */

__BEGIN_DECLS

#define  A_IMPLIES_B(a,b)	(!(a) || (b))

/* ----------------------------------------------------------------- */


/**
 *   First, a BSD find-first-bit-set. 0 if none, else N for bit N-1 
 *   set, when searching bit 0 to bit 31.
 *   GCC provides this as a built-in function!  For i386, it generates:
 *	__asm __volatile("testl %0,%0; je 1f; bsfl %0,%0; incl %0; 1:"
 *                        : "=r" (result) : "0" (bits));
 */
#if ! defined(__GNUC__)
extern int	ffs __P(( int bits ));
#endif


/**
 *	After exit() has processed, jump to the monitor that is
 *	hosting the operating system.  _cleanup() called by exit()
 *	and never returns.
 *
 *	@see	exit()
 *	@return NEVER.
 */
extern  void	 _cleanup __P(( void ));


/**
 *	Compute the CCITT 16-bit CRC polynomial upon some data.
 *	(These people now called ITU.)
 *
 *	@param buff (in) pointer to your data.
 *	@param size (in) Byte size of data buffer.
 *	@return CRC-CCITT-16 value.
 */
extern unsigned  crc_ccitt16(const unsigned char * buff, int size);


/**
 *	Print out "count" bytes from pointer "data_buf", displaying
 *	addresses starting at "addr".  Instead of hardwiring in a call
 *	to printf(), a callback function is used.  A newline is included
 *	with each line passed to "outfunc".
 *
 *	@param data_buf (in) actual data source.
 *	@param count (int) how many bytes to dump.
 *	@param addr (in) where user expects data to come from.
 *	@param outfunc (in) callback for each line to display.
 */
extern void	hexdump(const char *data_buf, long count, long addr,
			void (*outfunc)(const char *));

#ifdef _SPEDE_MACHINE_TRAP_H_

/**
 *	Print out a trap state "frame".  Depending on whether the code
 *	segment register has CPL == 0 or not, you get system or user 
 *	mode information.
 *	Prints using printf().
 */
extern void	trap_dump(const struct trap_frame * t);

#endif


/**
 *	General routine to immediately exit from program printing
 *	a message along the way.
 *	NOTE: Segments 0x20 and 0x28 must be original 16-bit segments.
 */
extern void	panic(const char * str);


/**
 *	A low-memory heap allocator.  Allocates from memory below
 *	the 1 meg boundary.  Actually below 0x0A0000, below video memory.
 *	Works like brk(), but has specific memory.  Good for DMA
 *	and things needed before malloc() has been initialized.
 *
 *	@param  bytes (in) bytes to allocated, rounded to 256 boundary.
 *	@return  base of memory.
 */
#define  _LOMEM_STARTING	((char *) 0x068000L)
extern char *	_lomem_heap_alloc(unsigned bytes);


/****  From target/fpu_control.S  *****/

/**
 *	Disable FPU access. If "state" is non-NULL, the current
 *	FPU state is stored.  The FPU is disabled by setting the
 *	EM bit in CR0.
 *
 *	@see fpu_enable()
 *	@param state (out) optional 108 byte buffer holding FPU state.
 */
extern void	fpu_disable(char * state[108]);


/**
 *	Enable FPU usage by clearing the EM bit in CR0.  If "state"
 *	is non-NULL, the FPU state is restored.
 *
 *	@see fpu_disable()
 *	@param state (in) optional 108 byte buffer holding FPU state.
 */
extern void	fpu_enable(const char * state[108]);


/**
 *	Clear the FPU state to reset and cleared.
 *
 *	@see fpu_enable()
 */
extern void	fpu_init(void);


/**
 *	Check to see if a 80387 -compatible FPU is available.  The Intel
 *	486 and later processors generally have a built-in FPU unit.
 *	Uses <CODE>FNINIT</CODE> and <CODE>FSTSW</CODE> to detect FPU.
 *
 *	@return 0 if FPU not detected, or 1 if FPU available.
 */
extern int 	fpu_detected(void);


/**
 *	Mask out pending interrupts from FPU by clearing bits in the 
 *	control word and status word.
 */
extern void	fpu_maskexcep(void);




/****  From target/io.S  *****/

extern void	spin_lock(char * lock);


__END_DECLS

#endif
