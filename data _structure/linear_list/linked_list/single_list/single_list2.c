#include <stdio.h>
#include <stdlib.h>


typedef int ElemType;

//链表节点结构，带头结点单向链表
typedef struct node {
    ElemType data;
    struct node* next;
} Node;

/**
 * @brief 创建头结点（初始化链表）
 * @return 头结点指针
 */
Node* initList()
{
    Node* head = (Node*)malloc(sizeof(Node));
    if (head == NULL) {
        perror("malloc fail");
        exit(EXIT_FAILURE);
    }
    head->data = 0;
    head->next = NULL;
    return head;
}

/**
 * @brief 创建一个普通数据节点
 * @param e 节点数据
 * @return 新节点指针
 */
Node* initListWithElem(ElemType e)
{
    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL) {
        perror("malloc fail");
        exit(EXIT_FAILURE);
    }
    node->data = e;
    node->next = NULL;
    return node;
}

/**
 * @brief 头插法
 * @param L 头结点
 * @param e 待插入元素
 * @return 成功返回1，失败0
 */
int insertHead(Node* L, ElemType e)
{
    if (L == NULL) return 0;
    Node* p = initListWithElem(e);
    p->next = L->next;
    L->next = p;
    return 1;
}

/**
 * @brief 遍历打印链表
 * @param L 头结点
 */
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

/**
 * @brief 获取链表尾节点
 * @param L 头结点
 * @return 尾节点指针
 */
Node* get_tail(Node* L)
{
    if (L == NULL) return NULL;
    Node* p = L;
    while (p->next != NULL)
    {
        p = p->next;
    }
    return p;
}

/**
 * @brief 尾插法，返回新的尾指针
 * @param tail 当前尾节点
 * @param e 插入数据
 * @return 新尾节点
 */
Node* insertTail(Node* tail, ElemType e)
{
    if (tail == NULL) return NULL;
    Node* p = initListWithElem(e);
    tail->next = p;
    p->next = NULL;
    return p;
}

/**
 * @brief 将已有节点接在链表尾部
 * @param tail 当前尾
 * @param node 待接入节点
 * @return 新尾节点
 */
Node* insertTailWithNode(Node* tail, Node* node)
{
    if (tail == NULL || node == NULL) return NULL;
    tail->next = node;
    node->next = NULL;
    return node;
}

/**
 * @brief 指定位置插入，pos从1开始
 * @param L 头结点
 * @param pos 插入位置(从1开始)
 * @param e 插入元素
 * @return 成功1，失败0
 */
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
    Node* q = initListWithElem(e);
    q->next = p->next;
    p->next = q;
    return 1;
}

/**
 * @brief 删除pos位置节点，pos从1开始
 * @param L 头结点
 * @param pos 删除位置
 * @return 成功1，失败0
 */
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
    free(q);
    return 1;
}

/**
 * @brief 获取链表有效数据节点长度（不统计头结点）
 * @param L 头结点
 * @return 数据节点个数
 */
int listLength(Node* L)
{
    if (L == NULL) return 0;
    Node* p = L->next;
    int len = 0;
    while (p != NULL)
    {
        p = p->next;
        len++;
    }
    return len;
}

/**
 * @brief 释放链表，头结点一起释放
 * @param L 链表头结点
 */
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
    free(L);
}

/**
 * @brief 查找倒数第k个节点
 * @param L 头结点
 * @param k 倒数序号，k>=1
 * @return 成功返回1；k非法返回0
 */
int findNodeFS(Node* L, int k)
{
    if (L == NULL || k < 1) return 0;
    int len = listLength(L);
    if (k > len) {
        printf("k超过链表长度！\n");
        return 0;
    }
    Node* fast = L->next;
    Node* slow = L->next;
    for (int i = 0; i < k; i++)
    {
        fast = fast->next;
    }
    while (fast != NULL)
    {
        fast = fast->next;
        slow = slow->next;
    }
    printf("倒数第%d个节点值为：%d\n", k, slow->data);
    return 1;
}

/**
 * @brief 找两个链表相交的起始节点
 * @param headA 链表A头结点
 * @param headB 链表B头结点
 * @return 相交节点，无相交返回NULL
 */
Node* findIntersectionNode(Node* headA, Node* headB)
{
    if (headA == NULL || headB == NULL)
    {
        return NULL;
    }
    int lenA = listLength(headA);
    int lenB = listLength(headB);

    Node* m = headA->next;
    Node* n = headB->next;
    int step;
    if (lenA > lenB)
    {
        step = lenA - lenB;
        for (int i = 0; i < step; i++)
            m = m->next;
    }
    else
    {
        step = lenB - lenA;
        for (int i = 0; i < step; i++)
            n = n->next;
    }
    while (m != NULL && n != NULL && m != n)
    {
        m = m->next;
        n = n->next;
    }
    return m;
}

