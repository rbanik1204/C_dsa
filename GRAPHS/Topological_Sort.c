#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define V 4
int count = 0;
typedef struct node{
    int data;
    struct node* next;
}NODE;
typedef struct{
    int *arr;
    int top;
}STACK;
NODE* createnode(int value){
    NODE* newnode = (NODE*)malloc(sizeof(NODE));
    newnode->data = value;
    newnode->next = NULL;
    return newnode;
}
void addEdge(NODE* adj[],int u,int v){
    NODE* newnode = createnode(v);
    newnode->next = adj[u];
    adj[u] = newnode;
}
STACK* createstack(){
    STACK* stack = (STACK*)malloc(sizeof(STACK));
    stack->arr = (int*)malloc(V*sizeof(int));
    stack->top = -1;
    return stack;
}
void DFS(NODE** adj,int current,bool *visited,STACK* stack){
    NODE *temp = adj[current];
    visited[current] = true;
    while(temp){
        int adjacent = temp->data;
        if(!visited[adjacent]){
            DFS(adj,adjacent,visited,stack);
        }
        temp = temp->next;
    }
    stack->arr[++stack->top] = current;
}
void dfstraverse(NODE* adj[],STACK* stack){
    bool *visited = (bool*)malloc((V+1)*sizeof(bool));
    for(int i=0;i<V+1;i++) visited[i] = false;
    for(int i=1;i<=V;i++){
        if(!visited[i]){
            DFS(adj,i,visited,stack);
        }
    }
    printf("Topological sort:");
    while(stack->top != -1){
        printf("%d ",stack->arr[stack->top--]);
    }
}
int main(void){
    NODE** adj = (NODE**)malloc((V+1)*sizeof(NODE*));
    STACK* stack = createstack();
    for(int i=0;i<V+1;i++) adj[i] = NULL;
    addEdge(adj,1,2);
    addEdge(adj,1,4);
    addEdge(adj,4,2);
    addEdge(adj,3,4);
    addEdge(adj,3,2);
    dfstraverse(adj,stack);
}