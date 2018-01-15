#include<stdio.h>
#include<stdlib.h>
typedef struct Link Link;
struct Link
{
	int date;
	struct Link *Next;
};
Link *initlink();//��ʼ������
int finddate(Link *PtrL, int x);//�������ݵ�λ��
int search(Link *PtrL, int pos);//����ĳλ�õ�����
Link *insert(Link *PtrL, int pos, int newdate);//��������(����ԭposλ����֮ǰ)
Link *add(Link *PtrL, int newdate);//׷������
int countlist(Link *PtrL);//����
Link *delete_date(Link *PtrL, int pos);//ɾ������
void delete_link(Link *PtrL);//ɾ������
Link *changedate(Link *PtrL, int pos, int newdate);//�޸�����
void showlink(Link *PtrL);//��ʾ����

Link *initlink()
{
	Link *PtrL= (Link *)malloc(sizeof(Link));
	Link *p = PtrL;
	for (int i = 0;i < 5;i++)
	{
		PtrL->date = i + 2;
		PtrL->Next = (Link *)malloc(sizeof(Link));
		PtrL = PtrL->Next;
	}
	PtrL->Next = NULL;
	return p;
} 
int countlist(Link *PtrL)
{
	int index=0;
	while (PtrL->Next != NULL)
	{
		PtrL = PtrL->Next;
		index++;
	}
	return index;
}
int finddate(Link *PtrL, int x)
{
	int num = countlist(PtrL);
	int index=1;
	while (PtrL->Next != NULL&&PtrL->date != x)
	{
		PtrL = PtrL->Next;
		index++;
	}
	if (index == num)
		return 0;
	else
		return index;
}
int search(Link *PtrL, int pos)
{
	int index = 1;
	while (PtrL->Next != NULL&&index != pos)
	{
		PtrL = PtrL->Next;
		index++;
	}
	return PtrL->date;
}
Link *insert(Link *PtrL, int pos, int newdate)
{
	Link *temp = PtrL;
	if (pos == 1)
	{
		Link *temp = (Link *)malloc(sizeof(Link));
		temp->date = newdate;
		temp->Next = PtrL;
		return temp;
	}
	else if (pos > countlist(PtrL)||pos<1)
	{
		printf("λ�ô���!\n");
		return PtrL;
	}
	else
	{
		Link *p = (Link *)malloc(sizeof(Link));
		p->date = newdate;
		for (int i = 2;i < pos;i++)
		{
			PtrL = PtrL->Next;
		}
		p->Next = PtrL->Next;
		PtrL->Next = p;
		return temp;
	}
}
Link *add(Link *PtrL, int newdate)
{
	Link *pos = PtrL;
	while (PtrL->Next != NULL)
	{
		PtrL = PtrL->Next;
	}
	Link *p = (Link *)malloc(sizeof(Link));
	PtrL->Next = p;
	PtrL->date = newdate;
	p->Next = NULL;
	return pos;
}

Link *delete_date(Link *PtrL, int pos)
{
	Link *p = PtrL;
	int index = 1;
	if (pos == 1)
	{
		Link *temp = PtrL->Next;
		free(PtrL);
		return temp;
	}
	else
	{
		while (PtrL->Next != NULL&&index != pos - 1)
		{
			PtrL = PtrL->Next;
			index++;
		}
		Link *temp2 = PtrL->Next;//ָ��Ҫɾ���Ľڵ�
		Link *temp3 = temp2->Next;//��ȡҪɾ���Ľڵ���ָ�����һ���ڵ�
		PtrL->Next = temp3;
		free(temp2);
		return p;
	}
}
void delete_link(Link *PtrL)
{
	Link *p,*temp;
	p = PtrL;
	while (p->Next != NULL)
	{
		temp= p->Next;
		free(p);
		p = temp;
	}
}
Link *changedate(Link *PtrL, int pos, int newdate)
{
	Link *p = PtrL;
	int index = 1;
	if (pos > countlist(PtrL))
		printf("�����λ�ô���\n");
	while (PtrL->Next != NULL&&index != pos)
	{
		PtrL = PtrL->Next;
		index++;
	}
	PtrL->date = newdate;
	return p;
}
void showlink(Link *PtrL)
{
	while (PtrL->Next != NULL)
	{
		printf("%d  ", PtrL->date);
		PtrL = PtrL->Next;
	}
	printf("\n");
}
int main()
{
	Link *pLink;
	int pos,value,num;
	pLink=initlink();//��ʼ������
	//Ѱ��4��λ��
	pos = finddate(pLink, 4);
	printf("ԭʼ����\n");
	showlink(pLink);
	printf("����4�ڵ� %d ��\n", pos);
	//���ҵ�4λ�õ�����
	value = search(pLink, 4);
	printf("���ĸ�����Ϊ��%d\n", value);
	//���������
	num = countlist(pLink);
	printf("�����е����ݸ�����%d\n", num);
	//�ڵ���λ����9
	printf("�ڵ���λ����9������Ϊ��\n");
	pLink=insert(pLink, 3, 9);
	showlink(pLink);
	//��ĩβ׷��11
	printf("��ĩβ׷��11������Ϊ��\n");
	pLink=add(pLink, 11);
	showlink(pLink);
	//�ѵڶ�λ��Ϊ30
	printf("�ѵڶ�λ��Ϊ30������Ϊ��\n");
	pLink=changedate(pLink, 2, 30);
	showlink(pLink);
	//�ѵ���λɾ��
	printf("ɾ������λ��\n");
	pLink=delete_date(pLink, 4);
	showlink(pLink);
	return 0;
}