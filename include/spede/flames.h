/*	spede/flames.h	Matching types for Modula-2           june 91, bjw */
/*	%W%	%G% */
/*	3-July-1998  bwitt  Moved ASCII defines to <sys/ascii.h>
 */

#ifndef _SPEDE_FLAMES_H
#define _SPEDE_FLAMES_H 1

#ifndef ASSEMBLER
/*  import `size_t' and `NULL': */
#include <spede/sys/cdefs.h>
#include <spede/sys/types.h>
#endif	/* ifndef ASSEMBLER */

#include <spede/sys/ascii.h>
#include <spede/sys/bits.h>


/* ------------------------------------------------------------------ */

#ifndef ASSEMBLER

__BEGIN_DECLS

/*  Use this short hand.  All asm code should be 'volatile'! */
#define ASM  __asm volatile

/*  Annotate the data flow direction of a parameter. */
#define  IN
#define  OUT

#define  UNUSED_ARG(a)	((void)(a))

/* ----------------------------------------------------------------- */

typedef unsigned 	splx_t[1];
extern void		splhigh(splx_t);	/* Save intr flag, disable */
extern void		splx(const splx_t);	/* Restore intr flag */

typedef unsigned	LONGWORD;		/* SPEDE type system. */


#ifdef __GNUC__
# define  DI()   ASM( " cli" )
# define  EI()   ASM( " sti" )
#endif

/* ----------------------------------------------------------------- */

#define HIBYTE(x)  ((BYTE)((x) >> 8))
#define LOBYTE(x)  ((BYTE)((x) & 0xff))

#define HIWORD(x)  ((unsigned short)((x) >> 16))
#define LOWORD(x)  ((unsigned short)((x) & 0x0FFFF))

#define BUILD_LONG(hi,lo)	(((uint32_t)(hi) << 16) | ((lo) & 0xFFFF))
#define MAKELONG(hi,lo) 	BUILD_LONG(hi,lo)
	
/* #define SHIFT(x,n)		(((n) > 0 ? ((x) << (n)) : ((x) >> (n)))) */

/*  Put 4 chrs together in little-endian order */
#define  _B2L(b)	((uint32)(BYTE)(b))
#define  MK4CODE(a,b,c,d)	(_B2L(a) | (_B2L(b) << 8) | \
				 (_B2L(c) << 16) | (_B2L(d) << 24))

/* ----------------------------------------------------------------- */

/*  Define a bitfield, name and bit width. */
#define BITFIELD(name,width)   unsigned int  name : width

/*  Change a pointer value into an integer value, type "diff_t" */
#define  PTR2INT(p)   ((char *)(p) - (char *)0)

/*  Return byte offset of "element" inside structure "type". */
#define  OFFSETOF(type,element)	(PTR2INT(& ((type *)0)->element))

/*  Return number of elements when array size is known. */
#define  NELEMENTS(arr)   ((int)(sizeof(arr)/sizeof((arr)[0])))

/*  Do a typed malloc... (requires #include <stdlib.h> first */
#define MALLOC(struc)	((struc *) malloc(sizeof(struc)))

/**
 *  Ways to "adjust" a pointer or integer.  Pointers get rounded up,
 *  and integers get rounded down.  Because these are macros, watch
 *  out for double usage of parameters.
 */
#define  PTR_ROUND_UP(p,incr)	 ((void *)((PTR2INT(p) + (incr)-1) & ~((incr)-1)))
#define  INT_ROUND_UP(v,incr)	 (((v)+(incr)-1) & ~((incr)-1))
#define  INT_ROUND_DOWN(v,incr)	 ((v) & ~((incr)-1))


/* ----------------------------------------------------------------- */

/*  I/O port $80 is reserved and will never be used.  If you 
 *  access this port, you create a delay of three cycles at 8.33MHz,
 *  plus the I/O access, which takes two clock cycles (total of 5).
 *  An unmapped I/O port goes out to the ISA bus, which runs with
 *  a 8.33MHz clock.  Especially true in PCI systems.
 *  Two of these in a row give a 1.2 microsecond delay.
 *			Attributed to James van Artsdalen.
 */
