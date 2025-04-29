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
    NODE* node;
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
void Push(int val,STACK* stack){
    stack[count].node = (NODE*)malloc(sizeof(NODE));
    stack[count].node->data = val;
    stack[count].top = count++;
}
void DFS(NODE** adj,int current,bool *visited,STACK* stack){
    NODE *temp = adj[current];
    Push(current,stack);
    while(temp){
        int adjacent = temp->data;
        if(!visited[adjacent]){
            DFS(adj,current,visited,stack);
        }
        temp = temp->next;
    }
}
STACK* dfstraverse(NODE* adj[]){
    STACK* stack = (STACK*)malloc(V*sizeof(STACK));
    bool *visited = (bool*)malloc((V+1)*sizeof(bool));
    for(int i=0;i<V+1;i++) visited[i] = false;
    for(int i=1;i<=V;i++){
        if(!visited[i]){
            DFS(adj,i,visited,stack);
        }
    }
    printf("Topological sort:");
    for(int i=V-1;i>=0;i--){
        printf("%d ",stack[i].node->data);
        stack[i].top = -1;
    }
}
int main(void){
    NODE** adj = (NODE**)malloc((V+1)*sizeof(NODE*));
    for(int i=0;i<V+1;i++) adj[i] = NULL;
    addEdge(adj,1,2);
    addEdge(adj,1,4);
    addEdge(adj,4,2);
    addEdge(adj,3,4);
    addEdge(adj,3,2);
    dfstraverse(adj);

}