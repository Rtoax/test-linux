" Vim syntax file
" Language:	bpftrace
" Maintainer:	Rong Tao <rongtao@cestc.cn>
" Last Change:	2026 Jan 28

" Quit when a syntax file was already loaded
if exists("b:current_syntax")
	finish
endif

autocmd BufRead,BufNewFile *.bt setfiletype bpftrace
syntax clear
syntax sync minlines=1000

syntax keyword btStatement	break comptime continue let macro return
syntax keyword btConditional	if else
syntax keyword btRepeat		while for
syntax keyword btTodo		contained TODO
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
syntax keyword btPatterns	BEGIN END begin end

syntax keyword btType	bool int int8 int16 int32 int64 uint8 uint16 uint32 uint64 string
syntax keyword btStructure	union struct

syntax region btString		start=+"+ skip=+\\\\\|\\"+ end=+"+ contains=@Spell extend

" Arithmetic operators: +, and - take care of ++, and --
syntax match btOperator		"+\|-\|\*\|/\|%\|="
syntax match btOperator		"+=\|-=\|\*=\|/=\|%="
syntax match btOperator		"\^\|\^="

syntax match btComment /\/\/.*/ contains=@Spell,btTodo

syntax region btComment start=/\/\*/ end=/\*\// fold contains=@Spell,btTodo

syntax match btProbe
	\ /\v(kprobe|kretprobe|k):.*/
	\ containedin=ALL

syntax match btProbe
	\ /\v(uprobe|uretprobe|kfunc|kretfunc|tracepoint|usdt|fentry|fexit|probe|interval):.*:.*/
	\ containedin=ALL

syntax match btShebang /\%^#![^[].*/
syntax region btIncluded	display contained start=+"+ skip=+\\\\\|\\"+ end=+"+
syntax match btIncluded	display contained "<[^>]*>"
syntax match btInclude	display "^\s*\zs\%(%:\|#\)\s*include\>\s*["<]" contains=btIncluded

" Define the default highlighting.
hi def link btConditional	Conditional
hi def link btFunction		Function
hi def link btRepeat		Repeat
hi def link btStatement		Statement
hi def link btStructure		Structure
hi def link btShebang		Comment
hi def link btComment		Comment
hi def link btTodo		Todo
hi def link btType		Type
hi def link btPatterns		Special
hi def link btProbe		Identifier
hi def link btString		String
hi def link btOperator		Special
hi def link btIncluded		btString
hi def link btInclude		Include
