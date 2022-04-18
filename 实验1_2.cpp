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
Status InsertLinkList(LinkList &l,ElemType e);//在头结点的后面插入元素 e
Status CreateLinkList(LinkList &l,int n);//创建具有n个结点的链表 
void PrintLinkList(LinkList &l);//输出所有结点
void swap(pLNode &p1,pLNode &p2);//p1和p2指向的结点进行交换,此处通过交换其二者的data域实行交换，实际并未真正更改其指针域 
Status SortLinkList(LinkList &l);
Status FindLinkList(LinkList &l,int i,ElemType &e);//在链表中查找第i个元素，i合法返回元素值，否则，返回Failed
Status FindLinkList2(LinkList &l,int &i, ElemType e);//在链表中查找与一已知字符相同的第一个结点，有则返回Succed，否则，返回Failed
Status DelLinkList(LinkList &l,int i,ElemType &e);//在链表中删除第i个结点
int GetLinkListLength(LinkList &l);
Status InsertOrderLinkList(LinkList &l,ElemType e);//在链表中按照有序方式插入元素 
int main()
{
	int cnt,loc;
	ElemType temp;
	LinkList list;
	InitLinkList(list);
	printf("请输入元素的个数：");
	scanf("%d",&cnt); 
	getchar();
	CreateLinkList(list,cnt);
	PrintLinkList(list);
	SortLinkList(list);
	printf("\n排序后：\n");
	PrintLinkList(list);
	printf("\n请输入要查找的位置：\n");
	scanf("%d",&loc);
	if(FindLinkList(list,loc,temp)==Failed)
	{
		printf("查找失败!\n");
	}
	else
	{
		printf("查找到的元素为：%c\n",temp);
	}
	getchar();//清空键盘缓冲区 
	printf("请输入要查找的元素：\n");
	scanf("%c",&temp);
	if(FindLinkList2(list,loc,temp)==Succeed)
	{
		printf("您要查找的元素为链表中的第%d个元素！\n",loc);
	}
	else
	{
		printf("您要查找的元素不在链表中！\n");		
	}
	printf("\n请输入要顺序插入的元素：\n");
	getchar(); 
	temp=getchar();
	if(InsertOrderLinkList(list,temp)==Succeed)
	{
		printf("插入新元素后的链表如下：\n");
		PrintLinkList(list);
	}
	printf("\n请输入要删除的位置：\n");
	scanf("%d",&loc);
	if(DelLinkList(list,loc,temp)==Succeed)
	{
		printf("删除的元素为：%c！\n删除后的链表为:\n",temp);
		PrintLinkList(list);
		
	}
	 printf("当前链表的长度为：%d",GetLinkListLength(list));
	return 0;
}
Status InitLinkList(LinkList &l)
{
	l.head.data='#';//为便于调试观察，将头结点数据域填为#
	l.head.next=&(l.head); 
	return Succeed;
}
Status InsertLinkList(LinkList &l,ElemType e)
{
	pLNode p=(pLNode)malloc(sizeof(LNode));
	if(!p) return Failed;
	p->data=e;
	p->next=l.head.next;//把第一个元素放在刚插入元素的后面
	l.head.next=p; 
	return Succeed;
}
Status CreateLinkList(LinkList &l,int n)
{
	int i;
	char temp;
	printf("请连续输入%d个元素：\n",n);
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
{//此处由于涉及到通过比较头指针判断循环结束，所以参数必须用引用类型，特别容易忽略 
	int i=1;
	LNode *pHead;
	pHead=&(l.head);
	LNode *pTemp=pHead->next;
	printf("链表所有元素如下：\n");
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
	pTemp=pHead->next;//已经指向第一个 
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
	return Failed;//i的位置不合法	
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
{//	此处要求l为有序链表 
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