#include<stdio.h>
#include<limits.h>
#define ASK_SIZE(msg,SIZE) \
(printf("%s",msg),scanf("%d",&SIZE))

void init_graph(int V,int graph[V][V]){
    for(int i=0;i<V;i++){
        for(int j=0;j<V;j++){
            if(i == j) graph[i][j] = 0;
            else graph[i][j] = INT_MAX;
        }
    }
}
void display(int V,int graph[V][V],int src,int dist[V]){
    printf("Distance from %d are :",src);
    for(int i=0;i<V;i++){
        if(dist[i] != INT_MAX)
        printf("%d\t",dist[i]);
    }
}
void Bellman_Ford(int V,int graph[V][V],int src){
    int dist[V];
    for(int i=0;i<V;i++){
        dist[i] = INT_MAX;
    }
    dist[src] = 0;
    for(int v=0;v<V-1;v++){
        for(int i=0;i<V;i++){
            for(int j=0;j<V;j++){
                if(graph[i][j]!= INT_MAX && dist[j]>dist[i]+graph[i][j]){
                    dist[j] = dist[i]+graph[i][j];
                }
            }
        }
    }
    //Check if graph has neg cycle or not
    for(int i=0;i<V;i++){
        for(int j=0;j<V;j++){
            if(graph[i][j]!= INT_MAX && dist[j]>dist[i]+graph[i][j]){
                printf("Negative Cycle is present!\n");
                return;
            }
        }
    }
    display(V,graph,src,dist);
}
int main(void){
    int V,u,v,w,E;
    ASK_SIZE("Enter Number of Vertices:",V);
    int graph[V][V];
    init_graph(V,graph);
    printf("Enter number of Edges:");
    scanf("%d",&E);
    printf("Enter in format:(src dest Distance)\n");
    for(int i=0;i<E;i++){
        scanf("%d %d %d",&u,&v,&w);
        graph[u][v] = w;
    }
    int source;
    printf("Enter starting Vetex:");
    scanf("%d",&source);
    Bellman_Ford(V,graph,source);
}