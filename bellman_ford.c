#include<stdio.h>
#include<stdlib.h>

#define V 5 //图中顶点的数量
#define E 8 //图中边的数量

//表示图中的一条边
struct Edge
{
	int src,dest,weight;
};

void Bellman_Ford(struct Edge* edge,int source)
{
	int dist[V];
	
	for(int i = 0;i < V;i++)
	{
		dist[i] = INT_MAX;
	}
	 
	dist[source] = 0;
	for(int i = 0;i < V - 1;i++)
	{
		for(int j = 0;j < E;j++)
		{
			int src = edge[j].src;
			int dest = edge[j].dest;
			int weight = edge[j].weight;
			
			if(dist[src] != INT_MAX && dist[src] + weight < dist[dest])
			{
				dist[dest] = dist[src] + weight;
			}
		}
	}

	for(int i = 0;i < E;i++)
	{
		int u = edge[i].src;
		int v = edge[i].dest;
		int weight = edge[i].weight;
		if(dist[u] != INT_MAX && dist[u] + weight < dist[v])
		{
			printf("there are some negative circle exists in this graph!\n");
			return;
		}
	}

	printf("Top\tShortest distance\n");
	for(int i = 0;i < V;i++)
	{
		printf("%d\t%d\n",i,dist[i]);
	}
	
	
}



int main()
{
	struct Edge edges[E] = {
			
				{0, 1, -1},
						{0, 2, 4},
								{1, 2, 3},
										{1, 3, 2},
												{1, 4, 2},
														{3, 2, 5},
																{3, 1, 1},
																		{4, 3, -3}
					};

		//第一轮松弛
		//	//dist[0] = 0;
		//		//dist[1] = -1;
		//			//dist[2] = 2;
		//				//dist[3] = -2;
		//					//dist[4] = 1;
		//
								int source = 0;
		
							Bellman_Ford(edges,source);
										return 0;

}
