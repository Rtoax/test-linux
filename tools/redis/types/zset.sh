#!/bin/bash
set -e

zadd() {
	redis-cli ZADD zset1 $@
}
zdel() {
	redis-cli ZDEL zset1 $@
}
zrange() {
	redis-cli ZRANGE zset1 $@
}

zadd 1 rongtao
zadd 2 lihaiqiang
zrange 0 10
