#include<stdio.h>
#include<assert.h>
#include<stdbool.h>
#include<string.h>

/*
 *	C与指针--二叉搜索树
 *	
 */
#define TREE_TYPE int
#define TREE_SIZE 100 //Tree's max values
#define ARRAY_SIZE (TREE_SIZE + 1)

//用于存储树的所有节点的数组
static TREE_TYPE  tree[ARRAY_SIZE];

//计算一个节点左子节点的下标

static int left_child(int current)
{
	return current * 2;
}

//计算一个节点右子节点的下标
static int right_child(int current)
{
	return current * 2 + 1;
}

//为树插入一个节点值
void insert(TREE_TYPE value)
{
	int current;
	
	//确保值非零，因为零用于提示一个未使用的节点
	assert(value != 0);

	//从根节点开始
	current = 1;

	//从合适的子树开始，直到到达一个叶节点
	
	while(tree[current] != 0)
	{
		//根据情况进入左子树或者右子树
		if(value < tree[current])
			current = left_child(current);
		else{
			assert(value != tree[current]);
			current = right_child(current);
		}
	}
	assert(current < ARRAY_SIZE);
	tree[current] = value;
}

//查找树节点
TREE_TYPE *find(TREE_TYPE value)
{
	int current;
	
	//从根节点开始
	current = 1;
	while(current < ARRAY_SIZE && tree[current] != value)
	{
		//根据情况进入左子树或者右子树
		if(value < tree[current])
			current = left_child(current);
		else{
			current = right_child(current);
		}
	}
	//if(tree[current] = value)
	//return &tree[current];
	if(current < ARRAY_SIZE)
		return tree + current;
	else
		return 0;
}

//前序遍历
static void do_pre_order_traverse(int current,void(*callback)(TREE_TYPE value))
{
	if(current < ARRAY_SIZE && tree[current] != 0)
	{
		callback(tree[current]);
		do_pre_order_traverse(left_child(current),callback);
		do_pre_order_traverse(right_child(current),callback);
	}
}

//整棵树前序遍历
static void pre_order_traverse(void (*callback)(TREE_TYPE value))
{
	do_pre_order_traverse(1,callback);
}
