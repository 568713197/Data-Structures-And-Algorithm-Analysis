#include<stdio.h>
#define Maxsize 20
#define Elementtype int

struct Stack
{
	Elementtype value[Maxsize];
	int Top1;
	int Top2;
};
struct Stack S;

bool IsFull(struct Stack *pStrL);//判断堆栈是否满了
bool IsEmpty(struct Stack *pStrL, int tag);//判断堆栈是否为空
void Push(struct Stack *pStrL, Elementtype x, int tag);//压栈
Elementtype Pop(struct Stack *pStrL, int tag);//出栈
void Show(struct Stack *pStrL, int tag);//打印栈

int main()
{
	S.Top1 = -1;
	S.Top2 = Maxsize;
	Elementtype num1, num2;
	struct Stack *p = &S;
	//将12345,98765分别压入栈1,2
	for (int i = 1;i <= 5;i++)
	{
		Push(p, i, 1);
	}
	for (int j = 9;j >= 5;j--)
	{
		Push(p, j, 2);
	}
	Show(p, 1);
	Show(p, 2);
	//栈1弹出一个数据
	num1 = Pop(p, 1);
	printf("%d\n", num1);
	//栈2弹出一个数据
	num2 = Pop(p, 2);
	printf("%d\n", num2);

	for (int i = 0;i < Maxsize;i++)
		printf("%d  ", p->value[i]);
	printf("\n");
}
bool IsFull(struct Stack *pStrL)
{
	if (pStrL->Top2 - pStrL->Top1 == 1)
		return true;
	else
		return false;
}
bool IsEmpty(struct Stack *pStrL, int tag)
{
	if (tag == 1)
	{
		if (pStrL->Top1 == -1)
			return true;
		else
			return false;
	}
	else
	{
		if (pStrL->Top1 ==Maxsize)
			return true;
		else
			return false;
	}
}
void Push(struct Stack *pStrL, Elementtype x, int tag)
{
	if (IsFull(pStrL))
	{
		printf("栈满了\n");
	}
	else
	{
		if (tag == 1)
			pStrL->value[++pStrL->Top1] = x;
		else
			pStrL->value[--pStrL->Top2] = x;
	}
}
Elementtype Pop(struct Stack *pStrL, int tag)
{
	if (IsEmpty(pStrL, tag))
	{
		printf("栈空！\n");
		return NULL;
	}
	else
	{
		if (tag == 1)
		{
			Elementtype i = pStrL->value[pStrL->Top1];
			pStrL->value[pStrL->Top1--] = NULL;
			return i;
		}
		else
		{
			Elementtype i = pStrL->value[pStrL->Top2];
			pStrL->value[pStrL->Top2++] = NULL;
			return i;
		}
	}
}
void Show(struct Stack *pStrL, int tag)
{
	if (tag ==  1)
	{
		if (IsEmpty(pStrL, tag))
			printf("空栈\n");
		else
		{
			for (int i = 0;i <= pStrL->Top1;i++)
				printf("%d  ", pStrL->value[i]);
			printf("\n");
		}	
	}
	else
	{
		if (IsEmpty(pStrL, tag))
			printf("空栈\n");
		else
		{
			for (int j = Maxsize-1;j >= pStrL->Top2;j--)
				printf("%d  ", pStrL->value[j]);
			printf("\n");
		}
	}
}