# push_swap

Sort a list of unique integers using **two stacks** (`a` and `b`) and a restricted
set of 11 operations. `push_swap` prints the instruction sequence; the bundled
`checker` replays it and tells you whether the result is sorted.

This repository merges two earlier 42 projects into one code base:

| Origin | What it brought |
|---|---|
| *push_swap* (first version) | the **Turk** algorithm (greedy, cost based) and the **checker** (stdin + `get_next_line`) |
| *push_swap* (strategies version) | pluggable **strategies** (`--simple/--medium/--complex/--adaptive`), the **disorder metric**, the `--bench` report, the `lib/` library |

Everything is written in C (`-Wall -Wextra -Werror`), with no dependency besides libc.

## Build

```sh
make          # push_swap
make check    # checker
make test     # edge cases + every strategy on 5 / 100 / 500 values
make bench    # markdown table of operation counts per strategy
make debug    # rebuild with AddressSanitizer + UBSan (then `make re`)
```

## Usage

```sh
./push_swap 2 1 3 6 5 8
./push_swap "2 1 3 6 5 8"                       # one quoted argument also works
./push_swap --turk 4 67 3 87 23
./push_swap --bench --complex 4 2 3 1           # report on stderr

ARG="4 67 3 87 23"
./push_swap $ARG | ./checker $ARG                # prints OK / KO
```

| Option | Behaviour |
|---|---|
| `--simple` | selection sort |
| `--medium` | chunk sort |
| `--complex` | binary radix sort |
| `--turk` | Turk algorithm |
| `--adaptive` | picks one of the three above from the measured disorder (**default**) |
| `--bench` | prints disorder, strategy, total and per-operation counts on **stderr** |

Options come first, in any order (at most one strategy). Invalid input prints
`Error` on stderr and exits with status 1: non-integers, values outside the
`int` range, duplicates, unknown options. No argument prints nothing.
Inputs of 2 or 3 values always use a dedicated routine (at most 2 operations
for 3 values), whatever the strategy.

## Strategies

| Strategy | Technique | Operations (bound) |
|---|---|---|
| `simple` | push the minimum to `b` until 3 values remain, sort them, push everything back | O(n²) |
| `medium` | push windows of ≈ √n ranks to `b` (small ranks sink), then bring the maxima back one by one | O(n√n) |
| `complex` | LSD radix sort on the ranks: one pass per bit, each pass ≤ 2n operations | O(n log n) |
| `turk` | push all but 3 values to `b`, then repeatedly insert the **cheapest** element of `b` into `a` (rotations of both stacks, merged into `rr`/`rrr`), finally rotate the minimum on top | heuristic, O(n²) worst case |
| `adaptive` | disorder `< 0.2` → simple, `< 0.5` → medium, otherwise complex | depends on the pick |

*Disorder* is the fraction of out-of-order pairs: `0` for a sorted input, `1` for a
reversed one, ≈ `0.5` for a random permutation.

Turk has no tight bound: its cost per insertion is only bounded by O(n). Measured
growth (table below) sits between n·log n and n·√n for the sizes tested, so it is
**not** advertised as O(n log n).

## Results

Operation counts on random permutations, every run verified by `./checker`
(`make bench`, 20 runs per cell):

| n | strategy | min | avg | max |
|---|---|---|---|---|
| 100 | simple | 1310 | 1447 | 1634 |
| 100 | medium | 550 | 591 | 633 |
| 100 | complex | 1084 | 1084 | 1084 |
| 100 | turk | 514 | 562 | 612 |
| 100 | adaptive | 542 | 784 | 1084 |
| 500 | simple | 30892 | 32331 | 33635 |
| 500 | medium | 5090 | 5272 | 5446 |
| 500 | complex | 6784 | 6784 | 6784 |
| 500 | turk | 4317 | 4552 | 4854 |
| 500 | adaptive | 5113 | 5797 | 6784 |

Growth of the average with n (3 runs per cell). The last column of each strategy
is the ratio to its reference function; a flat ratio confirms the class.

