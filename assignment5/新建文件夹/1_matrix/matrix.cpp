#include "matrix.h"

using namespace std;

Matrix::Matrix() {
    data.resize(1, vector<int>(1, 0));
}

Matrix::Matrix(int rowSize, int colSize) {
    if (rowSize <= 0 || colSize <= 0) {
        errorCode = InvalidDimension;
    } else {
        errorCode = NoError;
        data.resize(rowSize, std::vector<int>(colSize, 0));
    }
}

void Matrix::set(int row, int col, int value) {
    if (row >= data.size() || col >= data[0].size() || row < 0 ||col < 0) {
        errorCode = IndexOutOfRange;
    } else {
        errorCode = NoError;
        data[row][col] = value;
    }
}

int Matrix::get(int row, int col) {
    if (row >= data.size() || col >= data[0].size() || row < 0 ||col < 0) {
        errorCode = IndexOutOfRange;
        return -1;
    } else {
        errorCode = NoError;
        return data[row][col];
    }
}

Matrix Matrix::add(const Matrix& other) const {
    Matrix result(data.size(), data[0].size());
    if (data.size() != other.data.size() || data[0].size() != other.data[0].size()) {
        result.errorCode = DimensionMismatch;
    } else {
        result.errorCode = NoError;
        for (int i = 0; i < data.size(); ++i) {
            for (int j = 0; j < data[0].size(); ++j) {
                result.data[i][j] = data[i][j] + other.data[i][j];
            }
        }
    }
    return result;
}

Matrix Matrix::mul(const Matrix& other) const {
    Matrix result(data.size(), other.data[0].size());
    if (data[0].size() != other.data.size()) {
        result.errorCode = DimensionMismatch;
    } else {
        result.errorCode = NoError;
        for (int i = 0; i < data.size(); ++i) {
            for (int k = 0; k < other.data[0].size(); ++k) {
                int num = 0;
                for (int j = 0; j < data[0].size(); ++j) {
                    num += data[i][j] * other.data[j][k];
                }
                result.data[i][k] = num;
            }
        }
    }
    return result;
}

std::string Matrix::toString() const {
    string result;
    for (int i = 0; i < data.size(); ++i) {
        for (int j = 0; j < data[0].size(); ++j) {
            result += std::to_string(data[i][j]) + " ";
        }
        result += "\n";
    }
    return result;
}

ErrorCode Matrix::getErrorCode() const {
    return errorCode;
}

Matrix operator+(const Matrix& m1, const Matrix& m2) {
    return m1.add(m2);
}

Matrix operator*(const Matrix& m1, const Matrix& m2) {
    return m1.mul(m2);
}

std::ostream& operator<<(std::ostream& os, const Matrix& mat) {
    os << mat.toString();
    return os;
}
