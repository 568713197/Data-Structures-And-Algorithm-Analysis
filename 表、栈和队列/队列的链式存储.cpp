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

Queue * creatQ();//��������
bool IsEmpty(Queue *pQ);//�ж϶����Ƿ�Ϊ��
void AddQ(Queue *pQ, Elementtype x);//���
Elementtype DeleteQ(Queue *pQ);//����

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
		printf("����Ϊ��!\n");
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
	/*�½�һ������*/
	Queue *pQ = creatQ();
	/*��4,5,6,7�������*/
	for (int i = 4;i <= 7;i++)
	{
		AddQ(pQ, i);
	}
	/*��4����*/
	Elementtype temp = DeleteQ(pQ);
	printf("%d\n", temp);
	return 0;
}