| n | simple (÷ n²) | medium (÷ n√n) | complex (÷ n log₂n) | turk (÷ n log₂n) |
|---|---|---|---|---|
| 100 | 1505 (0.151) | 599 (0.599) | 1084 (1.632) | 595 (0.896) |
| 200 | 5351 (0.134) | 1482 (0.524) | 2468 (1.614) | 1402 (0.917) |
| 500 | 32554 (0.130) | 5281 (0.472) | 6784 (1.513) | 4571 (1.020) |
| 1000 | 125444 (0.125) | 14110 (0.446) | 15068 (1.512) | 11563 (1.160) |
| 2000 | – | 38073 (0.426) | 33136 (1.511) | 29910 (1.364) |

Observations:

- `complex` is the only strategy with a perfectly flat ratio. Its constant is
  high, so `medium` and `turk` do fewer operations up to n = 1000; `complex`
  overtakes `medium` somewhere between n = 1000 and n = 2000.
- On tiny inputs the radix is wasteful: for 5 values `complex` needs 25
  operations against about 7 for `simple` or `turk`, and `adaptive` inherits
  that on disordered inputs.
- A random permutation has a disorder of about 0.5, right on the `adaptive`
  threshold: about half of random inputs go to `medium`, half to `complex`.
  That is why `adaptive` averages more than `medium` at n ≤ 500. The thresholds
  are heuristics and live in a single place, `resolve_strategy()`.
- Turk does the fewest operations up to n = 2000 but recomputes targets and
  costs for the whole of `b` at every step (≈ n³/6 elementary steps): sorting
  2000 values takes about 5 s, against 0.1 s for `complex` and 0.2 s for `medium`.

## Project layout

```
include/push_swap.h      types and public prototypes
lib/                     libft + ft_printf (with ft_dprintf) + get_next_line -> libft.a
src/
├── main.c
├── parsing/             options.c (--flags) · numbers.c (strict int parsing, duplicates)
├── stack/               linked-list stack, ranks (index), disorder metric
├── ops/                 engine.c  silent primitives, safe on empty stacks
│                        table.c   one table: name <-> operation (push_swap + checker)
│                        emit.c    apply + print + count;  ops_*.c  sa/pb/rra… wrappers
├── algo/                dispatch.c · small.c · selection.c · chunks.c · radix.c
│   └── turk/            push_to_b · target · cost · execute · turk
├── bench/               --bench report
├── checker/             stdin instruction reader and verdict
└── utils/
tests/                   run.sh · errors.sh · bench.sh
```

Pipeline: `parse_options` → `parse_numbers` → ranks (`index_stack`) →
`compute_disorder` → `sort_stack` (resolves `adaptive`, calls the strategy) →
`op_run` for every instruction → optional `print_benchmark`.

### Design decisions

- **One operation table for both programs.** `ops/table.c` maps each of the 11
  operations to its name and primitive. `push_swap` prints the name and updates
  the statistics (`op_run`); `checker` parses a line back into an operation
  (`op_from_name`) and applies it silently (`op_apply`). No duplicated
  `*_bonus.c` operations.
- **Operations never crash**: on an empty or one-element stack they do nothing,
  like the official checker.
- **`adaptive` is resolved once** (`resolve_strategy`), and the benchmark reuses
  it, so the thresholds cannot drift between the sorter and its report.
- **Reports go to stderr**: stdout only carries instructions, so
  `push_swap --bench … | checker …` keeps working.
- **Strict parsing**: overflow is checked digit by digit, not after the fact.
- **`lib/` has no duplicated symbols**: `get_next_line` is built on libft and
  provides `get_next_line_clear()` to release its internal state.

## Checker

```sh
printf 'sa\nrra\n' | ./checker 2 1 3       # OK / KO on stdout
printf 'bogus\n'   | ./checker 2 1 3       # Error on stderr
```

`OK` means stack `a` is sorted **and** stack `b` is empty. A last line without
`\n` is accepted; an unknown, empty or padded line is an error.

## Tests

`make test` runs `tests/errors.sh` (invalid input, boundaries, checker verdicts,
operations on empty stacks) then `tests/run.sh` on every strategy.
`tests/run.sh <n> <runs> [options]` can also drive the official checker:
`CHECKER=./checker_linux tests/run.sh 100 50 --turk`.
GitHub Actions builds with `-Werror`, runs the suite and repeats it under
ASan + UBSan.

## Resources

- [Radix sort](https://en.wikipedia.org/wiki/Radix_sort)
- [GNU Make manual](https://www.gnu.org/software/make/manual/)
