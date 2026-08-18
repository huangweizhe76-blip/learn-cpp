#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

//链栈节点结构体，带头结点
typedef struct stack
{
    ElemType data;
    struct stack* next;
} Stack;

/**
 * @brief 初始化链栈，创建头结点
 * @return 成功返回栈指针；malloc失败返回NULL
 */
Stack* initStack()
{
    Stack* s = (Stack*)malloc(sizeof(Stack));
    if (s == NULL)
    {
        return NULL;
    }
    s->next = NULL; //头结点next置空，data字段不使用，无需赋值
    return s;
}

/**
 * @brief 销毁整个链栈，释放所有节点内存(含头结点)
 * @param s 栈指针
 */
void destroyStack(Stack* s)
{
    if (s == NULL)
        return;

    Stack* cur = s;
    while (cur != NULL)
    {
        Stack* temp = cur;
        cur = cur->next;
        free(temp);
    }
}

/**
 * @brief 判断栈是否为空
 * @return -1参数非法；1栈空；0非空
 */
int isEmpty(Stack* s)
{
    if (s == NULL)
        return -1;
    return (s->next == NULL) ? 1 : 0;
}

/**
 * @brief 压栈（头插法）
 * @return -1参数错误/内存分配失败；1成功
 */
int push(Stack* s, ElemType e)
{
    if (s == NULL)
        return -1;

    Stack* p = (Stack*)malloc(sizeof(Stack));
    if (p == NULL)
        return -1;

    p->data = e;
    p->next = s->next;
    s->next = p;
    return 1;
}

/**
 * @brief 出栈
 * @param e 传出弹出的元素
 * @return -1参数非法；0栈空；1成功
 */
int pop(Stack* s, ElemType* e)
{
    if (s == NULL || e == NULL)
        return -1;
    if (isEmpty(s))
        return 0;

    Stack* q = s->next;
    *e = q->data;
    s->next = q->next;
    free(q);
    return 1;
}

/**
 * @brief 获取栈顶元素(不删除)
 * @return -1参数非法；0栈空；1成功
 */
int getTop(Stack* s, ElemType* e)
{
    if (s == NULL || e == NULL)
        return -1;
    if (isEmpty(s))
        return 0;

    *e = s->next->data;
    return 1;
}

int main(int argc, char const* argv[])
{
    Stack* s = initStack();
    if (s == NULL)
    {
        printf("栈初始化失败\n");
        return -1;
    }

    push(s, 10);
    push(s, 20);
    push(s, 30);

    ElemType e;
    int ret;

    ret = pop(s, &e);
    if (ret == 1)
        printf("%d\n", e);

    ret = getTop(s, &e);
    if (ret == 1)
        printf("%d\n", e);

    destroyStack(s); //释放全部内存，必须调用
    return 0;
}