/*   spede/strings.h	String handlers...		*/
/*   @(#)string.h	1.4   12/31/00   */
/**
 *      hacked to bits for GCC/Spede environment....
 *	Can declare bzero ifndef __DEFINED_BZERO.
 */


#ifndef	_INC_STRINGS_H
#define	_INC_STRINGS_H

#ifndef TEST

/*  import __BEGIN_DECLS, size_t and NULL: */
#include <spede/stdlib.h>

__BEGIN_DECLS

/**  We now have bzero() in our library!! **/
#ifndef __DEFINED_BZERO
#define __DEFINED_BZERO  1
extern  void	    bzero __P(( void *, unsigned ));
#endif	/* end ifndef __DEFINED_BZERO */


/*  Local interface to bsd style memory movers:  */

extern char
	*strdup __P(( const char * orig )),
	*strcat	__P(( char *__s1, const char *__s2 )),	
	*strchr	__P(( const char *__s, int __c )),
	*strcpy	__P(( char *__s1, const char *__s2 )),
	/** *strerror __P(( int __n )),		*/
	*strncat __P(( char *__s1, const char *__s2, /* size_t */ int __n )),
	*strncpy __P(( char *__s1, const char *__s2, size_t __n )),
	*strpbrk __P((const char *__s1, const char *__s2 )),	
	*strrchr __P(( const char *__s, int __c )),
	*strstr	__P(( const char *__s, const char *__t )),
	*strtok	__P(( char *__s1, const char *__s2 )),
	*strtok_r __P(( char *s1, const char *s2, char **lasts )); /* re-entrant */

extern int
	memcmp __P((/* const void *__s1, const void *__s2, size_t __n */)),
	strcmp __P(( const char *__s1, const char *__s2 )),
	strcmpi __P(( const char *__s1, const char *__s2 )),  /* NON-STANDARD */
	/** strcoll __P(( const char *__s1, const char *__s2 )),	*/
	strncmp __P(( const char *__s1, const char *__s2, size_t __n ));

extern void
	*memchr __P(( const void *__s, int __c, size_t __n )),	
	*memcpy __P((/* void *__s1, const void *__s2, size_t __n */)),
	*memmove __P(( void *__s1, const void *__s2, size_t __n )),
	*memset __P(( void *__s, int __c, size_t __n ));

extern size_t
	strcspn __P(( const char *__s1, const char *__s2 )),
	strlen __P(( const char *__s )),
	strspn __P(( const char *__s1, const char *__s2 ));

__END_DECLS

#endif
#endif

