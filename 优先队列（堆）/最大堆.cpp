#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXDATE 1000
#define ElementType int
typedef struct HeapStruct *MaxHeap;
struct HeapStruct
{
	ElementType *Elements;
	int Size;
	int Capacity;
};

MaxHeap Creat(int MaxSize);//创建一个空的最大堆
bool IsFull(MaxHeap H);//堆是否已满
bool Insert(MaxHeap H, ElementType item);//向最大堆中插入一个数据
bool IsEmpty(MaxHeap H);//堆是否为空
ElementType DeleteMax(MaxHeap H);//删除最大的数据


int main()
{
	MaxHeap H1 = Creat(100);
	Insert(H1,20);
	printf("%d\n", H1->Size);
	for (int i = 1;i <= H1->Size;i++)
		printf("%d ", H1->Elements[i]);
	printf("\n");
	Insert(H1 ,23);
	printf("%d\n", H1->Size);
	for (int i = 1;i <= H1->Size;i++)
		printf("%d ", H1->Elements[i]);
	printf("\n");
	Insert(H1, 19);
	printf("%d\n", H1->Size);
	for (int i = 1;i <= H1->Size;i++)
		printf("%d ", H1->Elements[i]);
	printf("\n");
	Insert(H1, 17);
	printf("%d\n", H1->Size);
	for (int i = 1;i <= H1->Size;i++)
		printf("%d ", H1->Elements[i]);
	printf("\n");
	Insert(H1, 34);
	printf("%d\n", H1->Size);
	for (int i = 1;i <= H1->Size;i++)
		printf("%d ", H1->Elements[i]);
	printf("\n");
	Insert(H1, 56);
	printf("%d\n", H1->Size);
	for (int i = 1;i <= H1->Size;i++)
		printf("%d ", H1->Elements[i]);
	printf("\n");
	Insert(H1, 78);
	printf("%d\n", H1->Size);
	for (int i = 1;i <= H1->Size;i++)
		printf("%d ", H1->Elements[i]);
	printf("\n");
	DeleteMax(H1);
	printf("%d\n", H1->Size);
	for (int i = 1;i <= H1->Size;i++)
		printf("%d ", H1->Elements[i]);
	printf("\n");
	DeleteMax(H1);
	printf("%d\n", H1->Size);
	for (int i = 1;i <= H1->Size;i++)
		printf("%d ", H1->Elements[i]);
	printf("\n");
	DeleteMax(H1);
	printf("%d\n", H1->Size);
	for (int i = 1;i <= H1->Size;i++)
		printf("%d ", H1->Elements[i]);
	printf("\n");
	DeleteMax(H1);
	printf("%d\n", H1->Size);
	for (int i = 1;i <= H1->Size;i++)
		printf("%d ", H1->Elements[i]);
	printf("\n");

	return 0;
}


//创建一个空的最大堆
MaxHeap Creat(int MaxSize)
{
	MaxHeap H = (MaxHeap)malloc (sizeof(HeapStruct));
	H->Elements = (ElementType *)malloc(sizeof(MaxSize + 1));
	H->Size = 0;
	H->Capacity = MaxSize;
	H->Elements[0] = MAXDATE;
	return H;
}

//堆是否已满
bool IsFull(MaxHeap H)
{
	if (H->Size == H->Capacity)
		return true;
	else
		return false;
}

//向最大堆中插入一个数据
bool Insert(MaxHeap H, ElementType item)
{
	int i;
	if (IsFull(H))
	{
		printf("堆已满！\n");
		return 0;
	}
	//将数据放到堆的最底端，从下向上过滤，若根节点比该数据小换位
	i = ++H->Size;
	for (;H->Elements[i / 2] < item;i /= 2)
		H->Elements[i] = H->Elements[i / 2];
	H->Elements[i] = item;
}

//堆是否为空
bool IsEmpty(MaxHeap H)
{
	if (H->Size == 0)
		return true;
	else
		return false;
}

//删除最大的数据
ElementType DeleteMax(MaxHeap H)
{
	int Parent, Child;
	ElementType MaxItem, temp;
	//判断最大堆是否为空
	if (IsEmpty(H))
	{
		printf("最大堆已为空！\n");
		return 0;
	}

	MaxItem = H->Elements[1];//保存根节点（最大的数）
	temp = H->Elements[H->Size--];//保存最后一个节点同时将数组大小自减
	//用最后一个元素从下向上过滤下层节点
	for (Parent = 1;Parent * 2 <= H->Size;Parent = Child)
	{
		Child = Parent * 2;
		if ((Child != H->Size) &&
			(H->Elements[Child] <= H->Elements[Child + 1]))
			Child++;
		if (temp >= H->Elements[Child])
			break;
		else
			H->Elements[Parent] = H->Elements[Child];
	}
	H->Elements[Parent] = temp;
	return MaxItem;
}
