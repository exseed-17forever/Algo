#include<stdio.h>
#include<stdlib.h>

#ifndef _Stack_h

struct Node;
typedef struct Node* PtrToNode;
typedef PtrToNode Stack;
typedef int ElementType;

int IsEmpty(Stack S);
Stack CreateStack(void);
void DisposeStack(Stack S);
void MakeEmpty(Stack S);
void Push(ElementType X,Stack S);
ElementType Top(Stack S);
void Pop(Stack S);

#endif //_Stack_h

//Place in implementation file
//Stack implementation is a linked list with a header
struct Node
{
	ElementType Element;
	PtrToNode Next;
};



int main()
{
	
	Stack S = CreateStack();
	printf("is stack empty? %d\n",IsEmpty(S));
	int i;
	for(i = 0;i < 6;i++)
		Push(i,S);
	printf("Now on the top of the element is: %d\n",Top(S));
	Pop(S);
	Pop(S);
	printf("Now on the top of the element is: %d\n",Top(S));

	return 0;
}

int IsEmpty(Stack S)
{
	return S->Next == NULL;
}

Stack CreateStack(void)
{
	Stack NewStack = malloc(sizeof(struct Node));
	if(NewStack == NULL)
	{
		printf("malloc error!");
		exit(0);
	}
	//NewStack->Element = 0;
	NewStack->Next = NULL;
	MakeEmpty(NewStack);
	return NewStack;
}

void MakeEmpty(Stack S)
{
	if(S == NULL)
	{
		printf("must use createstack first!");
		exit(0);
	}	
	else
	{
		while(!IsEmpty(S))
			Pop(S);
	}
}

void Push(ElementType X,Stack S)
{
	PtrToNode TmpCell;

	TmpCell = malloc(sizeof(struct Node));
	if(TmpCell == NULL)
	{
		printf("malloc error!");
		exit(0);
	}
	else
	{
		TmpCell->Element = X;
		TmpCell->Next = S->Next;
		S->Next = TmpCell; //S在未push之前为栈顶元素
	}
}

ElementType Top(Stack S)
{
	if(!IsEmpty(S))
		return S->Next->Element;
	printf("error stack");
	return 0; //return value used to avoid warning
}

void Pop(Stack S)
{
	PtrToNode FirstCell;

	if(IsEmpty(S))
	{
		printf("Empty Stack!");
		exit(0);
	}
	else
	{
		FirstCell = S->Next;
		S->Next = S->Next->Next;
		free(FirstCell);	
	}
}

void DisposeStack(Stack S)
{
	if(!IsEmpty(S))
	{
		free(S);	
	}
}

