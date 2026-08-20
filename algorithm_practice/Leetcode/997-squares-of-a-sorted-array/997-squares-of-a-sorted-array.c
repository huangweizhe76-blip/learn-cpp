#include <stdio.h>
#include <stdlib.h>

/**
 * LeetCode 977 有序数组的平方 双指针 O(n)
 * @param nums 输入有序数组
 * @param numsSize 数组元素个数
 * @param returnSize 传出返回数组的长度
 * @return malloc出来的平方有序数组，调用方需要free释放
 */
int* sortedSquares(int* nums, int numsSize, int* returnSize)
{
    *returnSize = numsSize;
    int* res = (int*)malloc(sizeof(int) * numsSize);

    int left = 0;
    int right = numsSize - 1;
    int pos = numsSize - 1;

    while (left <= right)
    {
        int left_sq = nums[left] * nums[left];
        int right_sq = nums[right] * nums[right];
        if (left_sq > right_sq)
        {
            res[pos] = left_sq;
            left++;
        }
        else
        {
            res[pos] = right_sq;
            right--;
        }
        pos--;
    }
    return res;
}

// 打印数组工具函数
void printArr(int* arr, int len)
{
    for (int i = 0; i < len; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(void)
{
    // 测试用例1 [-4,-1,0,3,10]
    int nums1[] = { -4,-1,0,3,10 };
    int size1 = sizeof(nums1) / sizeof(nums1[0]);
    int retSize1;
    int* ans1 = sortedSquares(nums1, size1, &retSize1);
    printf("测试用例1输出：");
    printArr(ans1, retSize1);
    free(ans1);   // malloc必须手动释放，VS避免内存泄漏

    // 测试用例2 [-7,-3,2,3,11]
    int nums2[] = { -7,-3,2,3,11 };
    int size2 = sizeof(nums2) / sizeof(nums2[0]);
    int retSize2;
    int* ans2 = sortedSquares(nums2, size2, &retSize2);
    printf("测试用例2输出：");
    printArr(ans2, retSize2);
    free(ans2);

    return 0;
}