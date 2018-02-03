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

TreeNode *MakeEmpty(TreeNode *pNode);//清空二叉查找树
TreeNode *Find(TreeNode *pNode, Elementtype x);//查找一个数据
TreeNode *FindMin(TreeNode *pNode);//寻找最小值地址
TreeNode *FindMax(TreeNode *pNode);//寻找最大值地址
TreeNode *Insert(TreeNode *pNode, Elementtype x);//插入数据
TreeNode *Delete(TreeNode *pNode, Elementtype x);//删除数据
void PreOrderTraveral(TreeNode *pNode);//先序遍历 递归实现
void InOrderTraveral(TreeNode *pNode);//中序遍历 递归实现
void PostOrderTraveral(TreeNode *pNode);//后序遍历 递归实现
void PreOrderTraveral2(TreeNode *pNode);//先序遍历 堆栈实现
void InOrderTraveral2(TreeNode *pNode);//中序遍历 堆栈实现
void PostOrderTraveral2(TreeNode *pNode);//后序遍历 堆栈实现
void LevelrderTraveral(TreeNode *pNode);//层序遍历 队列实现
void Push(Stack *pStr, ValueType x);//压栈
ValueType Pop(Stack *pStr);//出栈
ValueType Top(Stack *pStr);//返回栈顶元素
bool IsEmpty(Stack *pStr);//检测是否为空栈
struct Queue * creatQ();//创建一个队列
bool IsFullQ(struct Queue *pQ);//判断队列是否已满
void AddQ(struct Queue *pQ, Elementtype x);//入队
bool IsEmptyQ(struct Queue *pQ);//判断队列是否为空
ValueType DeleteQ(struct Queue *pQ);//出队

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
	printf("最小值%d\n", Min->value);
	printf("最大值%d\n", Max->value);
	printf("先序遍历1\n");
	PreOrderTraveral(RootNode);
	printf("\n");
	printf("先序遍历2\n");
	PreOrderTraveral2(RootNode);
	printf("\n");
	printf("中序遍历1\n");
	InOrderTraveral(RootNode);
	printf("\n");
	printf("中序遍历2\n");
	InOrderTraveral(RootNode);
	printf("\n");
	printf("后序遍历1\n");
	PostOrderTraveral(RootNode);
	printf("\n");
	printf("后序遍历2\n");
	PostOrderTraveral(RootNode);
	printf("\n");
	printf("层序遍历\n");
	LevelrderTraveral(RootNode);
	printf("\n");

}
//压栈操作
void Push(Stack *pStr, ValueType x)
{
	pStr->Top++;
	pStr->Position[pStr->Top] = x;
}
//出栈操作
ValueType Pop(Stack *pStr)
{
	ValueType temp;
	temp = pStr->Position[pStr->Top];
	pStr->Top--;
	return temp;
}
//展示栈顶
ValueType Top(Stack *pStr)
{
	return pStr->Position[pStr->Top];
}
//检测栈是否为空
bool IsEmpty(Stack *pStr)
{
	if (pStr->Top == -1)
		return true;
	else
		return false;
}
//创建队列
struct Queue * creatQ()
{
	struct Queue *pQ = (struct Queue *)malloc(sizeof(struct Queue));
	pQ->front = -1;
	pQ->rear = -1;
	return pQ;
}
//判断队列是否满
bool IsFullQ(struct Queue *pQ)
{
	if ((pQ->rear + 1) % Maxsize == pQ->front)
		return true;
	else
		return false;
}
//入队
void AddQ(struct Queue *pQ, ValueType x)
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
//判断队列是否为空
bool IsEmptyQ(struct Queue *pQ)
{
	if (pQ->front == pQ->rear)
		return true;
	else
		return false;
}
//出队
ValueType DeleteQ(struct Queue *pQ)
{
	ValueType temp;
	temp = pQ->value[(pQ->front + 1) % Maxsize];
	pQ->front = (pQ->front + 1) % Maxsize;
	return temp;
}
//将树清空
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
//递归实现
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
//循环实现
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

//寻找最小值 递归实现
TreeNode *FindMin(TreeNode *pNode)
{
	if (!pNode)
		return NULL;
	if (pNode->Left == NULL)
		return pNode;
	else
		return FindMin(pNode->Left);
}
//寻找最大值 循环实现
TreeNode *FindMax(TreeNode *pNode)
{
	if (pNode)
	{
		while (pNode->Right)
			pNode = pNode->Right;
	}
	return pNode;
}

//插入数据
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
//删除节点
TreeNode *Delete(TreeNode *pNode, Elementtype x)
{
	TreeNode * pTemp;
	if (!pNode)
	{
		printf("树为空！\n");
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
//先序遍历 递归实现
void PreOrderTraveral(TreeNode *pNode)
{
	if (pNode)
	{
		printf("%4d", pNode->value);
		PreOrderTraveral(pNode->Left);
		PreOrderTraveral(pNode->Right);
	}
}
//中序遍历 递归实现
void InOrderTraveral(TreeNode *pNode)
{
	if(pNode)
	{ 
	InOrderTraveral(pNode->Left);
	printf("%4d", pNode->value);
	InOrderTraveral(pNode->Right);
	}
}
//后序遍历 递归实现
void PostOrderTraveral(TreeNode *pNode)
{
	if (pNode)
	{
		PostOrderTraveral(pNode->Left);
		PostOrderTraveral(pNode->Right);
		printf("%4d", pNode->value);
	}
}
//中序遍历 堆栈实现
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
//先序排列 堆栈实现
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
//后序排列 堆栈实现
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
//层序遍历 队列实现
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