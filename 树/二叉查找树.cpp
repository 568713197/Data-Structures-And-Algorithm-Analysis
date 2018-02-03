#include<stdio.h>
#include<stdlib.h>
#define Elementtype int
#define MaxSize 20

typedef struct TreeNode
{
	Elementtype value;
	struct TreeNode *Left;
	struct TreeNode *Right;
}TreeNode;
typedef TreeNode* ValueType;

typedef struct Stack
{
	int Top;
	ValueType Position[MaxSize];
}Stack;
typedef struct Queue
{
	ValueType Position[MaxSize];
	int front;
	int rear;
}Queue;

TreeNode *MakeEmpty(TreeNode *pNode);//��ն��������
TreeNode *Find(TreeNode *pNode, Elementtype x);//����һ������
TreeNode *FindMin(TreeNode *pNode);//Ѱ����Сֵ��ַ
TreeNode *FindMax(TreeNode *pNode);//Ѱ�����ֵ��ַ
TreeNode *Insert(TreeNode *pNode, Elementtype x);//��������
TreeNode *Delete(TreeNode *pNode, Elementtype x);//ɾ������
void PreOrderTraveral(TreeNode *pNode);//������� �ݹ�ʵ��
void InOrderTraveral(TreeNode *pNode);//������� �ݹ�ʵ��
void PostOrderTraveral(TreeNode *pNode);//������� �ݹ�ʵ��
void PreOrderTraveral2(TreeNode *pNode);//������� ��ջʵ��
void InOrderTraveral2(TreeNode *pNode);//������� ��ջʵ��
void PostOrderTraveral2(TreeNode *pNode);//������� ��ջʵ��
void LevelrderTraveral(TreeNode *pNode);//������� ����ʵ��
void Push(Stack *pStr, ValueType x);//ѹջ
ValueType Pop(Stack *pStr);//��ջ
ValueType Top(Stack *pStr);//����ջ��Ԫ��
bool IsEmpty(Stack *pStr);//����Ƿ�Ϊ��ջ
struct Queue * creatQ();//����һ������
bool IsFullQ(struct Queue *pQ);//�ж϶����Ƿ�����
void AddQ(struct Queue *pQ, Elementtype x);//���
bool IsEmptyQ(struct Queue *pQ);//�ж϶����Ƿ�Ϊ��
ValueType DeleteQ(struct Queue *pQ);//����

Stack *stack=(Stack *)malloc(sizeof(stack));
stack->Top = -1;

int main()
{
	TreeNode *RootNode = (TreeNode *)malloc(sizeof(TreeNode));
	Insert(RootNode, 15);
	for (int i = 0;i < 7;i++)
	{
		Insert(RootNode, (i * 2 - 1));
	}
	TreeNode *Min = FindMin(RootNode);
	TreeNode *Max = FindMax(RootNode);
	printf("��Сֵ%d\n", Min->value);
	printf("���ֵ%d\n", Max->value);
	printf("�������1\n");
	PreOrderTraveral(RootNode);
	printf("\n");
	printf("�������2\n");
	PreOrderTraveral2(RootNode);
	printf("\n");
	printf("�������1\n");
	InOrderTraveral(RootNode);
	printf("\n");
	printf("�������2\n");
	InOrderTraveral(RootNode);
	printf("\n");
	printf("�������1\n");
	PostOrderTraveral(RootNode);
	printf("\n");
	printf("�������2\n");
	PostOrderTraveral(RootNode);
	printf("\n");
	printf("�������\n");
	LevelrderTraveral(RootNode);
	printf("\n");

}
//ѹջ����
void Push(Stack *pStr, ValueType x)
{
	pStr->Top++;
	pStr->Position[pStr->Top] = x;
}
//��ջ����
ValueType Pop(Stack *pStr)
{
	ValueType temp;
	temp = pStr->Position[pStr->Top];
	pStr->Top--;
	return temp;
}
//չʾջ��
ValueType Top(Stack *pStr)
{
	return pStr->Position[pStr->Top];
}
//���ջ�Ƿ�Ϊ��
bool IsEmpty(Stack *pStr)
{
	if (pStr->Top == -1)
		return true;
	else
		return false;
}
//��������
struct Queue * creatQ()
{
	struct Queue *pQ = (struct Queue *)malloc(sizeof(struct Queue));
	pQ->front = -1;
	pQ->rear = -1;
	return pQ;
}
//�ж϶����Ƿ���
bool IsFullQ(struct Queue *pQ)
{
	if ((pQ->rear + 1) % Maxsize == pQ->front)
		return true;
	else
		return false;
}
//���
void AddQ(struct Queue *pQ, ValueType x)
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
//�ж϶����Ƿ�Ϊ��
bool IsEmptyQ(struct Queue *pQ)
{
	if (pQ->front == pQ->rear)
		return true;
	else
		return false;
}
//����
ValueType DeleteQ(struct Queue *pQ)
{
	ValueType temp;
	temp = pQ->value[(pQ->front + 1) % Maxsize];
	pQ->front = (pQ->front + 1) % Maxsize;
	return temp;
}
//�������
TreeNode *MakeEmpty(TreeNode *pNode)
{
	if (pNode != NULL)
	{
		pNode->Left == NULL;
		pNode->Right == NULL;
		free(pNode);
	}
	return NULL;	
}
//�ݹ�ʵ��
TreeNode *Find(TreeNode *pNode, Elementtype x)
{
	if (!pNode)
		return NULL;
	if (x > pNode->value)
		return Find(pNode->Right, x);
	else if (x < pNode->value)
		return Find(pNode->Left, x);
	else
		return pNode;
}
//ѭ��ʵ��
//TreeNode *Find(TreeNode *pNode, Elementtype x)
//{
//	while (pNode)
//	{
//		if (x > pNode->value)
//			pNode = pNode->Right;
//		else if (x < pNode->value)
//			pNode = pNode->Left;
//		else
//			return pNode;
//	}
//	return NULL;
//}

