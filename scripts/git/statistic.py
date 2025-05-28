#!/bin/env python3
import datetime
import getopt
import glob
import os
import platform
import re
import subprocess
import sys
import time
import argparse


ON_LINUX = (platform.system() == 'Linux')

conf = {
	'commit_begin': '',
	'commit_end': 'HEAD',
}

# arguments
examples = """examples:
    ./git-statistic.py                 # trace all open() syscalls
"""
parser = argparse.ArgumentParser(
    description="Statistic git repo",
    formatter_class=argparse.RawDescriptionHelpFormatter,
    epilog=examples)
parser.add_argument("-B", "--begin", help="begin commit hash")
parser.add_argument("-E", "--end", help="end commit hash")

args = parser.parse_args()

if args.begin:
    conf['commit_begin'] = args.begin
if args.end:
    conf['commit_end'] = args.end


def getpipeoutput(cmds, quiet = True):
    start = time.time()
    if not quiet and ON_LINUX and os.isatty(1):
        print('>> | '.join(cmds))
        sys.stdout.flush()
    p = subprocess.Popen(cmds[0], stdout = subprocess.PIPE, shell = True)
    processes=[p]
    for x in cmds[1:]:
        p = subprocess.Popen(x, stdin = p.stdout, stdout = subprocess.PIPE, shell = True)
        processes.append(p)
    output = p.communicate()[0]
    for p in processes:
        p.wait()
    end = time.time()
    if not quiet:
        if ON_LINUX and os.isatty(1):
            print ('\r')
        print ('[%.5f] >> %s' % (end - start, ' | '.join(cmds)))
    return output.decode().rstrip('\n')


def getcommitrange(defaultrange = 'HEAD', end_only = False):
	if len(conf['commit_end']) > 0:
		if end_only or len(conf['commit_begin']) == 0:
			return conf['commit_end']
		return '%s..%s' % (conf['commit_begin'], conf['commit_end'])
	return defaultrange


file_add_lines = {}
file_del_lines = {}
total_add_lines = 0
total_del_lines = 0

#print(getpipeoutput(['git --version']))
#print(getpipeoutput(['git show-ref --tags']))
#print(getcommitrange())


lines = getpipeoutput(['git log --pretty=tformat: --numstat %s' % getcommitrange()]).split('\n')
for line in lines:
    (add, delete, file) = (line.split('\t'))

    # binary don't have line number
    if add == '-' or delete == '-':
        continue

    if file in file_add_lines.keys():
        file_add_lines[file] += int(add)
        file_del_lines[file] += int(delete)
    else:
        file_add_lines[file] = int(add)
        file_del_lines[file] = int(delete)

for file in file_add_lines.keys():
    total_add_lines += file_add_lines[file]

for file in file_del_lines.keys():
    total_del_lines += file_del_lines[file]

print("%s %s %s" % ("FILE", "ADD", "DELETE"))
for file in file_add_lines.keys():
    print("%s %s %s" % (file, file_add_lines[file], file_del_lines[file]))

print("TOTAL_ADD %d" % total_add_lines)
print("TOTAL_DEL %d" % total_del_lines)
