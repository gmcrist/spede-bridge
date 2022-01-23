/*   include/spede/machine/page.h
 *	%W%   %G%
 *	Works for C and assembler.
 */

/**
 *	Page Table (level 1 and 2) defines and structures for Intel IA32
 *	architecture as used on 80386, i486 and Pentiums.
 */

#ifndef _SPEDE_MACHINE_PAGE_H
#define _SPEDE_MACHINE_PAGE_H 1

#include <spede/sys/bits.h>		/* For BIT() macro */


/* --------------------------------------------------------------------- */


/* PAGE_SHIFT determines the page size */
/*  The Intel 80386 has 4K pages  NBPG =" number bytes/page" (a UNIX term) */
#define  PAGE_SHIFT      12

#define  NBPG		(1U<<PAGE_SHIFT)
#define  btop(b)	( (unsigned)(b) >> PAGE_SHIFT)

#define  PAGE_SIZE	(NBPG)
#define  PT_PAGE_MASK	(~(PAGE_SIZE-1))	/* Trim offset */
#define  PT_OFFSET_MASK	(PAGE_SIZE-1)		/* Trim pagedir/table idx */

#define  PAGE_DIR_SHIFT	(10+PAGE_SHIFT)

#define  PTE_PRESENT	BIT(0)
#define  PTE_WRITABLE	BIT(1)		/* 1=R/W, 0=read-only */
#define  PTE_USER	BIT(2)		/* 1=user OK, 0=ring 2..0 only */
#define  PTE_WRITE_THRU	BIT(3)		/* 1=page write thru */
#define  PTE_NO_CACHE	BIT(4)		/* 1=don't cache this page */
#define  PTE_ACCESSED	BIT(5)		/* 1=been accessed */
#define  PTE_DIRTY	BIT(6)		/* 1=frame contents altered */
#define  PTE_4M_SIZE	BIT(7)		/* 1=4MB page, 0=4KB page */
#define  PTE_M_AVAIL	0x0C00		/* Bits <11:9> available for OS use */


#ifndef ASSEMBLER

#include <spede/sys/types.h>


/*  Page Table Entry, Page Map Directory, Page Directory, and Protection.
 *  CR3 is a "pte_t *" type.
 */
typedef uint32	pte_t;
typedef uint32	pmd_t;
typedef uint32	pgd_t;
typedef uint32	pgprot_t;


/*  Plain linear address translation (4K pages, no extended physical addr).
 *  You assign to "address" or "pointer", then read from "xlat.*" to access
 *  pieces of the linear address as the paging unit will use it.
 */
typedef union _linear_addr
{
    /* A virtual address contains all three parts: */
    struct {
	uint	offset : PAGE_SHIFT;
	uint	pagetable : 10;
	uint	pagedir : 10;
    } xlat;

    /*  The page directory entry has a 20-bit page table ptr within: */
    struct {
       uint	mode : PAGE_SHIFT;
       uint	tableptr : 10+10;
    } tableptr;

    uint32	address;

    void *	pointer;
} linear_addr_t;


/* to align the pointer to the (next) page boundary */
#define PAGE_ALIGN(addr)        (((uint32)(addr)+PAGE_SIZE-1)&PT_PAGE_MASK)

/* This handles the Pentium memory map.. */
#define PAGE_TABLE_NR(addr)	((((uint32)(addr)) >> PAGE_SHIFT) & 0x3FF)
#define PAGE_DIRECTORY_NR(addr)	((((uint32)(addr)) >> PAGE_DIR_SHIFT) & 0x3FF)

#endif	/* ifndef ASSEMBLER */

#endif

