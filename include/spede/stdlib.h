/*   spede/stdlib.h	POSIX standard library routines...	*/
/*	@(#)stdlib.h	1.7   09/26/02	*/
/*	hacked to bits for GCC/Spede environment....
 */

#ifndef TEST
#ifndef	SPEDE_STDLIB_H_
#define	SPEDE_STDLIB_H_

#include <spede/sys/cdefs.h>
#include <spede/sys/types.h>		/* For NEVER_RETURNING */


__BEGIN_DECLS

#ifndef _SIZE_T_
#define _SIZE_T_
typedef	unsigned int	size_t;	     /* type of sizeof, GCC -> 32-bits */
#endif


#define TRUE	1
#define FALSE	0

/*
 *  The return code from SPEDE's exit() is ignored, so these defines are
 *  of little value.  But ANSI C wants them.
 */
#define EXIT_SUCCESS	0
#define EXIT_FAILURE	2


#define  _MAX(a,b)  ((a)>(b) ? (a) : (b))
#define  _MIN(a,b)  ((a)<(b) ? (a) : (b))

#ifndef __GLIBC_INTERNAL_STARTING_HEADER_IMPLEMENTATION
typedef struct
  {
    int quot;           /* Quotient.  */
    int rem;            /* Remainder.  */
  } div_t;

typedef struct
  {
    long int quot;      /* Quotient.  */
    long int rem;       /* Remainder.  */
  } ldiv_t;
#endif

/*
 *	Null pointer.  Also defined in <spede/stdio.h>
 */
#ifndef NULL
#define	NULL ((void *)0)
#endif


/*
 *	Valid range of return values for rand()   0..RAND_MAX
 */
#define  RAND_MAX   077777


/*
 *  prototypes
 *
 */

/*	Communication with the environment.	*/
NEVER_RETURNING	abort __P(( void ));	

/*  putenv() will copy the strig and save it (different than POSIX).
 *  getenv() returns ptr to key-value node, so don't mess with it!
 */
const char *	getenv __P(( const char * key ));
int 		putenv __P(( const char * keyvalue ));

/*	String conversion.	*/
double		atof __P(( const char *__nptr ));	
int		atoi __P(( const char *__nptr ));
long		atol __P(( const char *__nptr ));
long		strtol __P(( const char *__nptr, char **__eptr, int __base ));

#if 0
/* THERE ARE NOT SUPPLIED BY SPEDE (bwitt, March2001) */
double		strtod __P(( const char *__nptr, char **__eptr ));
unsigned long	strtoul __P(( const char *__nptr, char **__eptr, int __base ));
#endif

/*	Searching and sorting.	*/
void *		bsearch __P(( const void *__key, const void *__base,
			size_t __nel, size_t __size ,
			int (*__compar)(const void *, const void *) ));
void		qsort __P(( void *__base, size_t __nel, size_t __width,
		      int (*__compar)(const void *, const void *) ));

/*	Integer arithmetic.	*/
int		abs __P(( int __i ));
div_t		div __P(( int __numer, int __denom ));	
NEVER_RETURNING  exit __P(( int __status ));	
long		labs __P(( long __j ));
ldiv_t		ldiv __P(( long int __numer, long int __denom ));

/*	Memory management.	*/
void *		calloc __P(( size_t __nelem, size_t __size ));
void		free __P(( void *__ptr ));
void *		malloc __P(( size_t __size ));	
void *		realloc __P(( void *__ptr, size_t __size ));

void 		srand __P(( unsigned int seed ));
int      	rand  __P(( void ));

__END_DECLS

#endif
#endif
