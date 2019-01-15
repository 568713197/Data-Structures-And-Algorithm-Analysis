#include<stdio.h>
#include<stdlib.h>
#define ElementType int

typedef struct TreeNode *PriorityQueue;
struct TreeNode
{
	ElementType Element;
	PriorityQueue Left;
	PriorityQueue Right;
	int Npl;
};


ElementType FindMin(PriorityQueue H);//Ѱ����Сֵ(���ڵ�)
bool IsEmpty(PriorityQueue H);//�жϸ���ʽ���Ƿ�Ϊ��
PriorityQueue Merge(PriorityQueue H1, PriorityQueue H2);//�ϲ�����
void Swap(PriorityQueue H1);//����һ����ʽ�ѵ���������
void PrintPreorder(int depth, PriorityQueue root);//��ӡһ����ʽ��
PriorityQueue Insert(ElementType value, PriorityQueue H);//����һ������
int Minimal(int a, int b);//ȡС
PriorityQueue InnerMerge(PriorityQueue H1, PriorityQueue H2);//�ϲ��������ڲ�����
PriorityQueue DeleteMin(PriorityQueue H1);//ɾ����Сֵ(���ڵ�)




int main()
{
	int i;
	PriorityQueue h1,h2;
	int data1[] = { 21,10,23,14,3,26,17,8 };
	int data2[] = { 18,12,33,24,6,37,7,18 };
	h1 = Insert(data1[0], NULL);
	for (i = 1;i < 8;i++)
	{
		h1 = Insert(data1[i], h1);
	}
	printf("\n====after the leftlist heap h1 is merged====\n");
	PrintPreorder(1, h1);

	h2 = Insert(data2[0], NULL);
	for (i = 1;i < 8;i++)
	{
		h2 = Insert(data2[i], h2);
	}
	printf("\n====after the leftlist heap h2 is merged====\n");
	PrintPreorder(1, h2);

	h1 = Merge(h1, h2);
	printf("\n====after both h1 and h2 are merged====\n");
	PrintPreorder(1, h1);

	h1 = DeleteMin(h1);
	printf("\n====after excuating DeleteMin operation====\n");
	PrintPreorder(1, h1);

	return 0;
}

//����һ������
PriorityQueue Insert(ElementType value, PriorityQueue H)
{
	PriorityQueue node;
	node = (PriorityQueue)malloc(sizeof(TreeNode));
	if (!node)
	{
		printf("failed inserting,for out if space !\n");
		return H;
	}
	node->Left = NULL;
	node->Right = NULL;
	node->Npl = 0;
	node->Element = value;
	if (H == NULL)
	{
		return node;
	}
	else
	{
		return Merge(node, H);
	}
}

//����һ����ʽ�ѵ���������
void Swap(PriorityQueue H1)
{
	PriorityQueue temp;
	temp = H1->Left;
	H1->Left = H1->Right;
	H1->Right = temp;
}

//ȡС
int Minimal(int a, int b)
{
	return a > b ? a : b;
}

//�жϸ���ʽ���Ƿ�Ϊ��
bool IsEmpty(PriorityQueue H)
{
	if (H==NULL)
		return true;
	else
		return false;
}


//Ѱ����Сֵ(���ڵ�)
ElementType FindMin(PriorityQueue H)
{
	if (!IsEmpty(H))
		return H->Element;
	else
		return -1;
}

//�ϲ�����
PriorityQueue Merge(PriorityQueue H1, PriorityQueue H2)
{
	if (H1 == NULL)
		return H2;
	else if (H2 == NULL)
		return H1;
	if (H1->Element > H2->Element)
	{
		return InnerMerge(H2, H1);
	}
	else
	{
		return InnerMerge(H1, H2);
	}
}

//�ϲ��������ڲ�����
PriorityQueue InnerMerge(PriorityQueue H1, PriorityQueue H2)
{
	if (H1->Left == NULL)
	{
		H1->Left = H2;
	}
	else
	{
		H1->Right = Merge(H1->Right, H2);
	}
	if (H1->Right == NULL)
	{
		H1->Npl = 0;
	}
	else
	{
		H1->Npl = Minimal(H1->Left->Npl, H1->Right->Npl) + 1;
		if (H1->Left->Npl < H1->Right->Npl)
		{
			Swap(H1);
		}
	}
	return H1;
}

//ɾ����Сֵ(���ڵ�)
PriorityQueue DeleteMin(PriorityQueue H1)
{
	PriorityQueue left;
	PriorityQueue right;

	if (!H1)
	{
		printf("faild to DeleteMin,for the root doesn't point to any position!\n");
		return NULL;
	}
	left = H1->Left;
	right = H1->Right;
	free(H1);
	return Merge(left, right);
}

//��ӡһ����ʽ��
void PrintPreorder(int depth, PriorityQueue root)
{
	int i;
	if (root)
	{
		for (i = 0;i < depth;i++)
			printf("  ");
		printf("%d\n", root->Element);
		PrintPreorder(depth + 1, root->Left);
		PrintPreorder(depth + 1, root->Right);
	}
	else
	{
		for (i = 0;i < depth;i++)
			printf("  ");
		printf("NULL\n");
	}

}
