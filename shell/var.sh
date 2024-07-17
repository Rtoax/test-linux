#!/bin/bash
#形式                      说明
#${var}              变量本来的值
#${var:-word}        如果变量 var 为空或已被删除(unset)，
#                    那么返回 word，但不改变 var 的值
#${var:=word}        如果变量 var 为空或已被删除(unset)，
#                    那么返回 word，并将 var 的值设置为 word。
#${var:?message}     如果变量 var 为空或已被删除(unset)，
#                    那么将消息 message 送到标 准错误输出，
#                    可以用来检测变量 var 是否可以被正常赋值。
#                    若此替换出现在 Shell 脚本中，那么脚本将停止运行。
#${var:+word}        如果变量 var 被定义，那么返回 word，但不改变 var 的值。

var=
message="错啦老铁，var没被定义"

echo ${var:+$message}
var=1
echo ${var:+$message}
unset var

echo ${var:-$message}
unset var

echo ${var:=$message}
echo var=$var
unset var

# shell exit here
echo ${var:?$message} || true

