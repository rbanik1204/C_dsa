#include<stdio.h>
#include<limits.h>
#include<stdlib.h>
#define ASK_SIZE(msg,SIZE) \
(printf("%s",msg),scanf("%d",&SIZE))
int matrixchainMul(int bracket[][],int **dp,int *array,int i,int j){
    if(i == j) return 0;
    if(dp[i][j]!=-1) return dp[i][j];
    int mini = INT_MAX;
    for(int k=i;k<j;k++){
        int steps = (array[i-1]*array[k]*array[j]) + matrixchainMul(bracket,dp,array,i,k)+matrixchainMul(bracket,dp,array,k+1,j);
        if(steps<mini) {
            mini = steps;
            bracket[i][j] = k;
        }
    }
    return (dp[i][j] = mini);
}
void parenthesization(int bracket[][],char name,int i, int j){
    if(i==j){
        printf("%c",name+(i-1));
        return;
    }
    printf("(");
    parenthesization(bracket,name,i,bracket[i][j]);
    parenthesization(bracket,name,bracket[i][j]+1,j);
    printf(")");
}
int main(){
    int *array,SIZE;
    int bracket[SIZE][SIZE];
    ASK_SIZE("Enter number of dimensions:",SIZE);
    array = calloc(SIZE,sizeof(int));
    int **dp = (int**) malloc(SIZE * sizeof(int*));
    for(int i = 0; i < SIZE; i++) 
        dp[i] = (int*) malloc(SIZE * sizeof(int));
    printf("Enter dimensions:");
    for(int i=0;i<SIZE;i++)
        scanf("%d",array+i);
    for(int i =0 ;i<SIZE;i++)
        for(int j=0;j<SIZE;j++){
            dp[i][j] = -1;
        }
    int cost = matrixchainMul(bracket,dp,array,1,SIZE-1);
    printf("Minimal cost of given matrices:%d",cost);
    printf("Corresponding parenthesization:");
    parenthesization(bracket,'A',1,SIZE-1);
}