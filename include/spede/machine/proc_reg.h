/*   spede/machine/proc_reg.h
 *	%W%   %G%
 */
/*  GNU 2.x register usage:
 *	Must preserve:	EBX, EDI, ESI
 *	Can trash:	EAX, ECX, EDX, EFlags
 *
 *  This file can be included by C or assembly code.
 */

/* 
 * Mach Operating System
 * Copyright (c) 1991,1990 Carnegie Mellon University
 * All Rights Reserved.
 * 
 * Permission to use, copy, modify and distribute this software and its
 * documentation is hereby granted, provided that both the copyright
 * notice and this permission notice appear in all copies of the
 * software, derivative works or modified versions, and any portions
 * thereof, and that both notices appear in supporting documentation.
 * 
 * CARNEGIE MELLON ALLOWS FREE USE OF THIS SOFTWARE IN ITS "AS IS"
 * CONDITION.  CARNEGIE MELLON DISCLAIMS ANY LIABILITY OF ANY KIND FOR
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
/*
 * Processor registers for i386 and i486, etc...
 */
#ifndef	_SPEDE_MACH_I386_PROC_REG_H_
#define	_SPEDE_MACH_I386_PROC_REG_H_

#include <spede/flames.h>	/* For BIT(b) define */


/**
 * CR0
 */
#define	CR0_PG	0x80000000		/*	 enable paging */
#define	CR0_CD	0x40000000		/* i486: cache disable */
#define	CR0_NW	0x20000000		/* i486: no write-through */
#define	CR0_AM	0x00040000		/* i486: alignment check mask */
#define	CR0_WP	0x00010000		/* i486: write-protect kernel access */
#define	CR0_NE	0x00000020		/* i486: handle numeric exceptions */
#define	CR0_ET	0x00000010		/*	 extension type is 80387 */
					/*	 (not official) */
#define	CR0_TS	0x00000008		/*	 task switch */
#define	CR0_EM	0x00000004		/*	 emulate coprocessor */
#define	CR0_MP	0x00000002		/*	 monitor coprocessor */
#define	CR0_PE	0x00000001		/*	 enable protected mode */

#define  CR0_BITSTRING	"\020\001ProtectedMode\002MathMonitor\003MathEmulate" \
			"\004TaskSwitched\005ET\006MathError" \
			"\020WriteProtect\022AlignCheck" \
			"\036NotWriteThru\037CacheDisable\040Paging"

/**
 * CR3
 */
#define CR3_PCD 0x0000010		/* Don't cache page directory */
#define	CR3_PWT	0x0000008		/* write-thru caching enabled */


/**
 * CR4: Bits in PPro special register
 */
#define	CR4_VME	0x00000001	/* Virtual 8086 mode extensions */
#define	CR4_PVI	0x00000002	/* Protected-mode virtual interrupts */
#define	CR4_TSD	0x00000004	/* Time stamp disable */
#define	CR4_DE	0x00000008	/* Debugging extensions */
#define	CR4_PSE	0x00000010	/* Page size extensions */
#define	CR4_PAE	0x00000020	/* Physical address extension */
#define	CR4_MCE	0x00000040	/* Machine check enable */
#define	CR4_PGE	0x00000080	/* Page global enable */
#define	CR4_PCE	0x00000100	/* Performance monitoring counter enable */

#define  CR4_BITSTRING	"\020\0018086Virtual\002PMvirtualIntrs\003RestrictTSC" \
			"\004DebugExtend\005PageSizeExtend\006PhysAddrExtend" \
			"\007MachineCheck\010PageGlobal\011PerfMonitor"

/**
 *  Proc Flags
 */
