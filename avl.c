#include<stdio.h>
#include<stdlib.h>

//define the structure of avl tree
struct AvlNode
{
	int data;
	struct AvlNode* left;
	struct AvlNode* right;
	int height;
};

//create a new node 
struct AvlNode* createNode(int data)
{
	struct AvlNode* newNode = (struct AvlNode*)malloc(sizeof(struct AvlNode));
	newNode->data = data;
	newNode->left = newNode->right = NULL;
	newNode->height = 1;
	return newNode;
}

//calculate the height of node
int getHeight(struct AvlNode* node)
{
	if(node == NULL)
	{
		return 0;
	}
	return node->height;
}

//comparsion
int Max(int a,int b)
{
	return a > b ? a : b;
}

//execute right-rotate
struct AvlNode* rightRotate(struct AvlNode* y)
{
	struct AvlNode* x = y->left;
	struct AvlNode* T2 = x->right;

	//rotate
	x->right = y;
	y->left = T2;

	//update the new height
	y->height = Max(getHeight(y->left),getHeight(y->right)) + 1;
	x->height = Max(getHeight(x->left),y->height) + 1;
	
	return x;
}

//execute left-rotate
struct AvlNode* leftRotate(struct AvlNode* x)
{
	struct AvlNode* y = x->right;
	struct AvlNode* T2 = y->left;

	//rotate
	y->left = x;
	x->right = T2;

	//update height
	x->height = Max(getHeight(x->left),getHeight(x->right)) + 1;
	y->height = Max(x->height,getHeight(y->right)) + 1;

	return y;
}

//get balance
int getBalance(struct AvlNode* node)
{
	if(node == NULL)
		return 0;
	return getHeight(node->left) - getHeight(node->right);
}

//insert node
struct AvlNode* insert(struct AvlNode* root,int data)
{
	//judge root
	if(root == NULL)
		return createNode(data);
	else if(data < root->data)
	{
		root->left = insert(root->left,data);
	}
	else if(data > root->data)
	{
		root->right = insert(root->right,data);
	}
	else //not allowed to insert the same data node
		return root;
	
	//更新节点高度
	root->height = 1 + Max(getHeight(root->left),getHeight(root->right));

	//获取节点的平衡因子
	int balance = getBalance(root);

	//如果节点不平衡，则执行平衡调整
	
	//left-left
	if(balance > 1 && data < root->left->data)
		return rightRotate(root);

	//right-right
	if(balance < -1 && data > root->right->data)
		return leftRotate(root);

	//left-right
	if(balance > 1 && data > root->left->data)
	{
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}

	//right-left
	if(balance < -1 && data < root->right->data)
	{
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}

	return root;
}

//中序遍历avl树
void inorderTraversal(struct AvlNode* root)
{
	if(root != NULL)
	{
		inorderTraversal(root->left);
		printf("%d ",root->data);
		inorderTraversal(root->right);
	}
}

int main()
{
	
}
