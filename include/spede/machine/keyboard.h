/*   spede/machine/keyboard.h
 *	Definitions for i386-AT keyboard
 *	@(#)keyboard.h	1.3   06/03/00
 */

#ifndef _INCL_MACHINE_KEYBOARD_H
#define _INCL_MACHINE_KEYBOARD_H

#include <spede/sys/cdefs.h>

/*
 * Common I/O ports.
 */
#define KIO_DATA 	0x60		/* keyboard data & cmds (read/write) */
#define KIO_CONTROL	0x61		/* r/w. speaker & status lines */
#define KIO_STATUS	0x64		/* keybd status (read-only) */
#define KIO_CMD 	0x64		/* keyboardd controller (write-only) */


/*
 * Bit definitions for KIO_STATUS port.
 */
#define K_OUTBUF_FUL	0x01            /* output (from keybd) buffer full */
#define K_INBUF_FUL	0x02            /* input (to keybd) buffer full */
#define K_SYSFLAG       0x04            /* "System Flag" (we're OK) */
#define K_CMD_DATA      0x08            /* 1 = input buf has cmd, 0 = data */
#define K_KBD_INHBT     0x10            /* 0 if keyboard inhibited */
#define K_MOUSE_EVT	0x20		/* Mouse activity on controller port */
#define K_TIMEOUT	0x40		/* Some general timeout occurred */
#define K_PARITY_ERR	0x80		/* Parity error on reception */

/*
 * Bit definitions for KIO_CONTROL port.
 */
#define  KEYBD_ENABLE	0x80		/* Tell control we want more! */


/* ------------------------------------------------------------------------ */

/*
 * Keyboard controller commands (sent to KIO_CMD port).
 */
#define KC_CMD_TEST     0xab            /* test interface */
#define KC_CMD_DISABLE	0xad            /* disable keyboard */
#define KC_CMD_ENABLE	0xae            /* enable keyboard */
#define KC_CMD_READ	0xd0		/* read controller command byte */
#define KC_CMD_WRITE	0xd1            /* write controller command byte */
#define KC_CMD_AUX_WRITE 0xd4		/* Write to mouse */

/*
 * Keyboard commands (send to KIO_DATA).
 */
#define K_CMD_LEDS      0xed            /* set status LEDs (caps lock, etc.) */
#define K_CMD_ECHO	0xee		/* used for diagnostic testing */
#define K_CMD_IDENT	0xf2		/* read keyboard ID */

/*
 * Bit definitions for controller command byte (sent following
 * K_CMD_WRITE command).
 */
#define K_CB_ENBLIRQ    0x01		/* enable data-ready intrpt */
#define K_CB_SETSYSF    0x04		/* Set System Flag */
#define K_CB_INHBOVR    0x08		/* Inhibit Override */
#define K_CB_DISABLE	0x10		/* disable keyboard */

/*
 * Bit definitions for "Indicator Status Byte" (sent after a
 * K_CMD_LEDS command).  If the bit is on, the LED is on.  Undefined
 * bit positions must be 0.
 */
#define K_LED_SCRLLK    0x1             /* scroll lock */
#define K_LED_NUMLK     0x2             /* num lock */
#define K_LED_CAPSLK    0x4             /* caps lock */

/*
 * Bit definitions for "Miscellaneous port B" (KIO_CONTROL).
 */
/* read/write */
#define K_ENABLETMR2    0x01            /* enable output from timer 2 */
#define K_SPKRDATA      0x02            /* direct input to speaker */
#define K_ENABLEPRTB    0x04            /* "enable" port B */
#define K_EIOPRTB       0x10		/* enable NMI on parity error */
#define K_RDKB		0x80		/* Want more keyboard data */
/* read-only */
#define K_REFRESHB      0x10            /* refresh flag from INLTCONT PAL */
#define K_OUT2B         0x20            /* timer 2 output */
#define K_ICKB          0x40            /* I/O channel check (parity error) */


/*
 * Scancode values, not to be confused with Ascii values.
 */

/* special codes */
#define K_UP            0x80            /* OR'd in if key below is released */
#define K_EXTEND        0xe0            /* prefix for "extended" sequence */
#define K_ACKSC         0xfa            /* ack of keyboard command */
#define K_RESEND        0xfe            /* request to resend keybd cmd */

/* modifier keys  */
#define K_CTLSC         0x1d            /* control down         */
#define K_LSHSC         0x2a            /* left shift down      */
#define K_RSHSC         0x36            /* right shift down     */
#define K_ALTSC         0x38            /* alt key down         */
#define K_CLCKSC        0x3a            /* caps lock            */
#define K_NLCKSC        0x45            /* num lock down        */


/*
 *   Function key scan codess, the "up" scancodes..  Function keys are
 *	numbered 1 to 12.
 */
#define  KUP_F(n)	(K_UP|((n)<=10 ? (n)-1+59 : (n)-11+87))
#define  KDOWN_F(n)	(((n)<=10 ? (n)-1+59 : (n)-11+87))

/* ---------------------------------------------------------------------- */

#ifndef ASSEMBLER

/*  User callbacks when a function key is pressed down.  The keyboard
 *  will auto-repeat it if held down a long time.
 */

__BEGIN_DECLS

extern void	_kbd_f1(void),  _kbd_f2(void),  _kbd_f3(void);
extern void	_kbd_f4(void),  _kbd_f5(void),  _kbd_f6(void);
extern void	_kbd_f7(void),  _kbd_f8(void),  _kbd_f9(void);
extern void	_kbd_f10(void), _kbd_f11(void), _kbd_f12(void);

__END_DECLS

#endif	/* ifndef ASSEMBLER */

#endif