//Ѱ����Сֵ �ݹ�ʵ��
TreeNode *FindMin(TreeNode *pNode)
{
	if (!pNode)
		return NULL;
	if (pNode->Left == NULL)
		return pNode;
	else
		return FindMin(pNode->Left);
}
//Ѱ�����ֵ ѭ��ʵ��
TreeNode *FindMax(TreeNode *pNode)
{
	if (pNode)
	{
		while (pNode->Right)
			pNode = pNode->Right;
	}
	return pNode;
}

//��������
TreeNode *Insert(TreeNode *pNode, Elementtype x)
{
	if (!pNode)
	{
		pNode = (TreeNode *)malloc(sizeof(TreeNode *));
		if (pNode == NULL)
			exit(-1); 
		pNode->Left = NULL;
		pNode->Right = NULL;
		pNode->value = x;
	}
	else
	{
		if (x < pNode->value)
			return Insert(pNode->Left, x);
		else if (x>pNode->value)
			return Insert(pNode->Right, x);
	}
	return pNode;
}
//ɾ���ڵ�
TreeNode *Delete(TreeNode *pNode, Elementtype x)
{
	TreeNode * pTemp;
	if (!pNode)
	{
		printf("��Ϊ�գ�\n");
		exit(-1);
	}
	if (x > pNode->value)
		pNode = pNode->Right;
	else if (x < pNode->value)
		pNode = pNode->Left;
	else
	{
		if (pNode->Left&&pNode->Right)
		{
			pTemp = FindMin(pNode->Right);
			pNode->value = pTemp->value;
			pNode->Right = Delete(pNode->Right, pNode->value);
		}
		else
		{
			pTemp = pNode;
			if (pNode->Left == NULL)
				pNode = pNode->Right;
			else if (pNode->Right == NULL)
				pNode = pNode->Left;
			free(pTemp);
		}
	}
	return pNode;
}
//������� �ݹ�ʵ��
void PreOrderTraveral(TreeNode *pNode)
{
	if (pNode)
	{
		printf("%4d", pNode->value);
		PreOrderTraveral(pNode->Left);
		PreOrderTraveral(pNode->Right);
	}
}
//������� �ݹ�ʵ��
void InOrderTraveral(TreeNode *pNode)
{
	if(pNode)
	{ 
	InOrderTraveral(pNode->Left);
	printf("%4d", pNode->value);
	InOrderTraveral(pNode->Right);
	}
}
//������� �ݹ�ʵ��
void PostOrderTraveral(TreeNode *pNode)
{
	if (pNode)
	{
		PostOrderTraveral(pNode->Left);
		PostOrderTraveral(pNode->Right);
		printf("%4d", pNode->value);
	}
}
//������� ��ջʵ��
void InOrderTraveral2(TreeNode *pNode)
{
	TreeNode *pTemp = pNode;
	while (pTemp || !IsEmpty(stack))
	{
		while (pTemp)
		{
			Push(stack, pTemp);
			pTemp = pTemp->Left;
		}
		if (!IsEmpty(stack))
		{
			pTemp = Pop(stack);
			printf("%4d", pTemp->value);
			pTemp = pTemp->Right;
		}
	}
}
//�������� ��ջʵ��
void PreOrderTraveral2(TreeNode *pNode)
{
	TreeNode *pTemp = pNode;
	while (pTemp || !IsEmpty(stack))
	{
		while(pTemp)
		{
			printf("%4d", pTemp->value);
			Push(stack, pTemp);
			pTemp = pTemp->Left;
		}
		if (!IsEmpty(stack))
		{
			pTemp = Pop(stack);
			pTemp = pTemp->Right;
		}
	}
}
//�������� ��ջʵ��
void PostOrderTraveral2(TreeNode *pNode)
{
	TreeNode *pTemp = pNode;
	while (pTemp || !IsEmpty(stack))
	{
		while (pTemp)
		{
			//printf("%4d", pTemp->value);
			Push(stack, pTemp);
			pTemp = pTemp->Left;
		}
		if (!IsEmpty(stack))
		{
			pTemp = Pop(stack);
			pTemp = pTemp->Right;
		}
	}
}
//������� ����ʵ��
void LevelrderTraveral(TreeNode *pNode)
{
	Queue *Q;
	Q = creatQ();
	TreeNode *pTemp;
	if (!pNode)
		return;
	AddQ(Q, pNode);
	while (!IsEmpty(Q))
	{
		pTemp= DeleteQ(Q);
		printf("%d", pTemp->value);
		if (pTemp->Left)
			AddQ(Q, pTemp->Left);
		if (pTemp->Right)
			AddQ(Q, pTemp->Right);
	}
}