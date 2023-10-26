#include<iostream>
#include<vector>
#include<queue>

using namespace std;

class Graph
{
public:
    int V; //顶点vertex个数
    vector<vector<int>>adj; //邻接表 adjacency List

    Graph(int V)
    {
        this->V = V;
        adj.resize(V);
    }

    void addEdge(int u,int v)
    {
        adj[u].push_back(v);
    }

    vector<int> kahnTopologicalSort()
    {
        vector<int>inDegree(V,0);//存储每个顶点的入度
        for(int u = 0;u < V;u++)
        {
            for(int v : adj[u])
            {
                inDegree[v]++;
            }
        }

        queue<int>q; //存储入度为0的顶点(box)
        for(int u = 0;u < V;u++)
        {
            if(inDegree[u] == 0)
                q.push(u);
        }

        vector<int> result; //存储拓扑排序的结果

        while(!q.empty())
        {
            int u = q.front();
            q.pop();
            result.push_back(u);

            for(int v : adj[u])
            {
                if(--inDegree[v] == 0)
                    q.push(v);
            }
        }

        if(result.size() != V)
            result.clear(); //图中存在环
        return result;
    }

};

int main()
{
    int V = 6;
    Graph graph(V);

    //添加图的边
    graph.addEdge(5, 2);
    graph.addEdge(5, 0);
    graph.addEdge(4, 0);
    graph.addEdge(4, 1);
    graph.addEdge(2, 3);
    graph.addEdge(3, 1);

    vector<int> result = graph.kahnTopologicalSort();

    if(result.empty())
        cout << "图中存在环" << endl;
    else
    {
        cout << "拓扑排序结果为：";
        for(int u : result)
            cout << u << " ";
        cout << endl;
    }

    return 0;
}