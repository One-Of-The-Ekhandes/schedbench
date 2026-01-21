\# SchedBench



SchedBench is a small experiment suite to observe scheduling behaviour under different workload types.



It does not try to benchmark a machine “in general”.

It is meant to produce repeatable timing data you can reason about.



\## What it includes

\- `cpu\_bound`: deterministic CPU-heavy loop

\- `io\_bound`: sleep-based latency workload

\- `run.sh`: runs both workloads repeatedly and writes results to CSV

\- `analyze.py`: prints p50 / p95 latency summaries from the CSV



\## Build (Linux/WSL)

```bash

make



