#include<stdio.h>
#include<stdlib.h>
#define Elementtype int

typedef struct Node
{
	Elementtype value;
	Node *Next;
}QNode;

typedef struct
{
	Node *front;
	Node *rear;
}Queue;

Queue * creatQ();//创建队列
bool IsEmpty(Queue *pQ);//判断队列是否为空
void AddQ(Queue *pQ, Elementtype x);//入队
Elementtype DeleteQ(Queue *pQ);//出队

Queue * creatQ()
{
	Queue *pQ = (Queue *)malloc(sizeof(Queue));
	pQ->front = NULL;
	pQ->rear = NULL;
	return pQ;
}
bool IsEmpty(Queue *pQ)
{
	if (pQ->front == NULL)
		return true;
	else
		return false;
}
void AddQ(Queue *pQ, Elementtype x)
{
	if (pQ->front ==NULL)
	{
		QNode *pTemp = (QNode *)malloc(sizeof(QNode));
		pTemp->value = x;
		pTemp->Next = NULL;
		pQ->front = pTemp;
		pQ->rear = pTemp;
	}
	else
	{
		QNode *pTemp = (QNode *)malloc(sizeof(QNode));
		pTemp->value = x;
		pTemp->Next = NULL;
		pQ->rear->Next = pTemp;
	}
}
Elementtype DeleteQ(Queue *pQ)
{
	QNode *pTemp;
	Elementtype tempvalue;
	if (IsEmpty(pQ))
	{
		printf("队列为空!\n");
		return 0;
	}
	pTemp = pQ->front;
	tempvalue = pTemp->value;
	if (pQ->front == pQ->rear)
	{
		free(pTemp);
		pQ->front = NULL;
		pQ->rear = NULL;
	}
	else
	{
		pQ->front = pTemp->Next;
		free(pTemp);
	}
	return tempvalue;
}
int main()
{
	/*新建一个队列*/
	Queue *pQ = creatQ();
	/*将4,5,6,7加入队列*/
	for (int i = 4;i <= 7;i++)
	{
		AddQ(pQ, i);
	}
	/*将4弹出*/
	Elementtype temp = DeleteQ(pQ);
	printf("%d\n", temp);
	return 0;
}