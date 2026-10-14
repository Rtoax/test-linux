#!/bin/bash
set -e

if which neofetch >/dev/null 2>&1; then
	neofetch --ascii_distro GNU
else
	echo '    _-`````-,           ,- `- .'
	echo '  .`   .- - |          | - -.  `.'
	echo ' /.`  /                     `.   \ '
	echo ':/   :      _...   ..._      ``   :'
	echo '::   :     /._ .`:`_.._\.    ||   :'
	echo '::    `._ ./  ,`  :    \ . _.``   .'
	echo '`:.      /   |  -.  \-. \\_      /'
	echo '  \:._ _/  .`   .@)  \@) ` `\ ,.`'
	echo '     _/,--`       .- .\,-.`--`.'
	echo '       ,`/``     (( \ `  )'
	echo '        /`/`  \    `-`  ('
	echo '         `/``  `._,-----`'
	echo '          ``/`    .,---`'
	echo '           ``/`      ;:'
	echo '             ``/``  ``/'
	echo '               ``/``/``'
	echo '                 `/`/`'
	echo '                  `;'
fi
