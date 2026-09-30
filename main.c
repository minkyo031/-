#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_SIZE 16000

/* =========================
   Insertion Sort
   ========================= */
void insertionSort(int arr[], int n)
{
    int i, j, key;

    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;
    }
}


/* =========================
   Quick Sort
   ========================= */
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[i + 1], &arr[high]);

    return i + 1;
}

void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pivot = partition(arr, low, high);

        quickSort(arr, low, pivot - 1);
        quickSort(arr, pivot + 1, high);
    }
}


/* =========================
   Heap Sort
   ========================= */
void heapify(int arr[], int n, int i)
{
    int largest = i;

    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i)
    {
        swap(&arr[i], &arr[largest]);

        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n)
{
    /* Max Heap 생성 */
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        heapify(arr, n, i);
    }

    /* 가장 큰 원소를 뒤에서부터 배치 */
    for (int i = n - 1; i > 0; i--)
    {
        swap(&arr[0], &arr[i]);

        heapify(arr, i, 0);
    }
}


/* =========================
   정렬 확인
   ========================= */
int isSorted(int arr[], int n)
{
    for (int i = 1; i < n; i++)
    {
        if (arr[i - 1] > arr[i])
            return 0;
    }

    return 1;
}


/* =========================
   성능 측정
   ========================= */
void runTest(int size)
{
    int *original = (int *)malloc(sizeof(int) * size);
    int *arr = (int *)malloc(sizeof(int) * size);

    if (original == NULL || arr == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    /* 랜덤 데이터 생성 */
    for (int i = 0; i < size; i++)
    {
        original[i] = rand() % 100000;
    }

    clock_t start;
    clock_t end;
    double time_used;


    /* ---------- Insertion Sort ---------- */

    memcpy(arr, original, sizeof(int) * size);

    start = clock();

    insertionSort(arr, size);

    end = clock();

    time_used =
        ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0;

    printf("Insertion Sort | n = %5d | %8.3f ms | %s\n",
           size,
           time_used,
           isSorted(arr, size) ? "PASS" : "FAIL");


    /* ---------- Quick Sort ---------- */

    memcpy(arr, original, sizeof(int) * size);

    start = clock();

    quickSort(arr, 0, size - 1);

    end = clock();

    time_used =
        ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0;

    printf("Quick Sort     | n = %5d | %8.3f ms | %s\n",
           size,
           time_used,
           isSorted(arr, size) ? "PASS" : "FAIL");


    /* ---------- Heap Sort ---------- */

    memcpy(arr, original, sizeof(int) * size);

    start = clock();

    heapSort(arr, size);

    end = clock();

    time_used =
        ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0;

    printf("Heap Sort      | n = %5d | %8.3f ms | %s\n",
           size,
           time_used,
           isSorted(arr, size) ? "PASS" : "FAIL");


    printf("\n");

    free(original);
    free(arr);
}


/* =========================
   Main
   ========================= */
int main(void)
{
    srand(42);

    int sizes[] =
    {
        1000,
        2000,
        4000,
        8000,
        16000
    };

    int testCount =
        sizeof(sizes) / sizeof(sizes[0]);

    printf("=============================================\n");
    printf("       Sorting Algorithm Comparison\n");
    printf("=============================================\n\n");

    for (int i = 0; i < testCount; i++)
    {
        runTest(sizes[i]);
    }

    return 0;
}
