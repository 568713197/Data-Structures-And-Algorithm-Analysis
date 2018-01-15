#include<stdio.h>
#include<stdlib.h>
#define Maxsize 20
struct List
{
	int date[Maxsize];
	int length;
};
List * makeempty();//�������Ա�
List *initlist(List *PtrL);//��ʼ�����Ա�
int finddate(List *PtrL, int x);//Ѱ��ĳ���ݵ�һ�γ��ֵ�λ��
int search(List *PtrL, int pos);//Ѱ��ĳ��λ�õ�����
List *changedate(List *PtrL, int pos, int newdate);//��ĳλ�õ����ݸ���
List *insert(List *PtrL, int pos, int x);//����
List *add(List *PtrL, int x);//׷��
void delete_List(List *PtrL);//ɾ��List
List *delete_date(List *PtrL, int pos);//ɾ������
void showlist(List *PtrL);//��ʾ


List * makeempty()
{
	List *PtrL;
	PtrL = (List *)malloc(sizeof(List)*Maxsize);
	PtrL->length = 0;
	return PtrL;
}
List *initlist(List *PtrL)
{
	for (int i = 0;i < 10;i++)
	{
		PtrL->date[i] = i + 3;
		PtrL->length++;
	}
	return PtrL;
}
int finddate(List *PtrL, int x)
{
	for (int i = 0;i < PtrL->length;i++)
	{
		if (PtrL->date[i] == x)
			return i + 1;
	}
	return -1;
}
int search(List *PtrL, int pos)
{
	if (pos <= PtrL->length)
	{
		return PtrL->date[pos - 1];
	}
	else
		return -1;
}
List *changedate(List *PtrL, int pos, int newdate)
{
	if (pos <= PtrL->length)
	{
		PtrL->date[pos - 1] = newdate;
		return PtrL;
	}
	else
	{
		printf("λ�ô���\n");
		return PtrL;
	}
}
List *insert(List *PtrL, int pos, int x)
{
	int i;
	if (PtrL->length == Maxsize)
	{
		printf("�ռ�����\n");
		return PtrL;
	}
	if (pos > PtrL->length|| pos < 1)
	{
		printf("λ�ô���\n");
		return PtrL;
	}
	for ( i = PtrL->length - 1;i >= pos;i--)
	{
		PtrL->date[i + 1] = PtrL->date[i];
	}
	PtrL->date[i] = x;
	PtrL->length++;
	return PtrL;
}
List *add(List *PtrL, int x)
{
	if (PtrL->length == Maxsize)
	{
		printf("�ռ�����\n");
		return PtrL;
	}
	else
	{
		PtrL->date[PtrL->length] = x;
		PtrL->length++;
		return PtrL;
	}
}
void delete_List(List *PtrL)
{
	free(PtrL);
}
List *delete_date(List *PtrL, int pos)
{
	if (pos > PtrL->length - 1 || pos < 1)
	{
		printf("λ�ô���\n");
		return PtrL;
	}
	if(pos==PtrL->length)
	{
		PtrL->length--;
		return PtrL;
	}
	for (int i = pos ;i < PtrL->length;i++)
	{
		PtrL->date[i - 1] = PtrL->date[i];
	}
	PtrL->length--;
	return PtrL;
}
void showlist(List *PtrL)
{
	for (int i = 0;i <PtrL->length;i++)
	{
		printf("%3d", PtrL->date[i]);	
	}
	printf("\n");
}
int main()
{
	List *PtrL;
	int pos, date;
	PtrL = makeempty();
	initlist(PtrL);
	showlist(PtrL);
	//Ѱ��9���ֵ�λ��
	pos = finddate(PtrL, 9);
	printf("9���ֵ�λ�ã�%d\n",pos);
	//������λ�õ�����
	date = search(PtrL, 3);
	printf("������λ�õ����ݣ�%d\n", date);
	//�����ĸ�λ�õ����ݸ�Ϊ22
	changedate(PtrL, 4, 22);
	showlist(PtrL);
	//�ڵ����λ�ò���11
	insert(PtrL, 5, 11);
	showlist(PtrL);
	//��ĩβ׷��30
	add(PtrL, 30);
	showlist(PtrL);
	//ɾ����8������
	delete_date(PtrL, 8);
	showlist(PtrL);
	return 0;
}