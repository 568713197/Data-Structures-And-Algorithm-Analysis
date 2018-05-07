//问题原型
//有十台电脑{1,2,3....9,10},已知下列电脑已经实现了连接
//1-2  2-4  3-5  4-7  5-8  6-9  6-10


/*并查集相关函数实现*/

#include <stdio.h>
#define ElementType int
#define MaxSize 10

typedef struct
{
	ElementType Date;
	int Parent;
}SetType;

SetType U_F[MaxSize];   //定义一个结构体数组

void Init(SetType *Pstr);  //初始化
int Find(SetType *Pstr, ElementType x);  //查找元素的根节点  返回根节点的下标
void Union(SetType *Pstr, ElementType element1, ElementType element2);  //将集合合并
void Union_Better(SetType *Pstr, ElementType element1, ElementType element2);//优化后的合并算法


/*初始化*/
/*分别赋值0-MaxSize，根节点都设为-1*/
void Init(SetType *Pstr)
{
	for (int i = 1;i <= MaxSize;i++)
	{
		Pstr->Date = i;
		Pstr->Parent = -1;
		Pstr++;
	}
}
/*查找*/
/*查找某个数据的根节点*/
int Find(SetType *Pstr, ElementType x)
{
	int i;
	for (i = 0;i < MaxSize&&Pstr[i].Date != x;i++)
		;
	if (i >= MaxSize)
		return -1;
	for (;Pstr[i].Parent >= 0;i = Pstr[i].Parent)
		;
	return i;
}
/*并运算*/
/*找到俩个数据的根节点，若相同，不用处理，若不同，将数据1的根节点设为数据2的根节点*/
/*缺点：数据量大，多次并运算后会使树的高度过高，Find函数的时间复杂度会过高*/
void Union(SetType *Pstr, ElementType element1, ElementType element2)
{
	int Root1, Root2;
	Root1 = Find(Pstr, element1);
	Root2 = Find(Pstr,element2);
	if (Root1 != Root2)
		U_F[Root2].Parent = Root1;
}
/*优化后的并运算算法，根节点的Parent的绝对值代表这个根节点上连同自己共有几个节点，每次并运算时先判断俩个求并的根节点
的Parent绝对值谁的大，把节点少的挂载到节点多的上，先把少的那个根节点挂载上去，再遍历把所有以它为根节点的节点挂载上去
这样，可以保证每个节点都直接与根节点相连，不会随着节点的增加使Find的函数的时间复杂度太高*/
void Union_Better(SetType *Pstr, ElementType element1, ElementType element2)
{
	int Root1, Root2,i;
	Root1 = Find(Pstr, element1);
	Root2 = Find(Pstr, element2);
	if (U_F[Root1].Parent <= U_F[Root2].Parent)
	{
		U_F[Root2].Parent = Root1;
		U_F[Root1].Parent--;
		for (i = 0;i < MaxSize;i++)
		{
			if (U_F[i].Parent == Root2)
			{
				U_F[i].Parent = Root1;
				U_F[Root1].Parent--;
			}
		}
	}
	else
	{
		U_F[Root1].Parent = Root2;
		U_F[Root2].Parent--;
		for (i = 0;i < MaxSize;i++)
		{
			if (U_F[i].Parent == Root1)
			{
				U_F[i].Parent = Root2;
				U_F[Root2].Parent--;
			}
		}
	}
}
int main()
{
	//初始化
	Init(U_F);
	Union_Better(U_F, 1, 2);
	Union_Better(U_F, 2, 4);
	Union_Better(U_F, 3, 5);
	Union_Better(U_F, 4, 7);
	Union_Better(U_F, 5, 8);
	Union_Better(U_F, 6, 9);
	Union_Better(U_F, 6, 10);
	/*打印集合的情况*/
	for (int i = 0;i < MaxSize;i++)
	{
		printf("NO.%d  Date:%d   Parent:%d\n", i, U_F[i].Date, U_F[i].Parent);
	}
	/*俩个根节点并运算*/
	Union_Better(U_F, 1, 3);
	printf("***************************************************************\n");
	/*打印集合的情况*/
	for (int i = 0;i < MaxSize;i++)
	{
		printf("NO.%d  Date:%d   Parent:%d\n", i, U_F[i].Date, U_F[i].Parent);
	}
	return 0;
}
//输出的数据
//NO.0  Date:1   Parent : -4
//NO.1  Date : 2   Parent : 0
//NO.2  Date : 3   Parent : -3
//NO.3  Date : 4   Parent : 0
//NO.4  Date : 5   Parent : 2
//NO.5  Date : 6   Parent : -3
//NO.6  Date : 7   Parent : 0
//NO.7  Date : 8   Parent : 2
//NO.8  Date : 9   Parent : 5
//NO.9  Date : 10   Parent : 5
//***************************************************************
//NO.0  Date : 1   Parent : -7
//NO.1  Date : 2   Parent : 0
//NO.2  Date : 3   Parent : 0
//NO.3  Date : 4   Parent : 0
//NO.4  Date : 5   Parent : 0
//NO.5  Date : 6   Parent : -3
//NO.6  Date : 7   Parent : 0
//NO.7  Date : 8   Parent : 0
//NO.8  Date : 9   Parent : 5
//NO.9  Date : 10   Parent : 5