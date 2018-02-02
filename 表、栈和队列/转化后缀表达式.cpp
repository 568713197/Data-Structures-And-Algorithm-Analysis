//还没有完全实现功能只能处理只有*和+的表达式，带有（）的表达式没有办法转化
//再过段时间我会把它的功能完善
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#define Maxsize 20
#define Elementtype char

typedef struct Stack
{
	Elementtype value[Maxsize];
	int Top;
}Stack;
Stack stack;
void Push(Stack *pArray, Elementtype x); //压栈
Elementtype ShowTop(Stack *pArray); //显示栈顶元素
Elementtype Pop(Stack *pArray);//弹出栈顶元素
bool IsEmpty(Stack *pArray);//栈是否为空
bool IsHigh(Elementtype a, Elementtype b);//判断优先级
int main()
{
	Stack *pStack = &stack;
	pStack->Top = -1;
	Elementtype original[20];
	printf("请输入算数表达式：\n");
	scanf("%s", original);
	int i = 0;
	if (!isalpha(original[0]))
	{
		printf("输入的表达式错误！按键结束程序\n");
		if (getchar())
			exit(0);
	}
	while (original[i] != '\0')
	{
		if (isalpha(original[i]))//若为字母输出
		{
			printf("%c", original[i]);
			i++;
			continue;
		}
		else
		{
			if (IsEmpty(pStack))
			{
				Push(pStack, original[i]);
				i++;
				continue;
			}
			else
			{
				Elementtype topvalue;
				topvalue = ShowTop(pStack);
				if (IsHigh(topvalue, original[i]))
				{
					while (!IsEmpty(pStack)&&IsHigh(topvalue, original[i]))
					{
						printf("%c", Pop(pStack));
						topvalue = ShowTop(pStack);
					}
					Push(pStack, original[i]);
					i++;
					continue;
				}
				else if (!IsHigh(topvalue, original[i]))
				{
					Push(pStack, original[i]);
				}
				i++;
				continue;
			}
		}
	}
	while (!IsEmpty(pStack))
	{
		printf("%c", Pop(pStack));
	}
	printf("\n");
	return 0;
}
void Push(Stack *pArray, Elementtype x)
{
	pArray->Top++;
	pArray->value[pArray->Top] = x;
}
Elementtype ShowTop(Stack *pArray)
{
	return pArray->value[pArray->Top];
}
Elementtype Pop(Stack *pArray)
{
	Elementtype temp;
	temp= pArray->value[pArray->Top];
	pArray->Top--;
	return temp;
}
bool IsEmpty(Stack *pArray)
{
	if (pArray->Top == -1)
		return true;
	else
		return false;
}
bool IsHigh(Elementtype a, Elementtype b)
{
	// '(' 40 ; ')' 41 ; '*' 42 ; '+' 43 
	if (a <= b)
		return true;
	else
		return false;
}