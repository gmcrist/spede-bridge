/*   spede/machine/ps2mouse.h
 *	Definitions for PS/2 style fancy mouse pointing device.
 *	Mouse uses IRQ 12.
 *	@(#)ps2mouse.h	1.3   06/22/00
 */

#ifndef _INCL_MACHINE_PS2MOUSE_H
#define _INCL_MACHINE_PS2MOUSE_H

#include <spede/machine/keyboard.h>		/* Borrow bunch of defines */

/*  The mouse can be in stream or remote mode, or echo or not echoing mode.
 */

#define  PS2AUX_OUTBUF_FULL	(K_MOUSE_EVT | K_OUTBUF_FUL)
#define  PS2AUX_INBUF_FULL	(K_INBUF_FUL)

/*
 *	PS/2 mouse commands.
 */
#define  MC_RESET_SCALING	0xe6	/* Reset to 1:1 scaling factor */

#define  MC_SET_SCALING		0xe7	/* Set to 2:1 scaling factor */

#define  MC_SET_RESOLUTION	0xe8	/* Set counts/MM resolution */
/*  PUT.byte2 -> 00..03 for 1,2,4,8 counts/mm	*/

#define  MC_GET_STATUS		0xe9	/* Ask mouse for status byte */
/*  GET.byte1 <- status 	*/
#define  MSTAT_RMB		BIT(0)		/* right mouse button down */
#define  MSTAT_LMB		BIT(2)		/* left mouse button down */
#define  MSTAT_SCALE_2_1	BIT(4)		/* In 2:1 scaling */
#define  MSTAT_ENABLED		BIT(5)		/* Is enabled */
#define  MSTAT_POLLED		BIT(6)		/* Poll (not stream) mode */

#define  MC_SET_STREAM_MODE	0xea	/* Mouse to streaming data mode */

#define  MC_READ_PACKET		0xeb	/* Ask mouse for coordinates */
/*  GET.byte1..byte8 <- mouse data packet	*/

#define  MC_NOECHO_MODE		0xec	/* Mouse normal operation */

#define  MC_ECHO_MODE		0xee	/* Mouse echos back all bytes */

#define  MC_POLL_MODE	 	0xf0	/* Must ask explicitly for data */

#define  MC_IDENTIFY		0xf2	/* If PS/2 mouse sends 0x00 */
/*  GET.byte1 -> 0x00 (ps2 mouse)		*/

#define  MC_SET_SAMPLING	0xf3	/* Streaming samples/second */
/*  PUT.byte1 <- 10, 20, 40, 60, 80, 100, 200 samples/second */

#define  MC_STREAM_NOW		0xf4	/* Start streaming packets */

#define  MC_STREAM_STOP		0xf5	/* Stop streaming packets */

#define  MC_SET_DEFAULTS	0xf6	/* streaming mode, 100 samples/sec,
					 *  1:1, 4 counts/mm, not streaming */

#define  MC_RESEND		0xfe	/* Have mouse resned response byte */

#define  MC_RESET		0xff	/* internal reset, no resonse at all */

/* ------------------------------------------------------------------- */

/*
 *	PS/2 mouse responses. 
 */
#define  MR_IDENT		0x00
#define  MR_ACK  		0xFA
#define  MR_RESEND		0xFE


/* ------------------------------------------------------------------- */

/*  The short, 3 byte version.  An 8 byte version also exists. */
struct ps2_data_packet {
    uint8	left_button : 1;
    uint8	right_button : 1;
    uint8	middle_button : 1;
    uint8	_res_b3 : 1;		/* bit 3 is reserved */
    uint8	xneg : 1;
    uint8	yneg : 1;
    uint8	xover : 1;
    uint8	yover : 1;

    uint8	xmotion;	/* moved units since last packet */
    uint8	ymotion;
};


#define  MR_PACKET_SIZE 	3	/* sizeof(PS/2 mouse data packet) */

/*  Here is a quick way to read the mouse packet, if treated as 3 bytes.
 *  (Taken from src/mouse/ms.c in SVGALIB)
 */
#if 0
    case MOUSE_PS2:             /* PS/2 mouse */
        but = (buf[i] & 0x04) >> 1 |    /* Middle */
            (buf[i] & 0x02) >> 1 |      /* Right */
            (buf[i] & 0x01) << 2;       /* Left */
        dx = (buf[i] & 0x10) ? buf[i + 1] - 256 : buf[i + 1];
        dy = (buf[i] & 0x20) ? -(buf[i + 2] - 256) : -buf[i + 2];
        break;
#endif	/* code sample */


#endif
