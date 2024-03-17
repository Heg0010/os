#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

// Utility Functions
void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

// Function Prototypes
int partition(int arr[], int low, int high);
void quickSort(int arr[], int low, int high);
void merge(int arr[], int l, int m, int r);
void merge_sort(int arr[], int l, int r);
void insertionSort(int arr[], int n);
int sort_verify(int arr[], long n);  // Prototype for sort_verify


// Quick Sort Implementation
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void quick_sort_top_level(long n) {
    int* arr = (int*)malloc(n * sizeof(int));
    for (long i = 0; i < n; i++) {
        arr[i] = rand() % n;
    }
    quickSort(arr, 0, n - 1);
    if (sort_verify(arr, n)) {
        printf("Quick Sort Successful\n");
    } else {
        printf("Quick Sort Failed\n");
    }
    free(arr);
}

// Merge Sort Implementation
void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    int L[n1], R[n2];

    for (int i = 0; i < n1; i++) {
        L[i] = arr[l + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[m + 1 + j];
    }

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void merge_sort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        merge_sort(arr, l, m);
        merge_sort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void merge_sort_top_level(long n) {
    int* arr = (int*)malloc(n * sizeof(int));
    for (long i = 0; i < n; i++) {
        arr[i] = rand() % n;
    }
    merge_sort(arr, 0, n - 1);
    if (sort_verify(arr, n)) {
        printf("Merge Sort Successful\n");
    } else {
        printf("Merge Sort Failed\n");
    }
    free(arr);
}

// Insertion Sort Implementation
void insertionSort(int arr[], int n) {
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void insertion_sort_top_level(long n) {
    int* arr = (int*)malloc(n * sizeof(int));
    for (long i = 0; i < n; i++) {
        arr[i] = rand() % n;
    }
    insertionSort(arr, n);
    if (sort_verify(arr, n)) {
        printf("Insertion Sort Successful\n");
    } else {
        printf("Insertion Sort Failed\n");
    }
    free(arr);
}

// Verify if the array is sorted
int sort_verify(int arr[], long n) {
    for (long i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            return 0; // Not sorted
        }
    }
    return 1; // Sorted
}

// Timing Macros
#define TIMER_CLEAR (tv1.tv_sec = tv1.tv_usec = tv2.tv_sec = tv2.tv_usec = 0)
#define TIMER_START gettimeofday(&tv1, (struct timezone*)0)
#define TIMER_ELAPSED (double) (tv2.tv_usec - tv1.tv_usec) / 1000000.0 + (tv2.tv_sec - tv1.tv_sec)
#define TIMER_STOP gettimeofday(&tv2, (struct timezone*)0)

struct timeval tv1, tv2;

int main() {
    srand(time(NULL)); // Seed for random number generation
    long n = 100000; // Adjust as needed

    // Quick Sort Test
    TIMER_CLEAR;
    TIMER_START;
    quick_sort_top_level(n);
    TIMER_STOP;
    printf("Quick Sort: Time elapsed = %f seconds\n", TIMER_ELAPSED);

    // Merge Sort Test
    TIMER_CLEAR;
    TIMER_START;
    merge_sort_top_level(n);
    TIMER_STOP;
    printf("Merge Sort: Time elapsed = %f seconds\n", TIMER_ELAPSED);

    // Insertion Sort Test
    TIMER_CLEAR;
    TIMER_START;
    insertion_sort_top_level(n);
    TIMER_STOP;
    printf("Insertion Sort: Time elapsed = %f seconds\n", TIMER_ELAPSED);

    return 0;
}
