/*   sys/ascii.h   ASCII characetr defines.          bwitt, June 1998 */
/*	@(#)ascii.h	1.4   01/24/01	*/

#ifndef _INCL_SYS_ASCII
#define _INCL_SYS_ASCII


/* ascii defines */
#define  CH_NUL 	0x00
#define  CH_SOH 	0x01		/* ^A */
#define  CH_STX 	0x02		/* ^B */
#define  CH_ETX 	0x03		/* ^C */
#define  CH_EOT 	0x04		/* ^D */
#define  CH_ENQ 	0x05		/* ^E */
#define  CH_ACK 	0x06		/* ^F */
#define  CH_BEL 	0x07		/* ^G */
#define  CH_BELL	0x07
#define  CH_BS  	0x08		/* ^H */
#define  CH_HT  	0x09		/* ^I */
#define  CH_NL  	0x0a		/* ^J */
#define  CH_LF  	0x0a
#define  CH_VT  	0x0b		/* ^K */
#define  CH_NP  	0x0c		/* ^L */
#define  CH_CR  	0x0d		/* ^M */
#define  CH_SO  	0x0e		/* ^N */
#define  CH_SI  	0x0f		/* ^O */
#define  CH_DLE  	0x10		/* ^P */
#define  CH_DC1  	0x11		/* ^Q - XON */
#define  CH_DC2  	0x12		/* ^R */
#define  CH_DC3  	0x13		/* ^S - XOFF */
#define  CH_DC4  	0x14		/* ^T */
#define  CH_NAK  	0x15		/* ^U */
#define  CH_SYN  	0x16		/* ^V */
#define  CH_ETB  	0x17		/* ^W */
#define  CH_CAN  	0x18		/* ^X */
#define  CH_EM   	0x19		/* ^Y */
#define  CH_SUB  	0x1a		/* ^Z */
#define  CH_ESC 	0x1b		/* ^[ */
#define  CH_FS  	0x1c		/* ^\ */
#define  CH_GS  	0x1d		/* ^] */
#define  CH_RS  	0x1e		/* ^^ */
#define  CH_US  	0x1f		/* ^_ */
#define  CH_DEL 	0x7f


#define  CH_NEWLINE    ('\n')
#define  CH_RETURN     ('\r')
#define  CH_RET	       CH_RETURN
#define  CH_BACKSPACE  (0x08)
#define  CH_ESCAPE     (0x1b)
#define  CH_SPACE      (' ')
#define  CH_CARET	('^')
#define  CH_QMARK      ('?')

#endif

/* end spede/sys/ascii.h */

