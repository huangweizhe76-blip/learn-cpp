/**
 * queue_optimized.c
 * 优化版：链式队列｜搬移式顺序队列｜循环顺序队列
 * 修复：内存泄漏、malloc判空、移除内部printf、错误使用返回值+出参
*/
#include <stdio.h>
#include <stdlib.h>

//====================【重点】宏定义挪到最前面！====================
// 三选一，取消注释其中一个
//#define USE_LINK_QUEUE
//#define USE_MOVE_SEQ_QUEUE
#define USE_CIRCLE_QUEUE

typedef int ElemType;

//==================== 1、带表头结点 链式队列 优化版 ====================
#ifdef USE_LINK_QUEUE
typedef struct QueueNode
{
    ElemType data;
    struct QueueNode* next;
} QueueNode;

typedef struct
{
    QueueNode* front;
    QueueNode* rear;
} LinkQueue;

LinkQueue* linkQueueInit()
{
    LinkQueue* q = (LinkQueue*)malloc(sizeof(LinkQueue));
    if (q == NULL) return NULL;
    QueueNode* head = (QueueNode*)malloc(sizeof(QueueNode));
    if (head == NULL)
    {
        free(q);
        return NULL;
    }
    head->next = NULL;
    q->front = head;
    q->rear = head;
    return q;
}

int linkQueueIsEmpty(LinkQueue* q)
{
    if (q == NULL) return 1;
    return q->front == q->rear;
}

//入队 成功返回1，失败0
int linkEnqueue(LinkQueue* q, ElemType e)
{
    if (q == NULL) return 0;
    QueueNode* node = (QueueNode*)malloc(sizeof(QueueNode));
    if (node == NULL) return 0;
    node->data = e;
    node->next = NULL;

    q->rear->next = node;
    q->rear = node;
    return 1;
}

//出队，e传出元素
int linkDequeue(LinkQueue* q, ElemType* e)
{
    if (q == NULL || linkQueueIsEmpty(q))
        return 0;
    QueueNode* del = q->front->next;
    *e = del->data;
    q->front->next = del->next;
    if (q->rear == del)
    {
        q->rear = q->front;
    }
    free(del);
    return 1;
}

//获取队头
int linkGetFront(LinkQueue* q, ElemType* e)
{
    if (q == NULL || linkQueueIsEmpty(q))
        return 0;
    *e = q->front->next->data;
    return 1;
}

//销毁整个链式队列，释放全部内存
void linkQueueDestroy(LinkQueue* q)
{
    if (q == NULL) return;
    QueueNode* p = q->front;
    while (p != NULL)
    {
        QueueNode* tmp = p;
        p = p->next;
        free(tmp);
    }
    free(q);
}

#endif

//==================== 2、搬移式顺序队列 优化版 ====================
#ifdef USE_MOVE_SEQ_QUEUE
#define MOVE_MAXSIZE 100
typedef struct
{
    ElemType* data;
    int front;
    int rear;
} MoveSeqQueue;

MoveSeqQueue* moveSeqQueueInit()
{
    MoveSeqQueue* q = (MoveSeqQueue*)malloc(sizeof(MoveSeqQueue));
    if (q == NULL) return NULL;
    q->data = (ElemType*)malloc(sizeof(ElemType) * MOVE_MAXSIZE);
    if (q->data == NULL)
    {
        free(q);
        return NULL;
    }
    q->front = 0;
    q->rear = 0;
    return q;
}

int moveSeqIsEmpty(MoveSeqQueue* q)
{
    if (q == NULL) return 1;
    return q->front == q->rear;
}

//内存向前压缩
static int queueCompact(MoveSeqQueue* Q)
{
    if (Q->front <= 0)
        return 0;
    int len = Q->rear - Q->front;
    for (int i = 0; i < len; i++)
    {
        Q->data[i] = Q->data[i + Q->front];
    }
    Q->front = 0;
    Q->rear = len;
    return 1;
}

int moveEnqueue(MoveSeqQueue* Q, ElemType e)
{
    if (Q == NULL) return 0;
    if (Q->rear >= MOVE_MAXSIZE)
    {
        if (!queueCompact(Q))
            return 0;
    }
    Q->data[Q->rear++] = e;
    return 1;
}

