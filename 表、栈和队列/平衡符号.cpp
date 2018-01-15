#include<stdio.h>
#include<stdlib.h>
#define Maxsize 20
#define Elementtype char

struct Stack
{
	Elementtype value[Maxsize];
	int Top;
};
struct Stack S;

bool IsEmpty(struct Stack *pStrL);//�ж϶�ջ�Ƿ�Ϊ��
void Push(struct Stack *pStrL,Elementtype sign);//ѹջ
Elementtype Pop(struct Stack *pStrL);//��ջ

bool IsEmpty(struct Stack *pStrL)
{
	if (pStrL->Top == -1)
		return true;
	else
		return false;
}
void Push(struct Stack *pStrL, Elementtype sign)
{
	pStrL->Top++;
	pStrL->value[pStrL->Top] = sign;
}
Elementtype Pop(struct Stack *pStrL)
{
	Elementtype temp;
	temp = pStrL->value[pStrL->Top];
	pStrL->Top--;
	return temp;
}
int main()
{
	S.Top = -1;
	struct Stack*p = &S;
	FILE *fp;
	char Filename[20];
	Elementtype Rtemp;
	printf("������Ҫ��ȡ���ļ�����\n");
	scanf("%s", Filename);
	if ((fp = fopen(Filename, "rb")) == NULL)
	{
		printf("�ļ���ʧ�ܣ�\n");
		exit(0);
	}
	Rtemp = fgetc(fp);
	while (Rtemp != EOF)
	{
		Elementtype temp;
		//printf("ok\n");
		//�ж��Ƿ�Ϊ����
		if ((Rtemp>= 65 && Rtemp <= 90) || (Rtemp >= 97 && Rtemp <= 122))
		{
			//printf("%c\n", Rtemp);
			Rtemp = fgetc(fp);
			continue;
		}
		else
		{
			if (Rtemp == '(' || Rtemp == '{' || Rtemp == '[')
			{
				Push(p, Rtemp);
				//printf("%c", Rtemp);
				Rtemp = fgetc(fp);
				continue;
			}
			else
			{
				if (IsEmpty(p))
				{
					printf("1�ļ��з��Ŵ���\n");
					return 0;
				}
				else
				{
					temp = Pop(p);
					if ((temp == '{'&&Rtemp == '}') || (temp == '('&&Rtemp == ')') || (temp == '['&&Rtemp == ']'))
					{
						Rtemp = fgetc(fp);
						continue;
					}
					else
					{
						printf("2�ļ��з��Ŵ���\n");
						return 0;
					}
				}
			}
		}
	}
	if (!IsEmpty(p))
	{
		printf("3�ļ��з��Ŵ���\n");
	}
	else
	{
		printf("�ļ�������ȷ��\n");
	}
	fclose(fp);
	return 0;
}