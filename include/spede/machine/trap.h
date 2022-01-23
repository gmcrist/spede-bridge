/*   spede/machine/trap.h
 *	%W%   %G%
 */
/*
 * Mach Operating System
 * Copyright (c) 1991,1990,1989 Carnegie Mellon University.
 * Copyright (c) 1994 The University of Utah and
 * the Center for Software Science (CSS).
 * All rights reserved.
 *
 * Permission to use, copy, modify and distribute this software and its
 * documentation is hereby granted, provided that both the copyright
 * notice and this permission notice appear in all copies of the
 * software, derivative works or modified versions, and any portions
 * thereof, and that both notices appear in supporting documentation.
 *
 * CARNEGIE MELLON, THE UNIVERSITY OF UTAH AND CSS ALLOW FREE USE OF
 * THIS SOFTWARE IN ITS "AS IS" CONDITION, AND DISCLAIM ANY LIABILITY
 * OF ANY KIND FOR ANY DAMAGES WHATSOEVER RESULTING FROM THE USE OF
 * THIS SOFTWARE.
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

/*  NOTE: If this has been included, then <spede/util.h> exports a
 *	trap dump routine.  Made optional since a reduced "trap.h" file
 *	is given out to the OS class.	(bwitt, March2000)
 */

#ifndef _SPEDE_MACHINE_TRAP_H_
#define _SPEDE_MACHINE_TRAP_H_

#ifndef ASSEMBLER

/**
 *  This structure corresponds to the state of user registers
 *  as saved upon kernel trap/interrupt entry.
 *  As always, it is only a default implementation;
 *  a well-optimized microkernel will probably want to override it
 *  with something that allows better optimization.
 *
 *  NOTE: When you examine the segment values on the stack, the upper
 *	16-bits must be ignored.  If using "pushl %gs" the CPU moves
 *	16-bits to the stack but decrements by 4.  (bwitt, Oct 1999)
 */

typedef unsigned short	seg_type_t;

struct trap_frame {
/**** 	unsigned int	cr2;	*****/

	/* Saved segment registers */
	seg_type_t	gs;
	seg_type_t	_notgs;
	seg_type_t	fs;
	seg_type_t	_notfs;
	seg_type_t	es;
	seg_type_t	_notes;
	seg_type_t	ds;
	seg_type_t	_notds;

	/* PUSHA register state frame */
	unsigned int	edi;
	unsigned int	esi;
	unsigned int	ebp;
	unsigned int	esp;	/* Push: before PUSHA, Pop: skipped */
	unsigned int	ebx;
	unsigned int	edx;
	unsigned int	ecx;
	unsigned int	eax;

	unsigned int	trapno;
	unsigned int	err;

	/* Processor state frame */
	unsigned int	eip;
	unsigned int	cs;
	unsigned int	eflags;

	/*  If fault occurs in ring-0, SS:ESP are not pushed. */
	unsigned int	non_r0_esp;
	unsigned int	non_r0_ss;

#if 0
  /**  REMOVED SINCE 159 DOESN'T DO VM86 MODE.  (bwitt, Feb2000) **/
	/* Virtual 8086 segment registers */
	unsigned int	v86_es;
	unsigned int	v86_ds;
	unsigned int	v86_fs;
	unsigned int	v86_gs;
#endif
};


/* The actual trap_frame frame pushed by the processor
 * varies in size depending on where the trap came from.
 */
#define TR_IS_USERMODE(t)  (((t)->cs & 03) || ((t)->eflags & EFL_VM))

#define TR_KSIZE	((int)&((struct trap_frame*)0)->esp)
#define TR_USIZE	sizeof(struct trap_frame)

#endif	/* ifndef ASSEMBLER */

/*
 * Hardware trap vectors for i386 family.
 */
#define T_DIVIDE_ERROR          0
#define T_DEBUG                 1
#define T_NMI                   2               /* non-maskable interrupt */
#define T_INT3                  3               /* int 3 instruction */
#define T_OVERFLOW              4               /* overflow test */
#define T_OUT_OF_BOUNDS         5               /* bounds check */
#define T_INVALID_OPCODE        6               /* invalid op code */
#define T_NO_FPU                7               /* no floating point */
#define T_DOUBLE_FAULT          8               /* double fault */
#define T_FPU_FAULT             9
#define T_INVALID_TSS		10
#define T_SEGMENT_NOT_PRESENT   11
#define T_STACK_FAULT           12
#define T_GENERAL_PROTECTION    13
#define T_PAGE_FAULT            14
/*                              15 */
#define T_FLOATING_POINT_ERROR  16
#define T_WATCHPOINT            17
#define T_MACHINE_CHECK		18		/* Check yourself, buddy! */


/*  General error code bits.  Intr 14 is different. */
#define  T_ERR_EXTERN		(1<<0)
#define  T_ERR_DESC_LOCATION	(1<<1)
#define  T_ERR_GDT_LDT		(1<<2)
#define  T_ERR_SEG_MASK		(~07)

/*
 * Page-fault trap codes (intr 14).
 */
#define T_PF_PROT               0x1             /* protection violation */
#define T_PF_WRITE              0x2             /* write access */
#define T_PF_USER               0x4             /* from user state */


#endif _SPEDE_MACHINE_TRAP_H_

