#!/bin/bash
set -e

key="zset2"

zadd() {
	redis-cli ZADD ${key} $@
}
zrange() {
	redis-cli ZRANGE ${key} $@
}
zpopmin() {
	redis-cli ZPOPMIN ${key} $@
}
zpopmax() {
	redis-cli ZPOPMAX ${key} $@
}
zincrby() {
	redis-cli ZINCRBY ${key} $@
}
zcard() {
	redis-cli ZCARD ${key}
}
zscore() {
	redis-cli ZSCORE ${key}
}

zadd 1 rongtao1
zadd 2 rongtao2
zadd 3 rongtao3
zscore rongtao3

zrange 0 10

zincrby 10 rongtao1

zrange 0 10

zpopmin
zpopmax

# List all
zrange 0 -1
zcard
