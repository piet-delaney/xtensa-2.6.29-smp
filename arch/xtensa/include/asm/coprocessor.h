/*
 * arch/xtensa/include/asm/coprocessor.h
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (C) 2003 - 2012 Tensilica Inc.
 */


#ifndef _XTENSA_COPROCESSOR_H
#define _XTENSA_COPROCESSOR_H

#include <linux/stringify.h>
#include <variant/tie.h>
#include <asm/types.h>

#ifdef __ASSEMBLY__
# include <variant/tie-asm.h>

/*
 * In generic parts of the kernel the registers for a core need to be saved and restored.
 * The classic case is the _switch_to() code in arch/xtensa/kernel/entry.S; which will invoke:
 *
 *	save_xtregs_user			[Generic - Defined below]
 *	load_xtregs_user			[Generic - Defined below]
 *
 * to save cores registers. These two functions are defined below but
 * need to invoke variant specific macros which know what registers the
 * variant has.
 *
 *	xchal_ncp_store				[Variant Specific]
 *	xchal_ncp_load				[Variant Specific]
 *
 * These variant specific macros are defined for each variant. For Example:
 *
 *	 variants/coh_232l/include/variant/tie-asm.h
 *
 * These variant specific macros make use of generic macros to start a load/store
 * save area and to align before saving or storing the variants registers. Ex:
 *
 *	xchal_sa_start				[Generic - Defined below]
 *	xchal_sa_align				[Generic - Defined below]
 *
 * Below we define the generic macros that will be used with the variant specific macros.
 */



/*
 *  Invoked at start of save area load/store sequence macro to setup macro
 *  internal offsets.  Not usually invoked directly.
 *
 *  Macro Parameters:
 *      continue        0 for 1st sequence, 1 for subsequent consecutive ones.
 *      totofs          offset from original ptr to next load/store location.
 */
.macro  xchal_sa_start  continue totofs
    .ifeq \continue
	.set   .Lxchal_pofs_, 0  	/* offset from original ptr to current \ptr */
	.set   .Lxchal_ofs_, 0         	/* offset from current \ptr to next load/store location */
    .endif

    .if \totofs + 1                 			/* if totofs specified (not -1) */
	.set   .Lxchal_ofs_, \totofs - .Lxchal_pofs_ 	/* specific offset from original ptr */
    .endif
.endm

/*
 *  Align portion of save area and bring ptr in range if necessary.
 *  Used by save area load/store sequences.  Not usually invoked directly.
 *  Allows combining multiple (sub-)sequences arbitrarily.
 *
 *  Macro Parameters:
 *      ptr             pointer to save area (may be off, see .Lxchal_pofs_)
 *      minofs,maxofs   range of offset from cur ptr to next load/store loc;
 *                      minofs <= 0 <= maxofs  (0 must always be valid offset)
 *                      range must be within +/- 30kB or so.
 *      ofsalign        alignment granularity of minofs .. maxofs (pow of 2)
 *                      (restriction on offset from ptr to next load/store loc)
 *      totalign        align from orig ptr to next load/store loc (pow of 2)
 *
 *  NOTE: Kept in sync with <xtensa_tools_root>/xtensa-elf/include/xtensa/config/core.h
 *        in Tensilica software tools; Ex: swtools-x86-linux.
 */
.macro  xchal_sa_align  ptr minofs maxofs ofsalign totalign
	/*
	 * First align where we start accessing the next register
	 * per \totalign relative to original ptr (i.e. start of the save area):
	 */
	.set	.Lxchal_ofs_, \
		((.Lxchal_pofs_ + .Lxchal_ofs_ + \totalign - 1) & -\totalign) - .Lxchal_pofs_

	/*
	 * If necessary, adjust \ptr to bring .Lxchal_ofs_ in acceptable range:
	 */
	.if (((\maxofs) - .Lxchal_ofs_) & 0xC0000000) | \
	    ((.Lxchal_ofs_ - (\minofs)) & 0xC0000000) | \
	    (.Lxchal_ofs_ & (\ofsalign-1))
		/* TODO: optimize to addmi, per aligns and .Lxchal_ofs_ */
		.set   .Ligmask, 0xFFFFFFFF
		addi   \ptr, \ptr, (.Lxchal_ofs_ & .Ligmask)
		.set   .Lxchal_pofs_, .Lxchal_pofs_ + (.Lxchal_ofs_ & .Ligmask)
		.set   .Lxchal_ofs_, (.Lxchal_ofs_ & ~.Ligmask)
	.endif
