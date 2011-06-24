#
# Makefile for the linux ext4-filesystem routines.
#


ifdef CONFIG_USE_XTENSA_XCC_COMPILER
#
# WORKAROUND for XCC Optimization Bugs when compiling -O3:
# ========================================================
#
# CONFIG_XTENSA_ALT_EXTRA_CFLAGS can be set -O2 when CONFIG_XTENSA_EXTRA_CFLAGS
# is set to -O3 to allow most of the kernel code to be compiled -O3 and a few
# functions like those below to be compiled -O2 till the XCC bugs are resolved.
#
# ./super.c:
#	Signal: Floating point exception in Loop Nest Optimizer phase.
#	Error: Signal Floating point exception in phase Loop Nest Optimizer -- processing aborted
#	Bug: 22624 
#
# ./mballoc.c:
# 	/export2/src/$ARCH/$PLATFORM.25-Mar-2011.xcc/Linux_*/linux-29/fs/ext4/mballoc.c:2734: ...
#	... warning: passing argument 3 of ‘__percpu_alloc_mask’ discards qualifiers from pointer target type
#	Signal: Floating point exception in Loop Nest Optimizer phase.
#	Error: Signal Floating point exception in phase Loop Nest Optimizer -- processing aborted
#	Bug: 22624
#
#
XTENSA_ALT_EXTRA_CFLAGS := $(strip $(subst ",,$(CONFIG_XTENSA_ALT_EXTRA_CFLAGS)))#")))

# EXTRA_CFLAGS += $(XTENSA_ALT_EXTRA_CFLAGS)

# XTENSA_XCC_WORKAROUND_22624_ENABLED: still required as of xcc-9.0.2 (09002)
CFLAGS_super.o   = $(call xcc-ifversion, -lt, 99003,  $(XTENSA_ALT_EXTRA_CFLAGS))
CFLAGS_mballoc.o = $(call xcc-ifversion, -lt, 99003,  $(XTENSA_ALT_EXTRA_CFLAGS))

endif

obj-$(CONFIG_EXT4_FS) += ext4.o

ext4-y	:= balloc.o bitmap.o dir.o file.o fsync.o ialloc.o inode.o \
		   ioctl.o namei.o super.o symlink.o hash.o resize.o extents.o \
		   ext4_jbd2.o migrate.o mballoc.o

ext4-$(CONFIG_EXT4_FS_XATTR)		+= xattr.o xattr_user.o xattr_trusted.o
ext4-$(CONFIG_EXT4_FS_POSIX_ACL)	+= acl.o
ext4-$(CONFIG_EXT4_FS_SECURITY)		+= xattr_security.o
