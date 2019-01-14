//��Ȩͼʹ���ڽӱ�ʵ��
//����ȨͼΪ����ͼ
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
	int Dist;                                    //����
	char Path;									 //���Ǳ��� ��������·��
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
	//Ϊͼ�����ڴ�ռ�
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
}


//��Ȩͼ���·��
Graph * UnWeighted(Graph G,char Element)
{
	int i, j, v;
	int Queue[MaxSize];
	ENode *node;
	int head = 0;
	int rear = 0;
	//��ʼ��
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
			v = i;							//��¼�ýڵ��λ��
		}
	}
	//���ýڵ����
	Queue[rear++] = v;
	
	while(head!=rear)
	{
		//����
		j = Queue[head++];
		node = G.Vertex[j].First_Edge;
		//printf("%d\n", j);
		while (node)
		{
			//������ýڵ������Ľڵ�
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

//��ӡ���·
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
	Graph * PG=(Graph *)malloc(sizeof(Graph));
	/*����һ��ͼ*/
	Create_Example_Graph(PG);
	/*��ӡ�ڽӱ�*/
	Print_Graph(*PG);
	//��AΪԴ�ڵ�����·��
	PG=UnWeighted(*PG,'A');
	//��ӡ���·��
	Print_UnWeighted(PG);
	
	
}
