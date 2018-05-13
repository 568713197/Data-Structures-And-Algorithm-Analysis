#include <stdio.h>
#include <stdlib.h>
#define MaxSize 10001

int men[MaxSize][MaxSize];								//邻接矩阵
int  Edges;float Mennum;								//边数和人数
int Visited[MaxSize];									//访问标记
int Queue[MaxSize];										//队列
int tail;
float BFS(int Verx)
{
	//初始化访问标记数组
	for (int i = 0;i < Mennum;i++)
		Visited[i] = 0;
	int head = 0;
	int rear = 0;
	int i, j,k,count=1,level=0,last=Verx;
	Visited[Verx] = 1;
	Queue[rear++] = Verx;
	while (head != rear)
	{
		 j=Queue[head++];
		 for (i = 0;i < Mennum;i++)
		 {
			 k = men[j][i];
			 if ((k!=0)&&(!Visited[i]))					//访问与j相连的每一个未被访问的节点
			 {
					 Visited[i] = 1;
					 Queue[rear++] = i;
					 count++;
					 tail = i;		
			 }
		 }
		 //当访问完所有后移向下一圈
			if (j == last)
				{
					level++;
					last = tail;
				}
		//访问完六度空间后跳出
			if (level == 6)
					break;	
	}
	//返回计数值
	return count;
}
int main()
{
	//输入
	scanf("%f %d", &Mennum, &Edges);
	for (int i = 0;i < Edges;i++)
	{
		int j, k;
		scanf("%d %d", &j, &k);
		men[j-1][k-1] = 1;
		men[k-1][j-1] = 1;
	}
	//计算每一个节点的比率
	for (int i = 0;i < Mennum;i++)
	{
		float count = BFS(i);
		float rate= count / Mennum;
		printf("%d: %.2f%%c\n", i + 1, rate *100,'%');
	}
}