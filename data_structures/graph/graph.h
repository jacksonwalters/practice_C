// graph.h
#ifndef GRAPH_H
#define GRAPH_H

#define MAX_VERTICES 100
#define INF 1000000

typedef struct AdjNode {
    int vertex;
    int weight;
    struct AdjNode* next;
} AdjNode;

typedef struct Graph {
    int num_vertices;
    AdjNode* adj_lists[MAX_VERTICES];
} Graph;

Graph* create_graph(int vertices);
void add_edge(Graph* graph, int src, int dest, int weight);
void dijkstra(Graph* graph, int start_vertex, int* distances);
void free_graph(Graph* graph);

#endif

#ifndef BELLMAN_FORD_H
#define BELLMAN_FORD_H

#define MAX_VERTICES 100
#define INF 1000000

typedef struct Edge {
    int src, dest, weight;
} Edge;

typedef struct BellmanGraph {
    int num_vertices, num_edges;
    Edge* edges;
} BellmanGraph;

BellmanGraph* create_bellman_graph(int vertices, int edges);
void add_bellman_edge(BellmanGraph* graph, int idx, int src, int dest, int weight);
int bellman_ford(BellmanGraph* graph, int src, int* distances);
void free_bellman_graph(BellmanGraph* graph);

#endif