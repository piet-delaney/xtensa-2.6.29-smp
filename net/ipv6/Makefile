#
# Makefile for the Linux TCP/IP (INET6) layer.
#

ifdef CONFIG_USE_XTENSA_XCC_COMPILER
#
# WORKAROUND for XCC Optimization Bugs when compiling -O3:
# ========================================================
#
# CONFIG_XTENSA_ALT_EXTRA_CFLAGS can be set -O2 when  CONFIG_XTENSA_EXTRA_CFLAGS
# is set to -O3 to allow most of the kernel code to be compiled -O3 and a few
# functions like those below to be compiled -O2 till the XCC bugs are resolved.
#
# tcp_ipv6.c:
# -----------
#       ### Assertion failure at line 562 of /home/pdelaney/work/cottonwood_1/p4root/Xtensa/Software/xcc/be/opt/opt_find.cxx:
#	### Compiler Error in file /export2/src/$ARCH/$PLATFORM_src.25-Mar-2011.xcc/Linux_*/linux-29/net/ipv6/tcp_ipv6.c
#	### Unknown DEFREP kind
#	Signal: Aborted in Global Optimization -- New PRE: Expr hoisting. phase.
#	Error: Signal Aborted in phase Global Optimization -- New PRE: Expr hoisting. -- processing aborted
#	Bug: 22626
#
XTENSA_ALT_EXTRA_CFLAGS := $(strip $(subst ",,$(CONFIG_XTENSA_ALT_EXTRA_CFLAGS)))#")))

# EXTRA_CFLAGS +=  $(XTENSA_ALT_EXTRA_CFLAGS)
# CFLAGS_addrlabel.o = -save-temps

# XTENSA_XCC_WORKAROUND_22626_ENABLED not required as of xcc-9.0.4 (09004)
CFLAGS_tcp_ipv6.o = $(call xcc-ifversion, -lt, 9004,  $(XTENSA_ALT_EXTRA_CFLAGS))

endif


obj-$(CONFIG_IPV6) += ipv6.o

ipv6-objs :=	af_inet6.o anycast.o ip6_output.o ip6_input.o addrconf.o \
		addrlabel.o \
		route.o ip6_fib.o ipv6_sockglue.o ndisc.o udp.o udplite.o \
		raw.o protocol.o icmp.o mcast.o reassembly.o tcp_ipv6.o \
		exthdrs.o datagram.o ip6_flowlabel.o inet6_connection_sock.o

ipv6-$(CONFIG_SYSCTL) = sysctl_net_ipv6.o
ipv6-$(CONFIG_IPV6_MROUTE) += ip6mr.o

ipv6-$(CONFIG_XFRM) += xfrm6_policy.o xfrm6_state.o xfrm6_input.o \
	xfrm6_output.o
ipv6-$(CONFIG_NETFILTER) += netfilter.o
ipv6-$(CONFIG_IPV6_MULTIPLE_TABLES) += fib6_rules.o
ipv6-$(CONFIG_PROC_FS) += proc.o
ipv6-$(CONFIG_SYN_COOKIES) += syncookies.o

ipv6-objs += $(ipv6-y)

obj-$(CONFIG_INET6_AH) += ah6.o
obj-$(CONFIG_INET6_ESP) += esp6.o
obj-$(CONFIG_INET6_IPCOMP) += ipcomp6.o
obj-$(CONFIG_INET6_XFRM_TUNNEL) += xfrm6_tunnel.o
obj-$(CONFIG_INET6_TUNNEL) += tunnel6.o
obj-$(CONFIG_INET6_XFRM_MODE_TRANSPORT) += xfrm6_mode_transport.o
obj-$(CONFIG_INET6_XFRM_MODE_TUNNEL) += xfrm6_mode_tunnel.o
obj-$(CONFIG_INET6_XFRM_MODE_ROUTEOPTIMIZATION) += xfrm6_mode_ro.o
obj-$(CONFIG_INET6_XFRM_MODE_BEET) += xfrm6_mode_beet.o
obj-$(CONFIG_IPV6_MIP6) += mip6.o
obj-$(CONFIG_NETFILTER)	+= netfilter/

obj-$(CONFIG_IPV6_SIT) += sit.o
obj-$(CONFIG_IPV6_TUNNEL) += ip6_tunnel.o

obj-y += addrconf_core.o exthdrs_core.o

obj-$(subst m,y,$(CONFIG_IPV6)) += inet6_hashtables.o
