#!/bin/bash
# zset - The non-repeatable nature of Set elements enables automatic sorting by
# associating a score with each element.
set -e

key="zset2"

cli() {
	echo -e "\033[1;32m${@}\033[m"
	eval "redis-cli ${@}"
}

# Insert and updates
zadd() {
	cli ZADD ${key} $@
}
zrem() {
	cli ZREM ${key} $@
}
zincrby() {
	cli ZINCRBY ${key} $@
}

# Get the score of a specified member
zscore() {
	cli ZSCORE ${key} $@
}
# Get scores in batches.
# ZMSCORE key member [member ...]
zmscore() {
	cli ZMSCORE ${key} $@
}
# Gets the total number of elements of the collection.
zcard() {
	cli ZCARD ${key} $@
}
# Count the number of members with scores in the range [min, max].
# ZCOUNT key min max
zcount() {
	cli ZCOUNT ${key} $@
}

# Get in positive order by rank (index, starting with 0). 0 - 1 means get
# everything.
# ZRANGE key start stop [WITHSCORES]
zrange() {
	cli ZRANGE ${key} $@
}
# ZREVRANGE key start stop [WITHSCORES]
zrevrange() {
	cli ZREVRANGE ${key} $@
}
# Acquire in positive order of score range.
# ZRANGEBYSCORE key min max [WITHSCORES] [LIMIT offset count]
zrangebyscore() {
	cli ZRANGEBYSCORE ${key} $@
}
zrevrangebyscore() {
	cli ZREVRANGEBYSCORE ${key} $@
}

# Gets the positive/negative ranking of members (starting with 0).
# ZRANK key member
zrank() {
	cli ZRANK ${key} $@
}
# ZREVRANK key member
zrevrank() {
	cli ZREVRANK ${key} $@
}

zpopmin() {
	cli ZPOPMIN ${key} $@
}
zpopmax() {
	cli ZPOPMAX ${key} $@
}

zadd 1 rongtao1
zadd 2 rongtao2
zadd 3 rongtao3
zcard
zrange 0 -1
zrevrange 0 -1
zrangebyscore 2 3
zrevrangebyscore 2 3
zrank rongtao3
zrevrank rongtao3

zscore rongtao3
zmscore rongtao1 rongtao2 rongtao3
zcount 2 3

zrange 0 10
zrevrange 0 10

zscore rongtao1
zincrby 10 rongtao1
zscore rongtao1

zrem rongtao1
zrange 0 10

zpopmin
zpopmax

# List all
zrange 0 -1
zcard
