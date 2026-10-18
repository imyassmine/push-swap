#!/usr/bin/env bash
# Sorts <runs> random sets of <n> values and checks each result with ./checker.
#
#   tests/run.sh <n> <runs> [push_swap options]
#   CHECKER=./checker_linux tests/run.sh 100 50 --turk
#
# Prints the min / avg / max number of operations. Stops at the first crash or KO.

PS=${PUSH_SWAP:-./push_swap}
CK=${CHECKER:-./checker}

[ $# -ge 2 ] || { echo "usage: $0 <n> <runs> [push_swap options]" >&2; exit 2; }
n=$1 runs=$2
shift 2

ops=$(mktemp)
trap 'rm -f "$ops"' EXIT
min=2147483647 max=0 sum=0

for ((i = 0; i < runs; i++)); do
	args=$(shuf -i 0-100000 -n "$n" | tr '\n' ' ')
	"$PS" "$@" $args > "$ops" || { echo "CRASH ($*): $args"; exit 1; }
	[ "$("$CK" $args < "$ops")" = OK ] || { echo "KO ($*): $args"; exit 1; }
	count=$(( $(wc -l < "$ops") ))
	(( count < min )) && min=$count
	(( count > max )) && max=$count
	(( sum += count ))
done

printf "n=%-5s runs=%-4s %-12s ops: min=%-6s avg=%-6s max=%s\n" \
	"$n" "$runs" "$*" "$min" "$((sum / runs))" "$max"
