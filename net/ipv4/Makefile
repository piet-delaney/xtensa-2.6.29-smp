#
# Makefile for the Linux TCP/IP (INET) layer.
#

ifdef CONFIG_USE_XTENSA_XCC_COMPILER
#
# WORKAROUNDS for XCC Optimization Bugs when compiling -O3:
# =========================================================
#
# CONFIG_XTENSA_ALT_EXTRA_CFLAGS can be set -O2 when  CONFIG_XTENSA_EXTRA_CFLAGS
# is set to -O3 to allow most of the kernel code to be compiled -O3 and a few
# functions like those below to be compiled -O2 till the XCC bugs are resolved.
#
# ./tcp_input.c:
# --------------
#	Signal: Segmentation fault in Global Optimization -- Local RVI phase.
#	Error: Signal Segmentation fault in phase Global Optimization -- Local RVI -- processing aborted
#	xt-xcc ERROR:  /././fac/vol6/software/pdelaney/Work/cottonwood_1/swtools-x86-linux/libexec/xcc/be ...
#	               ... died due to signal 4
#	Bug: 22625
#
# ./tcp_output.c:
# ---------------
#	Signal: Segmentation fault in Global Optimization -- Local RVI phase.
#	Error: Signal Segmentation fault in phase Global Optimization -- Local RVI -- processing aborted
#	xt-xcc ERROR:  /././fac/vol6/software/pdelaney/Work/cottonwood_1/swtools-x86-linux/libexec/xcc/be...
#		       ... died due to signal 4
#	Bug: 22625
#
# ./tcp_timer.c:
# --------------
#	Signal: Segmentation fault in Global Optimization -- Local RVI phase.
#	Error: Signal Segmentation fault in phase Global Optimization -- Local RVI -- processing aborted
#	xt-xcc ERROR:  /././fac/vol6/software/pdelaney/Work/cottonwood_1/swtools-x86-linux/libexec/xcc/be ...
#		       ... died due to signal 4
#	Bug: 22625
#
# ./tcp_ipv4.c:
# -------------
#        ### Assertion failure at line 562 of 
#	     /home/pdelaney/work/cottonwood_1/p4root/Xtensa/Software/xcc/be/opt/opt_find.cxx:
#        ### Compiler Error in file /export2/src/$ARCH/$PLATFORM.25-Mar-2011.xcc/Linux_*/linux-29/net/ipv4/tcp_ipv4.c ...
#	 ... during Global Optimization -- New PRE: Expr hoisting. phase:
#        ### Unknown DEFREP kind
#        Signal: Aborted in Global Optimization -- New PRE: Expr hoisting. phase.
#        Error: Signal Aborted in phase Global Optimization -- New PRE: Expr hoisting. -- processing aborted
#        xt-xcc ERROR:  /././fac/vol6/software/pdelaney/Work/cottonwood_1/swtools-x86-linux/libexec/xcc/be ...
#		        ... died due to signal 4
#	 Bug: 22626
#
#
# NOTE:
#  	Changing CFLAGS_$(file)_.o below DOESN'T cause the object to be re-made.
#
#
XTENSA_ALT_EXTRA_CFLAGS := $(strip $(subst ",,$(CONFIG_XTENSA_ALT_EXTRA_CFLAGS)))#")))

# XTENSA_XCC_WORKAROUND_22625_ENABLED still required as of xcc-9.0.2 (09002)
CFLAGS_tcp_input.o  += $(call xcc-ifversion, -lt, 99003,  $(XTENSA_ALT_EXTRA_CFLAGS))
CFLAGS_tcp_output.o += $(call xcc-ifversion, -lt, 99003,  $(XTENSA_ALT_EXTRA_CFLAGS))
CFLAGS_tcp_timer.o  += $(call xcc-ifversion, -lt, 99003,  $(XTENSA_ALT_EXTRA_CFLAGS))

