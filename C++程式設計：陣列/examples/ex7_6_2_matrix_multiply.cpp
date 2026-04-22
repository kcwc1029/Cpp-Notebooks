// ex7_6_2_matrix_multiply.cpp
// 矩陣乘法：A(M×N) × B(N×P) = C(M×P)
// C[i][j] = Σ A[i][k] * B[k][j]

#include <iostream>
#include <iomanip>
using namespace std;

const int M = 2, N = 3, P = 2;

void multiplyMatrix(const int A[][N], const int B[][P], int C[][P]) {
    for (int i = 0; i < M; i++)
        for (int j = 0; j < P; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++)
                C[i][j] += A[i][k] * B[k][j];
        }
}

int main() {
    int A[M][N] = {{1,2,3},{4,5,6}};
    int B[N][P] = {{7,8},{9,10},{11,12}};
    int C[M][P] = {};

    multiplyMatrix(A, B, C);

    cout << "A（2×3）：" << endl;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) cout << setw(5) << A[i][j];
        cout << endl;
    }

    cout << "\nB（3×2）：" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < P; j++) cout << setw(5) << B[i][j];
        cout << endl;
    }

    cout << "\nA × B（2×2）：" << endl;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < P; j++) cout << setw(5) << C[i][j];
        cout << endl;
    }

    return 0;
}
