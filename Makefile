CC=gcc
CFLAGS=-O2 -Wall -Wextra -std=c11

all: cpu io

cpu: workloads/cpu_bound.c
	$(CC) $(CFLAGS) -o workloads/cpu_bound workloads/cpu_bound.c

io: workloads/io_bound.c
	$(CC) $(CFLAGS) -o workloads/io_bound workloads/io_bound.c

clean:
	rm -f workloads/cpu_bound workloads/io_bound
	rm -rf out
