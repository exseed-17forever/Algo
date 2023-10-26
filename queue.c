#include<stdio.h>
#include<stdlib.h>

//队列的实现
#define OVERFLOW -2
#define OK 1
#define ERROR 0

typedef int Status;
typedef int QElemType;

typedef struct QNode1
{
	QElemType data;
	struct QNode1* next;
}QNode,*QueuePtr;

typedef struct 
{
	QueuePtr front; //队头指针
	QueuePtr rear; //队尾指针
	
}*LinkQueue;

Status InitQueue(LinkQueue Q)
{
	Q->front = Q->rear = (QueuePtr)malloc(sizeof(QNode));
	if(!Q->front)	exit(OVERFLOW); //分配存储失败
	Q->front->next = NULL;
	return OK;

	//首先传入一个包含队头指针和队尾指针的结构体类型数据
	//给这个形参的front和rear分配内存
	//判断是否分配成功
	//分配成功后front指针的next为null
	//返回初始化成功的标志
}

Status DestoryQueue(LinkQueue Q)
{
	while(Q->front)
	{
		Q->rear = Q->front->next;
		free(Q->front);
		Q->front = Q->rear;
	}
	return OK;
	//销毁队列Q
}

Status EnQueue(LinkQueue Q,QElemType e)
{
	QueuePtr p = (QueuePtr)malloc(sizeof(QNode));
	if(!p) exit(OVERFLOW); //存储分配失败
	p->data = e;
	p->next = NULL;
	Q->rear->next = p;
	Q->rear = p; //更新队尾
	return OK;
}

Status DeQueue(LinkQueue Q,QElemType* e)
{
	if(Q->front == Q->rear) return ERROR;
	QueuePtr p = Q->front->next; //Q.front没有data，next != NULL(除非空队列)
	*e = p->data;
	Q->front->next = p->next; //更新队头
	if(Q->rear == p) Q->rear = Q->front; //队列为空
	free(p);
	return OK;
}

void PrintQueue(LinkQueue Q)
{
	//打印队列Q的全部元素
	QueuePtr p = Q->front;
	while(p->next)
	{
		printf("%d ",p->next->data);
		p = p->next;
	}
	printf("\n");
}



int main(void)
{
	LinkQueue q = (LinkQueue)malloc(sizeof(QueuePtr) * 2);
	InitQueue(q); //初始化队列
	
	QElemType e1 = 666,e2 = 888;
	EnQueue(q,e1);
	EnQueue(q,e2);
	printf("队列元素： ");
	PrintQueue(q);

	QElemType* e3 = (int*)malloc(sizeof(int));
	DeQueue(q,e3);
	printf("删除元素为：%d \n",*e3);
	printf("队列元素：");
	PrintQueue(q);

	DestoryQueue(q);
	free(q);
	return 0;
}
