#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
//队列adt数组实现
struct Queue;

struct Queue* createQueue(int maxElements);

bool isEmpty(struct Queue* q);
bool isFull(struct Queue* q);

void disposeQueue(struct Queue* q); //释放队列内存空间

void makeEmpty(struct Queue* q);

void enqueue(int x,struct Queue* q);

void dequeue(struct Queue* q);

int succ(int index,struct Queue* q); //循环数组的角标计算

int front(struct Queue* q);
int frontAndDequeue(struct Queue* q);

void printQueue(struct Queue* q);

struct Queue
{
	int capacity; //队列的容量
	int size; //队列的有效数据大小
	
	int front; //队头的角标
	int rear; //队尾的角标
	int* array; //指针，指向数组首元素的地址(即数组地址)
};

int main(void)
{
	int val;
	struct Queue* q;
	//创建队列
	q = createQueue(5);

	//入队
	enqueue(1,q);
	enqueue(2,q);
	enqueue(3,q);
	enqueue(4,q);
	enqueue(5,q);
	
	//打印队列
	printQueue(q);

	printf("=================\n");

	//出队
	dequeue(q);
	dequeue(q);

	enqueue(9,q);
 
}

//判断队列是否为空
bool isEmpty(struct Queue* q)
{
	return q->size == 0;
}

//判断队列是否已满
bool isFull(struct Queue* q)
{
	return q->size == q->capacity;
}

//初始化队列
void makeEmpty(struct Queue* q)
{
	q->size = 0;
	q->front = 1;
	q->rear = 0;	
}

//创建队列
struct Queue* createQueue(int maxElements)
{
	struct Queue* q;
	q = malloc(sizeof(struct Queue));

	if(q == NULL)
	{
		printf("out of space!\n");
		return NULL;
	}

	q->array = malloc(sizeof(int) * maxElements);

	if(q->array == NULL)
	{
		printf("out of space!\n");
		return NULL;
	}
	q->capacity = maxElements;
	makeEmpty(q);

	return q;
}

//从队尾，元素x入队
void enqueue(int x,struct Queue* q)
{
	if(isFull(q))
	{
		printf("full Queue!\n");
		return;
	}
	else
	{
		q->size++;
		q->rear = succ(q->rear,q);
		q->array[q->rear] = x;
	}
}

//从队头出队
void dequeue(struct Queue* q)
{
	if(isEmpty(q))
	{
		printf("empty queue!\n");
		return;
	}
	else
	{
		q->size--;

		q->front = succ(q->front,q);
	}
}

//循环数组的角标计算
int succ(int index,struct Queue* q)
{
	index++;
	return index % q->capacity;
}

//返回队头的元素，但不出队
int front(struct Queue* q)
{
	if(isEmpty(q))
	{
		printf("empty queue!\n");
		return 0;
	}
	return q->array[q->front];
	
}

//返回队头的元素，且出队
int FrontAndDequeue(struct Queue* q)
{
	int element;

	if(isEmpty(q))
	{
		printf("empty queue!\n");
		return 0;
	}
	else
	{
		element = q->array[q->front];
		q->size--;
		q->front = succ(q->front,q);

		return element;
	}
}

//打印队中的元素
void printQueue(struct Queue* q)
{
	int i;

	int front = q->front;
	int rear = q->rear;
	int size = q->size;
	int capacity = q->capacity;

	for(i = front;i < front + size;i++)
	{
		printf("element is:%d\n",q->array[i % capacity]);
	}
}

//释放队列内存
void disposeQueue(struct Queue* q)
{
	if(q != NULL)
	{
		free(q->array);
		free(q);
	}
}

