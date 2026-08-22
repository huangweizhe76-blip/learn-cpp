#include <stdio.h>
#include <stdlib.h>

int** generateMatrix(int n, int* returnSize, int** returnColumnSizes) {
    *returnSize = n;
    // 分配每行列数数组
    *returnColumnSizes = (int*)malloc(sizeof(int) * n);

    int** matrix = (int**)malloc(sizeof(int*) * n);
    for (int i = 0; i < n; i++)
    {
        matrix[i] = (int*)malloc(sizeof(int) * n);
        (*returnColumnSizes)[i] = n; // 重点！必须带括号解引用
    }

    int top = 0, bottom = n - 1;
    int left = 0, right = n - 1;
    int num = 1;
    int total = n * n;

    while (num <= total)
    {
        //顶行左→右
        for (int i = left; i <= right && num <= total; i++)
            matrix[top][i] = num++;
        top++;

        //右列上→下
        for (int i = top; i <= bottom && num <= total; i++)
            matrix[i][right] = num++;
        right--;

        //底行右→左
        for (int i = right; i >= left && num <= total; i--)
            matrix[bottom][i] = num++;
        bottom--;

        //左列下→上
        for (int i = bottom; i >= top && num <= total; i--)
            matrix[i][left] = num++;
        left++;
    }

    return matrix;
}

int main()
{
    int n = 3;
    int retSize;
    int* retColSize;   // 接收函数输出的列大小数组
    int** mat = generateMatrix(n, &retSize, &retColSize);

    //打印
    for (int i = 0; i < retSize; i++)
    {
        for (int j = 0; j < retColSize[i]; j++)
        {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }

    //释放内存
    for (int i = 0; i < n; i++)
    {
        free(mat[i]);
    }
    free(mat);
    free(retColSize); //释放列大小数组
    return 0;
}