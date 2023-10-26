#include<stdio.h>
#include<stdlib.h>

#define MAX_NODES 100

typedef struct Node
{
	int value;
	struct Node* next;
}Node; //顶点元素结构体

typedef struct 
{
	Node* head;
}NodeList; //邻接表内头节点结构体定义

typedef struct
{
	int numNodes;
	NodeList adjacencyList[MAX_NODES];	
	int inDegree[MAX_NODES];
}Graph;

Node* createNode(int value)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->value = value;
	newNode->next = NULL;
	return newNode;
}

Graph* createGraph(int numNodes)
{
	Graph* graph = (Graph*)malloc(sizeof(Graph));
	graph->numNodes = numNodes;
	int i;
	for(i = 0;i < numNodes;i++)
	{
		graph->adjacencyList[i].head = NULL;
		graph->inDegree[i] = 0;
	}
	return graph;
}

void addEdge(Graph* graph,int src,int dest)
{
	Node* newNode = createNode(dest);
	newNode->next = graph->adjacencyList[src].head;
	graph->adjacencyList[src].head = newNode;
	graph->inDegree[dest]++; //添加一条边(弧)后入度++
}

void topologicalSort(Graph* graph)
{
	int numNodes = graph->numNodes;
	int result[MAX_NODES];
	int queue[MAX_NODES];
	int front = 0,rear = 0;
	
	for(int i = 0;i < numNodes;i++)
	{
		if(graph->inDegree[i] == 0)
		{
			queue[rear++] = i;
		}
	}
	int index = 0;
	
	while(front < rear)
	{
		int currentNode = queue[front++]; //从队列中取出当前顶点
		result[index++] = currentNode; //将当前顶点元素下标存在result
		
		Node* currentNeighbor = graph->adjacencyList[currentNode].head;
		while(currentNeighbor != NULL)
		{
			int neighbor = currentNeighbor->value;
			graph->inDegree[neighbor]--;
			if(graph->inDegree[neighbor] == 0)
			{
				queue[rear++] = neighbor; //每次操作queue时都要将rear++
			}
			currentNeighbor = currentNeighbor->next;
		}
	}

	printf("Topological Sort:\n");
	for(int i = 0;i < index;i++)
	{
		printf("%d ",result[i]);
	}
	printf("\n");
}

int main()
{
	int numNodes = 6;
	Graph* graph = createGraph(numNodes);
	
	addEdge(graph,5,2);
	addEdge(graph,5,0);
	addEdge(graph,4,0);
	addEdge(graph,4,1);
	addEdge(graph,2,3);
	addEdge(graph,3,1);

	topologicalSort(graph);

	free(graph);
	return EXIT_SUCCESS;
}
