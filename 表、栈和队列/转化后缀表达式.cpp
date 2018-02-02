//��û����ȫʵ�ֹ���ֻ�ܴ���ֻ��*��+�ı��ʽ�����У����ı��ʽû�а취ת��
//�ٹ���ʱ���һ�����Ĺ�������
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
void Push(Stack *pArray, Elementtype x); //ѹջ
Elementtype ShowTop(Stack *pArray); //��ʾջ��Ԫ��
Elementtype Pop(Stack *pArray);//����ջ��Ԫ��
bool IsEmpty(Stack *pArray);//ջ�Ƿ�Ϊ��
bool IsHigh(Elementtype a, Elementtype b);//�ж����ȼ�
int main()
{
	Stack *pStack = &stack;
	pStack->Top = -1;
	Elementtype original[20];
	printf("�������������ʽ��\n");
	scanf("%s", original);
	int i = 0;
	if (!isalpha(original[0]))
	{
		printf("����ı��ʽ���󣡰�����������\n");
		if (getchar())
			exit(0);
	}
	while (original[i] != '\0')
	{
		if (isalpha(original[i]))//��Ϊ��ĸ���
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