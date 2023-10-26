#include<stdio.h>
#include<stdlib.h>

struct SplayNode
{
	int value;
	struct SplayNode* left;
	struct SplayNode* right;
};

struct SplayNode* createNode(int value)
{
	struct SplayNode* newNode = (struct SplayNode*)malloc(sizeof(struct SplayNode));
	newNode->value = value;
	newNode->left = NULL;
	newNode->right = NULL;
	return newNode;
}

struct SplayNode* rightRotate(struct SplayNode* node)
{
	struct SplayNode* newRoot = node->left;
	node->left = newRoot->right;
	newRoot->right = node;
	return newRoot;
}

struct SplayNode* leftRotate(struct SplayNode* node)
{
	struct SplayNode* newRoot = node->right;
	node->right = newRoot->left;
	newRoot->left = node;
	return newRoot;
}

struct SplayNode* splay(struct SplayNode* root,int value)
{
	if(root == NULL || root->value == value)
	{
		return root;
	}

	if(value < root->value)
	{
		if(root->left == NULL)
			return root;
		//root->left = splay(root->left,value);
		//root = rightRotate(root);
		if(value < root->left->value)
		{
			root->left->left = splay(root->left->left,value);
			root = rightRotate(root);	
		}
		else if(value > root->left->value)
		{
			root->left->right = splay(root->left->right,value);
			if(root->left->right != NULL){
		
				root->left = leftRotate(root->left);
		
			}
		}
		return (root->left == NULL) ? root : rightRotate(root);
	}
	else
	{
		if(root->right == NULL)
		{
			return root;
		}

		if(value > root->right->value)
		{
			root->right->right = splay(root->right->right,value);
			root = leftRotate(root);
		}
		else if(value < root->right->value)
		{
			root->right->left = splay(root->right->left,value);
			if(root->right->left != NULL)
			{
				root->right = rightRotate(root->right);
			}
		}

		return (root->right == NULL) ? root : leftRotate(root);
	}
}

struct SplayNode* insert(struct SplayNode* root,int value)
{
	if(root == NULL)
	{
		return createNode(value);
	}

	root = splay(root,value);

	if(root->value == value)
	{
		return root;
	}

	struct SplayNode* newNode = createNode(value);

	if(value < root->value)
	{
		newNode->right = root;
		newNode->left = root->left;
		root->left = NULL;
	}
	else
	{
		newNode->left = root;
		newNode->right = root->right;
		root->right = NULL;
	}

	return newNode;
}

void inOrderTraversal(struct SplayNode* root)
{
	if(root != NULL)
	{
		inOrderTraversal(root->left);
		printf("%d ",root->value);
		inOrderTraversal(root->right);
	}
}

int main()
{
	struct SplayNode* root = NULL;
	root = insert(root,5);
	root = insert(root,15);
	root = insert(root,32);
	root = insert(root,24);
	root = insert(root,8);
	root = insert(root,1);

	printf("In-Order traversal: \n");
	inOrderTraversal(root);
	printf("\n");
	return 0;
}

