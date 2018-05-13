#include <stdio.h>
#include <stdlib.h>
#define MaxSize 10001

int men[MaxSize][MaxSize];								//�ڽӾ���
int  Edges;float Mennum;								//����������
int Visited[MaxSize];									//���ʱ��
int Queue[MaxSize];										//����
int tail;
float BFS(int Verx)
{
	//��ʼ�����ʱ������
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
			 if ((k!=0)&&(!Visited[i]))					//������j������ÿһ��δ�����ʵĽڵ�
			 {
					 Visited[i] = 1;
					 Queue[rear++] = i;
					 count++;
					 tail = i;		
			 }
		 }
		 //�����������к�������һȦ
			if (j == last)
				{
					level++;
					last = tail;
				}
		//���������ȿռ������
			if (level == 6)
					break;	
	}
	//���ؼ���ֵ
	return count;
}
int main()
{
	//����
	scanf("%f %d", &Mennum, &Edges);
	for (int i = 0;i < Edges;i++)
	{
		int j, k;
		scanf("%d %d", &j, &k);
		men[j-1][k-1] = 1;
		men[k-1][j-1] = 1;
	}
	//����ÿһ���ڵ�ı���
	for (int i = 0;i < Mennum;i++)
	{
		float count = BFS(i);
		float rate= count / Mennum;
		printf("%d: %.2f%%c\n", i + 1, rate *100,'%');
	}
}