#define  EF_CARRY		BIT(0)
#define  EF_PARITY		BIT(2)
#define  EF_AUX_CARRY		BIT(4)
#define  EF_ZERO		BIT(6)
#define  EF_SIGN		BIT(7)
#define  EF_TRAP		BIT(8)		/* Single-step mode */
#define  EF_INTR		BIT(9)		/* ON to allow CPu interrupts */
#define  EF_DIRECTION		BIT(10)
#define  EF_OVERFLOW		BIT(11)
#define  EF_IOPL_MASK		(0x03000)
# define   EF_IOPL_0		 (0)
# define   EF_IOPL_1		 (BIT(12))
# define   EF_IOPL_3		 (BIT(13)|BIT(12))
#define  EF_NESTED_TASK		BIT(14)
#define  EF_RESUME		BIT(16)
#define  EF_VIRTUAL_8088	BIT(17)
#define  EF_ALIGNMENT_CHECK	BIT(18)
#define  EF_VIRTUAL_INTR	BIT(20)
#define  EF_VIRUTAL_INTR_PENDING BIT(21)
#define  EF_IDENT		BIT(22)

#define  EF_DEFAULT_VALUE	BIT(1)		/* Intel says keep these bits on */

#define  EF_BITSTRING	"\020\001Carry\002BIT1\003Parity\004BIT3\005AuxCarry" \
			"\006BIT5\007Zero\010Sign\011Trap\012Intrs\013DirIncr" \
			"\014Overflow\017NestedTask" 			   \
			"\021Resume\022Virtual8088\023AlignCheck\024BIT19" \
			"\025VirtIntr\026VirtIntrPending\027HasCPUID"

#define  EF_BITSTRING_SHORT	"\020\001C\002Bit1\003PF\004Bit3\005AF" \
			"\006Bit5\007Z\010N\011T\012IE\013D"	\
			"\014V\017NT"				\
			"\021RF\022VM\023AC\024Bit19"		\
			"\025VIF\026VIP\027ID"

/* -------------------------------------------------------------- */

#ifndef	ASSEMBLER

/***  You probably really want "struct trap" instead.  ***/

/*  GNU 2.x register usage:
 *	Must preserve:	EBX, EDI, ESI
 *	Can trash:	EAX, ECX, EDX
 */
/*  Order of registers after a PUSHA instruction.  */
struct GeneralRegs {
	unsigned int   edi, esi, ebp, esp, ebx, edx, ecx, eax;
};

struct SegmentRegs {
	unsigned short	cs, ds, es, fs, gs;
};


/* -------------------------------------------------------------- */


# ifdef	__GNUC__

#  ifndef MACH_INLINE
#   ifdef __cplusplus__

/*  For some reason I got multiple definitions with GCC 2.7.2 in C mode.
 *  So for now, only do inline functions in C++ code.
 *	(bwitt, June 1999)
 */
#   define  MACH_INLINE   __inline

#  else

#   define MACH_INLINE   static __inline

#  endif	/* Ifdef __cplusplus__ */
# endif  /* ifndef MACH_INLINE */

__BEGIN_DECLS

/* --------------------------------------------------------------------- */

#ifdef __OPTIMIZE__

/* Some processors, notably my Am386DX/40,
   seem to have some rather subtle pipeline- or timing-related bugs
   which cause really weird things to happen with pushf's and popf's
   that come too close together...  */
/*  (Above comment found in mach4 distribution.) */

MACH_INLINE unsigned get_eflags() {
    unsigned eflags;
    asm volatile(
        "jmp	1f;"
        "1:	jmp	1f;"
        "1:	jmp	1f;"
        "1:	pushf;"
        "	jmp	1f;"
        "1:	jmp	1f;"
        "1:	jmp	1f;"
        "1:	jmp	1f;"
        "1:	popl %0;"
        : "=r" (eflags)
    );
    return eflags;
}

MACH_INLINE void set_eflags(unsigned eflags)
{
    asm volatile(
        "pushl %0;"
        "jmp	1f;"
        "1:	jmp	1f;"
        "1:	jmp	1f;"
        "1:	popf;"
        "jmp	1f;"
        "1:	jmp	1f;"
        "1:	jmp	1f;"
        "1:"
        :
        : "r" (eflags)
        : "cc"
    );
}

MACH_INLINE unsigned short get_cs()
{
	unsigned short cs;
	asm volatile("movw %%cs,%w0" : "=r" (cs));
	return cs;
}

MACH_INLINE unsigned short get_ds()
{
	unsigned short ds;
	asm volatile("movw %%ds,%w0" : "=r" (ds));
	return ds;
}
MACH_INLINE void set_ds(unsigned short ds)
{
	asm volatile("movw %w0,%%ds" : : "r" (ds));
}

