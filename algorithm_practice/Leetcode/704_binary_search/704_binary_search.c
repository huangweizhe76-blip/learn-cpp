#include<stdio.h>

int search(int* nums, int numsSize, int target) {
    int left = 0;
    int right = numsSize - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] == target) {
            return mid;
        }
        else if (nums[mid] < target) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return -1;
}

int main()
{
    int arr[] = { -1,0,3,5,9,12 };
    int size = sizeof(arr) / sizeof(arr[0]);
    int res = search(arr, size, 9);
    printf("%d\n", res);
    return 0;
}