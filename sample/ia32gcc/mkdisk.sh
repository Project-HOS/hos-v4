#!/bin/sh 
# ------------------------------------------------------------------------ 
#  Hyper Operating System V4  サンプルプログラム                           
#                                                                          
#                                  Copyright (C) 1998-2002 by Project HOS  
#                                  http://sourceforge.jp/projects/hos/     
# ------------------------------------------------------------------------ 
MKFSDOS="mformat -f 1440"
MKFSDEV=a:
MCOPY=mcopy
os_type=`uname -s`
case "$os_type" in
    FreeBSD) # FreeBSD Port
	GRUB=/usr/local/sbin/grub
	GRUBDIR=/usr/local/share/grub/i386-freebsd
	;;
    Linux) #Red Hat Linux, Turbo Linux, etc...
	GRUB=/sbin/grub
	GRUBDIR=/usr/share/grub/i386-pc
	;;
    *)  #Is it correct?
	GRUB=/usr/local/sbin/grub
	GRUBDIR=/usr/local/share/grub/i386-pc
	;;
esac
CAT=cat
RM=rm

if [ "$#" = 0  ]; then
    echo "mkdisk object-file "
    exit 1;
fi
 ${CAT} <<EOF > boot.conf
# Boot immediately
timeout 0

# By default, boot the first entry.
default 0

# Fallback to the second entry.
fallback 1

# For booting HOS
title Hyper Operating System V4
root (fd0)
kernel /$1

EOF
${MKFSDOS} ${MKFSDEV}
${MCOPY} $1 boot.conf ${GRUBDIR}/stage1 ${GRUBDIR}/stage2 a:
${GRUB}  --batch  <<EOF 
install (fd0)/stage1 (fd0) (fd0)/stage2 0x8000 p (fd0)/boot.conf
quit
EOF
${RM} boot.conf

# ------------------------------------------------------------------------
#                                  Copyright (C) 1998-2002 by Project HOS
#                                  http://sourceforge.jp/projects/hos/
# ------------------------------------------------------------------------
