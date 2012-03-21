
/*
 * arch/xtensa/machine/relocate_kernel.S
 *
 * Put the kernel image in place to boot.
 * NOTE: Very Preliminary.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (C) 2012 Tensilica Inc.
 *
 * Pete Delaney <piet@tensilica.com>
 */
#include <linux/linkage.h>
#include <asm/page.h>
#include <asm/pgtable.h>
#include <asm/asmmacro.h>
#include <asm/cacheasm.h>
#include <asm/tlbflush.h>
#include <asm/kexec.h>

	.globl relocate_new_kernel

/*
 * relocate_new_kernel(unsigned long, unsigned long, struct boot_param *, unsigned long);
 */
ENTRY(relocate_new_kernel)
	entry   a1, 16

	retw

	.globl kexec_start_address
kexec_start_address:
	.long	0x0

	.globl kexec_indirection_page
kexec_indirection_page:
	.long	0x0

	.globl kexec_mach_type
kexec_mach_type:
	.long	0x0

	/* phy addr of the atags for the new kernel */
	.globl kexec_boot_atags
kexec_boot_atags:
	.long	0x0

relocate_new_kernel_end:

	.globl relocate_new_kernel_size
relocate_new_kernel_size:
	.long relocate_new_kernel_end - relocate_new_kernel


