/*    spede/stdio.h	Standard entries and defines... 	*/
/*	@(#)stdio.h	1.7   07/02/00	*/
/*	--- stdio.h	1.8 (lunaC) 91/07/23	*/
/*   adapted for gcc68 system, 6-may-92, bjw    */

#ifndef SPEDE_STDIO_H
#define SPEDE_STDIO_H 1

#ifndef TEST

#include <spede/sys/cdefs.h>
#include <spede/stdarg.h>
#include <spede/stddef.h>

__BEGIN_DECLS

#ifndef NULL
#define NULL	((void *)0)
#endif

#define EOF	(-1)

/*  Misc from the library.  printf() does output to target.  */
extern  int      printf __P(( const char *, ... ));
extern  int      vprintf __P(( const char *, va_list ap ));
extern  int      sprintf __P(( char *, const char *, ... ));
extern  int      snprintf __P(( char *, size_t len, const char *, ... ));
extern  int	 sscanf __P(( const char * str, const char * fmt, ... ));
extern  void     exit __P(( int ));

#undef getchar
#undef putchar

/*  These from target/cons1.c  */
extern int	putchar(int);
extern int 	getchar(void);
extern void	putstr(const char * mesg);

/*  From target/cgets.c: */
extern char *	getstr(char * p, int cnt);

__END_DECLS
#endif
#endif

