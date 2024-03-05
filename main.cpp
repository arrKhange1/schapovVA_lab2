#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

// ������� ��� �������� ������� �������� 4 ��
int** createMatrix(int size) {
    int** matrix = new int* [size];
    for (int i = 0; i < size; ++i)
        matrix[i] = new int[size];
    return matrix;
}

// ������� ��� �������� ������� �� ������
void deleteMatrix(int** matrix, int size) {
    for (int i = 0; i < size; ++i)
        delete[] matrix[i];
    delete[] matrix;
}

void fillMatrixWithZeroes(int** matrix, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            matrix[i][j] = 0;
        }
    }
}

// ������� ��� ���������� ������� ���������� ����������
void fillMatrix(int** matrix, int size) {
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            matrix[i][j] = rand() % 100; // ��������� �������� �� 0 �� 99
}

// ������� ��� ������������ ������ ������� ������ �� �������
int** multiplyMatricesRowColumn(int** matrix1, int** matrix2, int size) {
    int** result = createMatrix(size);
    fillMatrixWithZeroes(result, size);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            for (int k = 0; k < size; ++k) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
    return result;
}

// ������� ��� ������������ ������ ������� ������ �� ������
int** multiplyMatricesRowRow(int** matrix1, int** matrix2, int size) {
    int** result = createMatrix(size);
    fillMatrixWithZeroes(result, size);
    for (int i = 0; i < size; ++i) {
        for (int k = 0; k < size; ++k) {
            for (int j = 0; j < size; ++j) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
    return result;
}

// ������� ��� ������������ ������ ������� ������� �� �������
int** multiplyMatricesColumnColumn(int** matrix1, int** matrix2, int size) {
    int** result = createMatrix(size);
    fillMatrixWithZeroes(result, size);
    for (int k = 0; k < size; ++k) {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
    return result;
}

int main() {
    const int matrixSize = 2000; // 2062x2062 ������� ~ 17 ��

    srand(time(0)); // ������������� ���������� ��������� �����

    // �������� � ���������� ������
    int** matrix1 = createMatrix(matrixSize);
    int** matrix2 = createMatrix(matrixSize);
    fillMatrix(matrix1, matrixSize);
    fillMatrix(matrix2, matrixSize);

    // ����� ������� ���������� ������������ ������ ������� ������ �� �������
    auto start = high_resolution_clock::now(); // ������ ������ �������
    int** result1 = multiplyMatricesRowColumn(matrix1, matrix2, matrixSize);
    auto stop = high_resolution_clock::now(); // ����� ������ �������
    auto duration1 = duration_cast<milliseconds>(stop - start); // ���������� ������������

    // ����� ������� ���������� ������������ ������ ������� ������ �� ������
    start = high_resolution_clock::now(); // ������ ������ �������
    int** result2 = multiplyMatricesRowRow(matrix1, matrix2, matrixSize);
    stop = high_resolution_clock::now(); // ����� ������ �������
    auto duration2 = duration_cast<milliseconds>(stop - start); // ���������� ������������

    // ����� ������� ���������� ������������ ������ ������� �������� ������������
    start = high_resolution_clock::now(); // ������ ������ �������
    int** result3 = multiplyMatricesColumnColumn(matrix1, matrix2, matrixSize);
    stop = high_resolution_clock::now(); // ����� ������ �������
    auto duration3 = duration_cast<milliseconds>(stop - start); // ���������� ������������

    cout << "Row * Column: " << duration1.count() << " ms" << endl;
    cout << "Row * Row: " << duration2.count() << " ms" << endl;
    cout << "Column * Column: " << duration3.count() << " ms" << endl;

    // ������������ ������
    deleteMatrix(matrix1, matrixSize);
    deleteMatrix(matrix2, matrixSize);
    deleteMatrix(result1, matrixSize);
    deleteMatrix(result2, matrixSize);
    deleteMatrix(result3, matrixSize);

    return 0;
}