#define  IO_DELAY()	ASM (" inb $0x80,%%al" : : : "eax")


/* ----------------------------------------------------------------- */


/*  From MODULE FlamesInterface: */
/*  "NEVER_RETURNING" defined in <spede/sys/types.h> */

extern NEVER_RETURNING  FlamingExit ( void );

/*  Cause a breakpoint to occur.  Only trips when using GDB.
 *	Source in "03-CRTL/gdb/i386-stub.c"
 */
extern void	breakpoint();

extern void	farmemcpy(int seg_dest, char * dest, int seg_src, char * src,
			  unsigned byte_size);

/*  These I/O routines send/get chars with keyboard and display. 
 *	WriteConsoleString() is in target/flames.c
 */
extern void	cons_gotoRC(int new_row, int new_col);
extern void	cons_clear(void);		/* Clear and home */
extern void	cons_putchar(int ch);		/* Cooks output chars */
extern int	cons_getchar(void);		/* Returns ASCII char */
extern int 	cons_kbhit(void);		/* FALSE if no char avail */

extern void	cons_println(void);		/* cook: NEWLINE */
extern void	WriteConsoleString(const char * mesg);
extern void	cons_putstr(const char * mesg);
extern char *	cons_getstr(char * buffer, int size);

extern int	cons_printf(const char *, ...);


/*  These from "target/cons0.c".  Called by "startup/crt0.c" _start() */
extern void	init_cons(void);

extern unsigned	_cons_attrib;	/* Background video, default=0x0700 */


/*  These I/O routines (plus those in <spede/stdio.h>) do host computer.
 *	(From target/targetio.c)
 */
extern void	println(void);

#endif	/* ifndef ASSEMBLER */


/* ------------------------------------------------------------------ */

#ifdef m68000
/*  When GDB is active, it sets "_UnderGDB" to 3.  This is a magic
 *  cookie for us.  It means the debug terminal will do local echo,
 *  and will send requests in $..#cc packets.   Check GDB 4.x documentation
 *  about this prototcol.
 *  Sudhir Cheruat has extended the protocol to include char input and output.
 *
 *	sudhir cheruat/brian witt, Nov 1994.
 */
# define  _UnderGDB    (*((short *) 0x2ffc))
# define  _cookie_UnderGDB  ((short)3)
#endif

#ifdef i386

# ifndef ASSEMBLER
/*  Well, the trick for M68010 was cute.  Today we use a variable.
 *  For startup/gdb0.c sets to _DEBUG_BEFORE, calls set_debug_traps(),
 *  then sets _DEBUG_USING_GDB.  Later on, there could be other 
 *  debuggers, so test this var when it's important to know!
 *
 *  If "_using_debug" > 0, then the debugger owns the IDT table.
 */
enum DebugSupport {
	_DEBUG_BEFORE		= -1,
	_DEBUG_NOPE		= 0,
	_DEBUG_USING_GDB	= 1
} ;

extern enum DebugSupport	_conf_using_debug;

/**
 *	Set "_conf_pager" to TRUE to enable the console output
 *	pager routine.  See target/cons1.c:cons_more() for details.
 *	In target/cons0.c:cons_init(), sets FALSE if
 *	"_conf_using_debugger == _DEBUG_NOPE".
 */
extern char			_conf_pager;

/**
 *	Console output can be sent to the serial port.  If a debugger
 *	is running, we'll call putpacket().  We'll share the serial
 *	port.  TRUE => chars to serial port and not to the video screen.
 */
extern char			_conf_cons_serial;

/**
 *	Perform handy initialize of machine to make the student's job
 *	easier.  For I386, install IDT and preset IRQ intr base to
 *	0x20..0x2F always there.  All IRQs are masked (disabled).
 *	(See <spede/machine/intrcntl.h for values.)
 *
 *	See target/machine.c for _init_machine()
 *	See target/cleanup.c for IBM PC-AT restore code.
 */
extern void	_init_machine();

# endif	/* ifndef ASSEMBLER */

#endif	/* endif ifdef(i386) */


#ifndef ASSEMBLER
__END_DECLS
#endif

#endif
/* end of "spede/flames.h" */

