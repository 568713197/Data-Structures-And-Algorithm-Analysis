#include<stdio.h>
#include<stdlib.h>
#define ElementType int
typedef struct HeapStruct *MinHeap;
struct HeapStruct
{
	ElementType* Elements;
	int Size;
	int Capacity;
};

MinHeap Creat(int Maxsize);//�½���С��
bool IsEmpty(MinHeap H);//��С���Ƿ�Ϊ��
bool IsFull(MinHeap H);//��С���Ƿ�����
bool Insert(MinHeap H, ElementType item);//��������
ElementType DeleteMin(MinHeap H);//ɾ����С����

int main()
{
	int i;
	MinHeap H = Creat(100);
	Insert(H, 50);
	printf("%d\n", H->Size);
	for (i = 1;i <= H->Size;i++)
		printf("%d ", H->Elements[i]);
	printf("\n");
	Insert(H, 47);
	printf("%d\n", H->Size);
	for (i = 1;i <= H->Size;i++)
		printf("%d ", H->Elements[i]);
	printf("\n");
	Insert(H, 23);
	printf("%d\n", H->Size);
	for (i = 1;i <= H->Size;i++)
		printf("%d ", H->Elements[i]);
	printf("\n");
	Insert(H, 34);
	printf("%d\n", H->Size);
	for (i = 1;i <= H->Size;i++)
		printf("%d ", H->Elements[i]);
	printf("\n");
	Insert(H, 12);
	printf("%d\n", H->Size);
	for (i = 1;i <= H->Size;i++)
		printf("%d ", H->Elements[i]);
	printf("\n");
	Insert(H, 9);
	printf("%d\n", H->Size);
	for (i = 1;i <= H->Size;i++)
		printf("%d ", H->Elements[i]);
	printf("\n");
	printf("min:%d\n", DeleteMin(H));
	printf("%d\n", H->Size);
	for (i = 1;i <= H->Size;i++)
		printf("%d ", H->Elements[i]);
	printf("\n");
	printf("min:%d\n", DeleteMin(H));
	printf("%d\n", H->Size);
	for (i = 1;i <= H->Size;i++)
		printf("%d ", H->Elements[i]);
	printf("\n");
	printf("min:%d\n", DeleteMin(H));
	printf("%d\n", H->Size);
	for (i = 1;i <= H->Size;i++)
		printf("%d ", H->Elements[i]);
	printf("\n");
	return 0;
}

//�½���С��
MinHeap Creat(int Maxsize)
{
	MinHeap H = (MinHeap)malloc(sizeof(HeapStruct));
	H->Elements = (ElementType*)malloc(sizeof(Maxsize + 1));
	H->Elements[0] = -1;
	H->Size = 0;
	H->Capacity = Maxsize;
	return H;
}

//��С���Ƿ�Ϊ��
bool IsEmpty(MinHeap H)
{
	if (H->Size == 0)
		return true;
	else
		return false;
}

//��С���Ƿ�����
bool IsFull(MinHeap H)
{
	if (H->Size == H->Capacity)
		return true;
	else
		return false;
}

//��������
bool Insert(MinHeap H, ElementType item)
{
	int i;
	if (IsFull(H))
	{
		printf("��С������!\n");
		return 0;
	}
	for (i = ++H->Size;H->Elements[i / 2] > item;i /= 2)
		H->Elements[i] = H->Elements[i/2];
	H->Elements[i] = item;
}

//ɾ����С����
ElementType DeleteMin(MinHeap H)
{
	ElementType MinElement, temp;
	int Parent, Child, i;
	if (IsEmpty(H))
	{
		printf("��С���ѿգ�\n");
		return -1;
	}
	MinElement = H->Elements[1];
	temp = H->Elements[H->Size--];
	for (i = 1;i * 2 <= H->Size;i = Child)
	{
		Child = i * 2;
		if (Child != H->Size&&H->Elements[Child + 1] < H->Elements[Child])
			Child++;

		if (temp > H->Elements[Child])
			H->Elements[i] = H->Elements[Child];
		else
			break;
	}
	H->Elements[i] = temp;
	return MinElement;
}