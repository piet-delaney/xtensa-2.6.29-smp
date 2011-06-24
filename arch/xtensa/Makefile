#
# This file is subject to the terms and conditions of the GNU General Public
# License.  See the file "COPYING" in the main directory of this archive
# for more details.
#
# Copyright (C) 2001 - 2009  Tensilica Inc.
#
# This file is included by the global makefile so that you can add your own
# architecture-specific flags and dependencies. Remember to do have actions
# for "archclean" and "archdep" for cleaning up and making dependencies for
# this architecture

#
# Remove Quotes from Variant and Platform Names;
# as well as Extra CFLAGS if Optimized for Debugging.
#
VARIANT_HASCODE		:= $(strip $(subst ",,$(CONFIG_XTENSA_VARIANT_HASCODE)))#")))
VARIANT			:= $(strip $(subst ",,$(CONFIG_XTENSA_VARIANT_NAME)))#")))
PLATFORM		:= $(strip $(subst ",,$(CONFIG_XTENSA_PLATFORM_NAME)))#")))
XTENSA_EXTRA_CFLAGS	:= $(strip $(subst ",,$(CONFIG_XTENSA_EXTRA_CFLAGS)))#")))
XTENSA_ALT_EXTRA_CFLAGS	:= $(strip $(subst ",,$(CONFIG_XTENSA_ALT_EXTRA_CFLAGS)))#")))

platform-$(CONFIG_XTENSA_PLATFORM_A2000)		:= A2000

UTS_MACHINE	:= xtensa_$(VARIANT)

# temporarily until string.h is fixed
KBUILD_CFLAGS += -ffreestanding

KBUILD_CFLAGS += -mlongcalls $(XTENSA_EXTRA_CFLAGS) -pipe
KBUILD_AFLAGS += -mlongcalls $(XTENSA_EXTRA_CFLAGS)

ifdef CONFIG_USE_XTENSA_XCC_COMPILER
KBUILD_CFLAGS += -D__linux__ 

# These may come in handy while your debuging:
#=============================================
# KBUILD_CFLAGS +=  -Wa,--schedule -Wa,--flix -Wa,--transform
# KBUILD_CFLAGS +=   -mno-flix
# KBUILD_CFLAGS +=   -mno-generate-flix
# KBUILD_CFLAGS +=  --no-standard-includes --no-standard-libraries
# KBUILD_CFLAGS +=  --save-temps
#
# -nostdlib 
# -nodefaultlib forces compiler to only use src
#               code provided in the kernel.
#
# LDFLAGS +=  -nostdlib -nodefaultlibs
#
endif

# KBUILD_DEFCONFIG := iss_defconfig

VARIANT_DIR := $(patsubst %,arch/xtensa/variants/%/,$(VARIANT))
PLATFORM_DIR := $(patsubst %,arch/xtensa/platforms/%/,$(PLATFORM))

ifeq ($(KBUILD_SRC),)
KBUILD_CPPFLAGS += $(patsubst %,-I%include,$(VARIANT_DIR) $(PLATFORM_DIR))
else
KBUILD_CPPFLAGS += $(patsubst %,-I$(srctree)/%include,$(VARIANT_DIR) $(PLATFORM_DIR))
endif


ifdef CONFIG_USE_XTENSA_XCC_COMPILER
 CROSS_COMPILE := xt-
 CC := $(CROSS_COMPILE)xcc
else
# Test for GCC cross compiling. Allow xtensa-*-* and xtensa_<variant>-*-*
 ifneq ($(SUBARCH),$(ARCH))
  ifeq ($(CROSS_COMPILE),)
    CROSS_COMPILE := $(call cc-cross-prefix, \
    		       xtensa-linux-uclibc-  xtensa_$(VARIANT)-linux-uclibc- \
    		       xtensa-linux-gnu-     xtensa_$(VARIANT)-linux-gnu-)
  endif
 endif
endif



CC_PATH := $(shell /usr/bin/which $(CC))
LD_PATH := $(shell /usr/bin/which $(LD))
ifdef CONFIG_USE_XTENSA_XCC_COMPILER
  CC_VERSION := $(shell $(CC) --version | grep version)
  LD_VERSION := $(shell $(LD) --version | grep Xtensa)
