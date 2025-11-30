#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

void bubble_sort(int *arr, int n) {
    for(int i=0; i<n-1; i++)
        for(int j=0; j<n-i-1; j++)
            if(arr[j] > arr[j+1]) {
                int tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp;
            }
}

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(argc != 2) {
        if(rank==0) printf("Usage: %s <input_file>\n", argv[0]);
        MPI_Finalize();
        return 1;
    }

    int *arr = NULL;
    int n;
    if(rank == 0) {
        FILE *f = fopen(argv[1], "r");
        if(!f) { printf("Cannot open file.\n"); MPI_Finalize(); return 1; }
        fscanf(f, "%d", &n);
        arr = malloc(n * sizeof(int));
        for(int i=0; i<n; i++) fscanf(f, "%d", &arr[i]);
        fclose(f);
    }

    // Broadcast array size to all processes
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    int chunk = n / size;
    int remainder = n % size;
    int local_n = (rank < remainder) ? chunk+1 : chunk;
    int *local_arr = malloc(local_n * sizeof(int));

    // Scatter the array
    int *sendcounts = NULL;
    int *displs = NULL;
    if(rank==0) {
        sendcounts = malloc(size * sizeof(int));
        displs = malloc(size * sizeof(int));
        int offset=0;
        for(int i=0;i<size;i++){
            sendcounts[i] = (i<remainder)? chunk+1 : chunk;
            displs[i] = offset;
            offset += sendcounts[i];
        }
    }

    MPI_Scatterv(arr, sendcounts, displs, MPI_INT,
                 local_arr, local_n, MPI_INT, 0, MPI_COMM_WORLD);

    // Local sort
    bubble_sort(local_arr, local_n);

    // Gather back
    MPI_Gatherv(local_arr, local_n, MPI_INT,
                arr, sendcounts, displs, MPI_INT,
                0, MPI_COMM_WORLD);

    if(rank==0) {
        for(int i=0;i<n;i++) printf("%d ", arr[i]);
        printf("\n");
        free(arr); free(sendcounts); free(displs);
    }

    free(local_arr);
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

void bubble_sort(int *arr, int n) {
    for(int i=0; i<n-1; i++)
        for(int j=0; j<n-i-1; j++)
            if(arr[j] > arr[j+1]) {
                int tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp;
            }
}

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(argc != 2) {
        if(rank==0) printf("Usage: %s <input_file>\n", argv[0]);
        MPI_Finalize();
        return 1;
    }

    int *arr = NULL;
    int n;
    if(rank == 0) {
        FILE *f = fopen(argv[1], "r");
        if(!f) { printf("Cannot open file.\n"); MPI_Finalize(); return 1; }
        fscanf(f, "%d", &n);
        arr = malloc(n * sizeof(int));
        for(int i=0; i<n; i++) fscanf(f, "%d", &arr[i]);
        fclose(f);
    }

    // Broadcast array size to all processes
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    int chunk = n / size;
    int remainder = n % size;
    int local_n = (rank < remainder) ? chunk+1 : chunk;
    int *local_arr = malloc(local_n * sizeof(int));

    // Scatter the array
    int *sendcounts = NULL;
    int *displs = NULL;
    if(rank==0) {
        sendcounts = malloc(size * sizeof(int));
        displs = malloc(size * sizeof(int));
        int offset=0;
        for(int i=0;i<size;i++){
            sendcounts[i] = (i<remainder)? chunk+1 : chunk;
            displs[i] = offset;
            offset += sendcounts[i];
        }
    }

    MPI_Scatterv(arr, sendcounts, displs, MPI_INT,
                 local_arr, local_n, MPI_INT, 0, MPI_COMM_WORLD);

    // Local sort
    bubble_sort(local_arr, local_n);

    // Gather back
    MPI_Gatherv(local_arr, local_n, MPI_INT,
                arr, sendcounts, displs, MPI_INT,
                0, MPI_COMM_WORLD);

    if(rank==0) {
        for(int i=0;i<n;i++) printf("%d ", arr[i]);
        printf("\n");
        free(arr); free(sendcounts); free(displs);
    }

    free(local_arr);
    MPI_Finalize();
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

