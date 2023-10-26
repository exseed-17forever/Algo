#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

//表达式树的实现

//首先是二叉树的实现
#ifndef _binary_tree
struct TreeNode;

typedef struct TreeNode TreeData;
typedef struct TreeNode* TreePtr;
typedef char* ElementType;

struct TreeNode
{
	ElementType data; //节点元素
	TreePtr left; //左子节点
	TreePtr right; //右子节点
};

//具体功能实现

//创建一个新的二叉树节点
TreePtr createNode(ElementType data)
{
	TreePtr newNode = (TreePtr)malloc(sizeof(TreeData));

	if(newNode == NULL)
	{
		printf("tree malloc error!\n");
		exit(0);
	}


	//分配内存成功
	newNode->data = data;
	newNode->left = NULL;
	newNode->right = NULL;
	
	return newNode;
}

//向二叉树中插入节点
TreePtr insertNode(TreePtr root,ElementType data)
{
	if(root == NULL)
	{
		printf("自动新分配一个root节点\n");
		return createNode(data);
	}

	if(data < root->data)
	{
		root->left = insertNode(root->left,data);
	}
	else if(data > root->data)
	{
		root->right = insertNode(root->right,data);
	}

	return root;
}

//在二叉树中查找节点
TreePtr searchNode(TreePtr root,ElementType key)
{
	if(root == NULL || root->data == key)
	{
		return root; //返回的是一个节点类型
	}

	if(key < root->data)
	{
		return searchNode(root->left,key);
	}
	return searchNode(root->right,key);
}

//释放整个二叉树的内存
void freeTree(TreePtr root)
{
	if(root == NULL)
	{
		return;
	}

	freeTree(root->left);
	freeTree(root->right);
	free(root);
}

#endif


//其次是栈的实现
#ifndef _stack

#define MAX_SIZE 100

struct Stack;
typedef struct Stack StackData;
typedef struct Stack* StackPtr;

struct Stack
{
	TreePtr data[MAX_SIZE];
	int top; //用下表的方式表示栈顶指针
};

//初始化栈
void initStack(StackPtr stack)
{
	stack->top = -1; //初始化栈顶为-1，表示栈为空
}

//判断栈是否为空
bool isEmpty(StackPtr stack)
{
	return stack->top == -1;
}

//判断栈是否已满
bool isFull(StackPtr stack)
{
	return stack->top == MAX_SIZE - 1;
}

//入栈
bool push(StackPtr stack,TreePtr value)
{
	if(isFull(stack))
	{
		printf("Error: Stack overflow!\n");
		return false;
	}

	stack->top++;
	stack->data[stack->top] = value;
	return true;
}

//出栈
bool pop(StackPtr stack)
{
	if(isEmpty(stack))
	{
		printf("Error: Stack is empty!\n");
		return false;
	}
	free(stack->data[stack->top]);
	stack->top--;
	return true;
}

//获取栈顶元素
TreePtr top(StackPtr stack)
{
	if(isEmpty(stack))
	{
		printf("Error: Stack is empty!\n");
		exit(0);
	}
	return stack->data[stack->top];
}

//删除整个栈
bool delete(StackPtr stack)
{
	if(isEmpty(stack))
	{
		printf("Error: Stack is empty!\n");
		return false;
	}
	while(!isEmpty(stack))
	{
		pop(stack);
	}
	return true;
}
#endif

#ifndef _expTree

/*void ExpTreeCreate(char* str,StackPtr stack)
{
	int i;
	char* string = str;//strcpy(string,str);
	

	for(i = 0;i < strlen(string),i++)
	{
		if(string[i] == '+' || string[i] == '*')
		{
			TreePtr node = (TreePtr)malloc(sizeof(TreeData));
			insertNode(node,string[i]);	
		}
		else
		{
		
			TreePtr node = (TreePtr)malloc(sizeof(TreeData));
			insertNode(node,string[i]);
			push(stack,node);
		}
	}	
	

}*/

#endif

int main(void)
{
	
	char* str = "ab+cde+**";
	//StackPtr mystack = (StackPtr)malloc(sizeof(StackData));
	
	printf("have a postfix expresssion :\n");
	printf("%s \n",str);

	printf("str1 is %c",str[0]);
	


	return EXIT_SUCCESS;
}

/*int main(void)
{
	 TreePtr root = NULL;
	 root = createNode(5);
		
	 insertNode(root,2);
	 insertNode(root,6);
	 insertNode(root,1);
	 insertNode(root,7);
	 insertNode(root,3);

	 int key = 7;
	 printf("i search %d elements :",key);
	
	 TreePtr result = searchNode(root,key);
	 if(result)
	 {
	 	printf("it was found in the binary tree.\n");	
	 }
	 else
	 {
	 	printf("it was not found in the binary tree.\n");
	 }

	 freeTree(root);
	 return EXIT_SUCCESS;
}*/

/*int main(void)
{
	StackPtr mystack = malloc(sizeof(StackData));
	initStack(mystack);

	TreePtr newNode = (TreePtr)malloc(sizeof(TreeData));
	TreePtr newNode1 = (TreePtr)malloc(sizeof(TreeData));
	TreePtr newNode2 = (TreePtr)malloc(sizeof(TreeData));

	newNode = createNode(4);
	newNode1 = createNode(10);
	newNode2 = createNode(7);
	
	

	push(mystack,newNode);
	push(mystack,newNode1);
	push(mystack,newNode2);

	printf("Top Elements: 0x%p",top(mystack));
	
	pop(mystack);
	
	printf("Top Elements after pop: ox%p",top(mystack));
	delete(mystack);

	return EXIT_SUCCESS;
}*/


