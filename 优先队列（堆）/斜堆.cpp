#include<stdio.h>
#include<stdlib.h>

#define ElementType int

typedef struct TreeNode *PriorityQueue;
struct TreeNode
{
	ElementType Element;
	PriorityQueue Left;
	PriorityQueue Right;
};

void Swap(PriorityQueue H);//交换左右子树
bool IsEmpty(PriorityQueue H);//斜堆是否为空
void PrintPreorder(int depth, PriorityQueue H);//打印斜堆
PriorityQueue Insert(PriorityQueue H, ElementType value);//向斜堆插入一个数据
PriorityQueue Merge(PriorityQueue H1, PriorityQueue H2);//合并两个斜堆
PriorityQueue InnerMerge(PriorityQueue H1, PriorityQueue H2);//合并斜堆的内部操作
PriorityQueue DeleteMin(PriorityQueue H);//删除最小值（根节点）
ElementType GetMin(PriorityQueue H);//得到最小值


int main()
{
	PriorityQueue h1,h2;
	int data1[] = { 21,10,23,14,3,26,17,8 };
	int data2[] = { 18,7,37,6,24,33,12,18 };
	int i;

	h1 = Insert(NULL,data1[0]);
	for (i = 1;i < 8;i++)
	{
		h1 = Insert(h1, data1[i]);
	}
	printf("\n====after the skew heap h1 is merged====\n");
	PrintPreorder(1, h1);
	h2 = Insert(NULL, data2[0]);
	for (i = 1;i < 8;i++)
	{
		h2 = Insert(h2, data2[i]);
	}
	printf("\n====after the skew heap h2 is merged====\n");
	PrintPreorder(1, h2);

	h1 = Merge(h1, h2);
	printf("\n====after both h1 and h2 are merged====\n");
	PrintPreorder(1, h1);

	return 0;
}

//交换左右子树
void Swap(PriorityQueue H)
{
	PriorityQueue temp;
	temp = H->Left;
	H->Left = H->Right;
	H->Right = temp;
}

//斜堆是否为空
bool IsEmpty(PriorityQueue H)
{
	if (H == NULL)
		return true;
	else
		return false;
}

//向斜堆插入一个数据
PriorityQueue Insert(PriorityQueue H, ElementType value)
{
	PriorityQueue temp;
	temp = (PriorityQueue)malloc(sizeof(TreeNode));
	if (!temp)
	{
		printf("failed inserting,for out of space!\n");
		return NULL;
	}
	temp->Left = NULL;
	temp->Right = NULL;
	temp->Element = value;

	if (IsEmpty(H))
	{
		return temp;
	}
	else
	{
		return Merge(H, temp);
	}
}

//合并两个斜堆
PriorityQueue Merge(PriorityQueue H1, PriorityQueue H2)
{
	if (H1 == NULL)
	{
		return H2;
	}
	else if (H2 == NULL)
	{
		return H1;
	}
	else
	{
		if (H1->Element < H2->Element)
			return InnerMerge(H1, H2);
		else
			return InnerMerge(H2, H1);
	}
}

//合并斜堆的内部操作
PriorityQueue InnerMerge(PriorityQueue H1, PriorityQueue H2)
{
	if (H1->Left == NULL)
	{
		H1->Left = H2;
	}
	else
	{
		H1->Right = Merge(H1->Right, H2);
		Swap(H1);
	}
	return H1;
}

//删除最小值（根节点）
PriorityQueue DeleteMin(PriorityQueue H)
{
	PriorityQueue temp;
	temp = Merge(H->Left, H->Right);
	free(H);
	return temp;
}

//得到最小值
ElementType GetMin(PriorityQueue H)
{
	return H->Element;
}

//打印斜堆
void PrintPreorder(int depth, PriorityQueue H)
{
	int i;
	if (H)
	{
		for (i = 0;i < depth;i++)
			printf(" ");
		printf("%d\n", H->Element);
		PrintPreorder(depth + 1, H->Left);
		PrintPreorder(depth + 1, H->Right);
	}
	else
	{
		for (i = 0;i < depth;i++)
			printf(" ");
		printf("NULL\n");
	}
}
