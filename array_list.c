#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define SIZE 100

struct List;
//函数原型声明
struct List* createList();

void insertFirst(struct List* p,int x);
void insertLast(struct List* p,int x);

int find(struct List* p,int x);

int findKth(struct List* p,int position);

void delete(struct List* p,int x);

bool isEmpty(struct List* p);

int size(struct List* p);

void printList(struct List* p);

//用于存储表的结构
struct List
{
	int elements[SIZE]; //表中元素都存在数组中

	int length; //表中元素的长度(即个数)，实际存储的有效元素个数
};

int main()
{
	int index;

	int element;

	//创建一个空表
	struct List* list = createList();

	printf("List isEmpty?:%d\n",isEmpty(list));
	printf("=================================\n");

	//表头部插入
	insertFirst(list,1);
	insertFirst(list,2);

	printList(list);
	printf("=================================\n");

	//表尾部插入
	insertLast(list,3);
	insertLast(list,4);

	printList(list);
	printf("==================================\n");

	//查找值为3的元素，如果找到返回数组角标，找不到返回-1
	index = find(list,3);
	if(index == -1)
	{
		printf("not find...\n");
	}	
	else
	{
		printf("find element index: %d\n",index);
	}
	printf("==================================\n");

	//查找数组中第二个元素，返回元素的值
	element = findKth(list,2);
	printf("find element: %d\n",element);

	printf("==================================\n");

	//删除值为3的元素
	delete(list,3);
	printList(list);
	printf("==================================\n");

	//获取表的大小
	printf("List size is: %d\n",size(list));
	printf("==================================\n");
	return 0;
}

//判断表是否为空
bool isEmpty(struct List* p)
{
	return p->length == 0;
}

//打印表
void printList(struct List* p)
{
	int i;
	for(i = 0;i < p->length;i++)
	{
		printf("list element  is:%d\n",p->elements[i]);
	}
}

//查找x，如果找到，返回x对应的数组角标，如果没有找到返回-1
int find(struct List* p,int x)
{
	int i; 

	for(i = 0;i < p->length;i++)
	{
		if(p->elements[i] == x)
		{
			return i;
		}
	}
	return -1;
}
//查找位置为position的元素，返回元素的值
int findKth(struct List* p,int position)
{
	if(position <= 0)
	{
		printf("position不能为负数\n");
		exit(1);
	}

	if(position > p->length)
	{
		printf("position超出表的长度\n");
		exit(1);
	}

	return p->elements[position - 1];
}

//在表的头部插入
void insertFirst(struct List* p,int x) // 1,2
{
	int i;

	if(p->length >= SIZE)
	{
		printf("表已满");
		return;
	}

	for(i = p->length;i > 0;i--)
	{
		p->elements[i] = p->elements[i - 1]; //将元素全向后移动一位
	}
	p->elements[0] = x;

	p->length++; //插入一个元素后长度加一
}

//在表的尾部插入
void insertLast(struct List* p,int x) //3，4
{
	int length = p->length;

	if(length >= SIZE)
	{
		printf("表已满\n");
		return;
	}

	p->elemnets[length] = x;
	p->length++; //插入元素后加一

}

//删除一个元素(第一个值匹配的元素)
void delete(struct List* p,int x)
{
	int i;
	for(i = 0;i < p->length;i++)
	{
		if(p->elements[i] == x)
		{
			for(;i < p->length - 1;i++)
			{
				p->elements[i] = p->elements[i + 1];
			}
		}
	}
	p->length--;
}


/*
void delKth(struct List* p,int x)
{
	int i;
	if(x <= 0 && x > p->length)
	{
		printf("超出数组长度！");
		exit(0);
	}

	for(;x < p->length - 1;x++)
	{
		p->elements[x] = p->elements[x + 1]; 
	}
}
*/
