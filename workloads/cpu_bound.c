#include <stdio.h>
#include <stdint.h>
#include <time.h>

static inline uint64_t now_ns(void) {
#if defined(CLOCK_MONOTONIC)
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (uint64_t)ts.tv_sec * 1000000000ULL + (uint64_t)ts.tv_nsec;
#else
    return (uint64_t)clock() * (1000000000ULL / CLOCKS_PER_SEC);
#endif
}

int main(int argc, char **argv) {
    // default work size
    uint64_t iters = 200000000ULL;
    if (argc > 1) {
        uint64_t v = 0;
        if (sscanf(argv[1], "%llu", (unsigned long long*)&v) == 1 && v > 0) iters = v;
    }

    volatile uint64_t x = 1;
    uint64_t t0 = now_ns();
    for (uint64_t i = 0; i < iters; i++) {
        x = x * 1664525ULL + 1013904223ULL; // cheap deterministic work
    }
    uint64_t t1 = now_ns();

    double ms = (double)(t1 - t0) / 1e6;
    printf("cpu_bound_ms=%.3f\n", ms);
    return 0;
}
