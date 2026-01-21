import csv
from statistics import median

data = {}
with open("out/results.csv", newline="") as f:
    r = csv.DictReader(f)
    for row in r:
        wl = row["workload"]
        ms = float(row["ms"])
        data.setdefault(wl, []).append(ms)

for wl, xs in data.items():
    xs_sorted = sorted(xs)
    p50 = median(xs_sorted)
    p95 = xs_sorted[int(0.95 * (len(xs_sorted)-1))]
    print(f"{wl}: runs={len(xs_sorted)} p50={p50:.3f}ms p95={p95:.3f}ms min={min(xs_sorted):.3f}ms max={max(xs_sorted):.3f}ms")
