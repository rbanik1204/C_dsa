#include<stdio.h>
#include<limits.h>
int minDistance(int visited[],int dist[],int V){
    int min = INT_MAX,min_index=-1;
    for(int i=0;i<V;i++){
        if(!visited[i] && dist[i]<min){
            min = dist[i],min_index = i;
        }
    }
    return min_index;
}
void Dijkstra(int V,int graph[][V],int Source){
    int dist[V],visited[V];
    for(int i=0;i<V;i++){
        dist[i] = INT_MAX;
        visited[i] = 0;
    }
    dist[Source] = 0;
    for(int count=0;count<V-1;count++){
        int u = minDistance(visited,dist,V);
        if (u == -1) break;
        visited[u] = 1;

        for(int v=0;v<V;v++){
            if(!visited[v] && graph[u][v] && dist[u]!=INT_MAX && dist[u]+graph[u][v]<dist[v])
                dist[v] = dist[u]+graph[u][v];
        }
    }
    printf("vertex\tDistance from Source vertex %d\n",Source);
    for(int i=0;i<V;i++)
        printf("%d\t%d\n",i,dist[i]);
}
// Driver code(Using Adjacency Matrix)
int main(void){
    int V,E;
    printf("Enter number of vertices & Edges:");
    scanf("%d %d",&V,&E);
    int graph[V][V],u,v,d;
    for(int i=0;i<V;i++)
        for(int j=0;j<V;j++) graph[i][j] = 0;
    printf("Enter in format:(src dest dist)\n");
    for(int i=0;i<E;i++){
        scanf("%d %d %d",&u,&v,&d);
        graph[u][v] = d;
        graph[v][u] = d;
    }
    Dijkstra(V,graph,0);
}