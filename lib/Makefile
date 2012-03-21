#
# Makefile for some libs needed in the kernel.
#

ifdef CONFIG_USE_XTENSA_XCC_COMPILER
#
# WORKAROUND for XCC Optimization Bugs when compiling -O3:
# =========================================================
#
# CONFIG_XTENSA_ALT_EXTRA_CFLAGS can be set -O2 when  CONFIG_XTENSA_EXTRA_CFLAGS
# is set to -O3 to allow most of the kernel code to be compiled -O3 and a few
# functions like those below to be compiled -O2 till the XCC bugs are resolved.
#
# PROBLEMS:
# --------
#
#  1. vsprintf.o:
#	sprintf(name, "%d", irq) fails here:
#		Line: 935                         end[-1] = '\0';
#
#	This 'overoptimization' can be avoided eventually by XCC supporting
#	the new:
#
#		-fno-strict-overflow
#
#	option available in recient GCC compilers.
#
#	As a workaround we can limit the optimization level to -O2 via
#	XTENSA_ALT_EXTRA_CFLAGS declared in the kernel .config file.
#
#       See Problem Report: 22630
#
#
#  2. libcrc32c.c:
#	 error: a member of a structure or union cannot have a variably modified type
#	 See libcrc32c.c for current workaround.
#
#	 See Problem Report: 22663
#
#
# EXTRA_CFLAGS += -O2
# CFLAGS_vsprintf.o = -O0
# CFLAGS_vsprintf.o = -save-temps
# FLAGS_libcrc32c.o = -save-temps

XTENSA_ALT_EXTRA_CFLAGS := $(strip $(subst ",,$(CONFIG_XTENSA_ALT_EXTRA_CFLAGS)))#")))

# XTENSA_XCC_WORKAROUND_22630_ENABLED - has been resolved as of xcc-9.0.4 (09004)
# CFLAGS_vsprintf.o += $(call xcc-ifversion, -lt, 9004,  $(XTENSA_ALT_EXTRA_CFLAGS))
CFLAGS_vsprintf.o += $(call xcc-ifversion, -lt, 9004,  -OPT:fold_ag=0)
CFLAGS_vsprintf.o += $(call xcc-ifversion, -ge, 9004,  -fno-strict-overflow)

endif


ifdef CONFIG_FUNCTION_TRACER
ORIG_CFLAGS := $(KBUILD_CFLAGS)
KBUILD_CFLAGS = $(subst -pg,,$(ORIG_CFLAGS))
endif

lib-y := ctype.o string.o vsprintf.o cmdline.o \
	 rbtree.o radix-tree.o dump_stack.o \
	 idr.o int_sqrt.o extable.o prio_tree.o \
	 sha1.o irq_regs.o reciprocal_div.o argv_split.o \
	 proportions.o prio_heap.o ratelimit.o show_mem.o is_single_threaded.o

lib-$(CONFIG_MMU) += ioremap.o
lib-$(CONFIG_SMP) += cpumask.o

lib-y	+= kobject.o kref.o klist.o

obj-y += bcd.o div64.o sort.o parser.o halfmd4.o debug_locks.o random32.o \
	 bust_spinlocks.o hexdump.o kasprintf.o bitmap.o scatterlist.o \
	 string_helpers.o

ifeq ($(CONFIG_DEBUG_KOBJECT),y)
CFLAGS_kobject.o += -DDEBUG
CFLAGS_kobject_uevent.o += -DDEBUG
endif

lib-$(CONFIG_HOTPLUG) += kobject_uevent.o
obj-$(CONFIG_GENERIC_IOMAP) += iomap.o
obj-$(CONFIG_HAS_IOMEM) += iomap_copy.o devres.o
obj-$(CONFIG_CHECK_SIGNATURE) += check_signature.o
obj-$(CONFIG_DEBUG_LOCKING_API_SELFTESTS) += locking-selftest.o
obj-$(CONFIG_DEBUG_SPINLOCK) += spinlock_debug.o
lib-$(CONFIG_RWSEM_GENERIC_SPINLOCK) += rwsem-spinlock.o
lib-$(CONFIG_RWSEM_XCHGADD_ALGORITHM) += rwsem.o
lib-$(CONFIG_GENERIC_FIND_FIRST_BIT) += find_next_bit.o
lib-$(CONFIG_GENERIC_FIND_NEXT_BIT) += find_next_bit.o
lib-$(CONFIG_GENERIC_FIND_LAST_BIT) += find_last_bit.o
obj-$(CONFIG_GENERIC_HWEIGHT) += hweight.o
obj-$(CONFIG_LOCK_KERNEL) += kernel_lock.o
obj-$(CONFIG_PLIST) += plist.o
obj-$(CONFIG_DEBUG_PREEMPT) += smp_processor_id.o
obj-$(CONFIG_DEBUG_LIST) += list_debug.o
obj-$(CONFIG_DEBUG_OBJECTS) += debugobjects.o

ifneq ($(CONFIG_HAVE_DEC_LOCK),y)
  lib-y += dec_and_lock.o
endif

obj-$(CONFIG_BITREVERSE) += bitrev.o
obj-$(CONFIG_CRC_CCITT)	+= crc-ccitt.o
obj-$(CONFIG_CRC16)	+= crc16.o
obj-$(CONFIG_CRC_T10DIF)+= crc-t10dif.o
obj-$(CONFIG_CRC_ITU_T)	+= crc-itu-t.o
obj-$(CONFIG_CRC32)	+= crc32.o
obj-$(CONFIG_CRC7)	+= crc7.o
obj-$(CONFIG_LIBCRC32C)	+= libcrc32c.o
obj-$(CONFIG_GENERIC_ALLOCATOR) += genalloc.o

obj-$(CONFIG_ZLIB_INFLATE) += zlib_inflate/
obj-$(CONFIG_ZLIB_DEFLATE) += zlib_deflate/
obj-$(CONFIG_REED_SOLOMON) += reed_solomon/
obj-$(CONFIG_LZO_COMPRESS) += lzo/
obj-$(CONFIG_LZO_DECOMPRESS) += lzo/

obj-$(CONFIG_TEXTSEARCH) += textsearch.o
obj-$(CONFIG_TEXTSEARCH_KMP) += ts_kmp.o
obj-$(CONFIG_TEXTSEARCH_BM) += ts_bm.o
obj-$(CONFIG_TEXTSEARCH_FSM) += ts_fsm.o
obj-$(CONFIG_SMP) += percpu_counter.o
obj-$(CONFIG_AUDIT_GENERIC) += audit.o

obj-$(CONFIG_SWIOTLB) += swiotlb.o
obj-$(CONFIG_IOMMU_HELPER) += iommu-helper.o
obj-$(CONFIG_FAULT_INJECTION) += fault-inject.o

lib-$(CONFIG_GENERIC_BUG) += bug.o

obj-$(CONFIG_HAVE_LMB) += lmb.o

obj-$(CONFIG_HAVE_ARCH_TRACEHOOK) += syscall.o

obj-$(CONFIG_DYNAMIC_PRINTK_DEBUG) += dynamic_printk.o

hostprogs-y	:= gen_crc32table
clean-files	:= crc32table.h

$(obj)/crc32.o: $(obj)/crc32table.h

quiet_cmd_crc32 = GEN     $@
      cmd_crc32 = $< > $@

$(obj)/crc32table.h: $(obj)/gen_crc32table
	$(call cmd,crc32)
