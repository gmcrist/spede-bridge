/*   spede/sys/elf_common.h
 *	ELF binary file formatting...
 *	From FreeBSD 3.1, from "sys/sys/include/elf.h"
 *	@(#)elf_common.h	1.1   07/02/00
 */

/*-
 * Copyright (c) 1998 John D. Polstra.
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
 *      $Id: elf_common.h,v 1.3 1998/09/14 20:30:13 jdp Exp $
 */

#ifndef _SYS_ELF_COMMON_H_
#define _SYS_ELF_COMMON_H_ 1

/*
 * ELF definitions that are independent of architecture or word size.
 */

/* Indexes into the e_ident array. */
#define EI_MAG0		0	/* Magic number, byte 0. */
#define EI_MAG1		1	/* Magic number, byte 1. */
#define EI_MAG2		2	/* Magic number, byte 2. */
#define EI_MAG3		3	/* Magic number, byte 3. */
#define EI_CLASS	4	/* Class of machine. */
#define EI_DATA		5	/* Data format. */
#define EI_VERSION	6	/* ELF format version. */
#define EI_PAD		7	/* Start of padding (per SVR4 ABI). */
#define EI_BRAND	8	/* Start of architecture identification. */
#define EI_NIDENT	16	/* Size of e_ident array. */

/* Values for the magic number bytes. */
#define ELFMAG0		0x7f
#define ELFMAG1		'E'
#define ELFMAG2		'L'
#define ELFMAG3		'F'

/* Values for e_ident[EI_VERSION] and e_version. */
#define EV_NONE		0
#define EV_CURRENT	1

/* Values for e_ident[EI_CLASS]. */
#define ELFCLASSNONE	0	/* Unknown class. */
#define ELFCLASS32	1	/* 32-bit architecture. */
#define ELFCLASS64	2	/* 64-bit architecture. */

/* Values for e_ident[EI_DATA]. */
#define ELFDATANONE	0	/* Unknown data format. */
#define ELFDATA2LSB	1	/* 2's complement little-endian. */
#define ELFDATA2MSB	2	/* 2's complement big-endian. */

/* e_ident */
#define IS_ELF(ehdr)	((ehdr).e_ident[EI_MAG0] == ELFMAG0 && \
			 (ehdr).e_ident[EI_MAG1] == ELFMAG1 && \
			 (ehdr).e_ident[EI_MAG2] == ELFMAG2 && \
			 (ehdr).e_ident[EI_MAG3] == ELFMAG3)

/* Values for e_type. */
#define ET_NONE		0	/* Unknown type. */
#define ET_REL		1	/* Relocatable. */
#define ET_EXEC		2	/* Executable. */
#define ET_DYN		3	/* Shared object. */
#define ET_CORE		4	/* Core file. */

/* Values for e_machine. */
#define EM_NONE		0	/* Unknown machine. */
#define EM_M32		1	/* AT&T WE32100. */
#define EM_SPARC	2	/* Sun SPARC. */
#define EM_386		3	/* Intel i386. */
#define EM_68K		4	/* Motorola 68000. */
#define EM_88K		5	/* Motorola 88000. */
#define EM_486		6	/* Intel i486. */
#define EM_860		7	/* Intel i860. */
#define EM_MIPS		8	/* MIPS R3000 Big-Endian only */

/* Extensions */
#define EM_MIPS_RS4_BE	10	/* MIPS R4000 Big-Endian */
#define EM_SPARC64	11	/* SPARC v9 64-bit unoffical */
#define EM_PARISC	15	/* HPPA */
#define EM_PPC		20	/* PowerPC */
#define EM_ALPHA	0x9026	/* Alpha */

/* Special section indexes. */
#define SHN_UNDEF	     0		/* Undefined, missing, irrelevant. */
#define SHN_LORESERVE	0xff00		/* First of reserved range. */
#define SHN_LOPROC	0xff00		/* First processor-specific. */
#define SHN_HIPROC	0xff1f		/* Last processor-specific. */
#define SHN_ABS		0xfff1		/* Absolute values. */
#define SHN_COMMON	0xfff2		/* Common data. */
#define SHN_HIRESERVE	0xffff		/* Last of reserved range. */

/* sh_type */
#define SHT_NULL	0		/* inactive */
#define SHT_PROGBITS	1		/* program defined information */
#define SHT_SYMTAB	2		/* symbol table section */
#define SHT_STRTAB	3		/* string table section */
#define SHT_RELA	4		/* relocation section with addends*/
#define SHT_HASH	5		/* symbol hash table section */
#define SHT_DYNAMIC	6		/* dynamic section */ 
#define SHT_NOTE	7		/* note section */
#define SHT_NOBITS	8		/* no space section */
#define SHT_REL		9		/* relation section without addends */
#define SHT_SHLIB	10		/* reserved - purpose unknown */
#define SHT_DYNSYM	11		/* dynamic symbol table section */ 
#define SHT_LOPROC	0x70000000	/* reserved range for processor */
#define SHT_HIPROC	0x7fffffff	/* specific section header types */
#define SHT_LOUSER	0x80000000	/* reserved range for application */
#define SHT_HIUSER	0xffffffff	/* specific indexes */

