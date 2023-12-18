#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

int* full_array(int* ptrarr, int size);
int put_array(int* ptrarr, int size);
void sort_selection(int* arr, int size);
void sort_bubble(int* arr, int size);
void sort_cocktail(int* arr, int size);
void sort_insert(int* arr, int size);
void run_experiment(int* arr, int size, void (*sort_func)(int*, int), const char* sort_name);

int main()
{
    setlocale(LC_ALL, "RUS");
    srand(time(NULL));
    int size;
    printf("Введите размер массива > ");
    scanf("%d", &size);
    int* int_array = (int*)malloc(size * sizeof(int));
    long* long_array = (long*)malloc(size * sizeof(long));
    float* float_array = (float*)malloc(size * sizeof(float));
    double* double_array = (double*)malloc(size * sizeof(double));
    long double* ld_array = (long double*)malloc(size * sizeof(long double));
    full_array(int_array, size);
    full_array(long_array, size);
    full_array(float_array, size);
    full_array(double_array, size);
    full_array(ld_array, size);
    run_experiment(int_array, size, sort_selection, "Выбором (int)");
    run_experiment(int_array, size, sort_bubble, "Пузырьковая (int)");
    run_experiment(int_array, size, sort_cocktail, "Коктельная (int)");
    run_experiment(int_array, size, sort_insert, "Вставками (int)");
    run_experiment(long_array, size, sort_selection, "Выбором (long)");
    run_experiment(long_array, size, sort_bubble, "Пузырьковая (long)");
    run_experiment(long_array, size, sort_cocktail, "Коктельная (long)");
    run_experiment(long_array, size, sort_insert, "Вставками (long)");
    run_experiment(float_array, size, sort_selection, "Выбором (float)");
    run_experiment(float_array, size, sort_bubble, "Пузырьковая (float)");
    run_experiment(float_array, size, sort_cocktail, "Коктельная (float)");
    run_experiment(float_array, size, sort_insert, "Вставками (float)");
    run_experiment(double_array, size, sort_selection, "Выбором (double)");
    run_experiment(double_array, size, sort_bubble, "Пузырьковая (double)");
    run_experiment(double_array, size, sort_cocktail, "Коктельная (double)");
    run_experiment(double_array, size, sort_insert, "Вставками (double)");
    run_experiment(ld_array, size, sort_selection, "Выбором (long double)");
    run_experiment(ld_array, size, sort_bubble, "Пузырьковая (long double)");
    run_experiment(ld_array, size, sort_cocktail, "Коктельная (long double)");
    run_experiment(ld_array, size, sort_insert, "Вставками (long double)");
    free(int_array);
    free(long_array);
    free(float_array);
    free(double_array);
    free(ld_array);
}

int* full_array(int* ptrarr, int size)
{
    for (int i = 0; i < size; i++)
    {
        ptrarr[i] = rand() % 100;
    }
    return ptrarr;
}

int put_array(int* ptrarr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", ptrarr[i]);
    }
    printf("\n");
}

void sort_selection(int* arr, int size) {
    for (int i = 0; i < size - 1; ++i) {
        int min_index = i;
        for (int j = i + 1; j < size; ++j) {
            if (arr[j] < arr[min_index]) {
                min_index = j;
            }
        }
        int temp = arr[i];
        arr[i] = arr[min_index];
        arr[min_index] = temp;
    }
}

void sort_bubble(int* arr, int size) {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void sort_cocktail(int* arr, int size) {
    int swapped = 1;
    int start = 0;
    int end = size - 1;

    while (swapped) {
        swapped = 0;

        for (int i = start; i < end; ++i) {
            if (arr[i] > arr[i + 1]) {
                int temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
                swapped = 1;
            }
        }

        if (!swapped) {
            break;
        }

        --end;

        for (int i = end - 1; i >= start; --i) {
            if (arr[i] > arr[i + 1]) {
                int temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
                swapped = 1;
            }
        }

        ++start;
    }
}

void sort_insert(int* arr, int size) {
    for (int i = 1; i < size; ++i) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }

        arr[j + 1] = key;
    }
}

void run_experiment(int* arr, int size, void (*sort_func)(int*, int), const char* sort_name) {
    clock_t t;
    t = clock();
    sort_func(arr, size);
    double time_taken = ((double)(clock() - t)) / CLOCKS_PER_SEC;
    printf("%s: %f секунд\n", sort_name, time_taken);
}