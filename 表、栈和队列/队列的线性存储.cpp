#include<stdio.h>
#include<stdlib.h>
#define Elementtype int
#define Maxsize 7

struct Queue
{
	Elementtype value[Maxsize];
	int front;
	int rear;
};

struct Queue * creatQ();//创建一个队列
bool IsFullQ(struct Queue *pQ);//判断队列是否已满
void AddQ(struct Queue *pQ, Elementtype x);//入队
bool IsEmpty(struct Queue *pQ);//判断队列是否为空
Elementtype DeleteQ(struct Queue *pQ);//出队

struct Queue * creatQ()
{
	struct Queue *pQ = (struct Queue *)malloc(sizeof(struct Queue));
	pQ->front = -1;
	pQ->rear = -1;
	return pQ;
}
bool IsFullQ(struct Queue *pQ)
{
	if ((pQ->rear+1)%Maxsize == pQ->front)
		return true;
	else
		return false;
}
void AddQ(struct Queue *pQ, Elementtype x)
{
	if (IsFullQ(pQ))
	{
		printf("队列已满！\n");
		return;
	}
	else
	{
		pQ->rear = (pQ->rear + 1) % Maxsize;
		pQ->value[pQ->rear] = x;
	}
}
bool IsEmpty(struct Queue *pQ)
{
	if (pQ->front == pQ->rear)
		return true;
	else
		return false;
}
Elementtype DeleteQ(struct Queue *pQ)
{
	Elementtype temp;
	temp = pQ->value[(pQ->front + 1) % Maxsize];
	pQ->front = (pQ->front + 1) % Maxsize;
	return temp;
}

int main()
{
	/*创建一个队列*/
	struct Queue *pQ = creatQ();
	/*将4,5,6,7入队*/
	for (int i = 4;i <= 7;i++)
	{
		AddQ(pQ, i);
	}
	Elementtype temp=DeleteQ(pQ);//将4弹出
	printf("%d\n", temp);
	return 0;

}