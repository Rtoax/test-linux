include git.mk

prog-y += check-ignore.sh
prog-y += diff.sh
prog-y += log.sh
prog-y += ls-files.sh
prog-$(call git_gt,2,27,0) += refs.sh
prog-y += rev-list.sh
