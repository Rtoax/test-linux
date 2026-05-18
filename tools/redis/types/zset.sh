#!/bin/bash
set -e

zadd() {
	redis-cli ZADD zset1 $@
}
zrange() {
	redis-cli ZRANGE zset1 $@
}
zpopmin() {
	redis-cli ZPOPMIN zsert $@
}
zpopmax() {
	redis-cli ZPOPMAX zsert $@
}

zadd 1 rongtao
zadd 2 lihaiqiang
zrange 0 10
zpopmin
zpopmax
