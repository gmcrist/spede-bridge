/*    include/spede/machine/i8237.h
 *	@(#)i8237.h	1.1   06/26/99
 *	Imported from FreeBSD version 2.6 (bwitt, June 1999)
 */

/*
 * Intel 8237 DMA Controller
 *
 *	$Id: i8237.h,v 1.6 1997/02/22 09:38:02 peter Exp $
 */

#define	DMA37MD_SINGLE	0x40	/* single pass mode */
#define	DMA37MD_CASCADE	0xc0	/* cascade mode */
#define	DMA37MD_AUTO	0x50	/* autoinitialise single pass mode */
#define	DMA37MD_WRITE	0x04	/* read the device, write memory operation */
#define	DMA37MD_READ	0x08	/* write the device, read memory operation */