# 
# Extract Xtensa Tooks Version, Ex: 9.0.2, to check is Workarounds in Makefiles should be enabled.
#
  XT_XCC_VERSION := $(shell echo $(CC_VERSION) | sed -e "s/.* version \([0-9]*\)*/\1/")
  XT_XCC_MAJOR   := $(shell echo $(CC_VERSION) | sed -e "s/.* version \([0-9*]\)\.\([0-9*]*\)\.\([0-9]*\)\(.*\)/\1/")
  XT_XCC_MINOR   := $(shell echo $(CC_VERSION) | sed -e "s/.* version \([0-9*]\)\.\([0-9*]*\)\.\([0-9]*\)\(.*\)/\3/")

  XT_LD_VERSION  := $(shell echo $(CC_VERSION) | sed -e "s/.* version \([0-9]*\)*/\1/")
  XT_LD_MAJOR    := $(shell echo $(CC_VERSION) | sed -e "s/.* version \([0-9*]\)\.\([0-9*]*\)\.\([0-9]*\)\(.*\)/\1/")
  XT_LD_MINOR    := $(shell echo $(CC_VERSION) | sed -e "s/.* version \([0-9*]\)\.\([0-9*]*\)\.\([0-9]*\)\(.*\)/\3/")
#
# Test xcc-version. This function is used in other areas of the kernel to limit
#                   code being comiled with xt-xcc.
#
XCC_VERSION 		:= $(call xcc-version)
XCC_FULLVERSION 	:= $(call xcc-fullversion)
XCC_RELAXATION_BROKEN   := $(shell if [ $(XCC_VERSION) -lt 09002 ] ; then echo "y" ; else echo "n"; fi)

#
#  Relaxation cuased problems in the final link with the call8's that were too far away.
#  Relaxation works fine with newer Xtensa Tools with one remaining problem  being Worked Around 
#  in entry.S, see Bug: 19701.
#
#  Relaxation is enabled by default, it Increases the  link time SIGNIFICANTLY.
#
#  Not sure if relaxation can be enabled on the final vmlinux link on older released;
#  leaving it off by default.
#
 ifeq ($(XCC_RELAXATION_BROKEN),y)
  LDFLAGS += --no-relax
# LDFLAGS_vmlinux += --relax
 else
#  LDFLAGS += --no-relax
 endif


else
  CC_VERSION := $(shell $(CC) --version  2>&1 | grep  -o "(GCC) *.*." -o )
  LD_VERSION := $(shell $(LD) -version 2>&1 | grep Binutils)
endif


# Only build variant and/or platform if it includes a Makefile

buildvar := $(shell test -a $(srctree)/arch/xtensa/variants/$(VARIANT)/Makefile && echo arch/xtensa/variants/$(VARIANT)/)
buildplf := $(shell test -a $(srctree)/arch/xtensa/platforms/$(PLATFORM)/Makefile && echo arch/xtensa/platforms/$(PLATFORM)/)

# Find libgcc.a

ifneq ($(strip $(VARIANT)),)
LIBGCC := $(shell $(CC) $(KBUILD_CFLAGS) -print-libgcc-file-name)
endif

head-y		:= arch/xtensa/kernel/head.o
core-y		+= arch/xtensa/kernel/ arch/xtensa/mm/
core-y		+= $(buildvar) $(buildplf)
libs-y		+= arch/xtensa/lib/ $(LIBGCC)

boot		:= arch/xtensa/boot

# archprepare: checkbin $(archinc)/.configured
archprepare: checkbin 

