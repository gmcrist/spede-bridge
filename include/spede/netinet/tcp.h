/*   include/spede/netinet/tcp.h
 *	%W%   %G%
 *	TCP (RFC 793) structures.  Based on FreeBSD 3.1 source.
 */

#ifndef _SPEDE_NETINET_TCP_H
#define _SPEDE_NETINET_TCP_H


#include <spede/netinet/in.h>			/* Get some types. */
#include <spede/netinet/ip.h>
#include <spede/flames.h>			/* For BIT() macro */


typedef u_int32_t	tcp_seq;

typedef struct {
    u_short	th_sport;		/* Source port */
    u_short	th_dport;		/* Destination port */
    tcp_seq	th_seq;			/* Our sequence number */
    tcp_seq	th_ack;			/* How far acknowledged */
    u_char	th_off;			/* 4 bits: Data offset (lwords) */
    u_char	th_flags;
# define  TH_FIN	BIT(0)
# define  TH_SYN	BIT(1)
# define  TH_RST	BIT(2)
# define  TH_PUSH	BIT(3)
# define  TH_ACK	BIT(4)
# define  TH_URG	BIT(5)
# define  TH_FLAGS	(TH_FIN|TH_SYN|TH_RST|TH_ACK|TH_URG)

    u_short	th_win;			/* Our window size */
    u_short	th_sum;			/* Packet checksum */
    u_short	th_urp;			/* Urgent pointer (offset) */
} NET_TCP;


/*  TCP Options codes: */
#define TCPOPT_EOL              0	/* End of List */
#define TCPOPT_NOP              1	/* Spacing filling no-op */
#define TCPOPT_MAXSEG           2	/* Maximum Segment Size to receive */
#define    TCPOLEN_MAXSEG	  4
#define TCPOPT_WINDOW           3	/* Largest window size */
#define    TCPOLEN_WINDOW	  3

#if 0
/*  APPLICAITON MUST DEFINE THESE VALUES! (bwitt, July 200)
 *  I got weird and redefined these values in <23-NoseX/pubnet.h>
 */
/*
 *	User settable options.
 */
#define	TCP_NODELAY	0x01	/* don't delay send to coalesce packets */
#define	TCP_MAXSEG	0x02	/* set maximum segment size */
#define TCP_NOPUSH	0x04	/* don't push last block of write */
#define TCP_NOOPT	0x08	/* don't use TCP options */
#endif

#endif
