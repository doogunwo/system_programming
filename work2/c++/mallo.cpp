/*
두 행렬의 크기를 입력받아서 필요한 만큼의 메모리를 동적으로 할당하여 행렬
의 내용을 저장하고 두 행렬을 더하는 프로그램을 작성하시오.

8번 문제를 C++ STL 의 vector 컨테이너로 구현하시오


*/

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

vector<vector<int> > createMatrix_v(int rows, int cols) {
    vector<vector<int> > matrix(rows, vector<int>(cols, 0));
    return matrix;
}

void fillMatrix(vector<vector<int> >& matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = rand() % 3 + 1;
        }
    }
}



int main(){
    cout << "doogunwo";
    srand(static_cast<unsigned>(time(nullptr)));
    int matrix1_x = 0;
    int matrix1_y = 0;

    cout << "1.matrix 행렬의 크기 입력: ";
    cin >> matrix1_x >>matrix1_y;

    vector<vector<int> > matrix1 = createMatrix_v(matrix1_x,matrix1_y);
    fillMatrix(matrix1,matrix1_x,matrix1_y);

    vector<vector<int> > matrix2 = createMatrix_v(matrix1_x, matrix1_y);
    fillMatrix(matrix2, matrix1_x, matrix1_y);

    vector<vector<int> > result = createMatrix_v(matrix1_x, matrix1_y);

    for (int i = 0; i < matrix1_x; i++) {
        for (int j = 0; j < matrix1_y; j++) {
            result[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }
    for (int i = 0; i < matrix1_x; i++) {
        for (int j = 0; j < matrix1_y; j++) {
            cout << result[i][j] << " ";
        }
        cout << endl;
    }

    matrix1.clear();
    matrix2.clear();
    result.clear();

}