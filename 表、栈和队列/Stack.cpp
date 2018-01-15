#include<stdio.h>
#include<stdlib.h>
#define Elementtype int

typedef struct Stack
{
	Elementtype value;
	struct Stack *Next;
}LinkStack;

LinkStack *CreatStack();//创建一个空栈
bool IfEmpty(LinkStack *Top);//判断堆栈是否为空
void Push(LinkStack *Top, Elementtype x);//压栈
Elementtype Pop(LinkStack *Top);//出栈
void Show(LinkStack *Top);//从顶部开始打印栈中的数据
int main()
{
	LinkStack *Top;
	Top = CreatStack();
	Push(Top, 5);
	Push(Top, 7);
	Push(Top, 9);
	Show(Top);
	Elementtype value1=Pop(Top);
	printf("%d \n", value1);
	Show(Top);	
}

LinkStack *CreatStack()
{
	LinkStack *p = (LinkStack *)malloc(sizeof(LinkStack));
	p->Next = NULL;
	return p;
}
bool IfEmpty(LinkStack *Top)
{
	if (Top->Next == NULL)
		return true;
	else
		return false;
}
void Push(LinkStack *Top, Elementtype x)
{
	LinkStack *temp = Top->Next;
	LinkStack *pNode=(LinkStack *)malloc(sizeof(LinkStack));
	pNode->value = x;
	pNode->Next = temp;
	Top->Next = pNode;
}
Elementtype Pop(LinkStack *Top)
{
	if (IfEmpty(Top))
	{
		printf("空栈！\n");
		return NULL;
	}
	else
	{
		LinkStack *temp;
		temp = Top->Next;
		Top->Next = temp->Next;
		Elementtype num = temp->value;
		free(temp);
		return num;
	}
}
void Show(LinkStack *Top)
{
	if (IfEmpty(Top))
	{
		printf("空栈！\n");
	}
	else
	{
		LinkStack *temp = Top->Next;
		printf("%d  ", temp->value);
		while (temp->Next != NULL)
		{
			temp = temp->Next;
			printf("%d  ", temp->value);	
		}
		printf("\n");
	}
}