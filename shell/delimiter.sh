#!/bin/bash
# EOF - End of File
set -e

var1="Hello, World!"

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


cat <<-EOF
#!/bin/bash
"\$var1=1"
echo ${var1}
EOF

cat <<-EOF | sudo tee a.out
Wrote by sudo tee
EOF
