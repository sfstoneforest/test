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
	ElemType *base;		//˳���Ļ�ַ 
	int		  len;		//˳���ǰ���� 
	int 	  listSize;	//˳���洢���� 
}Sqlist;
Status InitSqList(Sqlist &l);//����һ���յ�˳���l
Status InsertSqList(Sqlist &l,int i,ElemType e);//��˳���l�еĵ�i��λ��֮ǰ�����µ�Ԫ��e 
Status DelSqlist(Sqlist &l,int i,ElemType &e);//ɾ��˳���l�еĵ�i��λ�õ�Ԫ�أ�������ֵ���ظ�e
void PrintSqlist(Sqlist l);
int SqlistFind(Sqlist l,ElemType e );//����ʧ�ܷ���-1�����򷵻�����λ��+1 
int SqlistSum(Sqlist l);
ElemType SqlistGetElem(Sqlist l,int i);//i��1��ʼ���� 
int main()
{
	int cnt,i,temp,loc;
	Sqlist l;
	InitSqList(l);
	printf("���������Ա�Ԫ�صĸ�����\n");
	scanf("%d",&cnt);
	printf("������%d��Ԫ��",cnt);
	for(i=0;i<cnt;i++)
	{
		scanf("%d",&temp);
		InsertSqList(l,i+1,temp);
	}
	PrintSqlist(l);
	printf("������Ҫ��ȡԪ�ص�λ�ã�\n");	
	scanf("%d",&temp);	
	printf("˳����е�%d��Ԫ��Ϊ��%d\n",temp,SqlistGetElem(l,temp));
	printf("������Ҫ����Ԫ�ص�λ�ã�\n");	
	scanf("%d",&loc);
	printf("������Ҫ�����Ԫ�أ�\n");	
	scanf("%d",&temp);	
	InsertSqList(l,loc,temp);
	printf("����Ԫ�غ��˳���\n");
	PrintSqlist(l);
	printf("������Ҫɾ��Ԫ�ص�λ�ã�\n");	
	scanf("%d",&loc);
	DelSqlist(l,loc,temp);
	printf("ɾ����Ԫ��Ϊ��%d\n",temp);
	printf("ɾ��Ԫ�غ��˳���\n");
	PrintSqlist(l);
	printf("˳���������Ԫ��֮��Ϊ��%d\n",SqlistSum(l));		 
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
	//�˴���Ҫ��i�ĺϷ��Խ���У��
	if(i<1 || i>l.len+1)  return error;
	if(l.len >=l.listSize)//�洢�ռ��Ѿ�ռ���ˣ���Ҫ���·���ռ� 
	{
		ElemType * newBase=(ElemType*)realloc(l.base,(l.listSize+SQLIST_INCREMENT)*sizeof(ElemType));
		if(!newBase)	return Failed;
		l.base=newBase;
		l.listSize+=SQLIST_INCREMENT;
	}
	ElemType *temp=&(l.base[i-1]);//temp�洢����Ҫ����Ԫ��λ�õĵ�ַ
	ElemType *p=&(l.base[l.len-1]);//p�洢�˵�ǰ˳������Ԫ��λ�õĵ�ַ
	while(p>=temp)
	{//�Ѵ�����λ��֮���ÿ��Ԫ�������ƶ� 
		*(p+1)=*p;
		p--;
	}
	*temp=e;
	l.len++;
	return Succeed;
}
Status DelSqlist(Sqlist &l,int i,ElemType &e)
{
	//�˴���Ҫ��i�ĺϷ��Խ���У��
	if(i<1 || i>l.len) return error;
	ElemType* p =&(l.base[i-1]);//�ҵ�Ҫɾ���ĵ�i��λ�ã����������Ǵӵ�0�ſ�ʼ��ţ�����Ҫɾ���ĵ�i���ڵ���ʵ��i-1�� 
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
	printf("˳�����%d��Ԫ��������ʾ��\n",l.len);
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