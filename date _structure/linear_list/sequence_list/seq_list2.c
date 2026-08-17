#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100        //顺序表最大容量
typedef int ElemType;

//动态分配顺序表结构体
typedef struct {
    ElemType* data;   //动态数组，存放元素
    int length;       //当前有效元素个数
} SeqList;

/**
 * @brief 初始化顺序表，返回顺序表指针
 * @return 成功返回SeqList*，malloc失败返回NULL
 */
SeqList* initList()
{
    SeqList* L = (SeqList*)malloc(sizeof(SeqList));
    if (L == NULL)   //判断结构体malloc是否失败
    {
        perror("malloc SeqList failed");
        return NULL;
    }
    L->data = (ElemType*)malloc(sizeof(ElemType) * MAXSIZE);
    if (L->data == NULL)  //判断数组malloc失败
    {
        perror("malloc data array failed");
        free(L);   //分配数组失败要释放已经申请的结构体，避免泄漏
        return NULL;
    }
    L->length = 0;
    return L;
}

/**
 * @brief 销毁顺序表，释放全部堆内存
 * @param L 顺序表二级指针，置空外部指针防止野指针
 */
void destroyList(SeqList** L)
{
    if (L == NULL || *L == NULL)
        return;
    free((*L)->data);   //先释放数据数组
    free(*L);           //释放结构体
    *L = NULL;          //外部指针置为NULL，避免野指针
}

/**
 * @brief 清空顺序表，元素全部逻辑删除，不释放内存
 */
void clearList(SeqList* L)
{
    if (L == NULL)
        return;
    L->length = 0;
}

/**
 * @brief 尾部追加元素
 * @param L 顺序表指针
 * @param e 需要添加的元素
 * @return 1成功 0失败
 */
int appendElem(SeqList* L, ElemType e)
{
    if (L == NULL)
    {
        printf("顺序表指针为空!\n");
        return 0;
    }
    if (L->length >= MAXSIZE)
    {
        printf("顺序表已满，无法追加元素!\n");
        return 0;
    }
    L->data[L->length] = e;
    L->length++;
    return 1;
}

/**
 * @brief 遍历打印顺序表所有有效元素
 */
void listElem(SeqList* L)
{
    if (L == NULL)
    {
        printf("顺序表指针为空!\n");
        return;
    }
    if (L->length == 0)
    {
        printf("[空顺序表]");
    }
    for (int i = 0; i < L->length; i++)
    {
        printf("%d ", L->data[i]);
    }
    printf("\n");
}

/**
 * @brief 在逻辑位置pos插入元素e （pos从1开始）
 * @param pos 逻辑位置 [1 ~ length+1]，支持插到表尾
 * @return 1成功，0失败
 */
int insertElem(SeqList* L, int pos, ElemType e)
{
    if (L == NULL)
    {
        printf("顺序表指针为空!\n");
        return 0;
    }
    if (L->length >= MAXSIZE)
    {
        printf("顺序表已满，无法插入!\n");
        return 0;
    }
    //优化：插入可以支持插在表尾 pos = L->length+1
    if (pos < 1 || pos > L->length + 1)
    {
        printf("插入位置%d非法，合法范围1~%d\n", pos, L->length + 1);
        return 0;
    }
    //元素后移
    for (int i = L->length - 1; i >= pos - 1; i--)
    {
        L->data[i + 1] = L->data[i];
    }
    L->data[pos - 1] = e;
    L->length++;
    return 1;
}

/**
 * @brief 删除逻辑pos位置元素，被删元素存入*e传出
 * @param pos 逻辑位置1~length
 * @return 1成功，0失败
 */
int deleteElem(SeqList* L, int pos, ElemType* e)
{
    if (L == NULL || e == NULL)
    {
        printf("指针为空!\n");
        return 0;
    }
    if (L->length == 0)
    {
        printf("空表，不能删除!\n");
        return 0;
    }
    if (pos < 1 || pos > L->length)
    {
        printf("删除位置%d非法，合法范围1~%d\n", pos, L->length);
        return 0;
    }
    *e = L->data[pos - 1];
    //删除的不是最后一位，元素前移
    for (int i = pos; i < L->length; i++)
    {
        L->data[i - 1] = L->data[i];
    }
    L->length--;
    return 1;
}

/**
 * @brief 按值查找，返回第一个匹配元素的逻辑位置，找不到返回0
 */
int findFirstElem(SeqList* L, ElemType e)
{
    if (L == NULL)
    {
        printf("顺序表指针为空!\n");
        return 0;
    }
    for (int i = 0; i < L->length; i++)
    {
        if (L->data[i] == e)
        {
            return i + 1;
        }
    }
    return 0;
}

/**
 * @brief 查找全部等于e的元素，打印所有逻辑下标
 */
void findAllElem(SeqList* L, ElemType e)
{
    if (L == NULL)
    {
        printf("顺序表指针为空!\n");
        return;
    }
    int flag = 0;
    printf("值%d所有位置：", e);
    for (int i = 0; i < L->length; i++)
    {
        if (L->data[i] == e)
        {
            printf("%d ", i + 1);
            flag = 1;
        }
    }
    if (!flag)
        printf("不存在");
    printf("\n");
}

/**
 * @brief 根据逻辑位置获取元素
 * @param pos 逻辑位置
 * @param e 传出参数保存取到的值
 * @return 1成功，0失败
 */
int getElem(SeqList* L, int pos, ElemType* e)
{
    if (L == NULL || e == NULL)
        return 0;
    if (pos < 1 || pos > L->length)
        return 0;
    *e = L->data[pos - 1];
    return 1;
}

int main2(void)
{
    SeqList* list = initList();
    if (list == NULL)   //初始化失败直接退出
    {
        printf("顺序表初始化失败!\n");
        return -1;
    }

    printf("初始化成功，当前有效长度：%d\n", list->length);
    printf("数据数组总内存大小：%zu 字节\n", MAXSIZE * sizeof(ElemType));

    //尾部添加元素
    appendElem(list, 88);
    appendElem(list, 67);
    appendElem(list, 40);
    appendElem(list, 8);
    appendElem(list, 23);
    printf("\n尾部追加5个元素后：");
    listElem(list);

    //在第1号位置插入
    insertElem(list, 1, 18);
    printf("在位置1插入18后：");
    listElem(list);

    //删除第2号位置
    ElemType delData;
    deleteElem(list, 2, &delData);
    printf("删除位置2的数据：%d\n", delData);
    printf("删除之后顺序表：");
    listElem(list);

    //查找第一个40
    int pos = findFirstElem(list, 40);
    printf("元素40第一次出现的逻辑位置：%d\n", pos);

    findAllElem(list, 18);

    //测试表尾插入
    insertElem(list, list->length + 1, 999);
    printf("在表尾插入999：");
    listElem(list);

    //销毁顺序表，释放内存
    destroyList(&list);
    printf("\n顺序表已经销毁\n");

    return 0;
}