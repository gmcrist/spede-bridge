/*   spede/stddef.h	Misc typedefs...	*/
/*	@(#)stddef.h	1.2   07/09/00	*/

#ifndef _SPEDE__STDDEF_H
#define _SPEDE__STDDEF_H

/* Signed type of difference of two pointers.  */

#ifndef _PTRDIFF_T	/* in case <sys/types.h> has defined it. */
#ifndef __PTRDIFF_T
#ifndef _PTRDIFF_T_
#ifndef ___int_ptrdiff_t_h
#define _PTRDIFF_T
#define __PTRDIFF_T
#define _PTRDIFF_T_
#define ___int_ptrdiff_t_h
typedef long ptrdiff_t;
#endif /* ___int_ptrdiff_t_h */
#endif /* _PTRDIFF_T_ */
#endif /* __PTRDIFF_T */
#endif /* _PTRDIFF_T */

/* Unsigned type of `sizeof' something.  */
/*  Must match definition in <spede/stdlib.h> */

#ifndef _SIZE_T	/* in case <sys/types.h> has defined it. */
    #ifndef __SIZE_T
        #ifndef _SIZE_T_
            #ifndef ___int_size_t_h
                #define _SIZE_T
                #define __SIZE_T
                #define _SIZE_T_
                #define ___int_size_t_h
                typedef unsigned int  size_t;
            #endif /* ___int_size_t_h */
        #endif /* _SIZE_T_ */
    #endif /* __SIZE_T */
#endif /* _SIZE_T */

/* Data type for wide chars.  */

#ifndef _WCHAR_T
#define _WCHAR_T
typedef int wchar_t;
#endif

/* A null pointer constant.  */

#undef NULL		/* in case <stdio.h> has defined it. */
#define NULL ((void *)0)

/* Offset of member MEMBER in a struct of type TYPE.  */

#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)

#endif /* _SPEDE__STDDEF_H */

