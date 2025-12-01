CC = gcc
MPICC = mpicc
CFLAGS = -O2 -Wall -std=gnu99 -g

all: seq omp thread2 mpi seq_sort omp_sort thread_sort mpi_sort

seq:
	$(CC) $(CFLAGS) -o bin/seq src/matrix.c src/sequential.c

omp:
	$(CC) $(CFLAGS) -fopenmp -o bin/omp src/matrix.c src/omp.c

thread2:
	$(CC) $(CFLAGS) -pthread -o bin/thread2 src/matrix.c src/thread2.c

mpi:
	$(MPICC) $(CFLAGS) -o bin/mpi src/matrix.c src/mpi.c

# Sorting Programs
seq_sort: src/sorting/sequential_sort.c
	gcc -O2 -Wall -std=gnu99 -g -o bin/seq_sort src/sorting/sequential_sort.c

omp_sort: src/sorting/omp_sort.c
	gcc -O2 -Wall -std=gnu99 -g -fopenmp -o bin/omp_sort src/sorting/omp_sort.c

thread_sort: src/sorting/thread_sort.c
	gcc -O2 -Wall -std=gnu99 -g -pthread -o bin/thread_sort src/sorting/thread_sort.c

mpi_sort: src/sorting/mpi_sort.c
	mpicc -O2 -Wall -std=gnu99 -g -o bin/mpi_sort src/sorting/mpi_sort.c

all: seq_sort omp_sort thread_sort mpi_sort
