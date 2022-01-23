/**	spede/sys/timeb.h
 *	@(#)timeb.h	1.1   09/26/02
 *
 */

#include <spede/time.h>			/* For "time_t" */

#ifndef _INCL_SPEDE_SYS_TIMEB_H
#define _INCL_SPEDE_SYS_TIMEB_H

/***
 *	Note: The time and millitm members contain the seconds and
 *	    milliseconds  portions, respectively, of the current time in
 *	    seconds since 00:00:00  UTC  (Coordinated  Universal  Time),
 *	    January 1, 1970.
 */


struct timeb {
	time_t 	time;		/* Seconds since the epoch */
	unsigned short	millitm;	/* + millisecond (more accuracy) */
	short	timezone;	/* Timezone: minutes west of UTC */
	short 	dstflag;	/* Time relative to daylight savings? */
};

#endif
 