/* Flags for sh_flags. */
#define SHF_WRITE	0x1		/* Section contains writable data. */
#define SHF_ALLOC	0x2		/* Section occupies memory. */
#define SHF_EXECINSTR	0x4		/* Section contains instructions. */
#define SHF_MASKPROC	0xf0000000	/* Reserved for processor-specific. */

/* Values for p_type. */
#define PT_NULL		0	/* Unused entry. */
#define PT_LOAD		1	/* Loadable segment. */
#define PT_DYNAMIC	2	/* Dynamic linking information segment. */
#define PT_INTERP	3	/* Pathname of interpreter. */
#define PT_NOTE		4	/* Auxiliary information. */
#define PT_SHLIB	5	/* Reserved (not used). */
#define PT_PHDR		6	/* Location of program header itself. */

#define PT_COUNT	7	/* Number of defined p_type values. */

#define PT_LOPROC	0x70000000	/* First processor-specific type. */
#define PT_HIPROC	0x7fffffff	/* Last processor-specific type. */

/* Values for p_flags. */
#define PF_X		0x1	/* Executable. */
#define PF_W		0x2	/* Writable. */
#define PF_R		0x4	/* Readable. */

/* Values for d_tag. */
#define DT_NULL		0	/* Terminating entry. */
#define DT_NEEDED	1	/* String table offset of a needed shared
				   library. */
#define DT_PLTRELSZ	2	/* Total size in bytes of PLT relocations. */
#define DT_PLTGOT	3	/* Processor-dependent address. */
#define DT_HASH		4	/* Address of symbol hash table. */
#define DT_STRTAB	5	/* Address of string table. */
#define DT_SYMTAB	6	/* Address of symbol table. */
#define DT_RELA		7	/* Address of ElfNN_Rela relocations. */
#define DT_RELASZ	8	/* Total size of ElfNN_Rela relocations. */
#define DT_RELAENT	9	/* Size of each ElfNN_Rela relocation entry. */
#define DT_STRSZ	10	/* Size of string table. */
#define DT_SYMENT	11	/* Size of each symbol table entry. */
#define DT_INIT		12	/* Address of initialization function. */
#define DT_FINI		13	/* Address of finalization function. */
#define DT_SONAME	14	/* String table offset of shared object
				   name. */
#define DT_RPATH	15	/* String table offset of library path. */
#define DT_SYMBOLIC	16	/* Indicates "symbolic" linking. */
#define DT_REL		17	/* Address of ElfNN_Rel relocations. */
#define DT_RELSZ	18	/* Total size of ElfNN_Rel relocations. */
#define DT_RELENT	19	/* Size of each ElfNN_Rel relocation. */
#define DT_PLTREL	20	/* Type of relocation used for PLT. */
#define DT_DEBUG	21	/* Reserved (not used). */
#define DT_TEXTREL	22	/* Indicates there may be relocations in
				   non-writable segments. */
#define DT_JMPREL	23	/* Address of PLT relocations. */

#define DT_COUNT	24	/* Number of defined d_tag values. */

/* Values for n_type.  Used in core files. */
#define NT_PRSTATUS	1	/* Process status. */
#define NT_FPREGSET	2	/* Floating point registers. */
#define NT_PRPSINFO	3	/* Process state info. */

/* Symbol Binding - ELFNN_ST_BIND - st_info */
#define STB_LOCAL	0	/* Local symbol */
#define STB_GLOBAL	1	/* Global symbol */
#define STB_WEAK	2	/* like global - lower precedence */
#define STB_LOPROC	13	/* reserved range for processor */
#define STB_HIPROC	15	/*  specific symbol bindings */

/* Symbol type - ELFNN_ST_TYPE - st_info */
#define STT_NOTYPE	0	/* Unspecified type. */
#define STT_OBJECT	1	/* Data object. */
#define STT_FUNC	2	/* Function. */
#define STT_SECTION	3	/* Section. */
#define STT_FILE	4	/* Source file. */
#define STT_LOPROC	13	/* reserved range for processor */
#define STT_HIPROC	15	/*  specific symbol types */

/* Special symbol table indexes. */
#define STN_UNDEF	0	/* Undefined symbol index. */

#endif /* !_SYS_ELF_COMMON_H_ */