void bubble_sort(int *arr, int n) {
    for(int i=0; i<n-1; i++)
        for(int j=0; j<n-i-1; j++)
            if(arr[j] > arr[j+1]) {
                int tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp;
            }
}

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(argc != 2) {
        if(rank==0) printf("Usage: %s <input_file>\n", argv[0]);
        MPI_Finalize();
        return 1;
    }

    int *arr = NULL;
    int n;
    if(rank == 0) {
        FILE *f = fopen(argv[1], "r");
        if(!f) { printf("Cannot open file.\n"); MPI_Finalize(); return 1; }
        fscanf(f, "%d", &n);
        arr = malloc(n * sizeof(int));
        for(int i=0; i<n; i++) fscanf(f, "%d", &arr[i]);
        fclose(f);
    }

    // Broadcast array size to all processes
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    int chunk = n / size;
    int remainder = n % size;
    int local_n = (rank < remainder) ? chunk+1 : chunk;
    int *local_arr = malloc(local_n * sizeof(int));

    // Scatter the array
    int *sendcounts = NULL;
    int *displs = NULL;
    if(rank==0) {
        sendcounts = malloc(size * sizeof(int));
        displs = malloc(size * sizeof(int));
        int offset=0;
        for(int i=0;i<size;i++){
            sendcounts[i] = (i<remainder)? chunk+1 : chunk;
            displs[i] = offset;
            offset += sendcounts[i];
        }
    }

    MPI_Scatterv(arr, sendcounts, displs, MPI_INT,
                 local_arr, local_n, MPI_INT, 0, MPI_COMM_WORLD);

    // Local sort
    bubble_sort(local_arr, local_n);

    // Gather back
    MPI_Gatherv(local_arr, local_n, MPI_INT,
                arr, sendcounts, displs, MPI_INT,
                0, MPI_COMM_WORLD);

    if(rank==0) {
        for(int i=0;i<n;i++) printf("%d ", arr[i]);
        printf("\n");
        free(arr); free(sendcounts); free(displs);
    }

    free(local_arr);
    MPI_Finalize();
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

void bubble_sort(int *arr, int n) {
    for(int i=0; i<n-1; i++)
        for(int j=0; j<n-i-1; j++)
            if(arr[j] > arr[j+1]) {
                int tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp;
            }
}

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(argc != 2) {
        if(rank==0) printf("Usage: %s <input_file>\n", argv[0]);
        MPI_Finalize();
        return 1;
    }

    int *arr = NULL;
    int n;
    if(rank == 0) {
        FILE *f = fopen(argv[1], "r");
        if(!f) { printf("Cannot open file.\n"); MPI_Finalize(); return 1; }
        fscanf(f, "%d", &n);
        arr = malloc(n * sizeof(int));
        for(int i=0; i<n; i++) fscanf(f, "%d", &arr[i]);
        fclose(f);
    }

    // Broadcast array size to all processes
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    int chunk = n / size;
    int remainder = n % size;
    int local_n = (rank < remainder) ? chunk+1 : chunk;
    int *local_arr = malloc(local_n * sizeof(int));

    // Scatter the array
    int *sendcounts = NULL;
    int *displs = NULL;
    if(rank==0) {
        sendcounts = malloc(size * sizeof(int));
        displs = malloc(size * sizeof(int));
        int offset=0;
        for(int i=0;i<size;i++){
            sendcounts[i] = (i<remainder)? chunk+1 : chunk;
            displs[i] = offset;
            offset += sendcounts[i];
        }
    }

    MPI_Scatterv(arr, sendcounts, displs, MPI_INT,
                 local_arr, local_n, MPI_INT, 0, MPI_COMM_WORLD);

    // Local sort
    bubble_sort(local_arr, local_n);

    // Gather back
    MPI_Gatherv(local_arr, local_n, MPI_INT,
                arr, sendcounts, displs, MPI_INT,
                0, MPI_COMM_WORLD);

    if(rank==0) {
        for(int i=0;i<n;i++) printf("%d ", arr[i]);
        printf("\n");
        free(arr); free(sendcounts); free(displs);
    }

    free(local_arr);
    MPI_Finalize();
    return 0;
}
    MPI_Finalize();
    return 0;
}
