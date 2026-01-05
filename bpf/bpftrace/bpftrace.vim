" Vim syntax file
" Language:	bpftrace
" Maintainer:	Rong Tao <rongtao@cestc.cn>
" Last Chnage:	2026 Jan 5

" Quit when a syntax file was already loaded
if exists("b:current_syntax")
	finish
endif

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

highlight btstring
	\ ctermfg=yellow
	\ guifg=#FFFF00

syntax keyword btkeyword comptime macro return break continue
	\ containedin=ALL

syntax keyword btConditional	if else
syntax keyword btRepeat		while for
syntax keyword btTodo		TODO

syntax match btc_def /#.*/
	\ containedin=ALL

syntax match btComment /\/\/.*/
	\ contains=@Spell,awkTodo

syntax region btComment
	\ start=/\/\*/
	\ end=/\*\//
	\ fold
	\ contains=@Spell,awkTodo

syntax match btprobe
	\ /\v(kprobe|kretprobe|k):.*/
	\ containedin=ALL

syntax match btprobe
	\ /\v^(BEGIN|begin|END|end)/
	\ containedin=ALL

syntax match btprobe
	\ /\v(uprobe|uretprobe|kfunc|kretfunc|tracepoint|usdt|fentry|fexit|probe|interval):.*:.*/
	\ containedin=ALL

" Define the default highlighting.
hi def link btConditional	Conditional
hi def link btRepeat		Repeat
hi def link btComment		Comment
hi def link btTodo		Todo
