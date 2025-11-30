#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    if(argc != 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    FILE *f = fopen(argv[1], "r");
    if(!f) { printf("Cannot open file.\n"); return 1; }

    int size = 0;
    fscanf(f, "%d", &size); // first number = array size
    int *arr = malloc(size * sizeof(int));

    for(int i=0; i<size; i++)
        fscanf(f, "%d", &arr[i]);

    fclose(f);

    // Bubble sort
    for(int i=0; i<size-1; i++) {
        for(int j=0; j<size-i-1; j++) {
            if(arr[j] > arr[j+1]) {
                int tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp;
            }
        }
    }

    // Print sorted array
    for(int i=0; i<size; i++)
        printf("%d ", arr[i]);
    printf("\n");

    free(arr);
    return 0;
}
