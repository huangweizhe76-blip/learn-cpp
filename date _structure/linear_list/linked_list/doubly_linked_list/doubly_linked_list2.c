#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;
typedef struct node {
    ElemType data;
    struct node* next, * prev;
}Node;

//初始化哨兵头结点
Node* initList()
{
    Node* head = (Node*)malloc(sizeof(Node));
    if (head == NULL) {
        perror("malloc failed");
        return NULL;
    }
    head->next = NULL;
    head->prev = NULL;
    return head;
}

//头插法，L是哨兵头
int insertHead(Node* L, ElemType e)
{
    if (L == NULL) return 0;
    Node* p = (Node*)malloc(sizeof(Node));
    if (p == NULL) return 0;

    p->data = e;
    p->prev = L;
    p->next = L->next;

    if (L->next != NULL)
    {
        L->next->prev = p;
    }
    L->next = p;
    return 1;
}

//正向遍历
void listNode(Node* L)
{
    if (L == NULL) return;
    Node* p = L->next;
    while (p != NULL)
    {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

//获取尾结点
Node* get_tail(Node* L)
{
    Node* p = L;
    while (p->next != NULL)
    {
        p = p->next;
    }
    return p;
}

//【重构】尾插：直接传入头结点L，内部找尾部，不需要外部维护tail
int insertTail(Node* L, ElemType e)
{
    if (L == NULL) return 0;
    Node* tail = get_tail(L);
    Node* p = (Node*)malloc(sizeof(Node));
    if (p == NULL) return 0;

    p->data = e;
    p->prev = tail;
    tail->next = p;
    p->next = NULL;
    return 1;
}

//pos从1开始，在pos位置插入元素e
int insertNode(Node* L, int pos, ElemType e)
{
    if (L == NULL || pos < 1) return 0;
    Node* p = L;
    int i = 0;
    while (i < pos - 1)
    {
        p = p->next;
        i++;
        if (p == NULL)
        {
            return 0;
        }
    }
    Node* q = (Node*)malloc(sizeof(Node));
    if (q == NULL) return 0;
    q->data = e;
    q->prev = p;
    q->next = p->next;

    //修复：p->next不为空才访问prev，防止尾插场景空指针
    if (p->next != NULL) {
        p->next->prev = q;
    }
    p->next = q;
    return 1;
}

//删除pos位置结点，pos从1开始
int deleteNode(Node* L, int pos)
{
    if (L == NULL || pos < 1) return 0;
    Node* p = L;
    int i = 0;
    while (i < pos - 1)
    {
        p = p->next;
        i++;
        if (p == NULL)
        {
            return 0;
        }
    }
    if (p->next == NULL)
    {
        printf("要删除的位置错误\n");
        return 0;
    }
    Node* q = p->next;
    p->next = q->next;
    if (q->next != NULL) {
        q->next->prev = p;
    }
    free(q);
    return 1;
}

//释放整个链表
void freeList(Node* L)
{
    if (L == NULL) return;
    Node* p = L->next;
    Node* q;
    while (p != NULL)
    {
        q = p->next;
        free(p);
        p = q;
    }
    free(L);   //不要忘记释放哨兵头结点！原代码漏掉！
}

int main(int argc, char const* argv[])
{
    Node* list = initList();

    insertTail(list, 10);
    insertTail(list, 20);
    insertTail(list, 30);
    printf("尾插10 20 30：");
    listNode(list);

    insertNode(list, 2, 15);
    printf("pos2插入15：");
    listNode(list);

    deleteNode(list, 2);
    printf("删除pos2：");
    listNode(list);

    freeList(list);
    return 0;
}