#include <stdio.h>
#include <limits.h>

// leetcode原题函数：滑动窗口 O(n)
int minSubArrayLen(int target, int* nums, int numsSize) {
    int left = 0;
    int sum = 0;
    int min_len = INT_MAX; // 代替0x7fffffff，可读性更好

    for (int right = 0; right < numsSize; right++)
    {
        sum += nums[right];
        // 窗口总和>=target，收缩左边界求最小长度
        while (sum >= target)
        {
            int cur_len = right - left + 1;
            if (cur_len < min_len)
            {
                min_len = cur_len;
            }
            sum -= nums[left];
            left++;
        }
    }
    if (min_len == INT_MAX)
    {
        return 0;
    }
    return min_len;
}

int main()
{
    // 测试样例1 target=7, [2,3,1,2,4,3] 预期输出2
    int arr1[] = { 2,3,1,2,4,3 };
    int t1 = 7;
    int res1 = minSubArrayLen(t1, arr1, sizeof(arr1) / sizeof(arr1[0]));
    printf("case1 result: %d\n", res1);

    // 测试样例2 target=4, [1,4,4] 预期输出1
    int arr2[] = { 1,4,4 };
    int t2 = 4;
    int res2 = minSubArrayLen(t2, arr2, sizeof(arr2) / sizeof(arr2[0]));
    printf("case2 result: %d\n", res2);

    // 测试样例3 target=11, [1,1,1,1,1,1,1,1] 预期输出0
    int arr3[] = { 1,1,1,1,1,1,1,1 };
    int t3 = 11;
    int res3 = minSubArrayLen(t3, arr3, sizeof(arr3) / sizeof(arr3[0]));
    printf("case3 result: %d\n", res3);

    return 0;
}