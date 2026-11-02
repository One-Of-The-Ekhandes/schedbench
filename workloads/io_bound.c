#define _POSIX_C_SOURCE 200809L /* expose clock_gettime, CLOCK_MONOTONIC and nanosleep under -std=c11 */
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <errno.h>

#if defined(_WIN32)
#include <windows.h>
static void sleep_ms(int ms) { Sleep(ms); }
#else
/* nanosleep is the POSIX replacement for usleep, which was removed in POSIX.1-2008. */
static void sleep_ms(int ms) {
    struct timespec req = { ms / 1000, (long)(ms % 1000) * 1000000L };
    while (nanosleep(&req, &req) == -1 && errno == EINTR) { /* resume if interrupted by a signal */ }
}
#endif

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
    int ms_sleep = 10;
    int reps = 200;
    if (argc > 1) sscanf(argv[1], "%d", &ms_sleep);
    if (argc > 2) sscanf(argv[2], "%d", &reps);
    if (ms_sleep < 1) ms_sleep = 1;
    if (reps < 1) reps = 1;

    uint64_t t0 = now_ns();
    for (int i = 0; i < reps; i++) {
        sleep_ms(ms_sleep);
    }
    uint64_t t1 = now_ns();

    double ms = (double)(t1 - t0) / 1e6;
    printf("io_bound_ms=%.3f\n", ms);
    return 0;
}
