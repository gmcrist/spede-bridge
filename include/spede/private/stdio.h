/*  include/spede/private/stdio.h   Private stdio fakery
 *	@(#)stdio.h	1.4   G%G
 */


#ifndef _SPEDE_PRIVATE_STDIO_H
#define _SPEDE_PRIVATE_STDIO_H

#include <spede/stdarg.h>


#define	BUFSIZ	512
#define	_NFILE	20

struct	_iobuf {
	char	*	_ptr;
	int		_cnt;		/* Must be signed. */
	char	*	_base;
	unsigned char	_file;
	unsigned char	_flag;
};

# ifndef FILE
/* extern	struct	_iobuf	_iob[_NFILE]; */
# endif

#define	_IOREAD		0001
#define	_IOWRT		0002
#define	_IONBF		0004
#define	_IOMYBUF	0010
#define	_IOEOF		0020		/* Reads hit EndOfFile ? */
#define	_IOERR		0040		/* Last operation caused error */
#define	_IOSTRG		0100		/* For sprintf() */
#define _IO_UNUSED	0200
/*  If _flag._IOSTRG is set, then store char using __str_putc().
 *  If not set, then call (_iobuf._base)(ch, _iobuf *)
 */
typedef void (*_FILE_OUTCH)(int ch, struct _iobuf * file);


#define	FILE	struct _iobuf
#ifndef EOF
# define EOF	(-1)
#endif

#if 0
# define	stdin	(&_iob[0])
# define	stdout	(&_iob[1])
# define	stderr	(&_iob[2])

# define	getc(p)		(--(p)->_cnt>=0? *(p)->_ptr++&0377:_filbuf(p))
# define	getchar()	getc(stdin)
# define putc(x,p) (--(p)->_cnt>=0? ((int)(*(p)->_ptr++=(unsigned)(x))):_flsbuf((unsigned)(x),p))
# define	putchar(x)	putc(x,stdout)
# define	feof(p)		(((p)->_flag&_IOEOF)!=0)
# define	ferror(p)	(((p)->_flag&_IOERR)!=0)
# define	fileno(p)	(p)->_file

#endif

/*  Store character 'x' into 'struct _iobuf * p' buffer.  Each failed
 *  attempt will decrement p->_cnt, so it could end up with -9 in it.
 */
# define __str_putc(x,p) \
	(--(p)->_cnt>=0? ((int)(*(p)->_ptr++ = (unsigned)(x))):EOF)

/*  In stdio/sprintf.c: */
extern int	_doprnt(const char * fmt, va_list argp, FILE * file);

#endif
