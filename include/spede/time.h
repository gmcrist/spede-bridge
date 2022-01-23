/*   include/spede/time.h
 *	@(#)time.h	1.2   08/13/00
 */

/**
 *	Bogus time definitions, enough to compile available programs.
 */

#ifndef _INCL_SPEDE_TIME
#define _INCL_SPEDE_TIME

#ifndef TEST

#include <spede/sys/cdefs.h>
#include <spede/sys/types.h>

__BEGIN_DECLS

/*  Typically seconds since January 1st, 1970 */
typedef int	time_t;

/*  Ticks program has been running since */
typedef int64	clock_t;
# define CLK_TCK	100


struct timespec {
	time_t	tv_sec;		/* seconds */
	long	tv_nsec;	/* and nanoseconds */
};

struct tm {
	int	tm_sec;  	/* seconds after the minute [0..59] */
	int 	tm_min;		/* minutes after the hour [0..59] */
	int 	tm_hour; 	/* hours since midnight [0..23] */
	int 	tm_mday;	/* day of the month [1..31] */
	int 	tm_mon;  	/* months since January [0..11] */
	int 	tm_year; 	/* years since 1900 */
# define  TM_YEAR_BASE	1900
	int 	tm_wday;	/* days since Sunday [0..6] */
	int 	tm_yday; 	/* days since January 1 [0..365] */
# define  DAYSPERNYEAR	365
# define  DAYSPERLYEAR	366
	int 	tm_isdst;	/* Daylight savings time flag */
				/* >0 if DST,  ==0 if not, <0 if unknown. */
	char 	tm_zone[8];	/* string describing time zone */
};

extern clock_t		clock(void);
extern time_t		time(time_t * tp);
extern struct tm *	localtime(const time_t * tp);
extern char *		asctime(const struct tm * tmp);
extern char *		ctime(const time_t * tp);

/*  And the re-entrant versions... */
extern char *		asctime_r(const struct tm *, char *);
extern char *		ctime_r(const time_t *, char *);
extern struct tm *	localtime_r(const time_t * tp, struct tm * tim);


__END_DECLS

#endif
#endif
