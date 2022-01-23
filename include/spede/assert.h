/* Allow this file to be included multiple times
   with different settings of NDEBUG.  */
/*	@(#)assert.h	1.1   06/09/99	*/

#undef assert
#undef __assert

#ifdef NDEBUG
#define assert(ignore)  ((void)0)
#else

#include <spede/sys/cdefs.h>

__BEGIN_DECLS

void __eprintf ();		/* Defined in gnulib */

#ifdef __STDC__

#define assert(expression)  \
  ((void) ((expression) ? 0 : __assert (#expression, __FILE__, __LINE__)))

#define __assert(expression, file, lineno)  \
  (__eprintf ("Failed assertion `%s' at line %d of `%s'.\n",	\
	      expression, lineno, file), 0)

#else /* no __STDC__; i.e. -traditional.  */

#define assert(expression)  \
  ((void) ((expression) ? 0 : __assert (expression, __FILE__, __LINE__)))

#define __assert(expression, file, lineno)  \
  (__eprintf ("Failed assertion `%s' at line %d of `%s'.\n",	\
	      "expression", lineno, file), 0)

#endif /* no __STDC__; i.e. -traditional.  */

__END_DECLS

#endif