MACH_INLINE unsigned short get_es()
{
	unsigned short es;
	asm volatile("movw %%es,%w0" : "=r" (es));
	return es;
}
MACH_INLINE void set_es(unsigned short es)
{
	asm volatile("movw %w0,%%es" : : "r" (es));
}

MACH_INLINE unsigned short get_fs()
{
	unsigned short fs;
	asm volatile("movw %%fs,%w0" : "=r" (fs));
	return fs;
}
MACH_INLINE void set_fs(unsigned short fs)
{
	asm volatile("movw %w0,%%fs" : : "r" (fs));
}

MACH_INLINE unsigned short get_gs()
{
	unsigned short gs;
	asm volatile("movw %%gs,%w0" : "=r" (gs));
	return gs;
}
MACH_INLINE void set_gs(unsigned short gs)
{
	asm volatile("movw %w0,%%gs" : : "r" (gs));
}

MACH_INLINE unsigned short get_ss()
{
	unsigned short ss;
	asm volatile("movw %%ss,%w0" : "=r" (ss));
	return ss;
}

MACH_INLINE unsigned short get_msw()
{
	unsigned short msw;
	asm volatile("smsw %0" : "=r" (msw));
	return msw;
}

#else

extern unsigned		get_eflags();
extern void		set_eflags();
extern unsigned short	get_cs();
extern unsigned short	get_ds();
extern void		set_ds(unsigned short);
extern unsigned short	get_es();
extern void		set_es(unsigned short);
extern unsigned short	get_fs();
extern void		set_fs(unsigned short);
extern unsigned short	get_gs();
extern void		set_gs(unsigned short);
extern unsigned short	get_ss();
extern unsigned short	get_msw();

#endif	/* __OPTIMIZE__ */

/* --------------------------------------------------------------------- */

#define  set_ss(new_ss)   asm volatile("movw %w0,%%ss" : : "r" (ss))


/**
 *	Forcibly change the CPU's direction flag.  Affects
 *	string operations.
 */
#define DIR_INCR	{ asm volatile("cld"); } 	/* Incr */
#define DIR_DECR	{ asm volatile("std"); } 	/* Decr */


/**
 *	Exchange a four-byte `new_value' with `*ptr'.
 *	Returns old value.  Operation is SMP atomic.
 *	Use TAS() when you just need a non-zero integer value.
 *	Linux uses "xchg()", but I found swap_atomic() in 
 *	"UNIX systems for Modern Architectures" by Curt Schimmel,
 *	(AW, 1994), page 159.
 */
#define  SWAP_ATOMIC(ptr, new_value)			\
({						\
    unsigned	__old_value;			\
    ASM( "lock ; xchg %0,%1"			\
	 : "=r"(__old_value)			\
	 : "m"((unsigned *)ptr), "0"(new_value) \
	 : "memory" );				\
    __old_value ;				\
})

#define  TAS(ptr)	swap_atomic(ptr,1)


#define get_eax() \
    ({ \
	register unsigned int _temp__; \
	asm("movl %%eax, %0" : "=r" (_temp__)); \
	_temp__; \
    })

#define get_ebx() \
    ({ \
	register unsigned int _temp__; \
	asm("movl %%ebx, %0" : "=r" (_temp__)); \
	_temp__; \
    })

#define get_ecx() \
    ({ \
	register unsigned int _temp__; \
	asm("movl %%ecx, %0" : "=r" (_temp__)); \
	_temp__; \
    })

#define get_edx() \
    ({ \
	register unsigned int _temp__; \
	asm("movl %%edx, %0" : "=r" (_temp__)); \
	_temp__; \
    })

#define get_esi() \
    ({ \
	register unsigned int _temp__; \
	asm("movl %%esi, %0" : "=r" (_temp__)); \
	_temp__; \
    })

#define get_edi() \
    ({ \
	register unsigned int _temp__; \
	asm("movl %%edi, %0" : "=r" (_temp__)); \
	_temp__; \
    })

#define get_ebp() \
    ({ \
	register unsigned int _temp__; \
	asm("movl %%ebp, %0" : "=r" (_temp__)); \
	_temp__; \
    })

