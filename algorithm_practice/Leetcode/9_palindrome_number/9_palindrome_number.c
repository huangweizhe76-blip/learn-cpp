#include <stdio.h>
#include <stdbool.h>

bool isPalindrome(int x) {
    //负数直接false，末尾是0且x不等于0直接false
    if (x < 0 || (x != 0 && x % 10 == 0))
    {
        return false;
    }
    int reverseHalf = 0;
    while (x > reverseHalf)
    {
        reverseHalf = reverseHalf * 10 + x % 10;
        x = x / 10;
    }
    //偶数位相等；奇数位把反转后的后半段去掉中间一位
    return x == reverseHalf || x == reverseHalf / 10;
}

int main()
{
    printf("121: %d\n", isPalindrome(121));   //1(true)
    printf("-121: %d\n", isPalindrome(-121)); //0(false)
    printf("10: %d\n", isPalindrome(10));     //0(false)
    printf("0: %d\n", isPalindrome(0));       //1(true)
    printf("12321: %d\n", isPalindrome(12321));//1(true)
    return 0;
}