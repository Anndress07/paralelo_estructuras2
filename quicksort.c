//
// Created by XPC on 1/12/2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
//#include "listamuylarga.c"

#define SIZE 500000

int generateList(int list[], int size);
void swap(int *x, int *y);
void quicksort(int array[], int lenght);
void quicksort_recursion(int array[], int low, int high);
int partition(int array[], int low, int high);

int generateList(int list[], int size) {

    srand(time(NULL)); // Seed the random number generator

    for (int i = 0; i < size; i++) {
        list[i] = rand() % 1000; // Generates random numbers between 0 and 999 (adjust as needed)
    }
}

int main() {
    int a[SIZE];
    generateList(a, SIZE);
    int length = SIZE;
    clock_t begin = clock();
    quicksort(a, length);

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

//    for (int i = 0; i < length; i++) {
//        printf(" %d", a[i]);
//    };

    printf("\n");
    printf("Tiempo: %f", time_spent);
// printf("First element of myList: %d\n", myList[0]);

    return 0;
}
void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}
void quicksort(int array[], int length)
{
    srand(time(NULL));
    quicksort_recursion(array, 0, length-1);
}

void quicksort_recursion(int array[], int low, int high) {
    if (low < high) {
        int pivot_index = partition(array, low, high);

#pragma omp parallel sections num_threads(2)
        {
#pragma omp section
            {
                quicksort_recursion(array, low, pivot_index - 1);
            }

#pragma omp section
            {
                quicksort_recursion(array, pivot_index + 1, high);
            }
        }
    }
}
int partition(int array[], int low, int high)
{
    int pivot_index = low + (rand() % (high - low)); // numero random entre low y high
    if (pivot_index != high);
        swap(&array[pivot_index], &array[high]);
    int pivot_value = array[high];
    int i = low;
    for (int j = low; j < high; j++)
    {
        if (array[j] <= pivot_value)
        {
            swap(&array[i], &array[j]);
            i++;
        }
    }
swap(&array[i], &array[high]);
return i;
}

