/*   spede/machine/pic.h
 *	Programmable Interupt controller control.
 *	@(#)pic.h	1.7   06/16/01
 */

#ifndef _INCL_SPEDE_MACHINE_PIC_H
#define _INCL_SPEDE_MACHINE_PIC_H 

#include <spede/sys/bits.h>


/* ------------------------------------------------------------------ */


/*  init_machine() presets IRQ0 timer.  Better to use CLK_TCK from
 *  <spede/time.h>.  _INIT_TICKS_SECOND is deprecated.
 */
/* #define  _INIT_TICKS_SECOND	100 */

/*  IRQ_VECTOR() macro takes IRQ number, returns interrupt vector.
 *  It contains the base interrupt for IRQ's.
 */
#define  IRQ_VECTOR(i)		(0x20+(i))

#define   IRQ_TIMER	0
#define   IRQ_KEYBOARD	1
#define   IRQ_CASCADE	2
#define   IRQ_COM2	3
#define   IRQ_COM1	4
#define   IRQ_PAR2	5
#define   IRQ_FLOPPY	6
#define   IRQ_PAR1	7

#define   IRQ_RTC	8
#define   IRQ_MOUSE	12
#define   IRQ_IDE1	14
#define   IRQ_IDE2	15


/*  How many of those things are there? */
#define  NR_IRQS		16

/*  IRQ2 cascades the slave unit to the master. */
/* #define  _PIC_IRQ_SLAVE 	2 */
#define  _PIC_MASK_SLAVE 	BIT(IRQ_CASCADE)

#define  INTR_NAME_BS	"\040\001Timer0\002Keyboard\003Cascase\004COM2" \
			"\005COM1\006LPT2\007Floppy\010LPT1" \
			"\011RTC\012irq9\013irq10\014irq11" \
			"\015Mouse\016FPU\017PriIDE\020SecIDE"

/* ------------------------------------------------------------------ */

/*  Interrupt Controllers' I/O port base addresses: */
#define  ICU0_IOBASE	0x20
#define  ICU1_IOBASE	0xA0


/**
 *      OCW2 -- Control end-of-interrupt signalling.
 *	Send to base+0, ie outport port 0x20 or 0xA0.
 */

#define NON_SPEC_EOI            0x20
#define SPECIFIC_EOI(i)		(0x60+(i))	/* 0 <= i <= 7 */
#define SET_PRIORITY            0xE0
/* #define NO_OPERATION            0x40 */


/**
 *      OCW3 (operation control word 3).  Send to I/O port ICU+0.  Ie, to
 *	read IIR, output 0x0A "NO_POLL_CMD | READ_IR_ONRD" to 0x20.
 */
#define _OCW3_TEMPLATE		0x08
#define _READ_NEXT_RD		0x02

#define SPECIAL_MASK            (0x40 | _OCW3_TEMPLATE)
#define MASK_MODE_SET		0x20		/* Combine with SPECIAL_MASK */
#define MASK_MODE_RESET		0x00		/* Combine with SPECIAL_MASK */
#define POLL_COMMAND            (0x04 | _OCW3_TEMPLATE)
#define NO_POLL_CMD		(0x00 | _OCW3_TEMPLATE)
#define READ_IR_ONRD		(0x00 | _READ_NEXT_RD | _OCW3_TEMPLATE)
#define READ_IS_ONRD		(0x01 | _READ_NEXT_RD | _OCW3_TEMPLATE)


#endif
