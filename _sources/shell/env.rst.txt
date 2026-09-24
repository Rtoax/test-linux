=========
SHELL ENV
=========

.. list-table::
   :header-rows: 1

   * - ENV
     - Description
   * - \*
     - 含有所有命令行参数（以单个文本值的形式）
   * - @
     - 含有所有命令行参数（以多个文本值的形式）
   * - #
     - 命令行参数数目
   * - \?
     - 最近使用的前台进程的退出状态码
   * - \-
     - 当前命令行选项标记
   * - $
     - 当前shell的进程ID（ PID）
   * - !
     - 最近执行的后台进程的PID
   * - 0
     - 命令行中使用的命令名称
   * - _
     - shell的绝对路径名
   * - BASH
     - 用来调用shell的完整文件名
   * - BASHOPTS
     - 允许冒号分隔列表形式的shell选项
   * - BASHPID
     - 当前bash shell的进程ID
   * - BASH_ALIASED
     - 含有当前所用别名的数组
   * - BASH_ARGC
     - 当前子函数中的参数数量
   * - BASH_ARGV
     - 含有所有指定命令行参数的数组
   * - BASH_CMDS
     - 含有命令的内部散列表的数组
   * - BASH_COMMAND
     - 当前正在被执行的命令名
   * - BASH_ENV
     - 如果设置了的话，每个bash脚本都会尝试在运行前执行由该变量定义的起始文件
   * - BASH_EXECUTION_STRING
     - 在-c命令行选项中用到的命令
   * - BASH_LINENO
     - 含有脚本中每个命令的行号的数组
   * - BASH_REMATCH
     - 含有与指定的正则表达式匹配的文本元素的数组
   * - BASH_SOURCE
     - 含有shell中已声明函数所在源文件名的数组
   * - BASH_SUBSHELL
     - 当前shell生成的子shell数目
   * - BASH_VERSINFO
     - 含有当前bash shell实例的主版本号和次版本号的数组
   * - BASH_VERSION
     - 当前bash,shell实例的版本号
   * - BASH_XTRACEFD
     - 当设置一个有效的文件描述符整数时，跟踪输出生成，并与诊断和错误信息分离开文件描述符必须设置-x启动
   * - COLUMNS
     - 含有当前bash shell实例使用的终端的宽度
   * - COMP_CWORD
     - 含有变量COMP_WORDS的索引值， COMP_WORDS包含当前光标所在的位置
   * - COMP_KEY
     - 调用补全功能的按键
   * - COMP_LINE
     - 当前命令行
   * - COMP_POINT
     - 当前光标位置相对于当前命令起始位置的索引
   * - COMP_TYPE
     - 补全类型所对应的整数值
   * - COMP_WORDBREAKS
     - 在进行单词补全时用作单词分隔符的一组字符
   * - COMP_WORDS
     - 含有当前命令行上所有单词的数组
   * - COMPREPLY
     - 含有由shell函数生成的可能补全码的数组
   * - COPROC
     - 含有用于匿名协程I/O的文件描述符的数组
   * - DIRSTACK
     - 含有目录栈当前内容的数组
   * - EMACS
     - 如果设置了该环境变量，则shell认为其使用的是emacs shell缓冲区，同时禁止行编辑功能
   * - ENV
     - 当shell以POSIX模式调用时，每个bash脚本在运行之前都会执行由该环境变量所定义的起始文件
   * - EUID
     - 当前用户的有效用户ID（数字形式）
   * - FCEDIT
     - fc命令使用的默认编辑器
   * - FIGNORE
     - 以冒号分隔的后缀名列表，在文件名补全时会被忽略
   * - FUNCNAME
     - 当前执行的shell函数的名称
   * - FUNCNEST
     - 嵌套函数的最高层级
   * - GLOBIGNORE
     - 以冒号分隔的模式列表，定义了文件名展开时要忽略的文件名集合
   * - GROUPS
     - 含有当前用户属组的数组
   * - histchars
     - 控制历史记录展开的字符（最多可有3个）
   * - HISTCMD
     - 当前命令在历史记录中的编号
   * - HISTCONTROL
     - 控制哪些命令留在历史记录列表中
   * - HISTFILE
     - 保存shell历史记录列表的文件名（默认是.bash_history）
   * - HISTFILESIZE
     - 保存在历史文件中的最大行数
   * - HISTIGNORE
     - 以冒号分隔的模式列表，用来决定哪些命令不存进历史文件
   * - HISTSIZE
     - 最多在历史文件中保存多少条命令
   * - HISTIMEFORMAT
     - 设置后，决定历史文件条目的时间戳的格式字符串
   * - HOSTFILE
     - 含有shell在补全主机名时读取的文件的名称
   * - HOSTNAME
     - 当前主机的名称
   * - HOSTTYPE
     - 当前运行bash shell的机器
   * - IGNOREEOF
     - shell在退出前必须收到连续的EOF字符的数量。如果这个值不存在，默认是1
   * - INPUTRC
     - readline初始化文件名（默认是.inputrc）
   * - LANG
     - shell的语言环境分类
   * - LC_ALL
     - 定义一个语言环境分类，它会覆盖LANG变量
   * - LC_COLLATE
     - 设置对字符串值排序时用的对照表顺序
   * - LC_CTYPE
     - 决定在进行文件名扩展和模式匹配时，如何解释其中的字符
   * - LC_MESSAGES
     - 决定解释前置美元符（ $）的双引号字符串的语言环境设置
   * - LC_NUMERIC
     - 决定格式化数字时的所使用的语言环境设置
   * - LINENO
     - 脚本中当前执行代码的行号
   * - LINES
     - 定义了终端上可见的行数
   * - MACHTYPE
     - 用“ cpu-公司-系统”格式定义的系统类型，例如 x86_64-redhat-linux-gnu
   * - MAILCHECK
     - shell多久查看一次新邮件（以秒为单位，默认值是60）
   * - MAPFILE
     - 含有mapfile命令所读入文本的数组，当没有给出变量名的时候，使用该环境变量
   * - OLDPWD
     - shell之前的工作目录
   * - OPTERR
     - 设置为1时， bash shell会显示getopts命令产生的错误
   * - OSTYPE
     - 定义了shell运行的操作系统
   * - PIPESTATUS
     - 含有前台进程退出状态码的数组
   * - POSIXLY_CORRECT
     - 如果设置了该环境变量， bash会以POSIX模式启动
   * - PPID
     - bash shell父进程的PID
   * - PROMPT_COMMAND
     - 如果设置该环境变量，在显示命令行主提示符之前会执行这条命令
   * - PS1
     - 主命令行提示符字符串
   * - PS2
     - 次命令行提示符字符串
   * - PS3
     - select命令的提示符
   * - PS4
     - 如果使用了bash的-x选项，在命令行显示之前显示的提示符
   * - PWD
     - 当前工作目录
   * - RANDOM
     - 返回一个0~32 767的随机数，对其赋值可作为随机数生成器的种子
   * - READLINE_LINE
     - 保存了readline行缓冲区中的内容
   * - READLINE_POINT
     - 当前readline行缓冲区的插入点位置
   * - REPLY
     - read命令的默认变量
   * - SECONDS
     - 自shell启动到现在的秒数，对其赋值将会重置计时器
   * - SHELL
     - shell的全路径名
   * - SHELLOPTS
     - 已启用bash shell选项列表，由冒号分隔
   * - SHLVL
     - 表明shell层级，每次启动一个新的bash shell时计数加1
   * - TIMEFORMAT
     - 指定了shell显示的时间值的格式
   * - TMOUT
     - select和read命令在没输入的情况下等待多久（以秒为单位）。可用作终端的超时时间，如在 /etc/profile 中添加export TMOUT=600，表示10分钟无操作自动退出。默认值为零，表示无限长
   * - TMPDIR
     - 如果设置成目录名，shell会将其作为临时文件目录
   * - UID
     - 当前用户的真实用户ID（数字形式）
