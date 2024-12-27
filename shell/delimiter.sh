#!/bin/bash
# EOF - End of File
set -e

wc -l << EOF
    This is a simple lookup program
    for good (and bad) restaurants
    in Cape Town.
EOF

more << FLAG
    rong
    *.*
    "\n"
FLAG

cat << EOF
    This is a simple lookup program
    for good (and bad) restaurants
    in Cape Town.
EOF

_foo()
{
  cat >&2<< EOF
    Print to stderr
EOF
}
_foo

	cat <<-EOF
	#!/bin/bash
	EOF
