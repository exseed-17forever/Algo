#include<stdio.h>
#include<stdlib.h>

//定义边的结构体
struct Edge
{
	int src,dest,weight;
};

//定义并查集结构体
struct DisjointSet
{
	int* parent,*rank;
	int n;
};

//创建并查集
struct DisjointSet* createDisjointSet(int n)
{
	struct DisjointSet* ds = (struct DisjointSet*)malloc(sizeof(struct DisjointSet));
	ds->parent = (int*)malloc(sizeof(int) * n);
	ds->rank = (int*)malloc(sizeof(int) * n);
	ds->n = n;

	for(int i = 0;i < n;i++)
	{
		ds->parent[i] = i; //kruskal算法将每个顶点看做一个树
		ds->rank[i] = 0;
	}
	return ds;
}

//查找根节点(带路径压缩)
int find(struct DisjointSet* ds,int i)
{
	if(i != ds->parent[i]) //在顶点不为入点时向上遍历查找
	{
		ds->parent[i] = find(ds,ds->parent[i]);
	}
	return ds->parent[i];
}

//合并两个集合(按秩合并)
void unionSets(struct DisjointSet* ds,int i,int j)
{
	int root_i = find(ds,i);
	int root_j = find(ds,j);

	if(root_i == root_j)
		return; //同一个集合元素
	
	if(ds->rank[i] < ds->rank[j])
	{
		ds->parent[root_i] = root_j;
	}
	else if(ds->rank[i] > ds->rank[j])
	{
		ds->parent[root_j] = root_i;
	}
	else 
	{
		ds->parent[root_j] = root_i;
		ds->rank[root_i]++;
	}
}

//按权重升序排序边
void sortEdges(struct Edge* edges,int numEdges)
{
	int i,j,gap;
	struct Edge tmp;
	for(gap = numEdges >> 1;gap > 0;gap = gap >> 1)
	{
		for(i = gap;i < numEdges;i++)
		{
			tmp = edges[i];
			for(j = i - gap;j >= 0 && edges[j].weight > tmp.weight;j -= gap)
			{
				edges[j + gap] = edges[j];
			}
			edges[j + gap] = tmp;
		}
	}
}

//kruskal算法实现
void kruskalMST(struct Edge* edges,int numEdges,int numVertices)
{
	struct DisjointSet* ds = createDisjointSet(numVertices);
	int mstWeight = 0;
	sortEdges(edges,numEdges);

	for(int i = 0;i < numEdges;i++) //遍历所有的边，从最小边长开始
	{
		int srcRoot = find(ds,edges[i].src);
		int destRoot = find(ds,edges[i].dest);
		
		if(srcRoot != destRoot)
		{
			printf("Edges %d - %d,Weight: %d\n",edges[i].src,edges[i].dest,edges[i].weight);
			mstWeight += edges[i].weight;
			unionSets(ds,srcRoot,destRoot);
		}
	}
	printf("Minimum Spanning Tree Weight: %d\n",mstWeight);

	free(ds->parent);
	free(ds->rank);
	free(ds);
}

int main() {
	    int numVertices = 4;
	        int numEdges = 5;
		    
		    struct Edge edges[] = {
			            {0, 1, 10},
				            {0, 2, 6},
					            {0, 3, 5},
						            {1, 3, 15},
							            {2, 3, 4}
				        };
		        
		        kruskalMST(edges, numEdges, numVertices);
			    
			    return 0;
}



