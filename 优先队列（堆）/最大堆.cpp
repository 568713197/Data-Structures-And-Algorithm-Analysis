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

MaxHeap Creat(int MaxSize);//����һ���յ�����
bool IsFull(MaxHeap H);//���Ƿ�����
bool Insert(MaxHeap H, ElementType item);//�������в���һ������
bool IsEmpty(MaxHeap H);//���Ƿ�Ϊ��
ElementType DeleteMax(MaxHeap H);//ɾ����������


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


//����һ���յ�����
MaxHeap Creat(int MaxSize)
{
	MaxHeap H = (MaxHeap)malloc (sizeof(HeapStruct));
	H->Elements = (ElementType *)malloc(sizeof(MaxSize + 1));
	H->Size = 0;
	H->Capacity = MaxSize;
	H->Elements[0] = MAXDATE;
	return H;
}

//���Ƿ�����
bool IsFull(MaxHeap H)
{
	if (H->Size == H->Capacity)
		return true;
	else
		return false;
}

//�������в���һ������
bool Insert(MaxHeap H, ElementType item)
{
	int i;
	if (IsFull(H))
	{
		printf("��������\n");
		return 0;
	}
	//�����ݷŵ��ѵ���׶ˣ��������Ϲ��ˣ������ڵ�ȸ�����С��λ
	i = ++H->Size;
	for (;H->Elements[i / 2] < item;i /= 2)
		H->Elements[i] = H->Elements[i / 2];
	H->Elements[i] = item;
}

//���Ƿ�Ϊ��
bool IsEmpty(MaxHeap H)
{
	if (H->Size == 0)
		return true;
	else
		return false;
}

//ɾ����������
ElementType DeleteMax(MaxHeap H)
{
	int Parent, Child;
	ElementType MaxItem, temp;
	//�ж������Ƿ�Ϊ��
	if (IsEmpty(H))
	{
		printf("������Ϊ�գ�\n");
		return 0;
	}

	MaxItem = H->Elements[1];//������ڵ㣨��������
	temp = H->Elements[H->Size--];//�������һ���ڵ�ͬʱ�������С�Լ�
	//�����һ��Ԫ�ش������Ϲ����²�ڵ�
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