/**
 * @brief 删除绝对值重复节点
 * 注意：该实现依赖n为绝对值最大上限，适合小规模数据
 * @param L 头结点
 * @param n 最大绝对值
 */
void removeNode(Node* L, int n)
{
    if (L == NULL || n <= 0) return;
    Node* p = L;
    int* q = (int*)calloc(n + 1, sizeof(int));
    if (q == NULL) {
        perror("calloc fail");
        return;
    }
    while (p->next != NULL)
    {
        int index = abs(p->next->data);
        if (index > n) {
            p = p->next;
            continue;
        }
        if (q[index] == 0)
        {
            q[index] = 1;
            p = p->next;
        }
        else
        {
            Node* temp = p->next;
            p->next = temp->next;
            free(temp);
        }
    }
    free(q);
}

/**
 * @brief 反转链表，复用原有头结点，无内存泄漏
 * @param head 原链表头结点
 * @return 头结点（和入参head是同一个）
 */
Node* reverseList(Node* head)
{
    if (head == NULL || head->next == NULL)
        return head;
    Node* first = NULL;
    Node* second = head->next;
    Node* third;
    while (second != NULL)
    {
        third = second->next;
        second->next = first;
        first = second;
        second = third;
    }
    head->next = first;
    return head;
}

/**
 * @brief 删除链表中间节点
 * @param head 头结点
 * @return 成功返回1，失败0
 */
int delMiddleNode(Node* head)
{
    if (head == NULL || head->next == NULL)
        return 0;
    Node* fast = head->next;
    Node* slow = head;
    while (fast != NULL && fast->next != NULL)
    {
        fast = fast->next->next;
        slow = slow->next;
    }
    Node* q = slow->next;
    slow->next = q->next;
    free(q);
    return 1;
}

/**
 * @brief 链表重排：后半反转交替合并
 * @param head 头结点
 */
void reOrderList(Node* head)
{
    if (head == NULL || head->next == NULL) return;
    Node* fast = head;
    Node* slow = head;
    while (fast->next != NULL && fast->next->next != NULL)
    {
        fast = fast->next->next;
        slow = slow->next;
    }
    //截断后半段
    Node* first = NULL;
    Node* second = slow->next;
    slow->next = NULL;
    Node* third = NULL;
    //反转后半段
    while (second != NULL)
    {
        third = second->next;
        second->next = first;
        first = second;
        second = third;
    }
    //交替合并
    Node* p1 = head->next;
    Node* q1 = first;
    Node* p2, * q2;
    while (p1 != NULL && q1 != NULL)
    {
        p2 = p1->next;
        q2 = q1->next;
        p1->next = q1;
        q1->next = p2;
        p1 = p2;
        q1 = q2;
    }
}

/**
 * @brief 判断链表是否有环
 * @param head 头结点
 * @return 有环返回1，无环0
 */
int isCycle(Node* head)
{
    if (head == NULL) return 0;
    Node* fast = head;
    Node* slow = head;
    while (fast != NULL && fast->next != NULL)
    {
        fast = fast->next->next;
        slow = slow->next;
        if (fast == slow)
        {
            return 1;
        }
    }
    return 0;
}

/**
 * @brief 寻找环入口节点
 * @param head 头结点
 * @return 入口节点指针，无环返回NULL
 */
Node* findBegin(Node* head)
{
    if (head == NULL) return NULL;
    Node* fast = head;
    Node* slow = head;
    while (fast != NULL && fast->next != NULL)
    {
        fast = fast->next->next;
        slow = slow->next;
        if (fast == slow)
        {
            //统计环中节点数目
            Node* p = fast;
            int count = 1;
            while (p->next != slow)
            {
                count++;
                p = p->next;
            }
            fast = head;
            slow = head;
            for (int i = 0; i < count; i++)
            {
                fast = fast->next;
            }
            while (fast != slow)
            {
                fast = fast->next;
                slow = slow->next;
            }
            return slow;
        }
    }
    return NULL;
}

int main(int argc, char const* argv[])
{
    Node* list = initList();
    Node* tail = get_tail(list);

    tail = insertTail(tail, 1);
    tail = insertTail(tail, 2);
    tail = insertTail(tail, 3);
    Node* three = tail;   //保存节点3
    tail = insertTail(tail, 4);
    tail = insertTail(tail, 5);
    tail = insertTail(tail, 6);
    tail = insertTail(tail, 7);
    tail = insertTail(tail, 8);

    //制造环：8 ->3
    tail->next = three;

    Node* p = findBegin(list);
    if (p != NULL) {
        printf("环入口节点data = %d\n", p->data); //预期输出3
    }
    else {
        printf("链表无环\n");
    }

    //⚠有环链表不能直接freeList，会死循环！测试完环相关需要手动断开环再释放
    tail->next = NULL;
    freeList(list);
    return 0;
}