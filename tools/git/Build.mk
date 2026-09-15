include git.mk

subdir-y += log

prog-y += check-ignore.sh
prog-y += diff.sh
prog-y += ls-files.sh
prog-$(call git_gt,2,27,0) += refs.sh
prog-y += rev-list.sh
