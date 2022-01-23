/*   spede/machine/rs232.h
 *	@(#)rs232.h	1.5   01/24/01
 */

/*
 * rs232.h
 *	Defines for PC RS232 adaptor
 *
 * Derived from COM driver in FreeBSD, originally from the UC Regents
 * and the Berkeley Software Distribution.
 */
#ifndef _SPEDE_MACHINE_RS232_H
#define _SPEDE_MACHINE_RS232_H


/* --------------------------------------------------------------------- */

/*
 * Maximum range of I/O ports used
 */
#define RS232_HIGH(base) (base+7)

/*
 * 16 bit baud rate divisor (lower byte in dca_data, upper in dca_ier)
 */
#define	COMBRD(x)	(1843200 / (16*(x)))

/*
 * Parity constants
 */
#define PARITY_NONE	0x0
#define PARITY_EVEN	0x1
#define PARITY_ODD	0x2
#define PARITY_ZERO	0x3	
#define PARITY_ONE	0x4

/*
 * Receive/transmit data here, also baud low
 */
#define DATA (0)
#define BAUDLO (0)

/*
 * interrupt enable register, also baud high
 */
#define IER (1)
#define BAUDHI (1)
#define	IER_ERXRDY	0x1		/* Got a recieved char */
#define	IER_ETXRDY	0x2		/* Can accept one more xmit char */
#define	IER_ERLS	0x4		/* parity, framing or overrun error */
#define	IER_EMSC	0x8		/* change on CTS, DSR, DCD or RI */

/*
 * interrupt identification register (READ-ONLY)
 */
#define IIR (2)
#define	IIR_IMASK	0x0f
#define	IIR_RXTOUT	0x0c
#define	IIR_RLS		0x06
#define	IIR_RXRDY	0x04
#define	IIR_TXRDY	0x02
#define	IIR_NOPEND	0x01
#define	IIR_MLSC	0x00
#define	IIR_FIFO_MASK	0xc0	/* set if FIFOs are enabled */

/*
 * fifo control register (WRITE-ONLY)
 */
#define FIFO (2)
#define	FIFO_ENABLE	0x01
#define	FIFO_RCV_RESET	0x02
#define	FIFO_XMT_RESET	0x04
#define	FIFO_DMA_MODE	0x08
#define	FIFO_TRIGGER_1	0x00
#define	FIFO_TRIGGER_4	0x40
#define	FIFO_TRIGGER_8	0x80
#define	FIFO_TRIGGER_14	0xc0

/*
 * character format control register
 */
#define CFCR (3)
#define	CFCR_DLAB	0x80
#define	CFCR_SBREAK	0x40
#define	CFCR_PZERO	0x30
#define	CFCR_PONE	0x20
#define	CFCR_PEVEN	0x10
#define	CFCR_PODD	0x00
#define	CFCR_PENAB	0x08
#define	CFCR_2STOPB	0x04		/* Two stop bits */
#define	CFCR_8BITS	0x03
#define	CFCR_7BITS	0x02
#define	CFCR_6BITS	0x01
#define	CFCR_5BITS	0x00

/*
 * modem control register
 */
#define MCR (4)
#define	MCR_LOOPBACK	0x10
#define	MCR_IENABLE	0x08		/* OUT2 */
#define	MCR_DRS		0x04		/* OUT1 */
#define	MCR_RTS		0x02
#define	MCR_DTR		0x01

/*
 * line status register
 */
#define LSR (5)
#define	LSR_RCV_FIFO	0x80		/* B7: Any errors in RCVR FIFO? */
#define	LSR_TSRE	0x40		/* both XMIT FIFO and shift reg empty */
#define	LSR_TXRDY	0x20		/* B5: XMIT FIFO is empty */
#define	LSR_BI		0x10
#define	LSR_FE		0x08
#define	LSR_PE		0x04
#define	LSR_OE		0x02
#define	LSR_RXRDY	0x01
#define	LSR_RCV_MASK	0x1f

/*
 * modem status register
 */
#define MSR (6)
#define	MSR_DCD		0x80
#define	MSR_RI		0x40
#define	MSR_DSR		0x20
#define	MSR_CTS		0x10
#define	MSR_DDCD	0x08
#define	MSR_TERI	0x04
#define	MSR_DDSR	0x02
#define	MSR_DCTS	0x01

/*
 * Scrathpad register
 */
#define SCRATCH (7)

/*
 * UART types
 */
#define UART_UNKNOWN	-1
#define UART_8250	0
#define UART_16450	1
#define UART_16550	2
#define UART_16550A	3


/* -------------------------------------------------------------------- */

/*  Base I/O address for standard ports: */
#define  COM1_IOBASE	0x03F8
#define  COM2_IOBASE	0x02F8
#define  COM3_IOBASE	0x03E8
#define  COM4_IOBASE	0x02E8
#define  COM5_IOBASE	0x02F0
#define  COM6_IOBASE	0x03E0
#define  COM7_IOBASE	0x02E0
#define  COM8_IOBASE	0x0260


#endif /* _SPEDE_MACHINE_RS232_H */
