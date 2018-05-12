#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#define MaxSize 100
#define IsLetter(a)  ((((a)>='a')&&((a)<='z')) || (((a)>='A')&&((a)<='Z')))
#define LENGTH(a)  (sizeof(a)/sizeof(a[0]))

//�ڽӱ��ж�Ӧ����Ķ���
typedef struct _ENode
{
	int iVex;
	_ENode * Next_Edge;
}ENode;

//�ڽӱ��б�Ķ���
typedef struct _VNode
{
	char date;
	_ENode * First_Edge;
}VNode;

//�ڽӱ�
typedef struct _Graph
{
	int Vexs;
	int Edgs;
	VNode Vertex[MaxSize];
}Graph;

//�õ�ĳ���ڵ��λ�ã������ڷ��ؽڵ�λ�ã��������ڣ�����-1
static int Get_Position(Graph G, char Element)
{
	int i;
	for (i = 0;i < G.Vexs;i++)
		if (G.Vertex[i].date == Element)
			return i;
	return -1;
}

//����һ���ַ�
static char Read_Char()
{
	char ch;

	do
	{
		ch = getchar();
	} while (!IsLetter(ch));

	return ch;
}

//��node���ӵ�list��ĩβ
static void Link_Last(ENode *const List, ENode *node)
{
	ENode *p = List;
	if (p->Next_Edge)
		p = p->Next_Edge;
	p->Next_Edge = node;
}

//����һ��ͼ��ʾ����
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
	//Ϊͼ�����ڴ�ռ�
	if ((pG = (Graph *)malloc(sizeof(Graph))) == NULL)
		return NULL;
	memset(pG, 0, sizeof(Graph));
	//��ʼ�������Ͷ�����
	pG->Edgs = elen;
	pG->Vexs = vlen;
	//��ʼ������
	for (i = 0;i < pG->Vexs;i++)
	{
		pG->Vertex[i].date = vexs[i];
		pG->Vertex[i].First_Edge = NULL;
	}
	//��ʼ����
	for (i = 0;i < pG->Edgs;i++)
	{
		//��ȡ�ߵ���ʼ����ͽ�������
		c1 = edges[i][0];
		c2 = edges[i][1];

		p1 = Get_Position(*pG, c1);
		p2 = Get_Position(*pG, c2);
		//��ʼ��node1
		node1 = (ENode*)malloc(sizeof(ENode));
		node1->iVex = p2;
		node1->Next_Edge = NULL;				//ע��һ��Ҫ��ʼ��ΪNULL

		if (pG->Vertex[p1].First_Edge == NULL)
			pG->Vertex[p1].First_Edge = node1;
		else
			Link_Last(pG->Vertex[p1].First_Edge, node1);
		/*���������ͼ���ڽӱ�ʵ��Ψһ��Ҫ���ĵĵط�*/
		////��ʼ��node2
		//node2 = (ENode*)malloc(sizeof(ENode));
		//node2->iVex = p1;
		//node2->Next_Edge = NULL;				//ע��һ��Ҫ��ʼ��ΪNULL

		//if (pG->Vertex[p2].First_Edge == NULL)
		//	pG->Vertex[p2].First_Edge = node2;
		//else
		//	Link_Last(pG->Vertex[p2].First_Edge, node2);
	}
	return pG;
}

//������ȱ���ͼ�ĵݹ�ʵ��
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
	int Visited[MaxSize];						//������ʱ��
												//��ʼ�����ʱ��
	for (i = 0;i < G.Vexs;i++)
	{
		Visited[i] = 0;
	}
	//������ȱ���
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
	//��ʼ�����ʱ��
	for (i = 0;i < G.Vexs;i++)
	{
		Visited[i] = 0;
	}
	printf("BFS: ");
	//������ȱ���
	for (i = 0;i < G.Vexs;i++)
	{
		if (Visited[i] == 0)
		{
			Visited[i] = 1;
			printf("%c ", G.Vertex[i].date);
			Queue[rear++] = i;							//�����
		}
		while (head != rear)
		{
			j = Queue[head++];							//������
			node = G.Vertex[j].First_Edge;
			while (node != NULL)
			{
				k = node->iVex;
				if (Visited[k] == 0)
				{
					Visited[k] = 1;
					printf("%c ", G.Vertex[k].date);
					Queue[rear++] = k;					//�����
				}
				node = node->Next_Edge;
			}
		}
	}
	printf("\n");
}

//��ӡ�ڽӱ�
void Print_Graph(Graph G)
{
	int i, j;
	ENode * node;
	//��ʼ��ӡ
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
	/*����һ��ͼ*/
	PG = Create_Example_Graph();
	/*��ӡ�ڽӱ�*/
	Print_Graph(*PG);
	/*�����������*/
	DFSTraveling(*PG);
	/*�����������*/
	BFSTraveling(*PG);
}