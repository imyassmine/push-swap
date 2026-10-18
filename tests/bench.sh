#!/usr/bin/env bash
# Markdown table of operation counts per strategy (random inputs, verified by
# ./checker). Usage: tests/bench.sh [runs]   (default: 20)

runs=${1:-20}

echo "| n | strategy | min | avg | max |"
echo "|---|---|---|---|---|"
for n in 100 500; do
	for s in simple medium complex turk adaptive; do
		line=$(./tests/run.sh "$n" "$runs" "--$s") || { echo "$line"; exit 1; }
		sed -E "s/.*min=([0-9]+) +avg=([0-9]+) +max=([0-9]+).*/| $n | $s | \1 | \2 | \3 |/" <<< "$line"
	done
done
