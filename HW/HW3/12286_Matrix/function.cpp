#include <iostream>
#include "function.h"

using namespace std;

/// Can't redefine the default parameter in the implementation of the function
Matrix::Matrix(int s /*=5*/) : size(s) {
    buf = new int[size * size];
    matrix = new int*[size];
    for (int i = 0; i < size; i++) {
        matrix[i] = new int[size];
    }
}

Matrix::Matrix(const Matrix &mat) {
    size = mat.size;
    buf = new int [size * size];
    for (int i = 0; i < size * size; i++) {
        buf[i] = mat.buf[i];
    }
    matrix = new int*[size];
    for (int i = 0; i < size; i++) {
        matrix[i] = new int[size];
        for (int j = 0; j < size; j++) {
            matrix[i][j] = mat.matrix[i][j];
        }
    }
}

Matrix &Matrix::operator=(const Matrix &a) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            matrix[i][j] = a.matrix[i][j];
        }
    }
    return *this;
}

ostream &operator<<(ostream &out, const Matrix &mat) {
    for (int i = 0; i < mat.size; i++) {
        for (int j = 0; j < mat.size - 1; j++) {
            out << mat.matrix[i][j] << ' ';
        }
        out << mat.matrix[i][mat.size - 1] << endl;
    }
    return out;
}

istream &operator>>(istream &in, Matrix &mat) {
    int val;
    for (int i = 0; i < mat.size; i++) {
        for (int j = 0; j < mat.size; j++) {
            in >> val;
            mat.matrix[i][j] = val;
            mat.buf[mat.size * i + j] = val;
        }
    }
    return in;
}
