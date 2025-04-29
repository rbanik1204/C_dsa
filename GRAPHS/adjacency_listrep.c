#include<stdio.h>
#include<stdlib.h>
#define V 4
typedef struct node{
    int data;
    int weight;
    struct node *next;
}NODE;
NODE* createnode(int val,int w){
    NODE* newnode =(NODE*)realloc(NULL,sizeof(NODE));
    newnode->data = val;
    newnode->weight = w;
    newnode->next = NULL;
    return newnode;
}
//array[i] = *(array+i) = *(i+array)= i[array] we also know array = &array[0] = 100 , *(array+i)
void addEdge(NODE**adj,int i,int j,int w){
    NODE* newnode = createnode(j,w);
    newnode->next = adj[i];
    adj[i] = newnode;
    NODE* new = createnode(i,w);
    new->next =  adj[j];
    adj[j] = new;
}
void displayGraph(NODE** adj){
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
int main(void){
    static NODE* adj[V];
    addEdge(adj,0,1,4);
    addEdge(adj,0,2,5);
    addEdge(adj,1,2,6);
    addEdge(adj,2,3,7);
    displayGraph(adj);    
}