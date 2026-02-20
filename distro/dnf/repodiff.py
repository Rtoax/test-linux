#!/usr/bin/env python3

import dnf
import sys

def list_diff(li1, li2):
    return [i for i in li2 if i not in li1]

def get_pkgs(repo_url):
    with dnf.Base() as base:
        repo = dnf.repo.Repo(None, base.conf)
        repo.baseurl = repo_url
        base.repos.clear()
        base.repos.add(repo)
        base.fill_sack()
        query = base.sack.query().available()
    pkgs = []
    for pkg in query.run():
        if pkg.arch != 'i686':
            pkgs.append({'name': pkg.name, 'version': pkg.version, 'release': pkg.release, 'arch': pkg.arch, 'location': pkg.location})
    return pkgs


pkgs1 = get_pkgs('https://mirror.iscas.ac.cn/almalinux/9.0/BaseOS/x86_64/os/')
pkgs2 = get_pkgs('https://mirror.iscas.ac.cn/almalinux/9.1/BaseOS/x86_64/os/')

for i in list_diff(pkgs1, pkgs2):
    print(i['name'], i['version'], i['release'], i['arch'], i['location'])
