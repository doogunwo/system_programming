/*
두 행렬의 크기를 입력받아서 필요한 만큼의 메모리를 동적으로 할당하여 행렬
의 내용을 저장하고 두 행렬을 더하는 프로그램을 작성하시오.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int **createMatrix(int rows, int cols) {
    int **matrix = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int *)malloc(cols * sizeof(int));
    }
    return matrix;
}

void fillMatrix(int **matrix,int rows,int cols){
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = rand() % 3;
        }
    }
}  

void showMatrix(int **matrix,int rows, int cols){
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}


int main(){
    
    int matrix1_x = 0;
    int matrix1_y = 0;
    srand(time(NULL));

    printf("행렬의 크기 입력:");
    scanf("%d %d",&matrix1_x,&matrix1_y);

    int **matrix1 =(int **)malloc(matrix1_x * sizeof(int *));
    fillMatrix(matrix1, matrix1_x, matrix1_y);

     for (int i = 0; i < matrix1_x; i++) {
        for (int j = 0; j < matrix1_y; j++) {
            printf("%d ", matrix1[i][j]);
        }
        printf("\n");
    }
    showMatrix(matrix1,matrix1_x,matrix1_y);

    for (int i = 0; i < matrix1_y; i++) {
        free(matrix1[i]);
    }
    free(matrix1);

    return 0;

}   