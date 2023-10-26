#include<stdio.h>
#include<stdlib.h>
#ifndef _List_H

struct Node;
typedef struct Node* PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;
typedef int ElementType;

List MakeEmpty(List L);
int IsEmpty(List L);
int IsLast(Position P,List L);
Position Find(ElementType X,List L);
void Delete(ElementType X,List L);
Position FindPrevious(ElementType X,List L);
void Insert(ElementType X,List L,Position P);
void DeleteList(List L);
Position Header(List L);
Position First(List L);
Position Advance(Position P);
ElementType Retrieve(Position P);

#endif //_List_H

//place in the implementation file
struct Node
{
	ElementType Element;
	Position Next;
};

int main()
{
	
	return 0;
}

//return true if L is empty
int
IsEmpty(List L)
{
	return L->Next == NULL;
}

//return true if P is the last position in list L
//parameter L is unused in this implementation

int
IsLast(Position P,List L)
{
	return P->Next == NULL;
}

//return position of x in L,NULL if not found

Position
Find(ElementType X,List L)
{
	Position P;
	P = L->Next;
	while(P != NULL && P->Element != X)
		P = P->Next;

	return P; //这里一直没找到就是返回NULL
}

//delete first occurrence of X from a list
//assume use of a header node
void
Delete(ElementType X,List L)
{
	Position P,TmpCell;

	P = FindPrevious(X,L);

	if(!IsLast(P,L)) //assumption of header use
	{		//x is found ,delete it!
		TmpCell = P->Next;
		P->Next = TmpCell->Next;
		free(TmpCell);
	}
}

//if X is not found,then next field of returned
//position is NULL
//assumnes a header
Position
FindPrevious(ElementType X,List L)
{
	Position P;
	
	P = L;
	while(P->Next != NULL && P->Next->Element != X) //如果满足跳出while条件有两个可能
							//循环到最后一个节点或找到下一个节点
		P = P->Next;
	
	return P;	
}

//insert (after legal position P)
//header implementation assumed
//parameter L is unused in this implementation
void 
Insert(ElementType X,List L,Position P)
{
	Position TmpCell;

	TmpCell = malloc(sizeof(struct Node));
	if(TmpCell == NULL)
	{	
		printf("Out of space!!");
		return;
	} 
	TmpCell->Element = X;
	TmpCell->Next = P->Next;
	P->Next = TmpCell;
}
