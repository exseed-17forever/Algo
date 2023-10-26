#include<stdio.h>
#include<stdlib.h>

typedef struct Edge
{
	int src,dest,weight;
}Edge;

typedef struct DisjointSet
{
	int* parent,*rank;
	int n;
}DisjointSet;

DisjointSet* createDisjointSet(int n)
{
	DisjointSet* ds = (DisjointSet*)malloc(sizeof(DisjointSet));
	ds->parent = (int*)malloc(sizeof(int) * n);
	ds->rank = (int*)malloc(sizeof(int) * n);
	ds->n = n;
	for(int i = 0;i < n;i++)
	{
		ds->parent[i] = i;
		ds->rank[i] = 0;
	}
	return ds;
}

int find(DisjointSet* ds,int index)
{
	if(ds->parent[index] != index)
	{
		ds->parent[index] = find(ds,ds->parent[index]);
	}
	return ds->parent[index];
}

void unionSet(DisjointSet* ds,int a,int b)
{
	int rootA = find(ds,a);
	int rootB = find(ds,b);
	
	if(rootA == rootB)
		return;
	if(ds->rank[rootA] < ds->rank[rootB])
	{
		ds->parent[rootA] = rootB;
	}
	else if(ds->rank[rootA] > ds->rank[rootB])
	{
		ds->parent[rootB] = rootA;
	}
	else
	{
		ds->parent[rootA] = rootB;
		ds->rank[rootB]++;
	}
}

void sortEdges(Edge* edges,int numEdges)
{
	int i,j,gap;
	Edge tmp;
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

void kruskal(Edge* edges,int numEdges,int numVertices)
{
	DisjointSet* ds = createDisjointSet(numVertices);
	int mstWeight = 0;
	sortEdges(edges,numEdges);

	for(int i = 0;i < numEdges;i++)
	{
		int srcRoot = find(ds,edges[i].src);
		int destRoot = find(ds,edges[i].dest);
		
		if(srcRoot != destRoot)
		{
			printf("%d - %d,Weight:%d\n",edges[i].src,edges[i].dest,edges[i].weight);
			mstWeight += edges[i].weight;
			unionSet(ds,srcRoot,destRoot);
		}
	}
	printf("Minimum Spanning Tree Weight: %d\n",mstWeight);

	free(ds->parent);
	free(ds->rank);
	free(ds);
}


int main()
{
	int numVertices = 4;
	int numEdges = 5;
	Edge edges[] = {
	
		{0,1,10},
		{0,2,6},
		{0,3,5},
		{1,3,15},
		{2,3,4}	
	};
	kruskal(edges,numEdges,numVertices);

	return 0;
}
