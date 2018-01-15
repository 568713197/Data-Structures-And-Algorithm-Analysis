#include<stdio.h>
#include<stdlib.h>
typedef struct Link Link;
struct Link
{
	int date;
	struct Link *Next;
};
Link *initlink();//初始化链表
int finddate(Link *PtrL, int x);//查找数据的位置
int search(Link *PtrL, int pos);//查找某位置的数据
Link *insert(Link *PtrL, int pos, int newdate);//插入数据(插在原pos位数据之前)
Link *add(Link *PtrL, int newdate);//追加数据
int countlist(Link *PtrL);//计数
Link *delete_date(Link *PtrL, int pos);//删除数据
void delete_link(Link *PtrL);//删除链表
Link *changedate(Link *PtrL, int pos, int newdate);//修改数据
void showlink(Link *PtrL);//显示链表

Link *initlink()
{
	Link *PtrL= (Link *)malloc(sizeof(Link));
	Link *p = PtrL;
	for (int i = 0;i < 5;i++)
	{
		PtrL->date = i + 2;
		PtrL->Next = (Link *)malloc(sizeof(Link));
		PtrL = PtrL->Next;
	}
	PtrL->Next = NULL;
	return p;
} 
int countlist(Link *PtrL)
{
	int index=0;
	while (PtrL->Next != NULL)
	{
		PtrL = PtrL->Next;
		index++;
	}
	return index;
}
int finddate(Link *PtrL, int x)
{
	int num = countlist(PtrL);
	int index=1;
	while (PtrL->Next != NULL&&PtrL->date != x)
	{
		PtrL = PtrL->Next;
		index++;
	}
	if (index == num)
		return 0;
	else
		return index;
}
int search(Link *PtrL, int pos)
{
	int index = 1;
	while (PtrL->Next != NULL&&index != pos)
	{
		PtrL = PtrL->Next;
		index++;
	}
	return PtrL->date;
}
Link *insert(Link *PtrL, int pos, int newdate)
{
	Link *temp = PtrL;
	if (pos == 1)
	{
		Link *temp = (Link *)malloc(sizeof(Link));
		temp->date = newdate;
		temp->Next = PtrL;
		return temp;
	}
	else if (pos > countlist(PtrL)||pos<1)
	{
		printf("位置错误!\n");
		return PtrL;
	}
	else
	{
		Link *p = (Link *)malloc(sizeof(Link));
		p->date = newdate;
		for (int i = 2;i < pos;i++)
		{
			PtrL = PtrL->Next;
		}
		p->Next = PtrL->Next;
		PtrL->Next = p;
		return temp;
	}
}
Link *add(Link *PtrL, int newdate)
{
	Link *pos = PtrL;
	while (PtrL->Next != NULL)
	{
		PtrL = PtrL->Next;
	}
	Link *p = (Link *)malloc(sizeof(Link));
	PtrL->Next = p;
	PtrL->date = newdate;
	p->Next = NULL;
	return pos;
}

Link *delete_date(Link *PtrL, int pos)
{
	Link *p = PtrL;
	int index = 1;
	if (pos == 1)
	{
		Link *temp = PtrL->Next;
		free(PtrL);
		return temp;
	}
	else
	{
		while (PtrL->Next != NULL&&index != pos - 1)
		{
			PtrL = PtrL->Next;
			index++;
		}
		Link *temp2 = PtrL->Next;//指向要删除的节点
		Link *temp3 = temp2->Next;//获取要删除的节点所指向的下一个节点
		PtrL->Next = temp3;
		free(temp2);
		return p;
	}
}
void delete_link(Link *PtrL)
{
	Link *p,*temp;
	p = PtrL;
	while (p->Next != NULL)
	{
		temp= p->Next;
		free(p);
		p = temp;
	}
}
Link *changedate(Link *PtrL, int pos, int newdate)
{
	Link *p = PtrL;
	int index = 1;
	if (pos > countlist(PtrL))
		printf("输入的位置错误！\n");
	while (PtrL->Next != NULL&&index != pos)
	{
		PtrL = PtrL->Next;
		index++;
	}
	PtrL->date = newdate;
	return p;
}
void showlink(Link *PtrL)
{
	while (PtrL->Next != NULL)
	{
		printf("%d  ", PtrL->date);
		PtrL = PtrL->Next;
	}
	printf("\n");
}
int main()
{
	Link *pLink;
	int pos,value,num;
	pLink=initlink();//初始化链表
	//寻找4的位置
	pos = finddate(pLink, 4);
	printf("原始链表：\n");
	showlink(pLink);
	printf("数据4在第 %d 个\n", pos);
	//查找第4位置的数据
	value = search(pLink, 4);
	printf("第四个数据为：%d\n", value);
	//对链表计数
	num = countlist(pLink);
	printf("链表中的数据个数：%d\n", num);
	//在第三位插入9
	printf("在第三位插入9的链表为：\n");
	pLink=insert(pLink, 3, 9);
	showlink(pLink);
	//在末尾追加11
	printf("在末尾追加11的链表为：\n");
	pLink=add(pLink, 11);
	showlink(pLink);
	//把第二位改为30
	printf("把第二位改为30的链表为：\n");
	pLink=changedate(pLink, 2, 30);
	showlink(pLink);
	//把第四位删除
	printf("删除第四位：\n");
	pLink=delete_date(pLink, 4);
	showlink(pLink);
	return 0;
}