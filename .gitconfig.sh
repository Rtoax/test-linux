# Global
# FORCE=1
# VERBOSE=1

# clang-format.sh
# VCF=1
# FCF=1

# docs/linux-reference.sh
# VLR=1
# FLR=1
if [[ " 6.14.11-300.fc42_cxl.x86_64 " =~ " $(uname -r) " ]]; then
	FLR=1
fi

# git/hooks pre-commit
# VC=1
# FC=1
# NMOD=100
# NADD=2
# NDEL=100
# NREN=100

# git/hooks prepare-commit-msg
# AV=1
# VCM=1
# FCM=1
