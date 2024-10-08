#include <stdio.h>

struct Node {
    int set;
} nodes[100];

struct Edge {
    int u, v, dist, selected;
} edges[100];

int edge_count = 0;

void getEdges(int idx, int total) {
    int i;
    for (i = idx + 1; i < total; i++) {
        printf("Enter distance between vertex %c and %c: ", idx + 65, i + 65);
        scanf("%d", &edges[edge_count].dist);
        edges[edge_count].u = idx;
        edges[edge_count].v = i;
        edges[edge_count].selected = -1;
        edge_count++;
    }
}

void initialize(int total) {
int i;
    for ( i = 0; i < total; i++) nodes[i].set = i;
}

void sortEdges() {
    int i, j;
    for (i = 0; i < edge_count - 1; i++) {
        for (j = 0; j < edge_count - i - 1; j++) {
            if (edges[j].dist > edges[j + 1].dist) {
                struct Edge temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;
            }
        }
    }
}

int main() {
    int total_vertices, edges_selected = 0, i, j;
    printf("Enter the number of vertices: ");
    scanf("%d", &total_vertices);

    for (i = 0; i < total_vertices; i++) getEdges(i, total_vertices);
    initialize(total_vertices);
    sortEdges();

    printf("Sorted order of edges:\n");
    for (i = 0; i < edge_count; i++) {
        printf("Edge %d: %c <--> %c, Distance: %d\n", i, edges[i].u + 65, edges[i].v + 65, edges[i].dist);
    }

    for (i = 0; edges_selected < total_vertices - 1 && i < edge_count; i++) {
        int u_set = nodes[edges[i].u].set, v_set = nodes[edges[i].v].set;
        if (u_set != v_set) {
            edges[i].selected = 1;
            edges_selected++;
            for (j = 0; j < total_vertices; j++) {
                if (nodes[j].set == v_set) nodes[j].set = u_set;
            }
        }
    }

    printf("\nMinimal Spanning Tree:\n");
    for (i = 0; i < edge_count; i++) {
        if (edges[i].selected == 1) {
            printf("%c <--> %c, Distance: %d\n", edges[i].u + 65, edges[i].v + 65, edges[i].dist);
        }
    }
    return 0;
}
