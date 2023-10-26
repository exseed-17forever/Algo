#include<stdio.h>
#include<stdlib.h>

//栈的数组实现
#define EmptyTOS (-1)
#define MinStackSize (5)

#ifndef _Stack_h
struct StackRecord;
typedef struct StackRecord* Stack;
typedef int ElementType;

int IsEmpty(Stack S);
int IsFull(Stack S);
Stack CreateStack(int MaxElements);
void DisposeStack(Stack S);
void MakeEmpty(Stack S);
void Push(ElementType X,Stack S);
ElementType Top(Stack S);
void Pop(Stack S);
ElementType TopAndPop(Stack S);

#endif //_Stack_h

//place in implementation file
//Stack implementation is a dynamically allocated array

struct StackRecord
{
	ElementType* Array;
	int Capacity;
	int TopOfStack;
};



int main(void)
{
	Stack S = CreateStack(5);
	for(int i = 0;i < 5;i++)
		Push(i,S);
	printf("the top of the stack is :%d\n",Top(S));
	ElementType e = TopAndPop(S);
	printf("now the top of the stack is :%d\n",e);
	Pop(S);
	printf("the capacity of the stack is: %d\n",S->Capacity);
	return 0;
}

Stack CreateStack(int MaxElements)
{
	Stack S;

	if(MaxElements < MinStackSize)	
	{
		printf("Error,Stack Size is too small!\n");
		exit(0);
	}

	S = malloc(sizeof(struct StackRecord));
	if(S == NULL)
	{
		printf("malloc error!\n");
		exit(0);
	}

	S->Array = malloc(sizeof(ElementType) * MaxElements);

	if(S->Array == NULL)
	{
		printf("Array malloc error!\n");
		exit(0);
	}
	S->Capacity = MaxElements;
	MakeEmpty(S);
	return S;
}

void DisposeStack(Stack S)
{
	if(S != NULL)
	{
		free(S->Array);
		free(S);
	}
}

int IsEmpty(Stack S)
{
	return S->TopOfStack == EmptyTOS;
}

int IsFull(Stack S)
{
	return S->TopOfStack + 1 > S->Capacity;
}

void MakeEmpty(Stack S)
{
	S->TopOfStack = EmptyTOS;
}

void Push(ElementType X,Stack S)
{
	if(IsFull(S))
	{
		printf("Stack is full of elements!\n");
		exit(0);
	}
	else
	{
		S->Array[++(S->TopOfStack)] = X;
	}
}	

ElementType Top(Stack S)
{
	if(!IsEmpty(S))
	{
		return S->Array[S->TopOfStack];
	}
	printf("Stack is empty!\n");
	return 0; //return value used to avoid warning
}

void Pop(Stack S)
{
	if(IsEmpty(S))
	{
		printf("Stack is empty!\n");
		exit(0);	
	}
	else
		S->TopOfStack--;
}

ElementType TopAndPop(Stack S)
{
	if(!IsEmpty(S))
		return S->Array[S->TopOfStack--];
	printf("Stack is empty!\n");
	exit(0);
}

