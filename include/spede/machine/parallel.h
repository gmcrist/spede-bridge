/*   include/spede/machine/parallel.h
 *	@(#)parallel.h	1.2   06/08/00
 */

/*  From VSTa  http://www.zendo.com/VSTa/
 *  Contributed by: Robert Mayer (robert@par.univie.ac.at)
 */

#ifndef _INC_SPEDE_MACHINE_PARALLEL_H
#define _INC_SPEDE_MACHINE_PARALLEL_H


/*  OFfsets to find parallel port registers. */
#define  LPT_DATA	0
#define  LPT_STATUS	1
#define  LPT_CONTROL	2


/*
 * status register (PS..Parallel Status) Read-Only
 * bit 7 6 5 4 3 2 1 0
 *     | | | | |
 *     | | | | +-------- /ERROR         0...error
 *     | | | +---------- SLCT           1...printer is online
 *     | | +------------ PE             1...paper empty
 *     | +-------------- /ACK           0...printer can receive next character
 *     +---------------- /BUSY          0...busy
 */
#define PS_ERROR (1 << 3)
#define PS_SLCT  (1 << 4)
#define PS_PE    (1 << 5)
#define PS_ACK   (1 << 6)
#define PS_BUSY  (1 << 7)

#define  PS_BITSTRING	"\020\004/Error\005Select\006NoPaper\007/ACK\010/Busy"

/*
 * control register (PC..Parallel Control) Read/Write
 * bit 7 6 5 4 3 2 1 0
 *           | | | | |
 *           | | | | +-- STROBE         1...data are valid
 *           | | | +---- AUTO FEED      1...automatic LF after CR
 *           | | +------ /INIT          0...reset printer
 *           | +-------- SLCT IN        1...select input(put printer online)
 *           +---------- IRQ Enable     1...generate interrupt when /ACK
 *                                          goes low
 */
#define PC_STROBE   (1 << 0)
#define PC_AUTOFEED (1 << 1)
#define PC_INIT     (1 << 2)
#define PC_SLCTIN   (1 << 3)
#define PC_IRQEN    (1 << 4)


/* -------------------------------------------------------------------- */

/*  Base I/O address for standard ports: */
#define  LPT0_BASE	0x03BC
#define  LPT1_BASE	0x0378
#define  LPT2_BASE	0x0278
#define  LPT3_BASE	0x02BC

#endif
