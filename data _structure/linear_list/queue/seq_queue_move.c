#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100
typedef int ElemType;

typedef struct
{
	ElemType* data; //动态数组
	int front; //队头下标，指向头元素
	int rear;  队尾下表，下一个入队存放位置

}Queue;

//初始化
Queue* initQueue()
{
	Queue* q = (Queue*)malloc(sizeof(Queue));
	q->data = (ElemType*)malloc(sizeof(ElemType) * MAXSIZE);
	q->front = 0;
	q->rear = 0;
	return q;
}

//判断队列是否为空
int isEmpty(Queue* Q)
{
	if (Q->front == Q->rear)
	{
		printf("空的\n");
		return 1;
	}
	else
	{
		return 0;
	}
}

//出队
ElemType dequeue(Queue* Q)
{
	if (Q->front == Q->rear)
	{
		printf("空的\n");
		return 0;
	}
	ElemType e = Q->data[Q->front];
	Q->front++;
	return e;
}
//队尾满了，调整队列
int queueFull(Queue* Q)
{
	if (Q->front > 0)
	{
		int step = Q->front;  //需要向前移动的步数
		for (int i = Q->front; i <= Q->rear; ++i)  
		{
			Q->data[i - step] = Q->data[i];
		}
		Q->front = 0;  //队头归0
		Q->rear = Q->rear - step;  //队尾跟着往前偏移step
		return 1;  //偏移成功
	}
	else
	{
		printf("真的满了\n");
		return 0; //front已经等于0，前面没有空闲，数组真满
	}
}

//入队
int enqueue(Queue* Q, ElemType e)
{

	if (Q->rear >= MAXSIZE) //队尾下标抵达数组末尾，触发假满
	{
		if (!queueFull(Q)) //尝试向前搬移压缩
		{
			return 0;  //搬移失败，数组真满，入队失败返回0
		}
	}
	Q->data[Q->rear] = e;
	Q->rear++;
	return 1;
}

//获取队头元素
int getHead(Queue* Q, ElemType* e)
{
	if (Q->front == Q->rear)
	{
		printf("空的\n");
		return 0;
	}
	*e = Q->data[Q->front];
	return 1;
}

int main(int argc, char const* argv[])
{

	Queue* q = initQueue();

	equeue(q, 10);
	equeue(q, 20);
	equeue(q, 30);
	equeue(q, 40);
	equeue(q, 50);

	printf("%d\n", dequeue(q));
	printf("%d\n", dequeue(q));
	ElemType e;
	getHead(q, &e);
	printf("%d\n", e);

	return 0;
}



