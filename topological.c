#include<stdio.h>
#include<stdlib.h>

#define MAX_NODES 100

typedef struct Node
{
	int value;
	struct Node* next;
}Node;

typedef struct 
{
	Node* head;
}NodeList;

typedef struct 
{
	int numNodes;
	NodeList adjacencyList[MAX_NODES];
}Graph; //用散列表(分离链接法)

Node* createNode(int value)
{
	Node* newNode = (Node*)malloc(sizeof(Node)); //分配一个newNode
	//可能需要判断是否正确分配内存
	newNode->value = value;
	newNode->next = NULL;
	return newNode;
} //创建散列表上的顶点

Graph* createGraph(int numNodes)
{
	Graph* graph = (Graph*)malloc(sizeof(Graph));
	graph->numNodes = numNodes;
	int i;
	for(i = 0;i < numNodes;i++)
		graph->adjacencyList[i].head = NULL;
	return graph;
}//创建图 / 邻接表(散列表)

void addEdge(Graph* graph,int src,int dest)
{
	Node* newNode = createNode(dest); //为topo添加新顶点(Vertex)
	//可能需要判断是否正确分配内存
	newNode->next = graph->adjacencyList[src].head; //在散列表链表表头内前插
	graph->adjacencyList[src].head = newNode; //head指向新结点
} //添加边(弧)

void topologicalSortUtil(Graph* graph,int node,int visited[],Node** result,int* index)
{
	visited[node] = 1; //置一表示下表node的顶点已经访问过
	Node* current = graph->adjacencyList[node].head; //将下表为node的节点取出
	while(current != NULL) //如果节点不为空
	{
		int neighbor = current->value; //
		if(!visited[neighbor])
		{
			topologicalSortUtil(graph,neighbor,visited,result,index);
		}
		current = current->next;
	}
	result[*index] = createNode(node); //将当前节点添加到拓扑排序的结果中
	(*index)++;
}

Node** topologicalSort(Graph* graph)
{
	int numNodes = graph->numNodes;
	int* visited = (int*)malloc(numNodes * sizeof(int)); //判断当前结点是否已经被访问过
	int i; 
	for(i = 0;i < numNodes;i++)
	{
		visited[i] = 0; //清空操作
	}

	Node** result = (Node**)malloc(numNodes * sizeof(Node*)); //分配指针数组内存，用于存储拓扑数据
	int index = 0;
	for(i = 0;i < numNodes;i++)
	{
		if(!visited[i]) //遍历图中所有未访问节点	首次进入图是都未被访问的
		{
			topologicalSortUtil(graph,i,visited,result,&index);
		}
	}

	free(visited);
	return result;
}

void printTopologicalSort(Node** result,int numNodes)
{
	printf("Topological Sort: \n");
	int i;
	for(i = numNodes - 1;i >= 0;i--)
	{
		printf("%d ",result[i]->value);//倒排
	}
	printf("\n");
}

int main()
{
	int numNodes = 6;
	Graph* graph = createGraph(numNodes); //创建一个图
	
	addEdge(graph,5,2);
	addEdge(graph,5,0);
	addEdge(graph,4,0);
	addEdge(graph,4,1);
	addEdge(graph,2,3);
	addEdge(graph,3,1);

	//添加许多条边
	
	Node** result = topologicalSort(graph);
	printTopologicalSort(result,numNodes);
	

	//free memory
	for(int i = 0;i < numNodes;i++)
	{
		free(result[i]);
	}
	free(result);
	free(graph);

	return 0;
}
