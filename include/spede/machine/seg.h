/*   include/spede/machine/seg.h
 *	@(#)seg.h	1.9   06/16/00
 */
/* 
 * Mach Operating System
 * Copyright (c) 1991,1990 Carnegie Mellon University
 * Copyright (c) 1991 IBM Corporation 
 * All Rights Reserved.
 * 
 * Permission to use, copy, modify and distribute this software and its
 * documentation is hereby granted, provided that both the copyright
 * notice and this permission notice appear in all copies of the
 * software, derivative works or modified versions, and any portions
 * thereof, and that both notices appear in supporting documentation,
 * and that the name IBM not be used in advertising or publicity 
 * pertaining to distribution of the software without specific, written
 * prior permission.
 * 
 * CARNEGIE MELLON AND IBM ALLOW FREE USE OF THIS SOFTWARE IN ITS "AS IS"
 * CONDITION.  CARNEGIE MELLON AND IBM DISCLAIM ANY LIABILITY OF ANY KIND FOR
 * ANY DAMAGES WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE.
 * 
 * Carnegie Mellon requests users of this software to return to
 * 
 *  Software Distribution Coordinator  or  Software.Distribution@CS.CMU.EDU
 *  School of Computer Science
 *  Carnegie Mellon University
 *  Pittsburgh PA 15213-3890
 * 
 * any improvements or extensions that they make and grant Carnegie Mellon
 * the rights to redistribute these changes.
 */

#ifndef	_MACH_I386_SEG_H_
#define	_MACH_I386_SEG_H_


/*
 * i386 segmentation.
 */

#ifndef ASSEMBLER

/*
 * Real segment descriptor.
 */
struct i386_descriptor {
	unsigned int	limit_low:16,	/* limit 0..15 */
			base_low:16,	/* base  0..15 */
			base_med:8,	/* base  16..23 */
			access:8,	/* access byte */
			limit_high:4,	/* limit 16..19 */
			granularity:4,	/* granularity */
			base_high:8;	/* base 24..31 */
};

/*  Access macros.  Base is always 32-bits.  Granularity bit applies to
 *  "limit" value, which could be scaled up 4K.  Caller must apply granularity
 *  multiply if appropriate.
 */
#define  DESC_UNUSED(d)  ((d)->access == 0)
#define  DESC_GET_DPL(d)  (((d)->access >> 5) & 03)
#define  DESC_GET_BASE(d)  ((d)->base_low | ((long)(d)->base_med << 16) | ((long)(d)->base_high << 24))
#define  DESC_GET_LIMIT(d)  ((d)->limit_low | ((long)(d)->limit_high << 16))


struct i386_gate {
	unsigned int	offset_low:16,	/* offset 0..15 */
			selector:16,
			word_count:8,
			access:8,
			offset_high:16;	/* offset 16..31 */
};

#define  GATE_GET_OFFSET(g)   ((g)->offset_low | ((long)(g)->offset_high << 16))

#endif /* ASSEMBLER */


/*  i386_descriptor.granularity (4 bits): */
#define  GR_AVAIL	(1<<0)			/* User available bit */
			/*  bit 1 of granularity (really bit 5) is reserved. */
#define	SZ_32		0x4			/* 32-bit segment */
#define SZ_16		0x0			/* 16-bit segment */
#define SZ_32_CODE(gran)  ((gran & SZ_32) != 0)

/*  Intel calls gran.bit3 "granularity" and gran.bit2 "Big" Oh well. */
#define  GR_BIG		(1<<3)		/* 1=4K incr, 0=bytes */

/*  i386_descriptor.access, System=1 (8 bits): */
#define SZ_CODE		0x4			/* D/C = code */
#define SZ_DATA		0x0			/* bit6 off */

/*  i386_descriptor.access, System=0 (8 bits): */
#define	ACC_A		0x01			/* accessed */
#define	ACC_TYPE	0x1f			/* type field: */

#define	ACC_TYPE_SYSTEM	0x00			/* system descriptors: */

#define	ACC_LDT		0x02			    /* LDT */
#define	ACC_CALL_GATE_16 0x04			    /* 16-bit call gate */
#define	ACC_TASK_GATE	0x05			    /* task gate */
#define	ACC_TSS		0x09			    /* task segment */
#define	ACC_CALL_GATE	0x0c			    /* call gate */
#define	ACC_INTR_GATE	0x0e			    /* interrupt gate */
#define	ACC_TRAP_GATE	0x0f			    /* trap gate */

#define	ACC_TSS_BUSY	0x02			    /* task busy BIT */
						/* Busy 386 TSS 0x0B */

#define	ACC_TYPE_USER	0x10			/* user descriptors */

#define  DESC_SYSTEM(desc)   (0 == ((desc)->access & ACC_TYPE_USER))

/*  Data and code segments: */
#define	T_MEMRO		16		/* Read only */
#define	T_MEMRW		18		/* Read+write */
#define	T_MEMX		24		/* Execute only */
#define	T_MEMXR		26		/* Execute+read */

