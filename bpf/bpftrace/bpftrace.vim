autocmd BufRead,BufNewFile *.bt setfiletype bpftrace
syntax clear
syntax sync minlines=1000

highlight btkeyword
	\ ctermfg=red cterm=bold
	\ guifg=#FF0000 guibg=NONE gui=bold

highlight btprobe
	\ ctermfg=blue cterm=bold
	\ guifg=#FF0000 guibg=NONE gui=bold

highlight btc_def
	\ ctermfg=red cterm=bold
	\ guifg=#00FF00 gui=italic

highlight btcomment
	\ ctermfg=gray cterm=italic
	\ guifg=#00FF00 gui=italic

highlight btstring
	\ ctermfg=yellow
	\ guifg=#FFFF00

syntax region btcommentmultiline
	\ start=/\/\*/
	\ end=/\*\//
	\ containedin=ALL
	\ fold

syntax keyword btkeyword if else for while return break continue
	\ containedin=ALL

syntax match btc_def /#.*/
	\ containedin=ALL

syntax match btcomment /\/\/.*/
	\ containedin=ALL

syntax keyword btprobe interval kprobe kretprobe BEGIN begin END end kfunc kretfunc tracepoint usdt uprobe uretprobe fentry fexit probe
	\ containedin=ALL
