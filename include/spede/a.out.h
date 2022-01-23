/*  spede/a.out.h    A.OUT style header structures       bwitt, August 1998 */
/*	@(#)a.out.h	1.1   06/09/99	*/

/*
 *	Layout of a.out file :
 *
 *	header of 8 longs	magic number   0, 2, 1, 7
 *				text size		)
 *				data size		) in bytes
 *				bss size		)
 *				symbol table size	)
 *				entry point             )
 *				text relocation size	)
 *				data relocation size	)
 *
 *
 *	header:			0
 *	text:			32
 *	data:			32+textsize
 *	symbol table:		32+textsize+datasize
 *	text relocation:	32+textsize+datasize+symsize
 *	data relocation:	32+textsize+datasize+symsize+rtextsize
 *
 */


#ifdef __FLAMES
#include <spede/sys/types.h>
#else
typedef  unsigned long	 ULONG;
typedef  unsigned short	 UWORD;
#endif

struct aouthdr
{
    UWORD	machine;
    UWORD	magic;
    ULONG	text_size;
    ULONG	data_size;
    ULONG	bss_size;

    ULONG	syms_size;
    ULONG	entry;
    ULONG	text_reloc_size;
    ULONG	data_reloc_size;
};

typedef struct aouthdr	AOUTHDR;


#define  AOUT_MACHINE	0002
#define  OMAGIC   0407		/* ... object file or impure executable. */

/* end spede/a.out.h */
