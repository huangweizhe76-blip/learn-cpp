#include <stdio.h>

int lengthOfLongestSubstring(char* s) {
    int lastPos[128];
    for (int i = 0; i < 128; i++) {
        lastPos[i] = -1;
    }
    int left = 0;
    int maxLen = 0;
    int right = 0;
    while (s[right] != '\0')
    {
        unsigned char ch = s[right];
        if (lastPos[ch] >= left)
        {
            left = lastPos[ch] + 1;
        }
        lastPos[ch] = right;
        int curLen = right - left + 1;
        if (curLen > maxLen)
        {
            maxLen = curLen;
        }
        right++;
    }
    return maxLen;
}

int main()
{
    //样例1
    char s1[] = "abcabcbb";
    printf("case1:%d\n", lengthOfLongestSubstring(s1)); //输出3
    //样例2
    char s2[] = "bbbbb";
    printf("case2:%d\n", lengthOfLongestSubstring(s2)); //输出1
    //样例3
    char s3[] = "pwwkew";
    printf("case3:%d\n", lengthOfLongestSubstring(s3)); //输出3
    //空字符串测试
    char s4[] = "";
    printf("case4:%d\n", lengthOfLongestSubstring(s4)); //输出0
    return 0;
}
