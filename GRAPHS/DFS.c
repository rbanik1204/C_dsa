#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
typedef struct node{
    int data;
    struct node* next;
}NODE;

typedef struct list{
    NODE* head;
}LIST;

typedef struct graph{
    int vertices;
    LIST* array;
}GRAPH;
GRAPH* createGraph(GRAPH* graph,int V){
    graph = (GRAPH*)malloc(sizeof(GRAPH));
    graph->array = (LIST*)malloc(V*sizeof(LIST));
    graph->vertices = V;
    for(int i=0;i<V;i++)
        graph->array[i].head = NULL;
    return graph;
}
NODE* createnode(int value){
    NODE* newnode = (NODE*)malloc(sizeof(NODE));
    newnode->data = value;
    newnode->next = NULL;
    return newnode;
}
void addEdge(GRAPH* graph,int u,int v){
    NODE* newnode = createnode(v);
    newnode->next = graph->array[u].head;
    graph->array[u].head = newnode;
    NODE* new = createnode(u);
    new->next = graph->array[v].head;
    graph->array[v].head = new;
}
void dfs(GRAPH* graph,int node,bool *visited){
    visited[node] = true;
    printf("%d ",node);
    NODE* current = graph->array[node].head;
    while(current!= NULL){
        int adjacent = current->data;
        if(!visited[adjacent]){
            dfs(graph,adjacent,visited);
        }
        current = current->next;
    }

}
void dfsTraversal(GRAPH* graph,int *order,int V){
    bool *visited = (bool*)malloc(V*sizeof(bool));
    for(int i=0;i<V;i++)
        visited[i] = false;
    for(int i=0;i<V;i++){
        if(!visited[order[i]]){
            dfs(graph,order[i],visited);
        }
    }
}
int main(void){
    int V = 4;
    GRAPH *graph = createGraph(graph,V);
    addEdge(graph,2,0);
    addEdge(graph,1,2);
    addEdge(graph,0,1);
    addEdge(graph,3,3);
    addEdge(graph,1,3);
    int order[] = {0,1,2,3};
    int ordersize = sizeof(order)/sizeof(order[0]);
    printf("Corresponding dfs Traversal:");
    dfsTraversal(graph,order,ordersize);
    free(graph->array);
    free(graph);
}
