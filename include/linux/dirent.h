#ifndef _LINUX_DIRENT_H
#define _LINUX_DIRENT_H

/*
 * XTENSA-WORKAROUND:
 *   struct dirent is no longer used in the kernel, file system specific versions
 *   are now being used, thought the seem to be curretly equivalent. In 2.6.29 
 *   kernels the include/linux/dirent.h file is no longer made by unifdefing the
 *   kernel headers. Instead it seems to be part of the the GNU C library.
 *
 *   For compatability with older C libraries and applications like LTP we
 *   going to provide the old 32 bit struct dirent and export it in the
 *   the linux headers.
 *
 *   Note that linux_dirent64 wasn't previous shipped in kernel headers.
 *
 *   With newer version of LTP/buildroot we will be dropping this workaround.
 */
#ifndef __KERNEL__

struct dirent {
	long		d_ino;
	__kernel_off_t	d_off;
	unsigned short	d_reclen;
	char		d_name[256]; /* We must not include limits.h! */
};

#else

struct linux_dirent64 {
	u64		d_ino;
	s64		d_off;
	unsigned short	d_reclen;
	unsigned char	d_type;
	char		d_name[0];
};

#endif  /* __KERNEL__ */

#endif
