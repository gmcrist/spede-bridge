/*   spede/netinet/if_ether.h
 *	@(#)if_ether.h	1.3   06/29/00
 *	Definitions for an Ethernet interface (bwitt, June2000).
 */

#ifndef _SPEDE_NETINET_IF_ETHER_H
#define _SPEDE_NETINET_IF_ETHER_H

#include <spede/sys/types.h>
#include <spede/sys/cdefs.h>


/* --------------------------------------------------------------------- */


/*  An Ethernet address is 6 octets (bytes for American programmers).
 *	Available as a "type" or a structure.
 */
#define  ETHER_ADDR_LEN 	6
typedef uint8		ether_addr_t[ETHER_ADDR_LEN];

/*
 * The length of the combined header.
 */
#define	ETHER_HDR_LEN		(ETHER_ADDR_LEN*2+ETHER_TYPE_LEN)

struct ether_addr {
	uint8		octet[ETHER_ADDR_LEN];
};


/*  Structure of the 802.3 Ethernet header (14 bytes). */
struct ether_header {
	uint8			ether_dhost[ETHER_ADDR_LEN];
	uint8			ether_shost[ETHER_ADDR_LEN];
	ushort			ether_type;
};

#define ETHERTYPE_PUP		0x0200		/* PUP protocol */
#define ETHERTYPE_IP            0x0800          /* IP protocol */
#define ETHERTYPE_ARP           0x0806          /* Addr. resolution protocol */
#define ETHERTYPE_REVARP        0x8035          /* Reverse ARP */
#define ETHERTYPE_VLAN		0x8100		/* IEEE 802.1Q VLAN tag */

#define ETHER_MIN	60		/* Min frame w/header w/out FCS */
#define ETHER_MAX	1514		/* Max frame w/header w/out FCS */

/*  Is ethernet frame valid? (size includes 12 byte header) */
#define ETHER_IS_VALID_LEN(s)	(ETHER_MIN <= (s) && (s) <= ETHER_MAX)


/* --------------------------------------------------------------------- */

/*  Ethernet "data" can be at most 1500 bytes, plus 14 byte header.
 *   This size max is for ethernet payload size (between header and FCS).
 */
#define ETHERMTU	1500

/*  Declared here are the normal functions, plus some *re-entrant* versions.
 *	Generally, recursive version return -1 if error.
 */

__BEGIN_DECLS

/*  Convert 6 bytes of "e" into a string of "XX:XX:XX:XX:XX:XX" form.
 *	Buffer must be at least 36 bytes (6*4), recommend 48.
 */
extern char *	ether_ntoa(const struct ether_addr *e);
extern int	ether_ntoa_r(const struct ether_addr *e,
			     char * buff, int size_buff);

/*  Scan a "XX:XX:XX:XX:XX:XX" string producing 6 little bytes. */
extern struct ether_addr *	ether_aton(const char *xx);
extern int			ether_aton_r(const char *xx,
					     struct ether_addr *);


#define  ether_comp(a,b) 				\
		(((short *)a)[2] != ((short *)b)[2] || \
		 ((short *)a)[1] != ((short *)b)[1] || \
		 ((short *)a)[0] != ((short *)b)[0])

/*  BSD does this ala bcopy(), and moves left to right.  However, I model
 *  an ANSI C memcpy(), so it behaves and looks like an assignment.
 */
#define  ether_assign(d,s) 				\
		do { ((short *)d)[2] = ((short *)s)[2]; \
		     ((short *)d)[1] = ((short *)s)[1]; \
		     ((short *)d)[0] = ((short *)s)[0]; } while(0)

__END_DECLS

#endif
