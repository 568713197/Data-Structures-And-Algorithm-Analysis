#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
struct node
{
	int x, y;
}p[110];
int vis[110];
int flag = 0;
int n, m;
int keyi(int x)//如果可以成功到达岸边
{
	if ((p[x].x - m <= -50) || (p[x].x + m >= 50) || (p[x].y - m <= -50) || (p[x].y + m >= 50))
		return 1;
	return 0;
}
int first(int x)//第一步
{
	int p1 = pow(p[x].x, 2);
	int p2 = pow(p[x].y, 2);
	int r = (m + 7.5)*(m + 7.5);
	if (p1 + p2 <= r)
		return 1;
	return 0;
}
int jump(int x, int y)//能否从一个鳄鱼头跳到另一个鳄鱼头
{
	int p1 = pow(p[x].x - p[y].x, 2);
	int p2 = pow(p[x].y - p[y].y, 2);
	int r = m*m;
	if (p1 + p2 <= r)
		return 1;
	return 0;
}
int dfs(int t)
{
	vis[t] = 1;
	if (keyi(t) == 1)
	{
		flag = 1;
	}
	for (int i = 0;i<n;i++)
	{
		if (!vis[i] && jump(t, i))
		{
			flag = dfs(i);
			//            if(flag == 1)
			//                break;
		}
	}
	return flag;
}
int main()
{
	memset(vis, 0, sizeof(vis));
	scanf("%d %d", &n, &m);
	int i;
	for (i = 0;i<n;i++)
	{
		scanf("%d %d", &p[i].x, &p[i].y);
	}
	if (m >= 42.5)
	{
		printf("Yes\n");
	}
	else
	{
		for (i = 0;i<n;i++)
		{
			if (!vis[i] && first(i))
			{
				dfs(i);
			}
		}
		if (flag == 1)
			printf("Yes\n");
		else
			printf("No\n");
	}
	return 0;
}