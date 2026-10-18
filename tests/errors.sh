#!/usr/bin/env bash
# Edge cases. Invalid input must print "Error" on stderr (nothing on stdout)
# and exit with status 1; valid edge cases must succeed.

PS=${PUSH_SWAP:-./push_swap}
CK=${CHECKER:-./checker}
OPT=                                  # strategy option under test ("" = default)
fail=0
tmp=$(mktemp)
trap 'rm -f "$tmp"' EXIT

bad() { echo "FAIL: $*"; fail=1; }

# invalid <args>: "Error" on stderr only, exit status 1
invalid() {
	local err rc
	err=$("$PS" "$@" 2>&1 > /dev/null); rc=$?
	[ $rc -eq 1 ] && [ "$err" = Error ] && [ -z "$("$PS" "$@" 2> /dev/null)" ] \
		|| bad "should be an error: $*"
}

# valid <args>: exit status 0 and no output at all
valid() {
	local out
	out=$("$PS" "$@" 2>&1) && [ -z "$out" ] || bad "should succeed silently: $*"
}

# sorts <numbers>: push_swap $OPT | checker must answer OK
sorts() {
	"$PS" $OPT "$@" > "$tmp" || { bad "crash ($OPT): $*"; return; }
	[ "$("$CK" "$@" < "$tmp" 2>&1)" = OK ] || bad "not sorted ($OPT): $*"
}

# check <expected> <stdin> <numbers>: checker answer (OK, KO or Error)
check() {
	local want=$1 input=$2 got
	shift 2
	got=$(printf "$input" | "$CK" "$@" 2>&1)
	[ "$got" = "$want" ] || bad "checker '$input' on '$*': got '$got', want '$want'"
}

# --- push_swap: invalid input ---------------------------------------------
invalid a
invalid 1 a 3
invalid 1 2 3 2                       # duplicate
invalid 0 -0                          # same value written twice
invalid 2147483648                    # > INT_MAX
invalid -2147483649                   # < INT_MIN
invalid 99999999999999999999999999
invalid 1 -                           # sign without digits
invalid ""
invalid "1 2" 3                       # a quoted list must be the only argument
invalid --unknown 1 2
invalid --bench                       # option without numbers
invalid --simple --medium 1 2         # two strategies
invalid --benchmark 1 2               # exact option names only

# --- push_swap: valid edge cases ------------------------------------------
valid                                 # no argument: nothing to do
valid 42
valid 1 2 3                           # already sorted
valid "1 2 3"
valid -2147483648 2147483647

# --- push_swap | checker: the output really sorts --------------------------
sorts 2147483647 -2147483648 0
sorts +3 -1 02
sorts "  3   2 1 "
for OPT in "" --simple --medium --complex --turk; do   # "" = adaptive
	for input in "2 1" "3 2 1" "3 1 2" "2 3 1" "1 3 2" "2 1 3" \
		"4 3 2 1" "5 4 3 2 1" "5 1 4 2 3"; do
		sorts $input
	done
done

# --- checker ----------------------------------------------------------------
check OK    'sa\n' 2 1
check OK    'sa'   2 1                # last line without newline
check OK    ''     1 2 3
check KO    ''     2 1
check KO    'pb\n' 1 2                # b is not empty
check OK    'pb\npa\n' 1 2
check OK    'rra\n' 2 3 1
check KO    'rra\nrra\n' 2 3 1
check KO    'pa\npb\nsa\nsb\nra\nrb\nrra\nrrb\nss\nrr\nrrr\n' 7   # degenerate ops
check Error 'bogus\n' 1 2
check Error 'sa \n' 2 1               # padded line
check Error 'SA\n' 2 1                # case sensitive
check Error '\n' 2 1                  # empty line
check Error 'sa\n' 1 1                # invalid stack
check Error 'sa\n' a
[ -z "$("$CK" 2>&1 < /dev/null)" ] || bad "checker without argument must be silent"
[ -z "$(printf 'bogus\n' | "$CK" 1 2 2> /dev/null)" ] || bad "checker errors go to stderr"

[ $fail -eq 0 ] && echo "errors.sh: all edge cases passed"
exit $fail
