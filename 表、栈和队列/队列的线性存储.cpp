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

struct Queue * creatQ();//����һ������
bool IsFullQ(struct Queue *pQ);//�ж϶����Ƿ�����
void AddQ(struct Queue *pQ, Elementtype x);//���
bool IsEmpty(struct Queue *pQ);//�ж϶����Ƿ�Ϊ��
Elementtype DeleteQ(struct Queue *pQ);//����

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
		printf("����������\n");
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
	/*����һ������*/
	struct Queue *pQ = creatQ();
	/*��4,5,6,7���*/
	for (int i = 4;i <= 7;i++)
	{
		AddQ(pQ, i);
	}
	Elementtype temp=DeleteQ(pQ);//��4����
	printf("%d\n", temp);
	return 0;

}