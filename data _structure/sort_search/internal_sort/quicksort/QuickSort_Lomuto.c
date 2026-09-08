/**
 * @file QuickSort_Lomuto.c
 * @brief 快速排序‑Lomuto分区实现(C语言)
 * pivot选取区间最右侧元素
 * Avg O(nlogn), Worst O(n²), 不稳定排序
 */
#include <stdio.h>

static void swap(int* a, int* b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int partition_lomuto(int arr[], int left, int right)
{
    int pivot = arr[right];
    int i = left;
    for (int j = left; j < right; j++)
    {
        if (arr[j] <= pivot)
        {
            swap(&arr[i], &arr[j]);
            i++;
        }
    }
    swap(&arr[i], &arr[right]);
    return i;
}

void quicksort_lomuto(int arr[], int left, int right)
{
    if (left >= right)
        return;
    int pivot_idx = partition_lomuto(arr, left, right);
    quicksort_lomuto(arr, left, pivot_idx - 1);
    quicksort_lomuto(arr, pivot_idx + 1, right);
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
    quicksort_lomuto(nums, 0, len - 1);
    print_array(nums, len);
    return 0;
}