.endm



#define _SELECT	(  XTHAL_SAS_TIE | XTHAL_SAS_OPT \
		 | XTHAL_SAS_CC \
		 | XTHAL_SAS_CALR | XTHAL_SAS_CALE )

.macro save_xtregs_opt ptr clb at1 at2 at3 at4 offset
	.if XTREGS_OPT_SIZE > 0
		addi	\clb, \ptr, \offset
		xchal_ncp_store \clb \at1 \at2 \at3 \at4 select=_SELECT
	.endif
.endm

.macro load_xtregs_opt ptr clb at1 at2 at3 at4 offset
	.if XTREGS_OPT_SIZE > 0
		addi	\clb, \ptr, \offset
		xchal_ncp_load \clb \at1 \at2 \at3 \at4 select=_SELECT
	.endif
.endm
#undef _SELECT

#define _SELECT	(  XTHAL_SAS_TIE | XTHAL_SAS_OPT \
		 | XTHAL_SAS_NOCC \
		 | XTHAL_SAS_CALR | XTHAL_SAS_CALE | XTHAL_SAS_GLOB )

.macro save_xtregs_user ptr clb at1 at2 at3 at4 offset
	.if XTREGS_USER_SIZE > 0
		addi	\clb, \ptr, \offset
		xchal_ncp_store \clb \at1 \at2 \at3 \at4 select=_SELECT
	.endif
.endm

.macro load_xtregs_user ptr clb at1 at2 at3 at4 offset
	.if XTREGS_USER_SIZE > 0
		addi	\clb, \ptr, \offset
		xchal_ncp_load \clb \at1 \at2 \at3 \at4 select=_SELECT
	.endif
.endm
#undef _SELECT



#endif	/* __ASSEMBLY__ */

/*
 * XTENSA_HAVE_COPROCESSOR(x) returns 1 if coprocessor x is configured.
 *
 * XTENSA_HAVE_IO_PORT(x) returns 1 if io-port x is configured.
 *
 */

#define XTENSA_HAVE_COPROCESSOR(x)					\
	((XCHAL_CP_MASK ^ XCHAL_CP_PORT_MASK) & (1 << (x)))
#define XTENSA_HAVE_COPROCESSORS					\
	(XCHAL_CP_MASK ^ XCHAL_CP_PORT_MASK)
#define XTENSA_HAVE_IO_PORT(x)						\
	(XCHAL_CP_PORT_MASK & (1 << (x)))
#define XTENSA_HAVE_IO_PORTS						\
	XCHAL_CP_PORT_MASK

#ifndef __ASSEMBLY__


#if XCHAL_HAVE_CP

#define RSR_CPENABLE(x)	do {						  \
	__asm__ __volatile__("rsr %0," __stringify(CPENABLE) : "=a" (x)); \
	} while(0);
#define WSR_CPENABLE(x)	do {						  \
  	__asm__ __volatile__("wsr %0," __stringify(CPENABLE) "; rsync" 	  \
	    		     :: "a" (x));				  \
	} while(0);

#endif /* XCHAL_HAVE_CP */


/*
 * Additional registers.
 * We define three types of additional registers:
 *  ext: extra registers that are used by the compiler
 *  cpn: optional registers that can be used by a user application
 *  cpX: coprocessor registers that can only be used if the corresponding
 *       CPENABLE bit is set.
 */

#define XCHAL_SA_REG(list,cc,abi,type,y,name,z,align,size,...)	\
	__REG ## list (cc, abi, type, name, size, align)

#define __REG0(cc,abi,t,name,s,a)	__REG0_ ## cc (abi,name)
#define __REG1(cc,abi,t,name,s,a)	__REG1_ ## cc (name)
#define __REG2(cc,abi,type,...)		__REG2_ ## type (__VA_ARGS__)

