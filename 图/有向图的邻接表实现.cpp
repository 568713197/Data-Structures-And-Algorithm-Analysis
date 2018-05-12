#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#define MaxSize 100
#define IsLetter(a)  ((((a)>='a')&&((a)<='z')) || (((a)>='A')&&((a)<='Z')))
#define LENGTH(a)  (sizeof(a)/sizeof(a[0]))

//邻接表中对应链表的顶点
typedef struct _ENode
{
	int iVex;
	_ENode * Next_Edge;
}ENode;

//邻接表中表的顶点
typedef struct _VNode
{
	char date;
	_ENode * First_Edge;
}VNode;

//邻接表
typedef struct _Graph
{
	int Vexs;
	int Edgs;
	VNode Vertex[MaxSize];
}Graph;

//得到某个节点的位置，若存在返回节点位置，若不存在，返回-1
static int Get_Position(Graph G, char Element)
{
	int i;
	for (i = 0;i < G.Vexs;i++)
		if (G.Vertex[i].date == Element)
			return i;
	return -1;
}

//读入一个字符
static char Read_Char()
{
	char ch;

	do
	{
		ch = getchar();
	} while (!IsLetter(ch));

	return ch;
}

//将node连接到list的末尾
static void Link_Last(ENode *const List, ENode *node)
{
	ENode *p = List;
	if (p->Next_Edge)
		p = p->Next_Edge;
	p->Next_Edge = node;
}

//创建一个图（示例）
Graph * Create_Example_Graph()
{
	char c1, c2;
	char vexs[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G' };
	char edges[][2] = {
		{ 'A', 'B' },
		{ 'B', 'C' },
		{ 'B', 'E' },
		{ 'B', 'F' },
		{ 'C', 'E' },
		{ 'D', 'C' },
		{ 'E', 'B' },
		{ 'E', 'D' },
		{ 'F', 'G' } };
	int vlen = LENGTH(vexs);
	int elen = LENGTH(edges);
	int i, p1, p2;
	ENode *node1, *node2;
	Graph* pG;
	//为图分配内存空间
	if ((pG = (Graph *)malloc(sizeof(Graph))) == NULL)
		return NULL;
	memset(pG, 0, sizeof(Graph));
	//初始化边数和顶点数
	pG->Edgs = elen;
	pG->Vexs = vlen;
	//初始化顶点
	for (i = 0;i < pG->Vexs;i++)
	{
		pG->Vertex[i].date = vexs[i];
		pG->Vertex[i].First_Edge = NULL;
	}
	//初始化边
	for (i = 0;i < pG->Edgs;i++)
	{
		//读取边的起始顶点和结束顶点
		c1 = edges[i][0];
		c2 = edges[i][1];

		p1 = Get_Position(*pG, c1);
		p2 = Get_Position(*pG, c2);
		//初始化node1
		node1 = (ENode*)malloc(sizeof(ENode));
		node1->iVex = p2;
		node1->Next_Edge = NULL;				//注意一定要初始化为NULL

		if (pG->Vertex[p1].First_Edge == NULL)
			pG->Vertex[p1].First_Edge = node1;
		else
			Link_Last(pG->Vertex[p1].First_Edge, node1);
		/*相对于无向图的邻接表实现唯一需要更改的地方*/
		////初始化node2
		//node2 = (ENode*)malloc(sizeof(ENode));
		//node2->iVex = p1;
		//node2->Next_Edge = NULL;				//注意一定要初始化为NULL

		//if (pG->Vertex[p2].First_Edge == NULL)
		//	pG->Vertex[p2].First_Edge = node2;
		//else
		//	Link_Last(pG->Vertex[p2].First_Edge, node2);
	}
	return pG;
}

//深度优先遍历图的递归实现
static void DFS(Graph G, int i, int *Visited)
{
	ENode *node;

	Visited[i] = 1;
	printf("%c ", G.Vertex[i].date);
	node = G.Vertex[i].First_Edge;

	while (node != NULL)
	{
		if (!Visited[node->iVex])
			DFS(G, node->iVex, Visited);
		node = node->Next_Edge;
	}
}

//DFS
void DFSTraveling(Graph G)
{
	int i;
	int Visited[MaxSize];						//顶点访问标记
												//初始化访问标记
	for (i = 0;i < G.Vexs;i++)
	{
		Visited[i] = 0;
	}
	//深度优先遍历
	printf("DFS: ");
	for (i = 0;i < G.Vexs;i++)
	{
		if (Visited[i] == 0)
			DFS(G, i, Visited);
	}
	printf("\n");
}

//BFS
void BFSTraveling(Graph G)
{
	int head = 0;
	int rear = 0;
	int Queue[MaxSize];
	int Visited[MaxSize];
	int i, j, k;
	ENode * node;
	//初始化访问标记
	for (i = 0;i < G.Vexs;i++)
	{
		Visited[i] = 0;
	}
	printf("BFS: ");
	//广度优先遍历
	for (i = 0;i < G.Vexs;i++)
	{
		if (Visited[i] == 0)
		{
			Visited[i] = 1;
			printf("%c ", G.Vertex[i].date);
			Queue[rear++] = i;							//入队列
		}
		while (head != rear)
		{
			j = Queue[head++];							//出队列
			node = G.Vertex[j].First_Edge;
			while (node != NULL)
			{
				k = node->iVex;
				if (Visited[k] == 0)
				{
					Visited[k] = 1;
					printf("%c ", G.Vertex[k].date);
					Queue[rear++] = k;					//入队列
				}
				node = node->Next_Edge;
			}
		}
	}
	printf("\n");
}

//打印邻接表
void Print_Graph(Graph G)
{
	int i, j;
	ENode * node;
	//开始打印
	printf("Graph List:  \n");
	for (i = 0;i < G.Vexs;i++)
	{
		printf("%d(%c): ", i, G.Vertex[i].date);
		node = G.Vertex[i].First_Edge;
		while (node != NULL)
		{
			printf("%d(%c) ", node->iVex, G.Vertex[node->iVex].date);
			node = node->Next_Edge;
		}
		printf("\n");
	}
}

int main()
{
	Graph * PG;
	/*创建一个图*/
	PG = Create_Example_Graph();
	/*打印邻接表*/
	Print_Graph(*PG);
	/*深度优先搜索*/
	DFSTraveling(*PG);
	/*广度优先搜索*/
	BFSTraveling(*PG);
}