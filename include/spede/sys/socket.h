/*   spede/include/sys/socket.h
 *   @(#)socket.h	1.1   07/02/00
 *	Global "socket" options.
 */

#ifndef _SPEDE_INCLUDE_SYS_SOCKET_H
#define _SPEDE_INCLUDE_SYS_SOCKET_H

/*
 * Address families.
 */
#define	AF_UNSPEC	0		/* unspecified */
#define	AF_UNIX		1		/* local to host (pipes, portals) */
#define	AF_INET		2		/* internetwork: UDP, TCP, etc. */

#define	AF_MAX		2		/* (last item actually defined) */

/*
 * Protocol families, same as address families for now.
 */
#define	PF_UNSPEC	AF_UNSPEC
#define	PF_UNIX		AF_UNIX
#define	PF_INET		AF_INET

#define PF_MAX		(AF_MAX)


#endif
