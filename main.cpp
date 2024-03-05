#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Функция для создания матрицы размером 4 МБ
int** createMatrix(int size) {
    int** matrix = new int* [size];
    for (int i = 0; i < size; ++i)
        matrix[i] = new int[size];
    return matrix;
}

// Функция для удаления матрицы из памяти
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

// Функция для заполнения матрицы случайными значениями
void fillMatrix(int** matrix, int size) {
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            matrix[i][j] = rand() % 100; // случайное значение от 0 до 99
}

// Функция для перемножения матриц методом строка на столбец
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

// Функция для перемножения матриц методом строка на строку
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

// Функция для перемножения матриц методом столбец на столбец
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
    const int matrixSize = 2000; // 2062x2062 матрицы ~ 17 МБ

    srand(time(0)); // инициализация генератора случайных чисел

    // Создание и заполнение матриц
    int** matrix1 = createMatrix(matrixSize);
    int** matrix2 = createMatrix(matrixSize);
    fillMatrix(matrix1, matrixSize);
    fillMatrix(matrix2, matrixSize);

    // Замер времени выполнения перемножения матриц методом строка на столбец
    auto start = high_resolution_clock::now(); // начало замера времени
    int** result1 = multiplyMatricesRowColumn(matrix1, matrix2, matrixSize);
    auto stop = high_resolution_clock::now(); // конец замера времени
    auto duration1 = duration_cast<milliseconds>(stop - start); // вычисление длительности

    // Замер времени выполнения перемножения матриц методом строка на строку
    start = high_resolution_clock::now(); // начало замера времени
    int** result2 = multiplyMatricesRowRow(matrix1, matrix2, matrixSize);
    stop = high_resolution_clock::now(); // конец замера времени
    auto duration2 = duration_cast<milliseconds>(stop - start); // вычисление длительности

    // Замер времени выполнения перемножения матриц методом блочного перемножения
    start = high_resolution_clock::now(); // начало замера времени
    int** result3 = multiplyMatricesColumnColumn(matrix1, matrix2, matrixSize);
    stop = high_resolution_clock::now(); // конец замера времени
    auto duration3 = duration_cast<milliseconds>(stop - start); // вычисление длительности

    cout << "Row * Column: " << duration1.count() << " ms" << endl;
    cout << "Row * Row: " << duration2.count() << " ms" << endl;
    cout << "Column * Column: " << duration3.count() << " ms" << endl;

    // Освобождение памяти
    deleteMatrix(matrix1, matrixSize);
    deleteMatrix(matrix2, matrixSize);
    deleteMatrix(result1, matrixSize);
    deleteMatrix(result2, matrixSize);
    deleteMatrix(result3, matrixSize);

    return 0;
}
