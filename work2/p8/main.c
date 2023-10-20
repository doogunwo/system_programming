#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 행렬을 생성하고 초기화하는 함수
int **createMatrix(int rows, int cols) {
    int **matrix = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int *)malloc(cols * sizeof(int));
    }
    return matrix;
}

// 행렬에 랜덤 값을 할당하는 함수
void fillMatrix(int **matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = rand() % 3;
        }
    }
}

int main() {
    int matrix1_x = 0;
    int matrix1_y = 0;
    srand(time(NULL));

    printf("1. matrix1 행렬의 크기 입력: ");
    scanf("%d %d", &matrix1_x, &matrix1_y);

    int **matrix1;

    // 행렬을 생성하고 초기화하는 함수 호출
    matrix1 = createMatrix(matrix1_x, matrix1_y);
    matrix2 = createMatrix(matrix1_x, matrix1_y);
    // 행렬에 값을 할당하는 함수 호출
    fillMatrix(matrix1, matrix1_x, matrix1_y);
    fillMatrix(matrix2, matrix1_x, matrix1_y);

    for (int i = 0; i < matrix1_x; i++) {
        for (int j = 0; j < matrix1_y; j++) {
            printf("%d ", matrix1[i][j]);
        }
        printf("\n");
    }

    

    // 메모리 해제
    for (int i = 0; i < matrix1_x; i++) {
        free(matrix1[i]);
    }
    free(matrix1);

    return 0;
}
