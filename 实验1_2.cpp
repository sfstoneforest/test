#include <stdio.h>
#include <stdlib.h>
typedef char ElemType;
enum Status{
	Failed,
	Succeed,
	error
};
typedef struct LNode{
	ElemType data;
	struct LNode *next;
}LNode,*pLNode;
typedef struct LinkList{
	LNode head;
}LinkList;
Status InitLinkList(LinkList &l);
Status InsertLinkList(LinkList &l,ElemType e);//��ͷ���ĺ������Ԫ�� e
Status CreateLinkList(LinkList &l,int n);//��������n���������� 
void PrintLinkList(LinkList &l);//������н��
void swap(pLNode &p1,pLNode &p2);//p1��p2ָ��Ľ����н���,�˴�ͨ����������ߵ�data��ʵ�н�����ʵ�ʲ�δ����������ָ���� 
Status SortLinkList(LinkList &l);
Status FindLinkList(LinkList &l,int i,ElemType &e);//�������в��ҵ�i��Ԫ�أ�i�Ϸ�����Ԫ��ֵ�����򣬷���Failed
Status FindLinkList2(LinkList &l,int &i, ElemType e);//�������в�����һ��֪�ַ���ͬ�ĵ�һ����㣬���򷵻�Succed�����򣬷���Failed
Status DelLinkList(LinkList &l,int i,ElemType &e);//��������ɾ����i�����
int GetLinkListLength(LinkList &l);
Status InsertOrderLinkList(LinkList &l,ElemType e);//�������а�������ʽ����Ԫ�� 
int main()
{
	int cnt,loc;
	ElemType temp;
	LinkList list;
	InitLinkList(list);
	printf("������Ԫ�صĸ�����");
	scanf("%d",&cnt); 
	getchar();
	CreateLinkList(list,cnt);
	PrintLinkList(list);
	SortLinkList(list);
	printf("\n�����\n");
	PrintLinkList(list);
	printf("\n������Ҫ���ҵ�λ�ã�\n");
	scanf("%d",&loc);
	if(FindLinkList(list,loc,temp)==Failed)
	{
		printf("����ʧ��!\n");
	}
	else
	{
		printf("���ҵ���Ԫ��Ϊ��%c\n",temp);
	}
	getchar();//��ռ��̻����� 
	printf("������Ҫ���ҵ�Ԫ�أ�\n");
	scanf("%c",&temp);
	if(FindLinkList2(list,loc,temp)==Succeed)
	{
		printf("��Ҫ���ҵ�Ԫ��Ϊ�����еĵ�%d��Ԫ�أ�\n",loc);
	}
	else
	{
		printf("��Ҫ���ҵ�Ԫ�ز��������У�\n");		
	}
	printf("\n������Ҫ˳������Ԫ�أ�\n");
	getchar(); 
	temp=getchar();
	if(InsertOrderLinkList(list,temp)==Succeed)
	{
		printf("������Ԫ�غ���������£�\n");
		PrintLinkList(list);
	}
	printf("\n������Ҫɾ����λ�ã�\n");
	scanf("%d",&loc);
	if(DelLinkList(list,loc,temp)==Succeed)
	{
		printf("ɾ����Ԫ��Ϊ��%c��\nɾ���������Ϊ:\n",temp);
		PrintLinkList(list);
		
	}
	 printf("��ǰ����ĳ���Ϊ��%d",GetLinkListLength(list));
	return 0;
}
Status InitLinkList(LinkList &l)
{
	l.head.data='#';//Ϊ���ڵ��Թ۲죬��ͷ�����������Ϊ#
	l.head.next=&(l.head); 
	return Succeed;
}
Status InsertLinkList(LinkList &l,ElemType e)
{
	pLNode p=(pLNode)malloc(sizeof(LNode));
	if(!p) return Failed;
	p->data=e;
	p->next=l.head.next;//�ѵ�һ��Ԫ�ط��ڸղ���Ԫ�صĺ���
	l.head.next=p; 
	return Succeed;
}
Status CreateLinkList(LinkList &l,int n)
{
	int i;
	char temp;
	printf("����������%d��Ԫ�أ�\n",n);
	for(i=1;i<=n;i++)
	{
		//scanf("%c",&temp);
		temp=getchar();
		if(InsertLinkList(l,temp)==Failed)
		{
			return Failed;
		}
	}
	return Succeed;
}
void PrintLinkList(LinkList &l)
{//�˴������漰��ͨ���Ƚ�ͷָ���ж�ѭ�����������Բ����������������ͣ��ر����׺��� 
	int i=1;
	LNode *pHead;
	pHead=&(l.head);
	LNode *pTemp=pHead->next;
	printf("��������Ԫ�����£�\n");
	while(pTemp!=pHead)
	{
		printf("node %d:%c\t",i,pTemp->data);
		i++;
		pTemp=pTemp->next;
	}
}
void swap(pLNode &p1,pLNode &p2)
{
	ElemType temp;
	temp=p1->data;
	p1->data=p2->data;
	p2->data=temp;
}
Status SortLinkList(LinkList &l)
{
	pLNode pHead,pTemp,p1,p2;
	pHead=&(l.head);
	pTemp=pHead->next;
	while(pTemp!=pHead)
	{
		p1=pTemp->next;
		while(p1!=pHead)
		{
			if(pTemp->data > p1->data)
			{
				swap(pTemp,p1);
			}
			p1=p1->next;
		}
		pTemp=pTemp->next;
	}
}
Status FindLinkList(LinkList &l,int i,ElemType &e)
{
	pLNode pHead,pTemp;
	pHead=&(l.head);
	pTemp=pHead->next;
	int j=1;
	while(pTemp!=pHead)
	{
		if(j<i)
		{
			j++;
			pTemp=pTemp->next;
		}
		if(j==i)
		{
			e=pTemp->data;
			return Succeed;
		}		
	}
	return Failed;
}
Status FindLinkList2(LinkList &l,int &i, ElemType e)
{
	pLNode pHead,pTemp;
	pHead=&(l.head);
	pTemp=pHead->next;
	int j=1;
	while(pTemp!=pHead)
	{
		if(e==pTemp->data)
		{
			i=j;
			return Succeed;
		}
		else
		{
			pTemp=pTemp->next;
			j++;
		}		
	}
	return Failed;	
}
Status DelLinkList(LinkList &l,int i,ElemType &e)
{
	pLNode pHead,pTemp,q;
	pHead=&(l.head);
	pTemp=pHead->next;//�Ѿ�ָ���һ�� 
	int j=1;
	if(i<1) return Failed;
	q=pHead; 
	while(pTemp!=pHead)
	{
		if(j<i)
		{
			j++;
			q=pTemp;
			pTemp=pTemp->next;
		}
		else if(j==i)
		{
			e=pTemp->data;
			q->next=pTemp->next;
			free(pTemp);		
			return Succeed;
		}		
	}
	return Failed;//i��λ�ò��Ϸ�	
}
int GetLinkListLength(LinkList &l)
{
	pLNode pHead,pTemp;
	pHead=&(l.head);
	pTemp=pHead->next;
	int j=0;
	while(pTemp!=pHead)
	{
		j++;
		pTemp=pTemp->next;		
	}
	return j;//	
}
Status InsertOrderLinkList(LinkList &l,ElemType e)
{//	�˴�Ҫ��lΪ�������� 
	pLNode pHead,pTemp,p;
	pHead=&(l.head);
	pTemp=pHead->next;
	p=(pLNode)malloc(sizeof(LNode));
	if(!p) return Failed;
	while(pTemp!=pHead)
	{
		if(pTemp->data < e && pTemp->next!=pHead)
		{
			pTemp=pTemp->next;			
		}
		else if(pTemp->next!=pHead)
		{
			p->data=pTemp->data;
			pTemp->data=e;
			return Succeed;
		}
		else
		{
			p->data=e;
			p->next=pTemp->next;
			pTemp->next=p;
			return Succeed;
		}		
	}
	return Succeed;//		
}