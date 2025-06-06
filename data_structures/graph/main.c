// main.c
#include <stdio.h>
#include "graph.h"

int main() {
    Graph* g = create_graph(6);

    add_edge(g, 0, 1, 7);
    add_edge(g, 0, 2, 9);
    add_edge(g, 0, 5, 14);
    add_edge(g, 1, 2, 10);
    add_edge(g, 1, 3, 15);
    add_edge(g, 2, 3, 11);
    add_edge(g, 2, 5, 2);
    add_edge(g, 3, 4, 6);
    add_edge(g, 4, 5, 9);

    int distances[MAX_VERTICES];
    dijkstra(g, 0, distances);

    printf("Shortest distances from vertex 0:\n");
    for (int i = 0; i < g->num_vertices; i++)
        printf("To %d: %d\n", i, distances[i]);

    free_graph(g);

    // 5 vertices, 8 edges
    BellmanGraph* h = create_bellman_graph(5, 8);

    add_bellman_edge(h, 0, 0, 1, -1);
    add_bellman_edge(h, 1, 0, 2, 4);
    add_bellman_edge(h, 2, 1, 2, 3);
    add_bellman_edge(h, 3, 1, 3, 2);
    add_bellman_edge(h, 4, 1, 4, 2);
    add_bellman_edge(h, 5, 3, 2, 5);
    add_bellman_edge(h, 6, 3, 1, 1);
    add_bellman_edge(h, 7, 4, 3, -3);

    // int distances[MAX_VERTICES];

    if (bellman_ford(h, 0, distances)) {
        printf("Vertex distances from source 0:\n");
        for (int i = 0; i < h->num_vertices; i++) {
            printf("To %d: %d\n", i, distances[i]);
        }
    } else {
        printf("Negative-weight cycle detected!\n");
    }

    free_bellman_graph(h);
    return 0;
}
