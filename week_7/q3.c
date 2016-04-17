// Author: Utkarsh
// Reg no: 20142027
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
int **R;
int **A;
int **B;
int n;
struct ij{
    int row;
    int col;
};
void *mul_row_col(void *row_col){
    struct ij *r_c = row_col ;
    int i = 0;
    int j = 0;
    for(;i<n;i++){
        R[r_c->row][r_c->col] += A[r_c->row][i]*B[i][r_c->col];
    }
    pthread_exit(NULL);
}

int main(){
	struct timeval t_start, t_end;
    int m, l, i, j;
    printf("Enter the dimensions of matrix (respectively) m, n, l : ");
    scanf("%d %d %d",&m,&n,&l);
    pthread_t **threads = malloc(sizeof(pthread_t)*m);
    R = (int **)malloc(sizeof(int *)*m);
    A = (int **)malloc(sizeof(int *)*m);
    B = (int **)malloc(sizeof(int *)*n);
    for(i=0;i<m;i++){
        A[i] = (int *)malloc(sizeof(int)*n);
        R[i] = (int *)malloc(sizeof(int)*l);
        threads[i] = (pthread_t *)malloc(sizeof(int)*l);
    }
    for(i=0;i<n;i++){
        B[i] = (int *)malloc(sizeof(int)*l);
    }
    printf("Enter the value of array A:");
    for(i=0;i<m;i++){
        for(j=0;j<n;j++){
            scanf("%d",&A[i][j]);
        }
    }
    printf("Enter the value of array B:");
    for(i=0;i<n;i++){
        for(j=0;j<l;j++){
            scanf("%d",&B[i][j]);
        }
    }
    for(i=0;i<m;i++){
        for(j=0;j<l;j++){
            R[i][j] = 0;
        }
    }
    int error_code;
    struct ij thread_arg;
    for(i=0;i<m;i++){
        for(j=0;j<l;j++){
            thread_arg.row = i;
            thread_arg.col = j;
            error_code = pthread_create(&threads[i][j], NULL, mul_row_col, (void *)&thread_arg );
            pthread_join(threads[i][j],NULL);
            if(error_code){
                printf("Error %d",error_code);
            }
        }
    }
    for(i=0;i<m;i++){
        for(j=0;j<l;j++){
            printf("%d ",R[i][j]);
        }
        printf("\n");
    }
}
