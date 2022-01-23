/*   spede/machine/cpufunc.h
 *	@(#)cpufunc.h	1.1   08/02/99
 */

/**
 *	Special operations that affect the CPU directly.
 */


#ifndef _INCL_SPEDE_MACHINE_CPUFUNC_H
#define _INCL_SPEDE_MACHINE_CPUFUNC_H

#include <spede/sys/types.h>

/*  Read Time Stamp Counter.  Introduced by Intel in Pentium family. */
static __inline uint64
rdtsc(void)
{
        uint64 rv;

        __asm __volatile(".byte 0x0f, 0x31" : "=A" (rv));
        return (rv);
}


static __inline uint64
rdmsr(unsigned msr)
{
        uint64 rv;
	/*  ECX in, EDX:EAX out. */
        __asm __volatile(".byte 0x0f, 0x32" : "=A" (rv) : "c" (msr));
        return (rv);
}



#endif
