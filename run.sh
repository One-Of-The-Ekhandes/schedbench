#!/usr/bin/env bash
set -e

RUNS="${1:-20}"

mkdir -p out
CSV="out/results.csv"

echo "run,workload,ms" > "$CSV"

for i in $(seq 1 "$RUNS"); do
  cpu=$(./workloads/cpu_bound | cut -d= -f2)
  echo "$i,cpu_bound,$cpu" >> "$CSV"

  io=$(./workloads/io_bound | cut -d= -f2)
  echo "$i,io_bound,$io" >> "$CSV"
done

echo "wrote $CSV"