#
# Test for a Xtnesa Compiler and print Significant Env Variables
# if make started with V=1
#
checkbin:
ifneq ($(strip $(VARIANT)),)
	@if test "$(call cc-option-yn,-mlongcalls)" = "n" ; then                                       \
		echo '*** Default compiler does not appear to target an Xtensa core.';                 \
		echo '*** It didn't understand the '-mlongcalls' GCC option;                           \
		echo '*** Please put an appropriate Xtensa toolchain on your PATH';                    \
		echo '';                                                                               \
		echo 'CROSS_COMPILE:                            $(CROSS_COMPILE) ';                    \
		echo 'CC:                                       $(CC) ';                               \
		echo 'LD`:                                      $(LD) ';                               \
		echo 'PLATFORM:                                 $(PLATFORM) ';                         \
		echo 'VARIANT:                                  $(VARIANT) ';                          \
		echo 'KBUILD_CFLAGS:                            $(KBUILD_CFLAGS) ';                    \
		echo 'VARIANT_DIR:                              $(VARIANT_DIR) ';                      \
		echo 'PLATFORM_DIR:                             $(PLATFORM_DIR) ';                     \
		echo '';                                                                               \
		false;                                                                                 \
	fi
	@if test "$(KBUILD_VERBOSE)" -ge "1" ; then 						       \
		echo "" ; 									       \
                echo '-----------------------------------------------------------------------------------------------------------------------------------------------' ; \
                echo 'KBUILD_VERBOSE:                           $(KBUILD_VERBOSE) '; 			\
                echo 'CROSS_COMPILE:                            $(CROSS_COMPILE) '; 			\
                echo 'CC:                                       $(CC) '; 				\
                echo 'CC_VERSION:                               $(CC_VERSION) '; 			\
                echo 'CC_PATH:                                  $(CC_PATH) '; 				\
                echo 'LD:                                       $(LD) '; 			  	\
                echo 'LD_VERSION:                               $(LD_VERSION) '; 		  	\
                echo 'LD_PATH:                                  $(LD_PATH) '; 			  	\
                echo 'CONFIG_XTENSA_PLATFORM_NAME:              $(CONFIG_XTENSA_PLATFORM_NAME) '; 	\
                echo 'PLATFORM:                                 $(PLATFORM) '; 				\
                echo 'CONFIG_XTENSA_VARIANT_NAME:               $(CONFIG_XTENSA_VARIANT_NAME) '; 	\
                echo 'VARIANT_HASCODE:                          $(VARIANT_HASCODE) '; 			\
                echo 'VARIANT:                                  $(VARIANT) '; 				\
                echo 'CONFIG_CC_DEBUGGING_CFLAGS:               $(CONFIG_CC_DEBUGGING_CFLAGS) '; 	\
                echo 'XTENSA_EXTRA_CFLAGS:                      $(XTENSA_EXTRA_CFLAGS) '; 		\
                echo 'XTENSA_ALT_EXTRA_CFLAGS:                  $(XTENSA_ALT_EXTRA_CFLAGS) '; 		\
                echo 'KBUILD_CFLAGS:                            $(KBUILD_CFLAGS) '; 			\
                echo 'KBUILD_AFLAGS:                            $(KBUILD_AFLAGS) '; 			\
                echo 'KBUILD_CPPFLAGS:                          $(KBUILD_CPPFLAGS) '; 			\
                echo 'CFLAGS:                                   $(CFLAGS) '; 				\
                echo 'LDFLAGS:                                  $(LDFLAGS) '; 				\
                echo 'LIBGCC:                                   $(LIBGCC) '; 				\
                echo 'UTS_MACHINE:                              $(UTS_MACHINE) '; 			\
                echo 'VARIANT_DIR:                              $(VARIANT_DIR) '; 			\
                echo 'PLATFORM_DIR:                             $(PLATFORM_DIR) '; 			\
		echo '' ; 									        \
		true; 										        \
	fi
	@if test "$(KBUILD_VERBOSE)" -ge "1" ; then							\
		echo 'XCC_VERSION:                              $(XCC_VERSION) ';                       \
		echo 'XCC_FULLVERSION:                          $(XCC_FULLVERSION) ';                   \
		echo 'XCC_RELAXATION_BROKEN:                    $(XCC_RELAXATION_BROKEN) ';             \
		echo 'XT_XCC_VERSION:                           $(XT_XCC_VERSION) ';                    \
		echo 'XT_XCC_MAJOR:                             $(XT_XCC_MAJOR) ';                      \
		echo 'XT_XCC_MINOR:                             $(XT_XCC_MINOR) ';                      \
		echo 'XT_LD_VERSION:                            $(XT_LD_VERSION) ';                     \
		echo 'XT_LD_MAJOR:                              $(XT_LD_MAJOR) ';                       \
		echo 'XT_LD_MINOR:                              $(XT_LD_MINOR) ';                       \
		echo '' ;                                                                               \
		true;										        \
	fi
	@if test "$(KBUILD_VERBOSE)" -ge "1" ; then                                             	\
		echo 'KBUILD_OUTPUT:                            $(KBUILD_OUTPUT)' ;			\
		echo 'KBUILD_SRC:                               $(KBUILD_SRC)' ;			\
		echo 'CURDIR:                                   $(CURDIR)';				\
		echo 'SUBARCH:                                  $(SUBARCH)';				\
		echo 'HOSTCXXFLAGS:                             $(HOSTCXXFLAGS)';			\
		echo 'CHECKFLAGS:                               $(CHECKFLAGS)';				\
		echo 'NOSTDINC_FLAGS:                           $(NOSTDINC_FLAGS)';			\
		echo 'MODFLAGS:                                 $(MODFLAGS)';				\
		echo 'CFLAGS_MODULE:                            $(CFLAGS_MODULE)';			\
		echo 'AFLAGS_MODULE:                            $(AFLAGS_MODULE)';			\
		echo 'LDFLAGS_MODULE:                           $(LDFLAGS_MODULE)';			\
		echo 'CFLAGS_KERNEL:                            $(CFLAGS_KERNEL)';			\
		echo 'AFLAGS_KERNEL:                            $(AFLAGS_KERNEL)';			\
		echo 'EXTRA_LDFLAGS:                            $(EXTRA_LDFLAGS)';			\
		echo 'KERNELRELEASE:                            $(KERNELRELEASE)';			\
		echo 'KERNELVERSION:                            $(KERNELVERSION)';			\
		echo 'VERSION:                                  $(VERSION)';				\
		echo 'PATCHLEVEL:                               $(PATCHLEVEL)';				\
		echo 'SUBLEVEL:                                 $(SUBLEVEL)';				\
		echo 'EXTRAVERSION:                             $(EXTRAVERSION)';			\
		echo 'CONFIG_LOCALVERSION:                      $(CONFIG_LOCALVERSION)';		\
		echo 'CONFIG_LOCALVERSION_AUTO:                 $(CONFIG_LOCALVERSION_AUTO)';		\
		echo 'LOCALVERSION:                             $(LOCALVERSION)';			\
		echo 'MODVERDIR:                                $(MODVERDIR)';				\
		echo 'RCS_FIND_IGNORE:                          $(RCS_FIND_IGNORE)';			\
		echo 'PHONY:                                    $(PHONY)';				\
		echo 'MAKECMDGOALS:                             $(MAKECMDGOALS)';			\
		echo 'KBUILD_EXTMOD:                            $(KBUILD_EXTMOD)';			\
		echo 'KBUILD_KCONFIG:                           $(KBUILD_KCONFIG)';			\
		echo 'KBUILD_DEFCONFIG:                         $(KBUILD_DEFCONFIG)';			\
		echo 'CONFIG_KALLSYMS:                          $(CONFIG_KALLSYMS)';			\
		echo 'CONFIG_KALLSYMS_EXTRA_PASS:               $(CONFIG_KALLSYMS_EXTRA_PASS)';		\
		echo 'CONFIG_HEADERS_CHECK:                     $(CONFIG_HEADERS_CHECK)';		\
		echo 'CONFIG_BUILD_DOCSRC:                      $(CONFIG_BUILD_DOCSRC)';		\
		echo 'CONFIG_FRAME_POINTER:                     $(CONFIG_FRAME_POINTER)';		\
		echo 'CONFIG_DEBUG_INFO:                        $(CONFIG_DEBUG_INFO)';			\
		echo 'CONFIG_FUNCTION_TRACER:                   $(CONFIG_FUNCTION_TRACER)';		\
		echo 'CONFIG_DEBUG_SECTION_MISMATCH:            $(CONFIG_DEBUG_SECTION_MISMATCH)';	\
		echo 'KCPPFLAGS:                                $(KCPPFLAGS)';				\
		echo 'KAFLAGS:                                  $(KAFLAGS)';				\
		echo 'KCFLAGS:                                  $(KCFLAGS)';				\
		echo 'LDFLAGS_BUILD_ID:                         $(LDFLAGS_BUILD_ID)';			\
		echo 'LDFLAGS_vmlinux:                          $(LDFLAGS_vmlinux)';			\
		echo 'KBUILD_IMAGE:                             $(KBUILD_IMAGE)';			\
		echo 'INSTALL_PATH:                             $(INSTALL_PATH)';			\
		echo 'MODLIB:                                   $(INSTALL_PATH)';			\
		echo 'INSTALL_MOD_STRIP:                        $(INSTALL_MOD_STRIP)';			\
                echo '-----------------------------------------------------------------------------------------------------------------------------------------------' ; \
                echo ''; 									        \
		true; 										        \
	fi
else
	@echo '*** Xtensa core variant name cannot be empty (check config)' ; \
	false
endif

drivers-$(CONFIG_OPROFILE)	+= arch/xtensa/oprofile/

all: zImage

zImage zImage.initrd: vmlinux
	$(Q)$(MAKE) $(build)=$(boot) $@

# CLEAN_FILES	+= arch/xtensa/vmlinux.lds                      \
#		   $(archinc)/platform $(archinc)/variant	\
# 		   $(archinc)/.configured

define archhelp
  @echo '* zImage      - Compressed kernel image'
  @echo '* uImage      - Compressed kernel image for U-Boot'
endef

