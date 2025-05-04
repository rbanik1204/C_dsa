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
void display(int V,int graph[V][V]){
    printf("src\tdest\tDist\n");
    for(int i=0;i<V;i++){
        for(int j=0;j<V;j++){
            if(graph[i][j]!= INT_MAX)
                printf("%d\t%d\t%d\n",i,j,graph[i][j]);
        }
    }
}
void Floyd_Warshall(int V,int graph[V][V]){
    for(int k=0;k<V;k++){
        for(int i=0;i<V;i++){
            for(int j=0;j<V;j++){
                if(graph[i][k] != INT_MAX && graph[k][j] != INT_MAX && graph[i][j]>graph[i][k]+graph[k][j])
                    graph[i][j] = graph[i][k]+graph[k][j];
            }
        }
    }
    for(int i=0;i<V;i++){
        if(graph[i][i]<0){
            printf("Graph Has Negative Cycle");
        }
    }
    display(V,graph);
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
    Floyd_Warshall(V,graph);
}