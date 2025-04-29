#include<stdio.h>
#include<String.h>
#include<stdlib.h>
#include<errno.h>
#include<limits.h>
#define VERTICES(V)  \
    do{              \
       printf("Enter value of "#V":");\
       scanf("%d",&V); \
       }while(0) 
typedef struct node{
    int data;
    int weight;
    struct node* next;
}NODE;
NODE* createnode(int var,int w){
    NODE* newnode = (NODE*)calloc(1,sizeof(NODE));
    newnode->data = var;
    newnode->weight = w;
    newnode->next = NULL;
    return newnode;
}
// Static Variables size must be known at compile time
    void addEdge(NODE** adj,int s,int d,int w){
        NODE *newnode = createnode(d, w);
        newnode->next = adj[s];
        adj[s] = newnode;
    
        NODE *newnode2 = createnode(s, w);
        newnode2->next = adj[d];
        adj[d] = newnode2;
}
void displayGraph(NODE**adj,int V){
    NODE* temp = NULL;
    printf("Graph Representation is as follows:\n");
    for(int i=0;i<V;i++){
        temp = adj[i];
        printf("%d:",i);
        while(temp!=NULL){
            printf("(%d)->%d",temp->weight,temp->data);
            temp = temp->next;
        }
        printf("\n");
    }
}
int minkey(int *key,int *visited,int V){
    int min = INT_MAX;int min_index = -1;
    for(int i=0;i<V;i++){
        if(!visited[i] && key[i]<min){
            min = key[i];
            min_index = i;
        }
    }
    return min_index;
}
void prims(NODE** adj,int V){
    int *parent = (int*)malloc(V*sizeof(int));
    int *visited = (int*)malloc(V*sizeof(int));
    int *key = (int*)malloc(V*sizeof(int));
    for(int i=0;i<V;i++){
        parent[i] = -1;
        visited[i] = 0;
        key[i] = INT_MAX;
    }
    key[0] = 0; // Start from vertex 0(this array stores min key weights)
    for(int count = 0;count<V-1;count++){
        int u = minkey(key,visited,V);// min vertex not in MST
        visited[u] = 1; // u is visited
        NODE *temp = adj[u];
        while(temp!= NULL){
            int v = temp->data;
            int w = temp->weight;
            if(!visited[v] && w<key[v]){
                key[v] = w;
                parent[v] = u;
            }
            temp = temp->next;
        }
    }
    for(int i=0;i<V;i++){
    printf("%d-%d,weight:%d\n",parent[i],i,key[i]);    
    }free(key);free(visited);free(parent);
}
int main(){
    int V,e,u,v,w;
    VERTICES(V);
    NODE** adj =(NODE**)realloc(NULL,V*sizeof(NODE*));
    if(!adj) {
        printf("Error at runtime:%s",strerror(errno));
        exit(1);
    }
    for (int i = 0; i < V; i++) {
        adj[i] = NULL;
    }        
    printf("Enter number of edges:");
    scanf("%d",&e);
    //(please follow the syntax(u: v: w:))
    for(int i=1;i<=e;i++){
        printf("Enter values of u,v,w:");
        scanf(" %d %d %d",&u,&v,&w);
        addEdge(adj,u,v,w);
    }
    displayGraph(adj,V);
    prims(adj,V);
    free(adj);
}