#define __REG0_0(abi,name)
#define __REG0_1(abi,name)		__REG0_1 ## abi (name)
#define __REG0_10(name)	__u32 name;
#define __REG0_11(name)	__u32 name;
#define __REG0_12(name)

#define __REG1_0(name)	__u32 name;
#define __REG1_1(name)

#define __REG2_0(n,s,a)	__u32 name;
#define __REG2_1(n,s,a)	unsigned char n[s] __attribute__ ((aligned(a)));
#define __REG2_2(n,s,a) unsigned char n[s] __attribute__ ((aligned(a)));

typedef struct { XCHAL_NCP_SA_LIST(0) } xtregs_opt_t
	__attribute__ ((aligned (XCHAL_NCP_SA_ALIGN)));
typedef struct { XCHAL_NCP_SA_LIST(1) } xtregs_user_t
	__attribute__ ((aligned (XCHAL_NCP_SA_ALIGN)));

#if XTENSA_HAVE_COPROCESSORS

typedef struct { XCHAL_CP0_SA_LIST(2) } xtregs_cp0_t
	__attribute__ ((aligned (XCHAL_CP0_SA_ALIGN)));
typedef struct { XCHAL_CP1_SA_LIST(2) } xtregs_cp1_t
	__attribute__ ((aligned (XCHAL_CP1_SA_ALIGN)));
typedef struct { XCHAL_CP2_SA_LIST(2) } xtregs_cp2_t
	__attribute__ ((aligned (XCHAL_CP2_SA_ALIGN)));
typedef struct { XCHAL_CP3_SA_LIST(2) } xtregs_cp3_t
	__attribute__ ((aligned (XCHAL_CP3_SA_ALIGN)));
typedef struct { XCHAL_CP4_SA_LIST(2) } xtregs_cp4_t
	__attribute__ ((aligned (XCHAL_CP4_SA_ALIGN)));
typedef struct { XCHAL_CP5_SA_LIST(2) } xtregs_cp5_t
	__attribute__ ((aligned (XCHAL_CP5_SA_ALIGN)));
typedef struct { XCHAL_CP6_SA_LIST(2) } xtregs_cp6_t
	__attribute__ ((aligned (XCHAL_CP6_SA_ALIGN)));
typedef struct { XCHAL_CP7_SA_LIST(2) } xtregs_cp7_t
	__attribute__ ((aligned (XCHAL_CP7_SA_ALIGN)));
#if 1
typedef struct coprocessor_owner {
	struct thread_info *coprocessor_ti[XCHAL_CP_MAX];
} coprocessor_owner_t;

#else
extern DEFINE_PER_CPU(coprocessor_owner_t, coprocessor_owner);
extern struct thread_info* coprocessor_owner[XCHAL_CP_MAX];
#endif

extern void coprocessor_save(void*, int);
extern void coprocessor_load(void*, int);
extern void coprocessor_flush(struct thread_info*, int);
extern void coprocessor_restore(struct thread_info*, int);
extern void manage_coprocessors(void *, int);

/*
 * Commands passed to manage_coprocessor()
 */
#define CP_FLUSH_ALL			1	/* Flush All CP Registers to thread_info */
#define CP_RELEASE_ALL			2	/* Release Ownership of All Coprocessors */
#define CP_FLUSH_AND_RELEASE_ALL	3	/* Flush All CP Regs and Release Ownership of CP */
#define CP_SWITCH			4	/* Switching out, bind to CPU if not debugged */


static inline void coprocessor_clear_cpenable(void)
{
	unsigned long i = 0;
	WSR_CPENABLE(i);
}

static inline void coprocessor_set_cpenable(unsigned long cpenable)
{
	WSR_CPENABLE(cpenable);
}

static inline unsigned long coprocessor_get_cpenable(void)
{
	unsigned long cpenable;
	RSR_CPENABLE(cpenable);
	return cpenable;
}

#endif	/* XTENSA_HAVE_COPROCESSORS */

#endif	/* !__ASSEMBLY__ */
#endif	/* _XTENSA_COPROCESSOR_H */
