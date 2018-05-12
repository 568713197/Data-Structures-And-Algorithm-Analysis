#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MaxSize 100
#define IsLetter(a) ((((a)>='a')&&((a)<='z'))||(((a)>='A')&&((a)<='Z')))
#define Length(a) (sizeof(a)/sizeof(a[0]))

typedef struct _graph
{
	char Vertex[MaxSize];				//�ڵ�����
	int Vexs;							//�ڵ���    
	int Edgs;							//����
	int matrix[MaxSize][MaxSize];		//�ڽӾ���
}Graph;

//�õ�ĳ���ڵ��λ�ã������ڷ��ؽڵ�λ�ã��������ڣ�����-1
static int Get_Position(Graph Onegraph, char Element)
{
	int i;
	for (i = 0;i < Onegraph.Vexs;i++)
		if (Element == Onegraph.Vertex[i])
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

//����һ��ͼ��ʾ����
Graph *Creat_Example_Graph()
{
	char vexs[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G' };	//�ڵ�
	char edges[][2] = {
		{ 'A', 'B' },
		{ 'B', 'C' },
		{ 'B', 'E' },
		{ 'B', 'F' },
		{ 'C', 'E' },
		{ 'D', 'C' },
		{ 'E', 'B' },
		{ 'E', 'D' },
		{ 'F', 'G' } };									//��
	int vex = Length(vexs);									//�ڵ���
	int edg = Length(edges);								//����
	int i, p1, p2;
	Graph *PG;
	if ((PG = (Graph*)malloc(sizeof(Graph))) == NULL)		//Ϊ�ṹ������ڴ�ռ�
		return NULL;
	memset(PG, 0, sizeof(Graph));							//ȫ����ʼ��Ϊ0
															//����ߺͽڵ���
	PG->Edgs = edg;
	PG->Vexs = vex;
	//����ڵ�
	for (i = 0;i < vex;i++)
	{
		PG->Vertex[i] = vexs[i];
	}
	//�����
	for (i = 0;i < edg;i++)
	{
		p1 = Get_Position(*PG, edges[i][0]);
		p2 = Get_Position(*PG, edges[i][1]);

		PG->matrix[p1][p2] = 1;
		//PG->matrix[p2][p1] = 1;							//���������ͼ���ڽӾ���ʵ��Ψһ��Ҫ�޸ĵĵط�
	}

	return PG;

}

//���ض���v�ĵ�һ���ڽӶ����������ʧ���򷵻�-1
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

//���ض���v�����w����һ���ڽӶ����������ʧ���򷵻�-1
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

//���������������ͼ�ĵݹ�ʵ��
static void DFS(Graph G, int i, int *Visited)
{
	int w;
	Visited[i] = 1;
	printf("%c ", G.Vertex[i]);
	//�����ýڵ���������ڽڵ㣬����û���ʹ��ģ�������ȥ
	for (w = First_Vertex(&G, i);w >= 0;w = Next_Vertex(&G, i, w))
	{
		if (!Visited[w])
			DFS(G, w, Visited);
	}
}

//DFS�����������
void DFSTraverse(Graph G)
{
	int i;
	int Visited[MaxSize];
	//��ʼ��Visited
	for (i = 0;i < G.Vexs;i++)
		Visited[i] = 0;
	printf("DFS: ");
	for (i = 0;i < G.Vexs;i++)						//�����Ǳ������е���ͼ
	{
		//���û�б�������
		if (Visited[i] == 0)
			DFS(G, i, Visited);
	}
	printf("\n");
}

//BFS�����������
void BFSTraverse(Graph G)
{
	int head = 0;
	int rear = 0;
	int Visited[MaxSize];
	int Queue[MaxSize];									//����һ������
	int i, j, k;
	//��ʼ��Visited
	for (i = 0;i < G.Vexs;i++)
		Visited[i] = 0;
	printf("BFS: ");
	//BFS����
	for (i = 0;i < G.Vexs;i++)							//�����Ǳ������е���ͼ
	{
		if (!Visited[i])								//���û�б����� ���
		{
			Visited[i] = 1;
			printf("%c ", G.Vertex[i]);
			Queue[rear++] = i;
		}
		while (head != rear)								//����������Ԫ��ʱ
		{
			j = Queue[head++];							// ������
			for (k = First_Vertex(&G, j);k >= 0;k = Next_Vertex(&G, j, k))//k��Ϊ���ʵ��ڽӶ���
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

//��ӡ�ڽӾ���ͼ
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
	//����һ��ͼ
	G = Creat_Example_Graph();
	//��ӡ�ڽӾ���
	Print_Matrix(*G);
	//DFS
	DFSTraverse(*G);
	//BFS
	BFSTraverse(*G);

}