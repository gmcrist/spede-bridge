/*   spede/netinet/media.h
 *	Media header types... not really IP and not really solely Ethernet.
 *	%W%   %G%
 *	--- 18/my905b/media.h,v 1.1 2000/02/10 19:39:07 aleks Exp --
 *
 *	Based on the file "sys/net/if_media.h" from FreeBSD 3.1
 */

#ifndef _SPEDE_NETINET_MEDIA_H
#define _SPEDE_NETINET_MEDIA_H

/*
 * Ethernet
 */
#define IFM_ETHER       0x00000020
#define IFM_10_T        3               /* 10BaseT - RJ45 */
#define IFM_10_2        4               /* 10Base2 - Thinnet */
#define IFM_10_5        5               /* 10Base5 - AUI */
#define IFM_100_TX      6               /* 100BaseTX - RJ45 */
#define IFM_100_FX      7               /* 100BaseFX - Fiber */
#define IFM_100_T4      8               /* 100BaseT4 - 4 pair cat 3 */
#define IFM_100_VG      9               /* 100VG-AnyLAN */
#define IFM_100_T2      10              /* 100BaseT2 */

/*
 * Shared options (& IFM_GMASK)
 */
#define IFM_FDX         0x00100000      /* Force full duplex */
#define IFM_HDX         0x00200000      /* Force half duplex */
#define IFM_FLAG0       0x01000000      /* Driver defined flag */
#define IFM_FLAG1       0x02000000      /* Driver defined flag */
#define IFM_FLAG2       0x04000000      /* Driver defined flag */
#define IFM_LOOP        0x08000000      /* Put hardware in loopback */

/*
 * Masks
 */
#define IFM_NMASK       0x000000e0      /* Network type */
#define IFM_TMASK       0x0000000f      /* Media sub-type */
#define IFM_IMASK       0xf0000000      /* Instance */
#define IFM_ISHIFT      28              /* Instance shift */
#define IFM_OMASK       0x0000ff00      /* Type specific options */
#define IFM_GMASK       0x0ff00000      /* Global options */

/*
 * Macros to extract various bits of information from the media word.
 */
#define IFM_TYPE(x)     ((x) & IFM_NMASK)
#define IFM_SUBTYPE(x)  ((x) & IFM_TMASK)
#define IFM_INST(x)     (((x) & IFM_IMASK) >> IFM_ISHIFT)


#endif

