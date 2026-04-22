// ex7_6_1_matrix_add.cpp
// 矩陣加法：C[i][j] = A[i][j] + B[i][j]

#include <iostream>
#include <iomanip>
using namespace std;

const int N = 3;

void printMatrix(const int m[][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) cout << setw(6) << m[i][j];
        cout << endl;
    }
}

void addMatrix(const int A[][N], const int B[][N], int C[][N]) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            C[i][j] = A[i][j] + B[i][j];
}

int main() {
    int A[N][N] = {{1,2,3},{4,5,6},{7,8,9}};
    int B[N][N] = {{9,8,7},{6,5,4},{3,2,1}};
    int C[N][N] = {};

    addMatrix(A, B, C);

    cout << "矩陣 A：" << endl; printMatrix(A);
    cout << "\n矩陣 B：" << endl; printMatrix(B);
    cout << "\nA + B：" << endl; printMatrix(C);

    return 0;
}
