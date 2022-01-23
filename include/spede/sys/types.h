/*	spede/sys/types.h	Matching types for Modula-2           june 91, bjw */
/*	%W%	%G%	*/
/*
 *	This file defines the known types used by the SPEDE Modula-2
 *	compiler.  These defines should make porting code betwee the
 *	two system easier.  For documentation sakes, you should stick
 *	with the defins in the original code whenever possible.  Someday,
 *	some one may want to modify your source code.
 *
 *	Use type "BOOL" with caution.  Many systems (and C++) define
 *	type "bool" as "int" or an enum, which stores in an "int".
 *
 *	No longer includes <spede/stdlib.h> to import "size_t" and "NULL".
 *
 *	Use BOOL for a return type (really an "int"), and BOOLEAN for 
 *	small structure elements (really "unsigned char").
 */


#ifndef _SPEDE_SYS_TYPES_H
#define _SPEDE_SYS_TYPES_H

#ifndef ASSEMBLER


typedef  char		int8;
typedef  short		int16;
typedef  int 		int32;
typedef  long long	int64;

typedef unsigned char		uint8;
typedef unsigned short		uint16;
typedef unsigned int 		uint32;
typedef unsigned long long	uint64;

#ifndef TEST

typedef unsigned long       pos_t;
typedef unsigned int	    REGISTER;	/* Processor thing. */

#ifndef _PTRDIFF_T
#define _PTRDIFF_T
/*  Defined here and in <spede/stddef.h> */
typedef long 			ptrdiff_t;	/* pointer math! */
#endif

typedef unsigned char		BOOLEAN;  /* Some systems store in "int" */
typedef unsigned int		BOOL;	  /* Long small, large storage. */

/*  BYTE, WORD and DWORD also match MS-Windows definitions. */
typedef uint8			BYTE;
typedef uint16			WORD;
typedef uint32	 		DWORD;

typedef unsigned int		ADDRESS;	/* address is 32-bits */

typedef char *			caddr_t;	/* For my UNIX friends */
typedef long            	off_t;          /* offsets within files */

typedef unsigned char		TEXT;
typedef TEXT * 			STRPTR;   /* C-style text strings! */

typedef unsigned char	uchar;
typedef unsigned short	ushort;
typedef unsigned int	uint;
typedef unsigned long	ulong;

#define  BITS_PER_BYTE		(8)
#define  BITS_PER_INT		(BITS_PER_BYTE*sizeof(int))
#define  BITS_PER_LONG		(BITS_PER_BYTE*sizeof(long))


/* ------------------------------------------------------------------ */

/*  Some much BSD/Linux code uses these defines, we have them, too. */
typedef unsigned char		u_char;
typedef unsigned short		u_short;
typedef unsigned int		u_int;
typedef unsigned int		u_int32_t;
typedef unsigned int		u_int16_t;

typedef int		int32_t;

typedef uint8			uint8_t;
typedef uint16			uint16_t;
typedef uint32			uint32_t;

typedef uint16			n_short;	/* Network 16-bit "short" */
typedef uint32			n_time; 	/* Network time (32-bits) */
typedef uint32			n_long; 	/* Network long (32-bits) */


/* ------------------------------------------------------------------ */

#endif  /* ifndef TEST */

/*  Tell the compiler this routine nevers returns to its caller:  */
#ifdef __GNUCPP__
#define  NEVER_RETURNING   volatile void
#else
#define  NEVER_RETURNING   void
#endif

#endif	/* ifndef ASSEMBLER */


/* end of <spede/sys/types.h> */
#endif