#define get_esp() \
    ({ \
	register unsigned int _temp__; \
	asm("movl %%esp, %0" : "=r" (_temp__)); \
	_temp__; \
    })


#define	get_cr0() \
    ({ \
	register unsigned int _temp__; \
	asm volatile("mov %%cr0, %0" : "=r" (_temp__)); \
	_temp__; \
    })

#define	set_cr0(value) \
    ({ \
	register unsigned int _temp__ = (value); \
	asm volatile("mov %0, %%cr0" : : "r" (_temp__) : "memory"); \
     })

#define	get_cr2() \
    ({ \
	register unsigned int _temp__; \
	asm("mov %%cr2, %0" : "=r" (_temp__)); \
	_temp__; \
    })

#define	get_cr3() \
    ({ \
	register unsigned int _temp__; \
	asm("mov %%cr3, %0" : "=r" (_temp__)); \
	_temp__; \
    })

#define	set_cr3(value) \
    ({ \
	register unsigned int _temp__ = (value); \
	asm volatile("mov %0, %%cr3" : : "r" (_temp__) : "memory"); \
     })


#define	get_cr4() \
    ({ \
	register unsigned int _temp__; \
	asm("mov %%cr4, %0" : "=r" (_temp__)); \
	_temp__; \
    })

#define	set_cr4(value) \
    ({ \
	register unsigned int _temp__ = (value); \
	asm volatile("mov %0, %%cr4" : : "r" (_temp__) : "memory"); \
     })

/**
 *  "Clears the task-switched (TS) flag in the CR0 register."
 *  "The processor sets the TS flag every time a task switch occurs.  The
 *  flag is used to synchronize the saving of FPU context in multitasking
 *  applications."
 *		From "Intel Architecture Software Developer's Manual",
 *			vol 2, Instruction Set Reference, page. 3-55.
 */

#define	set_ts() \
	set_cr0(get_cr0() | CR0_TS)

#define	clear_ts() \
	asm volatile("clts")


#define	get_tr() \
    ({ \
	unsigned short _seg__; \
	asm volatile("str %0" : "=rm" (_seg__) ); \
	_seg__; \
    })

#define	set_tr(seg) \
	asm volatile("ltr %0" : : "rm" ((unsigned short)(seg)) )


  /*  Use "struct pseudo_descriptor" for next couple of macros.
   *  "limit" is the uint16 segmentl it's followed by a 32-bit offset
   *  value.  NOTE: This is backwards from a far pointer, where the
   *  segment is after the offset!
   */
  /*  The get_gdt() and get_ldt() functons are marked as changing memory.
   *  This is because even though "limit" is specified, the field after
   *  limit, "base_address", is also changed.
   *  Macro get_ldt() doens't need it since it moves only a selector value.
   */
#define set_gdt(pseudo_desc) \
    ({ \
	asm volatile("lgdt %0" : : "m" ((pseudo_desc)->limit)); \
    })

#define get_gdt(pseudo_desc) \
    ({ \
	asm volatile("sgdt %0" : "=m" ((pseudo_desc)->limit) : : "memory"); \
    })

#define set_idt(pseudo_desc) \
    ({ \
	asm volatile("lidt %0" : : "m" ((pseudo_desc)->limit)); \
    })

#define get_idt(pseudo_desc) \
    ({ \
	asm volatile("sidt %0" : "=m" ((pseudo_desc)->limit) : : "memory"); \
    })


#define	get_ldt() \
    ({ \
	unsigned short _seg__; \
	asm volatile("sldt %0" : "=rm" (_seg__) ); \
	_seg__; \
    })

#define	set_ldt(seg) \
	asm volatile("lldt %0" : : "rm" ((unsigned short)(seg)) : "memory" )


/*
 *  This doesn't change any processor registers,
 *  but it's often used immediately after setting segment regs
 *  to flush the instruction queue.
 */
#define flush_instr_queue() \
	asm volatile("jmp  9f ; 9:")

#endif	/* __GNUC__ */

/*  From "target/idt.c" : */
extern struct i386_gate *	get_idt_base(void);

__END_DECLS

#endif	/* ASSEMBLER */

#endif	/* _SPEDE_MACHINE_PROC_REG_H_ */

