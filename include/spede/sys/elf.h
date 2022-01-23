/*   spede/sys/elf.h
 *	ELF binary file formatting...
 *	From FreeBSD 3.1, from "sys/sys/include/elf.h"
 *	@(#)elf.h	1.2   12/31/00
 */

/*-
 * Copyright (c) 1996-1998 John D. Polstra.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *      $Id: elf32.h,v 1.5 1998/09/14 20:30:13 jdp Exp $
 */

#ifndef _INCL_SPEDE_SYS_ELF_H
#define _INCL_SPEDE_SYS_ELF_H

#include <spede/sys/types.h>
#include <spede/sys/elf_common.h>


/*
 * ELF definitions common to all 32-bit architectures.
 */

typedef uint32		Elf32_Addr;
typedef uint16		Elf32_Half;
typedef uint32		Elf32_Off;
typedef int32		Elf32_Sword;
typedef uint32		Elf32_Word;
typedef uint32		Elf32_Size;

/*
 * ELF header.  (size=52 bytes, 0x34)
 */
typedef struct {
        unsigned char   e_ident[EI_NIDENT];     /* File identification. */

        Elf32_Half      e_type;         /* (+16) File type. */
        Elf32_Half      e_machine;      /* Machine architecture. */
        Elf32_Word      e_version;      /* ELF format version. */
        Elf32_Addr      e_entry;        /* Entry point. */
        Elf32_Off       e_phoff;        /* Program header file offset. */

        Elf32_Off       e_shoff;        /* (+32) Section header file offset. */
        Elf32_Word      e_flags;        /* Architecture-specific flags. */
        Elf32_Half      e_ehsize;       /* Size of ELF header in bytes. */
        Elf32_Half      e_phentsize;    /* Size of program header entry. */
        Elf32_Half      e_phnum;        /* Number of program header entries. */
        Elf32_Half      e_shentsize;    /* Size of section header entry. */

        Elf32_Half      e_shnum;        /* (+48) Number section header entries. */
        Elf32_Half      e_shstrndx;     /* Section name strings section. */
} Elf32_Ehdr;

/*
 * Section header. (size=40 bytes, 0x38)
 */

typedef struct {
        Elf32_Word      sh_name;        /* Section name (index into the
                                           section header string table). */
        Elf32_Word      sh_type;        /* Section type. */
        Elf32_Word      sh_flags;       /* Section flags. */
        Elf32_Addr      sh_addr;        /* Address in memory image. */
        Elf32_Off       sh_offset;      /* Offset in file. */
        Elf32_Size      sh_size;        /* Size in bytes. */
        Elf32_Word      sh_link;        /* Index of a related section. */
        Elf32_Word      sh_info;        /* Depends on section type. */
        Elf32_Size      sh_addralign;   /* Alignment in bytes. */
        Elf32_Size      sh_entsize;     /* Size of each entry in section. */
} Elf32_Shdr;

/*
 * Program header. (size=32 bytes, 0x30)
 */

typedef struct {
        Elf32_Word      p_type;         /* Entry type. */
        Elf32_Off       p_offset;       /* File offset of contents. */
        Elf32_Addr      p_vaddr;        /* Virtual address in memory image. */
        Elf32_Addr      p_paddr;        /* Physical address (not used). */
        Elf32_Size      p_filesz;       /* Size of contents in file. */
        Elf32_Size      p_memsz;        /* Size of contents in memory. */
        Elf32_Word      p_flags;        /* Access permission flags. */
        Elf32_Size      p_align;        /* Alignment in memory and file. */
} Elf32_Phdr;


#endif
