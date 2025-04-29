#include <stdio.h>
#include <stdlib.h>

typedef struct Edge {
    int src, dest, weight;
} Edge;

int compareEdge(const void* a, const void* b) {
    Edge* e1 = (Edge*)a;
    Edge* e2 = (Edge*)b;
    return e1->weight - e2->weight;
}

typedef struct {
    int parent;
    int rank;
} DisjointSet;

int findPar(DisjointSet ds[], int u) {
    if (ds[u].parent != u)
        ds[u].parent = findPar(ds, ds[u].parent);
    return ds[u].parent;
}

void unionByRank(DisjointSet ds[], int u, int v) {
    int pu = findPar(ds, u);
    int pv = findPar(ds, v);

    if (ds[pu].rank < ds[pv].rank)
        ds[pu].parent = pv;
    else if (ds[pu].rank > ds[pv].rank)
        ds[pv].parent = pu;
    else {
        ds[pv].parent = pu;
        ds[pu].rank++;
    }
}

int spanningTree(int V, int** adj[], int* adjSizes) {
    Edge* edges = malloc(sizeof(Edge) * V * V);
    int edgeCount = 0;

    for (int i = 0; i < V; i++) {
        for (int j = 0; j < adjSizes[i]; j++) {
            int adjNode = adj[i][j][0];
            int wt = adj[i][j][1];
            int node = i;

            Edge temp;
            temp.src = node;
            temp.dest = adjNode;
            temp.weight = wt;
            edges[edgeCount++] = temp;
        }
    }

    qsort(edges, edgeCount, sizeof(Edge), compareEdge);

    DisjointSet* ds = malloc(sizeof(DisjointSet) * V);
    for (int i = 0; i < V; i++) {
        ds[i].parent = i;
        ds[i].rank = 0;
    }

    int mstWt = 0;

    for (int i = 0; i < edgeCount; i++) {
        int wt = edges[i].weight;
        int u = edges[i].src;
        int v = edges[i].dest;

        if (findPar(ds, u) != findPar(ds, v)) {
            mstWt += wt;
            unionByRank(ds, u, v);
        }
    }

    free(ds);
    free(edges);
    return mstWt;
}

int main() {
    int V, E;
    printf("Enter number of vertices and edges: ");
    scanf("%d %d", &V, &E);

    // Allocate adjacency list
    int*** adj = (int***)malloc(V * sizeof(int**));
    int* adjSizes = (int*)calloc(V, sizeof(int));

    // Temporary storage to count neighbors
    int** tempCount = (int**)malloc(V * sizeof(int*));
    for (int i = 0; i < V; i++) {
        tempCount[i] = (int*)malloc(V * 2 * sizeof(int));  // max V neighbors, each with pair
    }

    printf("Enter edges in format: src dest weight\n");
    for (int i = 0; i < E; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);

        int sizeU = adjSizes[u];
        tempCount[u][2 * sizeU] = v;
        tempCount[u][2 * sizeU + 1] = w;
        adjSizes[u]++;

        int sizeV = adjSizes[v];
        tempCount[v][2 * sizeV] = u;
        tempCount[v][2 * sizeV + 1] = w;
        adjSizes[v]++;
    }

    // Now convert to proper adj list
    for (int i = 0; i < V; i++) {
        adj[i] = (int**)malloc(adjSizes[i] * sizeof(int*));
        for (int j = 0; j < adjSizes[i]; j++) {
            adj[i][j] = (int*)malloc(2 * sizeof(int));
            adj[i][j][0] = tempCount[i][2 * j];
            adj[i][j][1] = tempCount[i][2 * j + 1];
        }
        free(tempCount[i]);
    }
    free(tempCount);

    int mstWt = spanningTree(V, adj, adjSizes);
    printf("Weight of MST: %d\n", mstWt);

    // Free memory
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < adjSizes[i]; j++) {
            free(adj[i][j]);
        }
        free(adj[i]);
    }
    free(adj);
    free(adjSizes);

    return 0;
}
