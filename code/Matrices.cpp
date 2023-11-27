#include "Matrices.h"

namespace Matrices
{
    // Matrix constructor
    Matrix::Matrix(int _rows, int _cols) : rows(_rows), cols(_cols)
    {
        a.resize(rows, vector<double>(cols, 0.0));
    }

    // Addition operator
    Matrix operator+(const Matrix& a, const Matrix& b)
    {
        int rows = a.getRows();
        int cols = a.getCols();

        Matrix result(rows, cols);

        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                result(i, j) = a(i, j) + b(i, j);
            }
        }

        return result;
    }

    // Multiplication operator
    Matrix operator*(const Matrix& a, const Matrix& b)
    {
        int rowsA = a.getRows();
        int colsA = a.getCols();
        int colsB = b.getCols();

        Matrix result(rowsA, colsB);

        for (int i = 0; i < rowsA; ++i)
        {
            for (int j = 0; j < colsB; ++j)
            {
                double sum = 0.0;

                for (int k = 0; k < colsA; ++k)
                {
                    sum += a(i, k) * b(k, j);
                }

                result(i, j) = sum;
            }
        }

        return result;
    }

    // Comparison operators
    bool operator==(const Matrix& a, const Matrix& b)
    {
        if (a.getRows() != b.getRows() || a.getCols() != b.getCols())
        {
            return false;
        }

        for (int i = 0; i < a.getRows(); ++i)
        {
            for (int j = 0; j < a.getCols(); ++j)
            {
                if (a(i, j) != b(i, j))
                {
                    return false;
                }
            }
        }

        return true;
    }

    bool operator!=(const Matrix& a, const Matrix& b)
    {
        return !(a == b);
    }

    // Output operator
    ostream& operator<<(ostream& os, const Matrix& a)
    {
        int rows = a.getRows();
        int cols = a.getCols();

        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                os << a(i, j) << ' ';
            }
            os << '\n';
        }

        return os;
    }

    // RotationMatrix class implementation
    RotationMatrix::RotationMatrix(double theta) : Matrix(2, 2)
    {
        /*
        cos(theta) -sin(theta)
        sin(theta) cos(theta)
        */

        a[0][0] = cos(theta);
        a[0][1] = -sin(theta);
        a[1][0] = sin(theta);
        a[1][1] = cos(theta);
    }

    // ScalingMatrix class implementation
    ScalingMatrix::ScalingMatrix(double scale) : Matrix(2, 2)
    {
        /*
        scale 0
        0 scale
        */

        a[0][0] = scale;
        a[0][1] = 0.0;
        a[1][0] = 0.0;
        a[1][1] = scale;
    }

    // TranslationMatrix class implementation
    TranslationMatrix::TranslationMatrix(double xShift, double yShift, int nCols) : Matrix(2, nCols)
    {
        /*
        xShift xShift xShift ...
        yShift yShift yShift ...
        */

        for (int j = 0; j < nCols; ++j)
        {
            a[0][j] = xShift;
            a[1][j] = yShift;
        }
    }
}