int moveDequeue(MoveSeqQueue* Q, ElemType* e)
{
    if (Q == NULL || moveSeqIsEmpty(Q))
        return 0;
    *e = Q->data[Q->front++];
    return 1;
}

int moveGetHead(MoveSeqQueue* Q, ElemType* e)
{
    if (Q == NULL || moveSeqIsEmpty(Q))
        return 0;
    *e = Q->data[Q->front];
    return 1;
}

void moveSeqDestroy(MoveSeqQueue* q)
{
    if (q == NULL) return;
    free(q->data);
    free(q);
}
#endif

//====================3、循环顺序队列（牺牲一格判满）优化版 ====================
#ifdef USE_CIRCLE_QUEUE
#define CIRC_MAXSIZE 100
typedef struct
{
    ElemType* data;
    int front;
    int rear;
} CircleSeqQueue;

CircleSeqQueue* circleQueueInit()
{
    CircleSeqQueue* q = (CircleSeqQueue*)malloc(sizeof(CircleSeqQueue));
    if (q == NULL) return NULL;
    q->data = (ElemType*)malloc(sizeof(ElemType) * CIRC_MAXSIZE);
    if (q->data == NULL)
    {
        free(q);
        return NULL;
    }
    q->front = 0;
    q->rear = 0;
    return q;
}

int circleIsEmpty(CircleSeqQueue* q)
{
    if (q == NULL) return 1;
    return q->front == q->rear;
}

static int circleIsFull(CircleSeqQueue* q)
{
    return ((q->rear + 1) % CIRC_MAXSIZE) == q->front;
}

int circleEnqueue(CircleSeqQueue* Q, ElemType e)
{
    if (Q == NULL || circleIsFull(Q))
        return 0;
    Q->data[Q->rear] = e;
    Q->rear = (Q->rear + 1) % CIRC_MAXSIZE;
    return 1;
}

int circleDequeue(CircleSeqQueue* Q, ElemType* e)
{
    if (Q == NULL || circleIsEmpty(Q))
        return 0;
    *e = Q->data[Q->front];
    Q->front = (Q->front + 1) % CIRC_MAXSIZE;
    return 1;
}

int circleGetHead(CircleSeqQueue* Q, ElemType* e)
{
    if (Q == NULL || circleIsEmpty(Q))
        return 0;
    *e = Q->data[Q->front];
    return 1;
}

void circleDestroy(CircleSeqQueue* q)
{
    if (q == NULL) return;
    free(q->data);
    free(q);
}
#endif

//==================== main测试入口 ====================
#if defined(USE_LINK_QUEUE)
int main(void)
{
    LinkQueue* q = linkQueueInit();
    if (q == NULL) return -1;
    linkEnqueue(q, 10);
    linkEnqueue(q, 20);
    linkEnqueue(q, 30);
    ElemType e;
    if (linkDequeue(q, &e)) printf("出队：%d\n", e);
    if (linkDequeue(q, &e)) printf("出队：%d\n", e);
    if (linkGetFront(q, &e)) printf("队头：%d\n", e);
    linkQueueDestroy(q);
    return 0;
}
#elif defined(USE_MOVE_SEQ_QUEUE)
int main(void)
{
    MoveSeqQueue* q = moveSeqQueueInit();
    if (q == NULL) return -1;
    moveEnqueue(q, 10);
    moveEnqueue(q, 20);
    moveEnqueue(q, 30);
    ElemType e;
    if (moveDequeue(q, &e)) printf("出队：%d\n", e);
    if (moveDequeue(q, &e)) printf("出队：%d\n", e);
    if (moveGetHead(q, &e)) printf("队头：%d\n", e);
    moveSeqDestroy(q);
    return 0;
}
#elif defined(USE_CIRCLE_QUEUE)
int main(void)
{
    CircleSeqQueue* q = circleQueueInit();
    if (q == NULL) return -1;
    circleEnqueue(q, 10);
    circleEnqueue(q, 20);
    circleEnqueue(q, 30);
    ElemType e;
    if (circleDequeue(q, &e)) printf("出队：%d\n", e);
    if (circleDequeue(q, &e)) printf("出队：%d\n", e);
    if (circleGetHead(q, &e)) printf("队头：%d\n", e);
    circleDestroy(q);
    return 0;
}
#endif