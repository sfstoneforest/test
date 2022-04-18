#include <stdio.h>
#include <stdlib.h>
#define SQLIST_INIT_SIZE 50
#define SQLIST_INCREMENT 10
enum Status{
	Failed,
	Succeed,
	error
};
typedef int ElemType ;
typedef struct Sqlist{
	ElemType *base;		//顺序表的基址 
	int		  len;		//顺序表当前长度 
	int 	  listSize;	//顺序表存储容量 
}Sqlist;
Status InitSqList(Sqlist &l);//构造一个空的顺序表l
Status InsertSqList(Sqlist &l,int i,ElemType e);//在顺序表l中的第i个位置之前插入新的元素e 
Status DelSqlist(Sqlist &l,int i,ElemType &e);//删除顺序表l中的第i个位置的元素，并将其值返回给e
void PrintSqlist(Sqlist l);
int SqlistFind(Sqlist l,ElemType e );//查找失败返回-1，否则返回所在位置+1 
int SqlistSum(Sqlist l);
ElemType SqlistGetElem(Sqlist l,int i);//i从1开始计数 
int main()
{
	int cnt,i,temp,loc;
	Sqlist l;
	InitSqList(l);
	printf("请输入线性表元素的个数：\n");
	scanf("%d",&cnt);
	printf("请输入%d个元素",cnt);
	for(i=0;i<cnt;i++)
	{
		scanf("%d",&temp);
		InsertSqList(l,i+1,temp);
	}
	PrintSqlist(l);
	printf("请输入要获取元素的位置：\n");	
	scanf("%d",&temp);	
	printf("顺序表中第%d个元素为：%d\n",temp,SqlistGetElem(l,temp));
	printf("请输入要插入元素的位置：\n");	
	scanf("%d",&loc);
	printf("请输入要插入的元素：\n");	
	scanf("%d",&temp);	
	InsertSqList(l,loc,temp);
	printf("插入元素后的顺序表：\n");
	PrintSqlist(l);
	printf("请输入要删除元素的位置：\n");	
	scanf("%d",&loc);
	DelSqlist(l,loc,temp);
	printf("删除的元素为：%d\n",temp);
	printf("删除元素后的顺序表：\n");
	PrintSqlist(l);
	printf("顺序表中所有元素之和为：%d\n",SqlistSum(l));		 
	return 0;
}
Status InitSqList(Sqlist &l)
{
	l.base=(ElemType*)malloc(SQLIST_INIT_SIZE*sizeof(ElemType));
	if(!l.base) return Failed;
	l.len=0;
	l.listSize=SQLIST_INIT_SIZE;
	return Succeed;
}
Status InsertSqList(Sqlist &l,int i,ElemType e)
{
	//此处需要对i的合法性进行校验
	if(i<1 || i>l.len+1)  return error;
	if(l.len >=l.listSize)//存储空间已经占满了，需要重新分配空间 
	{
		ElemType * newBase=(ElemType*)realloc(l.base,(l.listSize+SQLIST_INCREMENT)*sizeof(ElemType));
		if(!newBase)	return Failed;
		l.base=newBase;
		l.listSize+=SQLIST_INCREMENT;
	}
	ElemType *temp=&(l.base[i-1]);//temp存储了需要插入元素位置的地址
	ElemType *p=&(l.base[l.len-1]);//p存储了当前顺序表最后元素位置的地址
	while(p>=temp)
	{//把待插入位置之后的每个元素往后移动 
		*(p+1)=*p;
		p--;
	}
	*temp=e;
	l.len++;
	return Succeed;
}
Status DelSqlist(Sqlist &l,int i,ElemType &e)
{
	//此处需要对i的合法性进行校验
	if(i<1 || i>l.len) return error;
	ElemType* p =&(l.base[i-1]);//找到要删除的第i个位置，由于数组是从第0号开始编号，所以要删除的第i个节点其实在i-1处 
	e= *p;
	ElemType *q=l.base+l.len-1;
	while(q>p)
	{
		*p=*(p+1);
		p++;
	}
	l.len--;
	return Succeed; 
}
void PrintSqlist(Sqlist l)
{
	int i;
	printf("顺序表中%d个元素如下所示：\n",l.len);
	for(i=0;i<l.len;i++)
	{
		printf("%d:%d\t",i+1,l.base[i]);
	}
	printf("\n");
}
int SqlistFind(Sqlist l,ElemType e )
{
	int i;
	for(i=0;i<l.len;i++)
	{
		if(e==l.base[i])
		{
			return i+1; 
		}
	}
	if(i==l.len)
	{
		return -1;
	}
}
int SqlistSum(Sqlist l)
{
	int i;
	int sum=0;
	for(i=0;i<l.len;i++)
	{
		sum+=l.base[i];
	}
	return sum;
}
ElemType SqlistGetElem(Sqlist l,int i)
{
	return l.base[i-1];
}