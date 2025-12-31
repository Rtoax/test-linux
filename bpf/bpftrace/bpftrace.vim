autocmd BufRead,BufNewFile *.bt setfiletype bpftrace
syntax clear
syntax sync minlines=1000

highlight btkeyword
	\ ctermfg=red cterm=bold
	\ guifg=#FF0000 guibg=NONE gui=bold

highlight btprobe
	\ ctermfg=blue cterm=bold
	\ guifg=#FF0000 guibg=NONE gui=bold

highlight btcomment
	\ ctermfg=gray cterm=italic
	\ guifg=#00FF00 gui=italic

syntax region btcommentmultiline
	\ start=/\/\*/
	\ end=/\*\//
	\ containedin=ALL
	\ fold

highlight btstring
	\ ctermfg=yellow
	\ guifg=#FFFF00

syntax keyword btkeyword if else for while return break continue
	\ containedin=ALL

syntax match btcomment /\/\/.*/
	\ containedin=ALL

syntax keyword btprobe interval kprobe kretprobe
	\ containedin=ALL
