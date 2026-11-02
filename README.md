# SchedBench

[![CI](https://github.com/One-Of-The-Ekhandes/schedbench/actions/workflows/ci.yml/badge.svg)](https://github.com/One-Of-The-Ekhandes/schedbench/actions/workflows/ci.yml)

SchedBench is a small experiment suite to observe how Linux schedules different kinds of work.

It does not try to benchmark a machine "in general". It produces repeatable timing data you can reason about: how long a CPU-bound task takes compared with a task that mostly waits.

## What it includes

| File | What it does |
|---|---|
| `workloads/cpu_bound.c` | Deterministic CPU-heavy loop (200 million multiply-add steps on a `volatile` value, so the compiler cannot remove it). Optional argument: number of iterations. |
| `workloads/io_bound.c` | Sleep-based latency workload: sleeps 10 ms, 200 times (about 2 seconds). Optional arguments: sleep milliseconds, repetitions. |
| `run.sh` | Runs both workloads N times (default 20) and writes `run,workload,ms` rows to `out/results.csv`. |
| `analyze.py` | Prints p50, p95, min and max latency per workload from the CSV. |

Both workloads time themselves with `clock_gettime(CLOCK_MONOTONIC)`, a clock that only moves forward, so durations stay correct even if the system time is adjusted.

## Build (Linux or WSL)

```bash
make            # gcc -O2 -Wall -Wextra -std=c11
```

## Run

```bash
./run.sh 20             # 20 runs of each workload -> out/results.csv
python3 analyze.py      # p50 / p95 / min / max per workload
```

Example output shape:

```text
cpu_bound: runs=20 p50=...ms p95=...ms min=...ms max=...ms
io_bound:  runs=20 p50=...ms p95=...ms min=...ms max=...ms
```

`io_bound` should report a little over 2,000 ms per run (200 sleeps of 10 ms plus wake-up delays). The amount above 2,000 ms shows how long the scheduler takes to wake the process after each sleep.

## Experiments to try

- Run `./run.sh` while another CPU-heavy process is running and compare p95 for both workloads.
- Pin a workload to one core with `taskset -c 0 ./workloads/cpu_bound`.
- Lower a workload's priority with `nice -n 19` and compare.

## Clean

```bash
make clean
```
