#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_THREADS 4

typedef struct {
    int *arr;
    int start;
    int end;
} thread_data;

// Bubble sort for a chunk
void* bubble_sort_thread(void* arg) {
    thread_data *data = (thread_data*) arg;
    int *arr = data->arr;
    int start = data->start;
    int end = data->end;
    int len = end - start;

    for(int i=0; i<len-1; i++) {
        for(int j=start; j<start + len - i - 1; j++) {
            if(arr[j] > arr[j+1]) {
                int tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp;
            }
        }
    }

    pthread_exit(NULL);
}

// Merge sorted chunks
void merge_chunks(int *arr, int size, int num_chunks) {
    int *tmp = malloc(size * sizeof(int));
    int chunk_size = size / num_chunks;
    int *indices = calloc(num_chunks, sizeof(int));

    for(int i=0; i<size; i++) {
        int min_val = __INT_MAX__;
        int min_idx = -1;

        for(int c=0; c<num_chunks; c++) {
            int start = c * chunk_size;
            int end = (c == num_chunks-1) ? size : (c+1)*chunk_size;

            if(indices[c] < end - start) {
                int val = arr[start + indices[c]];
                if(val < min_val) {
                    min_val = val;
                    min_idx = c;
                }
            }
        }

        tmp[i] = min_val;
        indices[min_idx]++;
    }

    // Copy back to original array
    for(int i=0; i<size; i++)
        arr[i] = tmp[i];

    free(tmp);
    free(indices);
}

int main(int argc, char* argv[]) {
    if(argc != 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    FILE *f = fopen(argv[1], "r");
    if(!f) {
        printf("Cannot open file.\n");
        return 1;
    }

    int size;
    fscanf(f, "%d", &size);
    int *arr = malloc(size * sizeof(int));
    for(int i=0; i<size; i++)
        fscanf(f, "%d", &arr[i]);
    fclose(f);

    pthread_t threads[MAX_THREADS];
    thread_data tdata[MAX_THREADS];
    int chunk = size / MAX_THREADS;

    // Create threads
    for(int t=0; t<MAX_THREADS; t++) {
        tdata[t].arr = arr;
        tdata[t].start = t * chunk;
        tdata[t].end = (t == MAX_THREADS-1) ? size : (t+1) * chunk;
        pthread_create(&threads[t], NULL, bubble_sort_thread, &tdata[t]);
    }

    // Wait for threads to finish
    for(int t=0; t<MAX_THREADS; t++)
        pthread_join(threads[t], NULL);

    // Merge sorted chunks
    merge_chunks(arr, size, MAX_THREADS);

    // Print fully sorted array
    for(int i=0; i<size; i++)
        printf("%d ", arr[i]);
    printf("\n");

    free(arr);
    return 0;
}

