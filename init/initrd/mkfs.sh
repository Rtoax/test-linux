#!/bin/bash
# https://tthtlc.wordpress.com/2020/01/28/how-to-create-rootfs-filesystem-for-ubuntu-18-04/

IMG_NAME=myimg.test

sudo dd if=/dev/zero of=$IMG_NAME.img bs=32 count=1M

mkfs.ext3 -F -L linuxroot $IMG_NAME.img

mkdir $IMG_NAME

sudo mount $IMG_NAME.img $IMG_NAME

echo "Now, you can add some file into $IMG_NAME"
read a
# cp -ax /{bin,dev,etc,lib,root,sbin,usr,var} $IMG_NAME
# mkdir $IMG_NAME/{home,proc,opt,sys,tmp}

sudo umount $IMG_NAME
