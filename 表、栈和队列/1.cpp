#include<stdio.h>
#include<stdlib.h>
#define Maxsize 20
struct List
{
	int date[Maxsize];
	int length;
};
List * makeempty();//创建线性表
List *initlist(List *PtrL);//初始化线性表
int finddate(List *PtrL, int x);//寻找某数据第一次出现的位置
int search(List *PtrL, int pos);//寻找某个位置的数据
List *changedate(List *PtrL, int pos, int newdate);//将某位置的数据更改
List *insert(List *PtrL, int pos, int x);//插入
List *add(List *PtrL, int x);//追加
void delete_List(List *PtrL);//删除List
List *delete_date(List *PtrL, int pos);//删除数据
void showlist(List *PtrL);//显示


List * makeempty()
{
	List *PtrL;
	PtrL = (List *)malloc(sizeof(List)*Maxsize);
	PtrL->length = 0;
	return PtrL;
}
List *initlist(List *PtrL)
{
	for (int i = 0;i < 10;i++)
	{
		PtrL->date[i] = i + 3;
		PtrL->length++;
	}
	return PtrL;
}
int finddate(List *PtrL, int x)
{
	for (int i = 0;i < PtrL->length;i++)
	{
		if (PtrL->date[i] == x)
			return i + 1;
	}
	return -1;
}
int search(List *PtrL, int pos)
{
	if (pos <= PtrL->length)
	{
		return PtrL->date[pos - 1];
	}
	else
		return -1;
}
List *changedate(List *PtrL, int pos, int newdate)
{
	if (pos <= PtrL->length)
	{
		PtrL->date[pos - 1] = newdate;
		return PtrL;
	}
	else
	{
		printf("位置错误\n");
		return PtrL;
	}
}
List *insert(List *PtrL, int pos, int x)
{
	int i;
	if (PtrL->length == Maxsize)
	{
		printf("空间已满\n");
		return PtrL;
	}
	if (pos > PtrL->length|| pos < 1)
	{
		printf("位置错误！\n");
		return PtrL;
	}
	for ( i = PtrL->length - 1;i >= pos;i--)
	{
		PtrL->date[i + 1] = PtrL->date[i];
	}
	PtrL->date[i] = x;
	PtrL->length++;
	return PtrL;
}
List *add(List *PtrL, int x)
{
	if (PtrL->length == Maxsize)
	{
		printf("空间已满\n");
		return PtrL;
	}
	else
	{
		PtrL->date[PtrL->length] = x;
		PtrL->length++;
		return PtrL;
	}
}
void delete_List(List *PtrL)
{
	free(PtrL);
}
List *delete_date(List *PtrL, int pos)
{
	if (pos > PtrL->length - 1 || pos < 1)
	{
		printf("位置错误！\n");
		return PtrL;
	}
	if(pos==PtrL->length)
	{
		PtrL->length--;
		return PtrL;
	}
	for (int i = pos ;i < PtrL->length;i++)
	{
		PtrL->date[i - 1] = PtrL->date[i];
	}
	PtrL->length--;
	return PtrL;
}
void showlist(List *PtrL)
{
	for (int i = 0;i <PtrL->length;i++)
	{
		printf("%3d", PtrL->date[i]);	
	}
	printf("\n");
}
int main()
{
	List *PtrL;
	int pos, date;
	PtrL = makeempty();
	initlist(PtrL);
	showlist(PtrL);
	//寻找9出现的位置
	pos = finddate(PtrL, 9);
	printf("9出现的位置：%d\n",pos);
	//第三个位置的数据
	date = search(PtrL, 3);
	printf("第三个位置的数据：%d\n", date);
	//将第四个位置的数据改为22
	changedate(PtrL, 4, 22);
	showlist(PtrL);
	//在第五个位置插入11
	insert(PtrL, 5, 11);
	showlist(PtrL);
	//在末尾追加30
	add(PtrL, 30);
	showlist(PtrL);
	//删除第8个数据
	delete_date(PtrL, 8);
	showlist(PtrL);
	return 0;
}