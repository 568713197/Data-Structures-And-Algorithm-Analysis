#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MaxSize 100
#define IsLetter(a) ((((a)>='a')&&((a)<='z'))||(((a)>='A')&&((a)<='Z')))
#define Length(a) (sizeof(a)/sizeof(a[0]))

typedef struct _graph
{
	char Vertex[MaxSize];				//节点数组
	int Vexs;							//节点数    
	int Edgs;							//边数
	int matrix[MaxSize][MaxSize];		//邻接矩阵
}Graph;

//得到某个节点的位置，若存在返回节点位置，若不存在，返回-1
static int Get_Position(Graph Onegraph, char Element)
{
	int i;
	for (i = 0;i < Onegraph.Vexs;i++)
		if (Element == Onegraph.Vertex[i])
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

//创建一个图（示例）
Graph *Creat_Example_Graph()
{
	char vexs[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G' };	//节点
	char edges[][2] = {
		{ 'A', 'B' },
		{ 'B', 'C' },
		{ 'B', 'E' },
		{ 'B', 'F' },
		{ 'C', 'E' },
		{ 'D', 'C' },
		{ 'E', 'B' },
		{ 'E', 'D' },
		{ 'F', 'G' } };									//边
	int vex = Length(vexs);									//节点数
	int edg = Length(edges);								//边数
	int i, p1, p2;
	Graph *PG;
	if ((PG = (Graph*)malloc(sizeof(Graph))) == NULL)		//为结构体分配内存空间
		return NULL;
	memset(PG, 0, sizeof(Graph));							//全部初始化为0
															//读入边和节点数
	PG->Edgs = edg;
	PG->Vexs = vex;
	//读入节点
	for (i = 0;i < vex;i++)
	{
		PG->Vertex[i] = vexs[i];
	}
	//读入边
	for (i = 0;i < edg;i++)
	{
		p1 = Get_Position(*PG, edges[i][0]);
		p2 = Get_Position(*PG, edges[i][1]);

		PG->matrix[p1][p2] = 1;
		//PG->matrix[p2][p1] = 1;							//相对于无向图的邻接矩阵实现唯一需要修改的地方
	}

	return PG;

}

//返回顶点v的第一个邻接顶点的索引，失败则返回-1
static int First_Vertex(Graph *PG, char v)
{
	int i;
	if (v<0 || v>PG->Vexs - 1)
		return -1;
	for (i = 0;i < PG->Vexs;i++)
		if (PG->matrix[v][i] == 1)
			return i;
	return -1;
}

//返回顶点v相对于w的下一个邻接顶点的索引，失败则返回-1
static int Next_Vertex(Graph *PG, char v, int w)
{
	int i;
	if (v<0 || v>PG->Vexs - 1 || w<0 || w>PG->Vexs - 1)
		return -1;
	for (i = w + 1;i < PG->Vexs;i++)
		if (PG->matrix[v][i] == 1)
			return i;
	return -1;
}

//深度优先搜索遍历图的递归实现
static void DFS(Graph G, int i, int *Visited)
{
	int w;
	Visited[i] = 1;
	printf("%c ", G.Vertex[i]);
	//遍历该节点的所有相邻节点，若是没访问过的，访问下去
	for (w = First_Vertex(&G, i);w >= 0;w = Next_Vertex(&G, i, w))
	{
		if (!Visited[w])
			DFS(G, w, Visited);
	}
}

//DFS深度优先搜索
void DFSTraverse(Graph G)
{
	int i;
	int Visited[MaxSize];
	//初始化Visited
	for (i = 0;i < G.Vexs;i++)
		Visited[i] = 0;
	printf("DFS: ");
	for (i = 0;i < G.Vexs;i++)						//作用是遍历所有的子图
	{
		//如果没有被遍历过
		if (Visited[i] == 0)
			DFS(G, i, Visited);
	}
	printf("\n");
}

//BFS广度优先搜索
void BFSTraverse(Graph G)
{
	int head = 0;
	int rear = 0;
	int Visited[MaxSize];
	int Queue[MaxSize];									//定义一个队列
	int i, j, k;
	//初始化Visited
	for (i = 0;i < G.Vexs;i++)
		Visited[i] = 0;
	printf("BFS: ");
	//BFS遍历
	for (i = 0;i < G.Vexs;i++)							//作用是遍历所有的子图
	{
		if (!Visited[i])								//如果没有被遍历 入队
		{
			Visited[i] = 1;
			printf("%c ", G.Vertex[i]);
			Queue[rear++] = i;
		}
		while (head != rear)								//当队列中有元素时
		{
			j = Queue[head++];							// 出队列
			for (k = First_Vertex(&G, j);k >= 0;k = Next_Vertex(&G, j, k))//k是为访问的邻接顶点
			{
				if (!Visited[k])
				{
					Visited[k] = 1;
					printf("%c ", G.Vertex[k]);
					Queue[rear++] = k;
				}
			}
		}
	}
	printf("\n");
}

//打印邻接矩阵图
void Print_Matrix(Graph G)
{
	int i, j;
	printf("Graph Matrix: \n");

	for (i = 0;i < G.Vexs;i++)
	{
		for (j = 0;j < G.Vexs;j++)
			printf("%d ", G.matrix[i][j]);
		printf("\n");
	}
}

int main()
{
	Graph *G;
	//创建一个图
	G = Creat_Example_Graph();
	//打印邻接矩阵
	Print_Matrix(*G);
	//DFS
	DFSTraverse(*G);
	//BFS
	BFSTraverse(*G);

}