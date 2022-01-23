/*   include/spede/netinet/tcp.h
 *	@(#)arp.h	1.1   07/02/00
 *	ARP structures.
 */

#ifndef _SPEDE_NETINET_ARP_H
#define _SPEDE_NETINET_ARP_H

#include <spede/netinet/if_ether.h>
#include <spede/netinet/in.h>

#pragma pack(2)

/*  Sent at Ethernet level, no IP */
typedef struct
{
    uint16 	arp_hard_type;
    uint16 	arp_prot_type;
    uint8  	arp_hard_size;
    uint8  	arp_prot_size;
    uint16 	arp_op;
    uint8  	arp_enet_sender[ETHER_ADDR_LEN];
    in_addr_t 	arp_ip_sender;
  /*  MUST PACK HERE */
    uint8  	arp_enet_target[ETHER_ADDR_LEN];
    in_addr_t	arp_ip_target;
} NET_ARP;


#define ARP_OP_REQUEST  1
#define ARP_OP_REPLY    2
#define RARP_OP_REQUEST 3
#define RARP_OP_REPLY   4


#endif
