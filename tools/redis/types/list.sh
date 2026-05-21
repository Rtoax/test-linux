#!/bin/bash
set -e

cli() {
	redis-cli "$@"
}

key="tasks"

cli RPUSH ${key} "task1" "task2" "task3"
cli LRANGE ${key} 0 -1

cli LSET ${key} 10 "task2.modify"
cli LRANGE ${key} 0 -1

cli LINSERT ${key} BEFORE "task2.modify" "task2.before"
cli LINSERT ${key} AFTER "task2.modify" "task2.after"
cli LRANGE ${key} 0 -1

cli LPUSHX ${key} "task.lpushx"
cli RPUSHX ${key} "task.rpushx"
cli LRANGE ${key} 0 -1

cli LREM ${key} 2 "task2"
cli LRANGE ${key} 0 -1

cli LREM ${key} -2 "task3"
cli LRANGE ${key} 0 -1

cli LPOP ${key}
cli LRANGE ${key} 0 -1

cli DEL ${key}
