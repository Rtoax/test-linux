" Vim syntax file
" Language:	bpftrace
autocmd BufRead,BufNewFile *.bt setfiletype bpftrace
syntax clear
syntax sync minlines=1000

highlight btkeyword
	\ ctermfg=red
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

syntax keyword btkeyword if else for comptime macro while return break continue
	\ containedin=ALL

syntax match btc_def /#.*/
	\ containedin=ALL

syntax match btcomment /\/\/.*/
	\ containedin=ALL

syntax region btcomment
	\ start=/\/\*/
	\ end=/\*\//
	\ containedin=ALL
	\ fold

syntax match btprobe
	\ /\v(kprobe|kretprobe|k):.*/
	\ containedin=ALL

syntax match btprobe
	\ /\v^(BEGIN|begin|END|end)/
	\ containedin=ALL

syntax match btprobe
	\ /\v(uprobe|uretprobe|kfunc|kretfunc|tracepoint|usdt|fentry|fexit|probe|interval):.*:.*/
	\ containedin=ALL
