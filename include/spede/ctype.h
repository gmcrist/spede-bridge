/*   ctype.h    Character Classifiction from lunaC                          */
/*	@(#)ctype.h	1.5   06/29/00	*/
/*   protected toupper() and tolower().
 */

#ifndef _INC_CTYPE_H
#define _INC_CTYPE_H 1

#include <spede/sys/cdefs.h>

__BEGIN_DECLS

#define	_U	01
#define	_L	02
#define	_N	04
#define	_S	010
#define _P	020
#define _C	040

extern	const unsigned char	_ctype_[];

/*  NEWLINE, TAB, BACKSPACE, RETURN, VERTICAL-TAB are both control
 *	chars and "spacing" chars.
 *		(bwitt, June 2000)
 */

#define	isalpha(c)	((_ctype_+1)[(int)(c)]&(_U|_L))
#define	isupper(c)	((_ctype_+1)[(int)(c)]&_U)
#define	islower(c)	((_ctype_+1)[(int)(c)]&_L)
#define	isdigit(c)	((_ctype_+1)[(int)(c)]&_N)
#define	isspace(c)	((_ctype_+1)[(int)(c)]&_S)
#define ispunct(c)	((_ctype_+1)[(int)(c)]&_P)
#define isalnum(c)	((_ctype_+1)[(int)(c)]&(_U|_L|_N))
#define isgraph(c)	((_ctype_+1)[(int)(c)]&(_P|_U|_L|_N))	/* no spaces */
#define iscntrl(c)	((_ctype_+1)[(int)(c)]&_C)
extern int		isxdigit(int c);

#define isprint(c)	(' ' <= (unsigned)(c) && (unsigned)(c) < 0x7F)
#define isascii(c)	((unsigned)(c)<=0177)


/*  Sneaky and quick translation: */
#define _toupper(c)	((c)-'a'+'A')
#define _tolower(c)	((c)-'A'+'a')
#define _tocontrol(c)	((c) & 0x1F)
#define _toascii(c)	((c) & 0177)

/*  Abritrary character translation: */
extern int	toupper(int c);
extern int	tolower(int c);


__END_DECLS

#endif

