/*   spede/sys/bits.h
 *	@(#)bits.h	1.1   12/31/00
 *	Common defines for bit masks and tests.
 */

#ifndef _SPEDE_SYS_BITS_H
#define _SPEDE_SYS_BITS_H

/**
 *	Macros for bit test.  Use BIT() to create a mask bit.
 *	The "Q" prefix on the test is from LISP paradigm.
 *	For masking of a single bit, use QBIT_ON() or QBIT_OFF().
 */
#define  BIT(b)  (1L << (b))

#define  QBIT_ALL_ON(val,mask)  (((val) & (mask)) == (mask))
#define  QBIT_ANY_ON(val,mask)  (((val) & (mask)) != 0)
#define  QBIT_ALL_OFF(val,mask)  (((val) & (mask)) == 0)

#define  QBIT_ON(val,mask)	QBIT_ALL_ON(val,mask)
#define  QBIT_OFF(val,mask)	QBIT_ALL_OFF(val,mask)

#endif

