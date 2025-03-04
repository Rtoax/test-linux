
# 修改的 RPM 包

## cclinux-2108

* [cclinux-logos-2108](https://gitee.com/cestcos/cclinux-logos-2108)
  * cclinux-backgrounds-85.5-2.el9.noarch.rpm
    * Provide: cclinux-backgrounds
    * Provide: system-backgrounds
    * Require: cclinux-logos
  * cclinux-logos-httpd-85.5-2.el9.noarch.rpm
    * Provide: cclinux-logos-httpd
    * Provide: redhat-logos-httpd
    * Provide: system-logos-httpd
    * Require: ...
  * cclinux-logos-ipa-85.5-2.el9.noarch.rpm
    * Provide: cclinux-logos-ipa
    * Provide: redhat-logos-ipa
    * Provide: system-logos-ipa
    * Require: ...
  * cclinux-logos-85.5-2.el9.x86_64.rpm
    * Provide: cclinux-logos
    * Provide: cclinux-logos(x86-64)
    * Provide: config(cclinux-logos)
    * Provide: redhat-logos
    * Provide: system-logos
    * Require: config(cclinux-logos)
* [cclinux-indexhtml-2108](https://gitee.com/cestcos/cclinux-indexhtml-2108)
  * cclinux-indexhtml-8.0-1.el9.noarch.rpm
    * Provide: cclinux-indexhtml
    * Provide: redhat-indexhtml
    * Require: ...
* [cclinux-repos-2108](https://gitee.com/cestcos/cclinux-repos-2108)
  * cclinux-gpg-keys-8-4.el9.noarch.rpm
    * Provide: cclinux-gpg-keys
    * Require: ...
  * cclinux-linux-repos-8-4.el9.noarch.rpm
    * Provide: cclinux-linux-repos
    * Provide: cclinux-repos(8)
    * Provide: config(cclinux-linux-repos)
    * Require: cclinux-gpg-keys
    * Require: config(cclinux-linux-repos)
    * Require: system-release(releasever)
* [cclinux-linux-release-2108](https://gitee.com/cestcos/cclinux-linux-release-2108)
  * cclinux-linux-release-8.5-1.2207.el9.noarch.rpm
    * Provide: cclinux-linux-release
    * Provide: cclinux-release
    * Provide: cclinux-release-eula
    * Provide: config(cclinux-linux-release)
    * Provide: redhat-release
    * Provide: redhat-release-eula
    * Provide: system-release
    * Provide: system-release(releasever)
    * Require: cclinux-repos(8)
    * Require: config(cclinux-linux-release)
* [cclinux-obsolete-packages-2108](https://gitee.com/cestcos/cclinux-obsolete-packages-2108)
  * cclinux-obsolete-packages-8-4.noarch.rpm
    * Provide: cclinux-obsolete-packages
    * Provide: libsolv-self-destruct-pkg()
    * Require: ...




## cclinux-2203

* [cclinux-logos](https://gitee.com/cestcos/cclinux-logos)
* [cclinux-indexhtml](https://gitee.com/cestcos/cclinux-indexhtml)
* [cclinux-stream-release](https://gitee.com/cestcos/cclinux-stream-release)


## ceaos

* [ceaos-release-spec](https://gitee.com/cestcos/ceaos-release-spec)
* [ceaos-repos-spec](https://gitee.com/cestcos/ceaos-repos-spec)


