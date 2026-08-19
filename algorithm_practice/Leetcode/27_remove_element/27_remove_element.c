#include <stdio.h>

// leetcode核心函数，和你截图逻辑完全一致
int removeElement(int* nums, int numsSize, int val) {
    int left = 0;
    int right = numsSize - 1;
    while (left <= right)
    {
        if (nums[left] == val)
        {
            nums[left] = nums[right];
            right--;
        }
        else
        {
            left++;
        }
    }
    return left;
}

int main()
{
    //测试样例 nums = [3,2,2,3], val=3
    int nums[] = { 3,2,2,3 };
    int val = 3;
    int size = sizeof(nums) / sizeof(nums[0]);

    int k = removeElement(nums, size, val);

    printf("k = %d\n", k);
    printf("数组前k个元素：");
    for (int i = 0; i < k; i++)
    {
        printf("%d ", nums[i]);
    }
    printf("\n");
    return 0;
}