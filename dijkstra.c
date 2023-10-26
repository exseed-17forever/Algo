#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define V 6 //图中顶点的数量
	    
//函数用于找到距离数组中最小距离的顶点索引
int minDistance(int dist[],bool visited[])
{
	int min = INT_MAX, min_index;

	int i;
	for(i = 0;i < V;i++)
	{
		if(!visited[i] && dist[i] <= min)
		{
			min = dist[i];
			min_index = i;
		}
	}

	return min_index;
}

//打印最短路径结果
void printSolution(int dist[])
{
	printf("顶点\t最短距离\n");
	for(int i = 0;i < V;i++)
	{
		printf("%d\t%d\n",i,dist[i]);
	}
}

void dijkstra(int graph[V][V],int src)
{
	int dist[V]; //存储从源到各顶点的最短距离
	bool visited[V]; //标记顶点是否已经被访问
	
	//初始化距离数组和访问标记数组
	for(int i = 0;i < V;i++)
	{
		dist[i] = INT_MAX;
		visited[i] = false;
	}

	dist[src] = 0; //源顶点到自身的距离为0
	
	for(int count = 0;count < V - 1;count++)
	{
		int u = minDistance(dist,visited);
		visited[u] = true; //第一次执行时找到src，第二次执行时找到src的neighbor顶点，第三次，第四次。。。

		for(int v = 0;v < V;v++)
		{
			if(!visited[v] && graph[u][v] && dist[u] != INT_MAX
					&& dist[u] + graph[u][v] < dist[v]) //保证未被访问，保证值存在，保证当前最小顶点
									    //的距离不为最大，保证接下来的顶点dist未定义

			{
				dist[v] = dist[u] + graph[u][v];
			}
		}
	}

	printSolution(dist);
}

int main()
{
	int graph[V][V] = 
	{
		{0, 3, 0, 0, 0, 0},
	        {3, 0, 1, 0, 0, 0},
	        {0, 1, 0, 7, 5, 0},
	        {0, 0, 7, 0, 2, 4},
	        {0, 0, 5, 2, 0, 3},
	        {0, 0, 0, 4, 3, 0}	
	};

	int source = 0; //源顶点

	dijkstra(graph,source);

	return 0;
}
