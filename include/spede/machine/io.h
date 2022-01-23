/*   spede/machine/io.h
 *   @(#)io.h	1.2   06/08/00
 *	Intel X86 input and output functions.
 */

#ifndef _SPEDE_MACHINE_IO_H
#define _SPEDE_MACHINE_IO_H

#include <spede/sys/types.h>
#include <spede/sys/cdefs.h>
#include <spede/stddef.h>		/* Get "size_t" typedef */

__BEGIN_DECLS

/****  From target/io.S  *****/

/**
 *	Get a byte/short/long from an I/O port.
 *
 *	@param port (in) input port.
 *	@return (unsigned) bits of Input data.
 */
extern unsigned	 inportb(unsigned port);
extern unsigned  inportw(unsigned port);
extern unsigned  inportl(unsigned port);

/**
 *	Store a byte/short/long to an I/O port.
 *
 *	@param port (in) output port.
 *	@param value (in) data value to write.
 *	@return (void)
 */
extern void	outportb(unsigned port, unsigned byte_val);
extern void	outportw(unsigned port, unsigned short_val);
extern void	outportl(unsigned port, unsigned long_val);


/**
 *	Read a bunch of 16-bit shorts from an I/O port.
 *
 *	@param port (in) input port.
 *	@param buffer (out) input values stored here.
 *	@param count (in) how many shorts to read.
 */
extern void	repinsw(unsigned port, uint16 * buffer, size_t count);

/**
 *	Write a bunch of 16-bit shorts to an I/O port.
 *
 *	@param port (in) input port.
 *	@param buffer (out) input values read from here.
 *	@param count (in) how many shorts to read.
 */
extern void	repoutsw(unsigned port, const uint16 * buffer, size_t count);

__END_DECLS

#endif
