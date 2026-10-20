# push_swap

[![CI](https://github.com/imyassmine/push-swap/actions/workflows/ci.yml/badge.svg)](https://github.com/imyassmine/push-swap/actions/workflows/ci.yml)
![C](https://img.shields.io/badge/language-C-blue)

**Sorting integers through two stacks and 11 instructions.** Five strategies
in one binary — from selection sort to an O(n log n) radix and a greedy "Turk"
heuristic — with a disorder-driven adaptive selector, a bundled checker and an
instrumented benchmark mode.

*Algorithms · complexity analysis · benchmarking · strict parsing · C*

## Highlights

- **Five strategies + adaptive dispatch** — selection `O(n²)`, chunk sort
  `O(n√n)`, LSD radix `O(n log n)`, Turk greedy insertion, and an adaptive mode
  that measures input disorder and picks the strategy that fits it.
- **Measured, not claimed** — every instruction is counted; `--bench` reports
  disorder, strategy, total and per-operation counts, and every benchmark run
  is verified by the bundled checker.
- **Single source of truth** — one table maps each of the 11 operations to its
  name and primitive: `push_swap` prints and counts it, `checker` parses and
  applies it. No duplicated instruction code.
- **Hardened parsing** — digit-by-digit overflow detection, duplicate and
  `int`-range rejection, exact option matching, nothing on stdout for invalid
  input.

## Quick start

```console
$ make
$ make check
$ ./push_swap 2 1 3 6 5 8 | ./checker 2 1 3 6 5 8
OK
$ ./push_swap --bench --complex 4 67 3 87 23   # report on stderr
```

## Results

Average number of operations on random permutations, 20 runs per cell, each
run validated by `./checker` (`make bench`):

| Strategy | 100 values | 500 values |
| --- | ---: | ---: |
| `--simple` | 1472 | 32449 |
| `--medium` | 588 | 5258 |
| `--complex` | 1084 | 6784 |
| `--turk` | 579 | 4540 |
| `--adaptive` | 887 | 5860 |

`--complex` is the only strategy with a flat O(n log n) curve. `--turk` needs
the fewest operations on random inputs, but it recomputes targets and costs for
the whole of `b` at every step: on 2,000 values it takes ~9.5 s against ~0.25 s
for `--complex`. The adaptive thresholds (0.2 / 0.5) live in a single function,
`resolve_strategy()`.

## Strategies

| Option | Algorithm | Complexity |
| --- | --- | --- |
| `--simple` | push the minimum to `b` until 3 values remain, then rebuild `a` | O(n²) |
| `--medium` | push √n-rank windows to `b`, bring the maxima back one by one | O(n√n) |
| `--complex` | LSD radix sort on ranks, one pass per bit | O(n log n) |
| `--turk` | greedy cheapest-insertion from `b` into `a`, shared rotations merged | heuristic |
| `--adaptive` | disorder `< 0.2` → simple, `< 0.5` → medium, otherwise complex | — |

## Testing

```console
$ make test    # edge cases + every strategy on 5 / 100 / 500 values
$ make bench   # markdown table of operation counts (20 runs per cell)
$ make debug   # rebuild with -g3 -fsanitize=address,undefined
```

`tests/errors.sh` covers invalid input, boundaries, checker verdicts and
operations on empty stacks; `tests/run.sh <n> <runs> [options]` drives any
compatible checker through `CHECKER`:
`CHECKER=./checker tests/run.sh 100 50 --turk`. CI builds with `-Werror` and
runs the full suite under ASan + UBSan.

## Under the hood

- `src/parsing/` — strict options and numbers, duplicate detection.
- `src/stack/` — linked-list stacks, rank indexing, disorder metric.
- `src/algo/` — dispatch and four strategies; `src/algo/turk/` holds the
  target/cost/execute pipeline.
- `src/ops/` — engine (silent primitives), operation table, emit (apply, print,
  count).
- `--bench` writes to stderr, keeping stdout machine-readable for pipes.
- ~1.3k LOC of C, no dependency besides libc.

---
*Built at [42 Paris](https://42.fr) by [Yassmine Abdallah (@imyassmine)](https://github.com/imyassmine)
and rumenage.*
