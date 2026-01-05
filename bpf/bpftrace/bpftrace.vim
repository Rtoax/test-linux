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

syntax keyword btStatement	break continue
syntax keyword btConditional	if else
syntax keyword btRepeat		while for
syntax keyword btTodo		TODO
syntax keyword btFunction	assert bswap buf cat
syntax keyword btFunction	cgroup cgroup_path cgroupid
syntax keyword btFunction	clear comm cpid cpu curtask
syntax keyword btFunction	delete elapsed errorf exit
syntax keyword btFunction	fail func getopt gid
syntax keyword btFunction	has_key is_array is_integer is_literal is_ptr is_unsigned_integer
syntax keyword btFunction	jiffies join kaddr kfunc_allowed kfunc_exist kptr
syntax keyword btFunction	kstack ksym
syntax keyword btFunction	len macaddr memcmp ncpus nsecs ntop numaid
syntax keyword btFunction	override offsetof path pcomm percpu_kaddr pid ppid print printf
syntax keyword btFunction	probe probetype pton rand reg retval signal signal_thread
syntax keyword btFunction	sizeof skboutput socket_cookie static_assert str strcap
syntax keyword btFunction	strcontains strerror strftime strlen strstr
syntax keyword btFunction	syscall_name system
syntax keyword btFunction	tid time uaddr uid unwatch uptr usermode username ustack usym
syntax keyword btFunction	warnf zero avg count
syntax keyword btFunction	hist lhist max min stats sum tseries

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
hi def link btFunction		Function
hi def link btRepeat		Repeat
hi def link btStatement		Statement
hi def link btComment		Comment
hi def link btTodo		Todo
