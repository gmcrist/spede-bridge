/*   spede/machine/bus_pci.h
 *	@(#)bus_pci.h	1.1   07/02/00
 *	Defines for PCI bus.
 *	--- 16-pci/bus_pci.h,v 1.4 2000/06/15 22:38:31 aleks Exp aleks -
 */

/**
 *	For more information about the PCI bus, you can surf over to
 *	http://www.pcisig.com/.  Here are some important manuals:
 *		PCI BIOS SPecification
 *		PCI Local Bus Specification
 *		PCI to PCI Bridge Specification
 *		PCI Systsem Design Guide
 */

#ifndef _SPEDE_MACHINE_BUS_PCI_H
#define _SPEDE_MACHINE_BUS_PCI_H

#include <spede/sys/types.h>
#include <spede/sys/pci.h>
#include <spede/sys/cdefs.h>


/* ------------------------------------------------------------------- */

__BEGIN_DECLS

struct pci_types {
    unsigned	vendor;
    unsigned	device;
    const char *  name;
};

/*  Returns 0 if matched and attach OK. -2 if matched, but attach failed,
 *	and -1 if no match.
 */
#define  OK			0
#define  ERR_ALL_TAKEN		-3	/* Like no more intrs */
#define  PROBE_OK		(OK)
#define  PROBE_NO_MATCH		-1
#define  PROBE_FAIL_ATTACH	-2
#define  PROBE_NO_PCI		-3	/* Doesn't respond to config. */
#define  PROBE_PCI_EMPTY	-4	/* PCI0.0.0 empty. */


struct pci_dev;
typedef int		(*pci_work_fct)(struct pci_dev * dev);

typedef void		(*intr_func)(void * anchor);

typedef	char * 		PCIaddr;


struct pci_dev {
	unsigned	busdevfn;		/* Conf1 addr */

	uint		vendorID;
	uint		deviceID;
	uint		class_code;	/* 16-bit class code (no prog API) */
		/* See programAPI below for lower 8 bits of this 24 bit field) */

	struct pci_types *	type;
	pci_work_fct	attachit;
	pci_work_fct	initit;
	pci_work_fct	resetit;
    
	void *		dev_private_ptr;
  
	uint		struct_size;

	PCIaddr		mem_base;
	unsigned	mem_size;
	unsigned	io_base;
	unsigned	io_size;
	unsigned	intr;
	unsigned	caps_first;	/* Where PCI capabilities list starts */
	uint8		unit;
	uint8		dma;		/* ~0 means none. */

	uint8		programAPI;	/* Byte 9 */

	struct pci_dev * next;
};



/* -------------------------------------------------------------------- */
/*	Architecture Independent API					*/

extern PCIaddr	pci_base_addr(PCIaddr from_base_addr_reg);

extern void	pci_format_config(const struct pci_dev * dev, uint verbose,
				  void (*outfunc)(const char *) );

extern int	pci_sanity_check(void);

/*  Finds vendor/device match. Init busdevfn to 0 on first call. */
extern int	pci_find_vendor_device(struct pci_dev * dev);
extern int	pci_find_class(struct pci_dev * dev);

/*  Increment config address to next device: */
extern uint	pci_next_device(uint bdf);

extern void	DELAY(unsigned microseconds);

#define  PCI_READ_CONFIG_BYTE(dev,off)	pci_conf1_read_config_byte(dev,off)
#define  PCI_READ_CONFIG_WORD(dev,off)	pci_conf1_read_config_word(dev,off)
#define  PCI_READ_CONFIG_LONG(dev,off)	pci_conf1_read_config_long(dev,off)

#define  PCI_WRITE_CONFIG_BYTE(dev,off,v)   pci_conf1_write_config_byte(dev,off,v)
#define  PCI_WRITE_CONFIG_WORD(dev,off,v)   pci_conf1_write_config_word(dev,off,v)
#define  PCI_WRITE_CONFIG_LONG(dev,off,v)   pci_conf1_write_config_long(dev,off,v)

#define  PCI_CLEAR_CONFIGURE(dev)	pci_conf1_clear_config()


/* -------------------------------------------------------------------- */
/*	Architecture Specific API					*/


#ifdef i386

/*  Intel maps CPU addr == PCI bus master addr.  Not true for MIPS and
 *  PowerPC chips.
 *  Macro cpu2pci() changes a pointer from CPU's view to the address a
 *  PCI device would use for the same location
 */
#define  cpu2pci(ptr)    ((void *)(ptr))

#define  CONF1_ENABLE       (BIT(31))
#define  PCI_CONF1_ADDR	     0xCF8
#define  PCI_CONF1_DATA	     0xCFC


extern unsigned	pci_conf1_read_config_byte(const struct pci_dev * dev,
					   unsigned offset);
extern void	pci_conf1_write_config_byte(const struct pci_dev * dev,
					   unsigned offset, unsigned data);
extern unsigned	pci_conf1_read_config_word(const struct pci_dev * dev,
					   unsigned offset);
extern void	pci_conf1_write_config_word(const struct pci_dev * dev,
					   unsigned offset, unsigned data);
extern unsigned	pci_conf1_read_config_long(const struct pci_dev * dev,
					   unsigned offset);
extern void	pci_conf1_write_config_long(const struct pci_dev * dev,
					   unsigned offset, unsigned data);

extern void	pci_conf1_clear_config(void);


#endif	/* ifdef i386 */

__END_DECLS


#endif

