/*   include/spede/netinet/udp.h
 *	@(#)udp.h	1.1   07/02/00
 *	UDP (RFC 768) structures.
 */

#ifndef _SPEDE_NETINET_UDP_H
#define _SPEDE_NETINET_UDP_H


#include <spede/netinet/in.h>			/* Get some types. */
#include <spede/netinet/ip.h>


typedef struct {
    uint16_t	uh_src;			/* source port */
    uint16_t	uh_dest;		/* destination port */
    uint16_t	uh_len; 		/* UDP byte size */
    uint16_t	uh_sum;		/* Packet checksum */
} NET_UDP;


typedef struct {
    NET_IP	ip;
    NET_UDP	udp;
} UDP_PACKET;

#endif
