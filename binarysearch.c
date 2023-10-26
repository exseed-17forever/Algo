#include<stdio.h>
#include<stdlib.h>
#include<time.h>
//查找树ADT-二叉查找树

struct TreeNode;
typedef struct TreeNode* Position;
typedef struct TreeNode* SearchTree;
typedef int ElementType;

SearchTree MakeEmpty(SearchTree T);
Position Find(ElementType X,SearchTree T);
Position FindMin(SearchTree T);
Position FindMax(SearchTree T);
SearchTree Insert(ElementType X,SearchTree T);
SearchTree Delete(ElementType X,SearchTree T);

//place in the implementation file
struct TreeNode
{
	ElementType Element;
	SearchTree Left;
	SearchTree Right;
};


int main()
{
	srand((unsigned int)time(NULL));
	SearchTree mytree = (SearchTree)malloc(sizeof(struct TreeNode));
	int i;
	for(i = 0;i < 4;i++)
	{
		int random = (int)rand () % 100 + 200;
		Insert(random,mytree);
	}
	Position pos = (Position)malloc(sizeof(struct TreeNode));
	pos = FindMax(mytree);
	printf("the biggest element in mytree is : %d.\n",pos->Element);
	pos = FindMin(mytree);
	printf("the smallest element in mytree is : %d.\n",pos->Element);
	//int del = pos->Element;
	//Delete(del,mytree);
	//printf("the smallest element after delete is: %d.\n",pos->Element);
	free(pos);

	return 0;
}

//initiate Tree
SearchTree MakeEmpty(SearchTree T)
{
	if(T != NULL)
	{
		MakeEmpty(T->Left);
		MakeEmpty(T->Right);
		free(T);
	}
	return NULL;
}

//find elements
Position Find(ElementType X,SearchTree T)
{
	if(T == NULL)
	{
		return NULL;
	}
	if(X < T->Element)
	{
		return Find(X,T->Left);
	}
	else if(X > T->Element)
	{
		return Find(X,T->Right);
	}
	else
	{
		return T;
	}
}

//findMin
Position FindMin(SearchTree T)
{
	if(T == NULL)
		return NULL;
	else if(T->Left == NULL)
		return T;
	else
		return FindMin(T->Left);
}
/*以非递归的方式实现查找二叉搜索树的最大最小值
*	if(T != NULL)
*		while(T->Left != NULL)
*			T = T->Left;
*	return T;
*
*	if(T != NULL)
*		while(T->Right != NULL)
*			T = T->Right;
* 
*/

//findMax
Position FindMax(SearchTree T)
{
	if(T == NULL)
		return NULL;
	else if(T->Right == NULL)
		return T;
	else
		return FindMax(T->Right);
}

//Insert element
SearchTree Insert(ElementType X,SearchTree T)
{
	if(T == NULL)	
	{
		//create and return a one-node tree
		T = (SearchTree)malloc(sizeof(struct TreeNode));
		if(T == NULL)
		{
			printf("Tree malloc Error!\n");
			exit(0);
		}
		else
		{
			T->Element = X;
			T->Left = NULL;
			T->Right = NULL;
		}
	}
	else if(X < T->Element)
		T->Left = Insert(X,T->Left);
	else if(X > T->Element)
		T->Right = Insert(X,T->Right);
	//else X is in the tree already,we'll do nothing
		return T; //返回这个树
}

//Delete
SearchTree Delete(ElementType X,SearchTree T)
{
	Position TmpCell;

	if(T == NULL)
	{
		printf("Element not found");
		exit(0);
	}
	else if(X < T->Element) // go left
	{
		T->Left = Delete(X,T->Left);
	}
	else if(X > T->Element)
	{
		T->Right = Delete(X,T->Right);
	}
	else if(T->Left && T->Right) //two children
	{
		//replace with smallest in right subtree
		TmpCell = FindMin(T->Right);
		T->Element = TmpCell->Element; //将右节点树上的最小节点元素赋值给当前节点元素
		T->Right = Delete(T->Element,T->Right); //再删除掉右节点树中最小节点
	}
	else //one or zero children
	{
		TmpCell = T;
		if(T->Left == NULL) //also handles 0 children
		{
			T = T->Right;
		}
		else if(T->Right == NULL)
		{
			T = T->Left;
		}
		free(TmpCell);
	}
	return T;
}


