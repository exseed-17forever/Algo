#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 100

typedef struct Node {
    int value;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
} NodeList;

typedef struct {
    int numNodes;
    NodeList adjacencyList[MAX_NODES];
} Graph;

Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

Graph* createGraph(int numNodes) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numNodes = numNodes;
    for (int i = 0; i < numNodes; ++i) {
        graph->adjacencyList[i].head = NULL;
    }
    return graph;
}

void addEdge(Graph* graph, int src, int dest) {
    Node* newNode = createNode(dest);
    newNode->next = graph->adjacencyList[src].head;
    graph->adjacencyList[src].head = newNode;
}

void bfsShortestPaths(Graph* graph, int startNode) {
    int numNodes = graph->numNodes;
    int visited[MAX_NODES] = {0};
    int distance[MAX_NODES];
    int parent[MAX_NODES];

    for (int i = 0; i < numNodes; ++i) {
        distance[i] = -1; // Initialize distances as -1 (unreachable)
        parent[i] = -1;   // Initialize parents as -1
    }

    visited[startNode] = 1;
    distance[startNode] = 0;

    Node* queue = createNode(startNode);
    Node* tail = queue;

    while (queue != NULL) {
        int currentNode = queue->value;
        queue = queue->next;
        
        Node* currentNeighbor = graph->adjacencyList[currentNode].head;
        while (currentNeighbor != NULL) {
            int neighbor = currentNeighbor->value;
            if (!visited[neighbor]) {
                visited[neighbor] = 1;
                distance[neighbor] = distance[currentNode] + 1;
                parent[neighbor] = currentNode;
                tail->next = createNode(neighbor);
                tail = tail->next;
            }
            currentNeighbor = currentNeighbor->next;
        }
    }

    free(queue);

    printf("Node\tDistance\tParent\n");
    for (int i = 0; i < numNodes; ++i) {
        printf("%d\t%d\t\t%d\n", i, distance[i], parent[i]);
    }
}

int main() {
    int numNodes = 7;
    Graph* graph = createGraph(numNodes);

    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 2, 4);
    addEdge(graph, 3, 5);
    addEdge(graph, 4, 5);
    addEdge(graph, 5, 6);

    int startNode = 0;
    bfsShortestPaths(graph, startNode);

    // Free memory
    for (int i = 0; i < numNodes; ++i) {
        Node* current = graph->adjacencyList[i].head;
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(graph);

    return 0;
}