# XTENSA_XCC_WORKAROUND_22626_ENABLED no longer required as xcc-9.0.4 (09004)
CFLAGS_tcp_ipv4.o   += $(call xcc-ifversion, -lt, 9004,  $(XTENSA_ALT_EXTRA_CFLAGS))

# CFLAGS_tcp.o = -save-temps
endif


obj-y     := route.o inetpeer.o protocol.o \
	     ip_input.o ip_fragment.o ip_forward.o ip_options.o \
	     ip_output.o ip_sockglue.o inet_hashtables.o \
	     inet_timewait_sock.o inet_connection_sock.o \
	     tcp.o tcp_input.o tcp_output.o tcp_timer.o tcp_ipv4.o \
	     tcp_minisocks.o tcp_cong.o \
	     datagram.o raw.o udp.o udplite.o \
	     arp.o icmp.o devinet.o af_inet.o  igmp.o \
	     fib_frontend.o fib_semantics.o \
	     inet_fragment.o

obj-$(CONFIG_SYSCTL) += sysctl_net_ipv4.o
obj-$(CONFIG_IP_FIB_HASH) += fib_hash.o
obj-$(CONFIG_IP_FIB_TRIE) += fib_trie.o
obj-$(CONFIG_PROC_FS) += proc.o
obj-$(CONFIG_IP_MULTIPLE_TABLES) += fib_rules.o
obj-$(CONFIG_IP_MROUTE) += ipmr.o
obj-$(CONFIG_NET_IPIP) += ipip.o
obj-$(CONFIG_NET_IPGRE) += ip_gre.o
obj-$(CONFIG_SYN_COOKIES) += syncookies.o
obj-$(CONFIG_INET_AH) += ah4.o
obj-$(CONFIG_INET_ESP) += esp4.o
obj-$(CONFIG_INET_IPCOMP) += ipcomp.o
obj-$(CONFIG_INET_XFRM_TUNNEL) += xfrm4_tunnel.o
obj-$(CONFIG_INET_XFRM_MODE_BEET) += xfrm4_mode_beet.o
obj-$(CONFIG_INET_LRO) += inet_lro.o
obj-$(CONFIG_INET_TUNNEL) += tunnel4.o
obj-$(CONFIG_INET_XFRM_MODE_TRANSPORT) += xfrm4_mode_transport.o
obj-$(CONFIG_INET_XFRM_MODE_TUNNEL) += xfrm4_mode_tunnel.o
obj-$(CONFIG_IP_PNP) += ipconfig.o
obj-$(CONFIG_NETFILTER)	+= netfilter.o netfilter/
obj-$(CONFIG_INET_DIAG) += inet_diag.o 
obj-$(CONFIG_INET_TCP_DIAG) += tcp_diag.o
obj-$(CONFIG_NET_TCPPROBE) += tcp_probe.o
obj-$(CONFIG_TCP_CONG_BIC) += tcp_bic.o
obj-$(CONFIG_TCP_CONG_CUBIC) += tcp_cubic.o
obj-$(CONFIG_TCP_CONG_WESTWOOD) += tcp_westwood.o
obj-$(CONFIG_TCP_CONG_HSTCP) += tcp_highspeed.o
obj-$(CONFIG_TCP_CONG_HYBLA) += tcp_hybla.o
obj-$(CONFIG_TCP_CONG_HTCP) += tcp_htcp.o
obj-$(CONFIG_TCP_CONG_VEGAS) += tcp_vegas.o
obj-$(CONFIG_TCP_CONG_VENO) += tcp_veno.o
obj-$(CONFIG_TCP_CONG_SCALABLE) += tcp_scalable.o
obj-$(CONFIG_TCP_CONG_LP) += tcp_lp.o
obj-$(CONFIG_TCP_CONG_YEAH) += tcp_yeah.o
obj-$(CONFIG_TCP_CONG_ILLINOIS) += tcp_illinois.o
obj-$(CONFIG_NETLABEL) += cipso_ipv4.o

obj-$(CONFIG_XFRM) += xfrm4_policy.o xfrm4_state.o xfrm4_input.o \
		      xfrm4_output.o
