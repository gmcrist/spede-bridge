/*   spede/machine/timer.h
 *	Definitions for both IBM PC timers.
 *	@(#)timer.h	1.3   06/12/00
 */

#ifndef _INCL_MACHINE_TIMER_H
#define _INCL_MACHINE_TIMER_H

/*
 * Timer chip #0 I/O ports.
 */
#define PIT0_TMR0 	0x40		/* timer 0, 1, or 2 value (r/w) */
#define PIT0_TMR1 	0x41
#define PIT0_TMR2 	0x42
#define PIT0_TMRCTL	0x43		/* timer control (write-only) */

/*
 * Timer chip #1 I/O ports (i8254).
 */
#define PIT1_TMR0 	0x48		/* timer 0, 1, or 2 value (r/w) */
#define PIT1_TMR1 	0x49
#define PIT1_TMR2 	0x4A
#define PIT1_TMRCTL	0x4B		/* timer control (write-only) */

#endif

