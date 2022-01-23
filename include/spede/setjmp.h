/* spede/setjmp.h   Non-local goto's */
/*	@(#)setjmp.h	1.2   06/21/00	*/

#ifndef	_SPEDE_SETJMP_H
#define	_SPEDE_SETJMP_H

#include <spede/sys/cdefs.h>

__BEGIN_DECLS

/*
 * array stored: EIP, EDI, ESI, EBP, ESP, EBX, EDX, ECX, EAX.
 *	9 * sizeof(REGISTER) --> 36 bytes.
 */
#define  _JBLEN   (9)

typedef	int 	jmp_buf[_JBLEN];


extern int	setjmp __P(( jmp_buf env ));
extern void	longjmp __P(( jmp_buf env, int val ));


#ifdef __GNUC__
/*
 * Routines that call setjmp have strange control flow graphs,
 * since a call to a routine that calls resume/longjmp will eventually
 * return at the setjmp site, not the original call site.  This
 * utterly wrecks control flow analysis.
 */
#pragma unknown_control_flow(sigsetjmp, setjmp, _setjmp)

/*
 * Using longjmp(), there is the additional problem that registers
 * are restored to their values at the time of the call to setjmp;
 * they should be set to their values at the time of the call to
 * whoever eventually called longjmp.  Thus, on routines that call
 * setjmp, automatic register allocation must be suppressed.
 */
#pragma makes_regs_inconsistent(sigsetjmp, setjmp, _setjmp)

#endif

__END_DECLS

#endif	/* if ! _SPEDE_SETJMP_H */

