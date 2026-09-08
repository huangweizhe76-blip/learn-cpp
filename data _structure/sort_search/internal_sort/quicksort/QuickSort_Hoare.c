/**
 * @file QuickSort_Hoare.c
 * @brief 快速排序‑Hoare双边指针分区(C语言)
 * 原版快排，交换次数更少，注意递归边界！
 * Avg O(nlogn), Worst O(n²), 不稳定排序
 */
#include <stdio.h>

static void swap(int* a, int* b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int partition_hoare(int arr[], int l, int r)
{
    int pivot = arr[(l + r) / 2];
    int i = l - 1;
    int j = r + 1;
    while (1)
    {
        do { i++; } while (arr[i] < pivot);
        do { j--; } while (arr[j] > pivot);
        if (i >= j) return j;
        swap(&arr[i], &arr[j]);
    }
}

void quicksort_hoare(int arr[], int l, int r)
{
    if (l >= r) return;
    int split = partition_hoare(arr, l, r);
    quicksort_hoare(arr, l, split);
    quicksort_hoare(arr, split + 1, r);
}

void print_array(int arr[], int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main(void)
{
    int nums[] = { 5,2,9,3,7,6,1,8,4 };
    int len = sizeof(nums) / sizeof(nums[0]);
    quicksort_hoare(nums, 0, len - 1);
    print_array(nums, len);
    return 0;
}