#define	ACC_DATA	0x10			    /* data, readonly */
#define	ACC_DATA_W	0x12			    /* data, writable */
#define	ACC_DATA_E	0x14			    /* data, expand-down */
#define	ACC_DATA_EW	0x16			    /* data, expand-down,
							     writable */
#define	ACC_CODE	0x18			    /* code */
#define	ACC_CODE_R	0x1a			    /* code, readable */
#define	ACC_CODE_C	0x1c			    /* code, conforming */
#define	ACC_CODE_CR	0x1e			    /* code, conforming,
						       readable */

/*  Privilege level extraction:  */
#define	ACC_PL		0x60			/* access rights: */
#define	ACC_PL_K	0x00			/* kernel access only */
#define	ACC_PL_U	0x60			/* user access */
#define	ACC_P		0x80			/* segment present */

/* -----------------------------------------------------------------
 * Components of a selector
 */
#define	SEL_PL		0x03			/* privilege level: */
#define	SEL_PL_K	0x00			    /* kernel selector */
#define	SEL_PL_U	0x03			    /* user selector */

#define SEL_TI		BIT(2)			/* 1=local, 0=GDT */
#define	SEL_LDT		0x04			/* local selector */
#define SEL_ISLDT(sel)	(((sel) & SEL_LDT) != 0)
#define SEL_ISGDT(sel)	(((sel) & SEL_LDT) == 0)

/*
 * Convert selector to descriptor table index, and back again.
 */
#define	sel_idx(sel)	((sel)>>3)
#define	idx_sel(idx)	((idx)<<3)


/* ----------------------------------------------------------------- */

#ifndef ASSEMBLER

#ifndef MACH_INLINE
# ifdef __cplusplus
#  define  MACH_INLINE   inline
# else
#  define  MACH_INLINE   static __inline
# endif	/* Ifdef __cplusplus__ */
#endif  /* ifndef MACH_INLINE */


/*  Not to be confused with the "pseudo-descriptor". The Far Pointer is
 *  used in far jump and far call assembly instructions.  Little-endian
 *  CPUs _naturally_ place the segment after the offset.
 */
struct far_pointer {
	unsigned long  offset;
	unsigned short  segment;
};


/*  Format of a "pseudo-descriptor", used for loading the IDT and GDT. 
 *  Only 16-bits of `limit' are stored because SIDT anmd SGDT are 
 *  originally '286 instructions, which had only 16-bit limits.
 *  Works great for backwards-compatibility!
 *
 *  The CPU always writes 48-bits.  Include the `_pad' element so the
 *  `linear_base' is on a natural (32-bit) alignment.
 */
struct pseudo_descriptor
{
	short _pad;
	unsigned short limit;
	unsigned int   linear_base;
};


# if defined(__OPTIMIZE__) || defined(__cplusplus)

/* Fill a segment descriptor.  */
MACH_INLINE void
fill_descriptor(struct i386_descriptor *desc, unsigned base, unsigned limit,
		unsigned char access, unsigned char sizebits)
{
	if (limit > 0xfffff)
	{
		limit >>= 12;
		sizebits |= GR_BIG;
	}
	desc->limit_low = limit & 0xffff;
	desc->base_low = base & 0xffff;
	desc->base_med = (base >> 16) & 0xff;
	desc->access = access | ACC_P;		/* Segment is Present */
	desc->limit_high = limit >> 16;
	desc->granularity = sizebits;
	desc->base_high = base >> 24;
}

/* Set the base address in a segment descriptor.  */
MACH_INLINE void
fill_descriptor_base(struct i386_descriptor *desc, unsigned base)
{
	desc->base_low = base & 0xffff;
	desc->base_med = (base >> 16) & 0xff;
	desc->base_high = base >> 24;
}

/* Set the limit in a segment descriptor.  */
MACH_INLINE void
fill_descriptor_limit(struct i386_descriptor *desc, unsigned limit)
{
	if (limit > 0xfffff)
	{
		limit >>= 12;
		desc->granularity |= GR_BIG;
	} else {
		desc->granularity &= ~GR_BIG;
	}
	desc->limit_low = limit & 0xffff;
	desc->limit_high = limit >> 16;
}

/* Fill a trap/interrupt/task/call gate with particular values.  */
MACH_INLINE void
fill_gate(struct i386_gate *gate, unsigned offset, unsigned short selector,
	  unsigned char access, unsigned char word_count)
{
	gate->offset_low = offset & 0xffff;
	gate->selector = selector;
	gate->word_count = word_count;
	gate->access = access | ACC_P;
	gate->offset_high = (offset >> 16) & 0xffff;
}

# else

# endif	/* else __OPTIMIZE__ || __cplusplus */

extern void	fill_descriptor(struct i386_descriptor *desc,
				unsigned base, unsigned limit,
				unsigned char access, unsigned char sizebits);
extern void	fill_descriptor_base(struct i386_descriptor *desc,
				     unsigned base);
extern void	fill_descriptor_limit(struct i386_descriptor *desc,
				      unsigned limit);
extern void	fill_gate(struct i386_gate *gate, unsigned offset,
			  unsigned short selector,
			  unsigned char access, unsigned char word_count);

#endif /* ASSEMBLER */

#endif	/* _MACH_I386_SEG_H_ */
