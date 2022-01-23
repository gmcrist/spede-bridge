/*   spede/netinet/in.h
 *	@(#)in.h	1.4   12/31/00
 */
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
 */

/*
 * Constants and structures defined by the internet system,
 * Per RFC 790, September 1981.
 */

#ifndef _SPEDE_NETINET_IN_H
#define	_SPEDE_NETINET_IN_H

#include <spede/sys/types.h>
#include <spede/sys/cdefs.h>
#include <spede/machine/endian.h>

__BEGIN_DECLS

#ifndef _IN_PORT_T
#define	_IN_PORT_T
typedef	uint16	in_port_t;
#endif

#ifndef _IN_ADDR_T
#define	_IN_ADDR_T
typedef	uint32	in_addr_t;
#endif

#ifndef _IPADDR_T
#define	_IPADDR_T
typedef uint32	ipaddr_t;
#endif

#ifndef _SA_FAMILY_T
#define	_SA_FAMILY_T
typedef	unsigned short	sa_family_t;
#endif

/*
 * Protocols
 */
#define	IPPROTO_IP		0		/* dummy for IP */
#define	IPPROTO_ICMP		1		/* control message protocol */
#define	IPPROTO_IGMP		2		/* group control protocol */
#define	IPPROTO_GGP		3		/* gateway^2 (deprecated) */
#define	IPPROTO_ENCAP		4		/* IP in IP encapsulation */
#define	IPPROTO_TCP		6		/* tcp */
#define	IPPROTO_EGP		8		/* exterior gateway protocol */
#define	IPPROTO_PUP		12		/* pup */
#define	IPPROTO_UDP		17		/* user datagram protocol */
#define	IPPROTO_IDP		22		/* xns idp */
#define	IPPROTO_RSVP		46		/* rsvp */
#define	IPPROTO_HELLO		63		/* "hello" routing protocol */
#define	IPPROTO_ND		77		/* UNOFFICIAL net disk proto */
#define	IPPROTO_EON		80		/* ISO clnp */

#define	IPPROTO_RAW		255		/* raw IP packet */
#define	IPPROTO_MAX		256

/*
 * Port/socket numbers: network standard functions
 */
#define	IPPORT_ECHO		7
#define	IPPORT_DISCARD		9
#define	IPPORT_SYSTAT		11
#define	IPPORT_DAYTIME		13
#define	IPPORT_NETSTAT		15
#define	IPPORT_FTP		21
#define	IPPORT_TELNET		23
#define	IPPORT_SMTP		25
#define	IPPORT_TIMESERVER	37
#define	IPPORT_NAMESERVER	42
#define	IPPORT_WHOIS		43
#define	IPPORT_MTP		57
#define IPPORT_HTTP		80

/*
 * Port/socket numbers: host specific functions
 */
#define	IPPORT_BOOTPS		67
#define	IPPORT_BOOTPC		68
#define	IPPORT_TFTP		69
#define	IPPORT_RJE		77
#define	IPPORT_FINGER		79
#define	IPPORT_TTYLINK		87
#define	IPPORT_SUPDUP		95

/*
 * UNIX TCP sockets
 */
#define	IPPORT_EXECSERVER	512
#define	IPPORT_LOGINSERVER	513
#define	IPPORT_CMDSERVER	514
#define	IPPORT_EFSSERVER	520

/*
 * UNIX UDP sockets
 */
#define	IPPORT_BIFFUDP		512
#define	IPPORT_WHOSERVER	513
#define	IPPORT_ROUTESERVER	520	/* 520+1 also used */

/*
 * Ports < IPPORT_RESERVED are reserved for
 * privileged processes (e.g. root).
 * Ports > IPPORT_USERRESERVED are reserved
 * for servers, not necessarily privileged.
 */
#define	IPPORT_RESERVED		1024
#define	IPPORT_USERRESERVED	5000


/*
 * Internet address
 *	ALWAYS IN NETWORK BYTE ORDER !!!
 */

struct in_addr {
	in_addr_t	s_addr;	/* always in network byte order */
};

/*
 * Definitions of bits in internet address integers.
 * On subnets, the decomposition of addresses to host and net parts
 * is done according to subnet mask, not the masks here.
 */
#define	IN_CLASSA(i)		(((ipaddr_t)(i) & 0x80000000U) == 0)
#define	IN_CLASSA_NET		(ipaddr_t)0xff000000U
#define	IN_CLASSA_NSHIFT	24
#define	IN_CLASSA_HOST		(ipaddr_t)0x00ffffffU
#define	IN_CLASSA_MAX		128

#define	IN_CLASSB(i)		(((ipaddr_t)(i) & 0xc0000000U) == 0x80000000U)
#define	IN_CLASSB_NET		(ipaddr_t)0xffff0000U
#define	IN_CLASSB_NSHIFT	16
#define	IN_CLASSB_HOST		(ipaddr_t)0x0000ffffU
#define	IN_CLASSB_MAX		65536

#define	IN_CLASSC(i)		(((ipaddr_t)(i) & 0xe0000000U) == 0xc0000000U)
#define	IN_CLASSC_NET		(ipaddr_t)0xffffff00U
#define	IN_CLASSC_NSHIFT	8
#define	IN_CLASSC_HOST		(ipaddr_t)0x000000ffU

#define	IN_CLASSD(i)		(((ipaddr_t)(i) & 0xf0000000U) == 0xe0000000U)
#define	IN_CLASSD_NET		(ipaddr_t)0xf0000000U /* These aren't really  */
#define	IN_CLASSD_NSHIFT	28		  /* net and host fields, but */
#define	IN_CLASSD_HOST		(ipaddr_t)0x0fffffffU /* routing needn't know */
#define	IN_MULTICAST(i)		IN_CLASSD(i)

#define	IN_EXPERIMENTAL(i)	(((ipaddr_t)(i) & 0xe0000000U) == 0xe0000000U)
#define	IN_BADCLASS(i)		(((ipaddr_t)(i) & 0xf0000000U) == 0xf0000000U)

#define	INADDR_ANY		(ipaddr_t)0x00000000U
#define	INADDR_LOOPBACK		(ipaddr_t)0x7F000001U
#define	INADDR_BROADCAST	(ipaddr_t)0xffffffffU	/* must be masked */

#define	INADDR_UNSPEC_GROUP	(ipaddr_t)0xe0000000U	/* 224.0.0.0   */
#define	INADDR_ALLHOSTS_GROUP	(ipaddr_t)0xe0000001U	/* 224.0.0.1   */
#define	INADDR_ALLRTRS_GROUP	(ipaddr_t)0xe0000002U	/* 224.0.0.2   */
#define	INADDR_MAX_LOCAL_GROUP	(ipaddr_t)0xe00000ffU	/* 224.0.0.255 */

#define	IN_LOOPBACKNET		127			/* official! */

/*
 * Define a macro to stuff the loopback address into an Internet address
 */
#define	IN_SET_LOOPBACK_ADDR(a) \
	do { (a)->sin_addr.s_addr = htonl(INADDR_LOOPBACK); \
	     (a)->sin_family = AF_INET; } while(0)

/*
 * Socket address, internet style.
 */
struct sockaddr_in {
	sa_family_t	sin_family;
	in_port_t	sin_port;
	struct	in_addr sin_addr;
	unsigned char	sin_zero[8];
};

/*
 * Macros for number representation conversion now live in <sys/byteorder.h>.
 */

extern struct	in_addr in_makeaddr();
extern uint32_t	in_netof(), in_lnaof();

__END_DECLS

#endif	/* _SPEDE_NETINET_IN_H */

