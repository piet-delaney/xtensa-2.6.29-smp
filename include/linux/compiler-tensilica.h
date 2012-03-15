#ifndef __LINUX_COMPILER_H
#error "Please don't include <linux/compiler-tensilica.h> directly, include <linux/compiler.h> instead."
#endif

#ifdef __XCC__
/* 
 * Some compiler specific definitions are overwritten here
 * for Tensilica XCC compiler and associated linker. Currenty
 * only CPP stuff is being used so it can all be #included
 * into both C and asm code.
 */

/*
 * Compiler Workarounds:
 *   Enabled based on XCC Version Numbers visible by doing:
 *	'xt-xcc -v foo.c'
 *	'xt-xcc -version'
 */

#if (__XCC__ < 9000)
/* Boreal Release, Rev C,  doesn't suppport ' __attribute__((no_instrument_function)' */
#undef notrace
#define notrace
#endif 

/*
 * Prior to Rev. D.2, (Cottonwood.2), XCC used boolean registers in unoptimized code 
 * involving simple constant expressions; See Tensilica Problem Report 22651. This
 * enables a workaround in entry.S that causes the exception handler save and
 * restore boolean registers if they exist for the current config/varriant.
 */
#if  (__XCC__ < 9000) || ( (__XCC__ == 9000) && (__XCC_MINOR__ < 2))
 #define XTENSA_XCC_WORKAROUND_22651_ENABLED
#endif

/* Workarounds that can be dropped after D.4 */
#if  (__XCC__ < 9000) || ( (__XCC__ == 9000) && (__XCC_MINOR__ < 4))
#define XTENSA_XCC_WORKAROUND_19701_ENABLED	"xt-ld Relaxation issue in entry.S"
#define XTENSA_XCC_WORKAROUND_22415_ENABLED     "xcc optimization requires weak functions in init.c"
#endif

/*
 * The following are Open Problem Reports (PR), when they are fixed these workarounds
 * will be disabled for the current and subsequent versions of XCC. These #defines are
 * used by C code and the equilavent Makefile workarounds are enabled in the Xtensa kernel 
 * Makefile files (arch/xtensa/Makefile) based on the current versions of the xtensa tools.
 */
#define XTENSA_XCC_WORKAROUND_22663_ENABLED	"libctc32.c variable type in struct member"
#define XTENSA_XCC_WORKAROUND_22679_ENABLED	"IP V6 addrlabel.c ip6addrlbl_init_table implicit literals"
#define XTENSA_XCC_WORKAROUND_23816_ENABLED	"A few Weak functions still required in init.c not fixed by PR:22415"

#endif /* __XCC__ */
