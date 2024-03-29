/*   spede/machine/endian.h	Macros for byte-endian issues.
 *	@(#)endian.h	1.4   03/01/00
 */
/*
 * Copyright (c) 1987, 1991 Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	from: --- endian.h	7.8 (Berkeley) 4/3/91
 *	-Id: endian.h,v 1.16 1997/08/31 22:43:46 bde Exp -
 */

#ifndef _SPEDE_MACHINE_ENDIAN_H_
#define	_SPEDE_MACHINE_ENDIAN_H_

#ifndef ASSEMBLER
#include <spede/sys/cdefs.h>
#endif


/*
 * Definitions for byte order, according to byte significance from low
 * address to high.
 */
#define	LITTLE_ENDIAN	1234	/* LSB first: i386, vax */
#define	BIG_ENDIAN	4321	/* MSB first: 68000, ibm, net */
#define	PDP_ENDIAN	3412	/* LSB first in word, MSW first in long */


/* vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv */


/*  Define the Intel i386 family: */
#define	BYTE_ORDER	LITTLE_ENDIAN

/*
 * Define the order of 32-bit words in 64-bit words.
 */
#define	_QUAD_HIGHWORD 1
#define	_QUAD_LOWWORD 0


/* ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ */

#ifndef ASSEMBLER

/**
 *	Basic functions for changing between network byte-ordered and
 *	host byte-ordered integers.  The argument is not alerted.  On
 *	a big-endian CPU, these functions are do-nothing macros.  But
 *	for Intel, work is required, though they might be inline 
 *	assembler routines.  This happens when using the GNU compiler!
 */
__BEGIN_DECLS

unsigned long	htonl __P((unsigned long));
unsigned short	htons __P((unsigned short));
unsigned long	ntohl __P((unsigned long));
unsigned short	ntohs __P((unsigned short));

__END_DECLS


#define __word_swap_long(x) \
__extension__ ({ register unsigned long __X = (x); \
   __asm ("rorl $16, %1" \
	: "=r" (__X) \
	: "0" (__X)); \
   __X; })

#define __byte_swap_long(x) \
__extension__ ({ register unsigned long __X = (x); \
   __asm ("xchgb %h1, %b1\n\trorl $16, %1\n\txchgb %h1, %b1" \
	: "=q" (__X) \
	: "0" (__X)); \
   __X; })

/*  Exchange high byte and low byte of 16-bit integer. */
#define __byte_swap_word(x) \
__extension__ ({ register unsigned short __X = (x); \
   __asm ("xchgb %h1, %b1" \
	: "=q" (__X) \
	: "0" (__X)); \
   __X; })


/*
 *  Macros for network/external number representation conversion.
 *  Intel requires the byte-swapping.
 */
#ifdef __GNUC__
#define	ntohl	__byte_swap_long
#define	ntohs	__byte_swap_word
#define	htonl	__byte_swap_long
#define	htons	__byte_swap_word

#else

/* yeah, ugly as shit */
#define ntohs(n) ( (((n) & 0xFF00) >> 8) | (((n) & 0x00FF) << 8) )
#define htons(n) ( (((n) & 0xFF00) >> 8) | (((n) & 0x00FF) << 8) )
#define ntohl(n) ( (((n) & 0xFF000000) >> 24) | (((n) & 0x00FF0000) >> 8) | (((
n) & 0x0000FF00) << 8) | (((n) & 0x000000FF) << 24) )
#define htonl(n) ( (((n) & 0xFF000000) >> 24) | (((n) & 0x00FF0000) >> 8) | (((
n) & 0x0000FF00) << 8) | (((n) & 0x000000FF) << 24) )

#endif


/**
 *	These macros (names in all upper-case), cast the value to
 *	ulong/ushort, then perform the coversion in-place.
 */
#define	NTOHL(x)	((x) = ntohl((unsigned long)(x)))
#define	NTOHS(x)	((x) = ntohs((unsigned short)(x)))
#define	HTONL(x)	((x) = htonl((unsigned long)(x)))
#define	HTONS(x)	((x) = htons((unsigned short)(x)))

#endif	/* ifndef ASSEMBLER */


#endif /* !_SPEDE_MACHINE_ENDIAN_H_ */

