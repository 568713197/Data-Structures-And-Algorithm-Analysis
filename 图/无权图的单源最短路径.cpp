//无权图使用邻接表实现
//该无权图为有向图
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
	int Dist;                                    //距离
	char Path;									 //薄记变量 用来回溯路径
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
void Create_Example_Graph(Graph *P_G)
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
	Graph* pG=P_G;
	//为图分配内存空间
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
}


//无权图最短路径
Graph * UnWeighted(Graph G,char Element)
{
	int i, j, v;
	int Queue[MaxSize];
	ENode *node;
	int head = 0;
	int rear = 0;
	//初始化
	for (i = 0;i < G.Vexs;i++)
	{
		if (G.Vertex[i].date != Element)
		{
			G.Vertex[i].Dist = -1;
			G.Vertex[i].Path = 0;
		}
		else
		{
			G.Vertex[i].Dist = 0;
			G.Vertex[i].Path = 0;
			v = i;							//记录该节点的位次
		}
	}
	//将该节点入队
	Queue[rear++] = v;
	
	while(head!=rear)
	{
		//出队
		j = Queue[head++];
		node = G.Vertex[j].First_Edge;
		//printf("%d\n", j);
		while (node)
		{
			//处理与该节点相连的节点
			if (G.Vertex[node->iVex].Dist == -1)
			{
				G.Vertex[node->iVex].Dist = G.Vertex[j].Dist + 1;
				G.Vertex[node->iVex].Path = G.Vertex[j].date;
				Queue[rear++] = node->iVex;
			}
			node = node->Next_Edge;
		}
	}
	return &G;
}

//打印最短路
void Print_UnWeighted(Graph *G)
{
	int Top = -1, i,j, count = 1;
	VNode  node;
	char G_Stack[MaxSize];
	memset(G_Stack, 0, MaxSize);
	G_Stack[MaxSize-1] = '\0';
	for ( i = 0;i < G->Vexs;i++)
	{
		node = G->Vertex[i];
		G_Stack[++Top] = node.date;
		while (node.Path != 0)
		{
			for (j= 0;j < G->Vexs;j++)
			{
				if (G->Vertex[j].date == node.Path)
					break;
			}
			node = G->Vertex[j];
			++Top;
			count++;
			G_Stack[Top] = node.date;
		}
		printf("%c: ", G->Vertex[i]);
		for (int k = 0;k < count;k++)
		{
			printf("%c ", G_Stack[Top]);
			--Top;
		}
		Top = -1;
		count = 1;
		printf("\n");
	}
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
	Graph * PG=(Graph *)malloc(sizeof(Graph));
	/*创建一个图*/
	Create_Example_Graph(PG);
	/*打印邻接表*/
	Print_Graph(*PG);
	//以A为源节点的最短路径
	PG=UnWeighted(*PG,'A');
	//打印最短路径
	Print_UnWeighted(PG);
	
	
}
