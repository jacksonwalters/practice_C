// graph.c
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "graph.h"

AdjNode* create_node(int vertex, int weight) {
    AdjNode* node = malloc(sizeof(AdjNode));
    node->vertex = vertex;
    node->weight = weight;
    node->next = NULL;
    return node;
}

Graph* create_graph(int vertices) {
    Graph* graph = malloc(sizeof(Graph));
    graph->num_vertices = vertices;
    for (int i = 0; i < vertices; i++)
        graph->adj_lists[i] = NULL;
    return graph;
}

void add_edge(Graph* graph, int src, int dest, int weight) {
    AdjNode* node = create_node(dest, weight);
    node->next = graph->adj_lists[src];
    graph->adj_lists[src] = node;

    node = create_node(src, weight);  // undirected
    node->next = graph->adj_lists[dest];
    graph->adj_lists[dest] = node;
}

int extract_min(int* dist, int* visited, int num_vertices) {
    int min_dist = INF;
    int min_vertex = -1;
    for (int i = 0; i < num_vertices; i++) {
        if (!visited[i] && dist[i] < min_dist) {
            min_dist = dist[i];
            min_vertex = i;
        }
    }
    return min_vertex;
}

void dijkstra(Graph* graph, int start_vertex, int* distances) {
    int visited[MAX_VERTICES] = {0};
    for (int i = 0; i < graph->num_vertices; i++)
        distances[i] = INF;
    distances[start_vertex] = 0;

    for (int i = 0; i < graph->num_vertices; i++) {
        int u = extract_min(distances, visited, graph->num_vertices);
        if (u == -1) break;
        visited[u] = 1;

        AdjNode* neighbor = graph->adj_lists[u];
        while (neighbor) {
            int v = neighbor->vertex;
            int weight = neighbor->weight;
            if (!visited[v] && distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
            }
            neighbor = neighbor->next;
        }
    }
}

void free_graph(Graph* graph) {
    for (int i = 0; i < graph->num_vertices; i++) {
        AdjNode* node = graph->adj_lists[i];
        while (node) {
            AdjNode* next = node->next;
            free(node);
            node = next;
        }
    }
    free(graph);
}

// Add to graph.c
#include <stdbool.h>

BellmanGraph* create_bellman_graph(int vertices, int edges) {
    BellmanGraph* graph = malloc(sizeof(BellmanGraph));
    graph->num_vertices = vertices;
    graph->num_edges = edges;
    graph->edges = malloc(edges * sizeof(Edge));
    return graph;
}

void add_bellman_edge(BellmanGraph* graph, int idx, int src, int dest, int weight) {
    graph->edges[idx].src = src;
    graph->edges[idx].dest = dest;
    graph->edges[idx].weight = weight;
}

int bellman_ford(BellmanGraph* graph, int src, int* distances) {
    int V = graph->num_vertices;
    int E = graph->num_edges;

    for (int i = 0; i < V; i++)
        distances[i] = INF;
    distances[src] = 0;

    // Relax all edges V-1 times
    for (int i = 0; i < V - 1; i++) {
        for (int j = 0; j < E; j++) {
            int u = graph->edges[j].src;
            int v = graph->edges[j].dest;
            int weight = graph->edges[j].weight;
            if (distances[u] != INF && distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
            }
        }
    }

    // Check for negative-weight cycles
    for (int j = 0; j < E; j++) {
        int u = graph->edges[j].src;
        int v = graph->edges[j].dest;
        int weight = graph->edges[j].weight;
        if (distances[u] != INF && distances[u] + weight < distances[v]) {
            return 0; // Negative cycle found
        }
    }

    return 1; // Success
}

void free_bellman_graph(BellmanGraph* graph) {
    free(graph->edges);
    free(graph);
}
