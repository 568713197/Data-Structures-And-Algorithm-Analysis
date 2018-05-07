//����ԭ��
//��ʮ̨����{1,2,3....9,10},��֪���е����Ѿ�ʵ��������
//1-2  2-4  3-5  4-7  5-8  6-9  6-10


/*���鼯��غ���ʵ��*/

#include <stdio.h>
#define ElementType int
#define MaxSize 10

typedef struct
{
	ElementType Date;
	int Parent;
}SetType;

SetType U_F[MaxSize];   //����һ���ṹ������

void Init(SetType *Pstr);  //��ʼ��
int Find(SetType *Pstr, ElementType x);  //����Ԫ�صĸ��ڵ�  ���ظ��ڵ���±�
void Union(SetType *Pstr, ElementType element1, ElementType element2);  //�����Ϻϲ�
void Union_Better(SetType *Pstr, ElementType element1, ElementType element2);//�Ż���ĺϲ��㷨


/*��ʼ��*/
/*�ֱ�ֵ0-MaxSize�����ڵ㶼��Ϊ-1*/
void Init(SetType *Pstr)
{
	for (int i = 1;i <= MaxSize;i++)
	{
		Pstr->Date = i;
		Pstr->Parent = -1;
		Pstr++;
	}
}
/*����*/
/*����ĳ�����ݵĸ��ڵ�*/
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
/*������*/
/*�ҵ��������ݵĸ��ڵ㣬����ͬ�����ô�������ͬ��������1�ĸ��ڵ���Ϊ����2�ĸ��ڵ�*/
/*ȱ�㣺�������󣬶�β�������ʹ���ĸ߶ȹ��ߣ�Find������ʱ�临�ӶȻ����*/
void Union(SetType *Pstr, ElementType element1, ElementType element2)
{
	int Root1, Root2;
	Root1 = Find(Pstr, element1);
	Root2 = Find(Pstr,element2);
	if (Root1 != Root2)
		U_F[Root2].Parent = Root1;
}
/*�Ż���Ĳ������㷨�����ڵ��Parent�ľ���ֵ����������ڵ�����ͬ�Լ����м����ڵ㣬ÿ�β�����ʱ���ж������󲢵ĸ��ڵ�
��Parent����ֵ˭�Ĵ󣬰ѽڵ��ٵĹ��ص��ڵ����ϣ��Ȱ��ٵ��Ǹ����ڵ������ȥ���ٱ�������������Ϊ���ڵ�Ľڵ������ȥ
���������Ա�֤ÿ���ڵ㶼ֱ������ڵ��������������Žڵ������ʹFind�ĺ�����ʱ�临�Ӷ�̫��*/
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
	//��ʼ��
	Init(U_F);
	Union_Better(U_F, 1, 2);
	Union_Better(U_F, 2, 4);
	Union_Better(U_F, 3, 5);
	Union_Better(U_F, 4, 7);
	Union_Better(U_F, 5, 8);
	Union_Better(U_F, 6, 9);
	Union_Better(U_F, 6, 10);
	/*��ӡ���ϵ����*/
	for (int i = 0;i < MaxSize;i++)
	{
		printf("NO.%d  Date:%d   Parent:%d\n", i, U_F[i].Date, U_F[i].Parent);
	}
	/*�������ڵ㲢����*/
	Union_Better(U_F, 1, 3);
	printf("***************************************************************\n");
	/*��ӡ���ϵ����*/
	for (int i = 0;i < MaxSize;i++)
	{
		printf("NO.%d  Date:%d   Parent:%d\n", i, U_F[i].Date, U_F[i].Parent);
	}
	return 0;
}
//���������
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