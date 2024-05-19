#ifndef GEOMETRY_SB_H
#define GEOMETRY_SB_H

/// \geometry_sb.h
///	\brief Содержит классы Vector3D и Matrix3D для геометрических преобразований координат
//
///  Classes for three-dimensional vectors and 3*3 matrices,
///   functions and operators for vector/matrix calculations
//

//#include "stdafx.h"

//--------------------
class Matrix3D; // Forward declaration of class Matrix3D used in class Vector3D


//
// Vector3D: трехмерный вектор
//
class Vector3D
{
  public:
    // Члены-данные
    double x,y,z;        // компоненты вектора

  public:
    // Конструкторы
    Vector3D ();  // создает нулевой вектор
    Vector3D (double X, double Y, double Z);

    // Доступ к компонентам (read only)
    double operator [] (int index) const;

    void set_value(int index, double value);
    void set_values(double X, double Y, double Z);
    void normalize();

    // component access
//    friend Vector3D Col(const Matrix3D& Mat, int Index);
//    friend Vector3D Row(const Matrix3D& Mat, int Index);

    // in-place addition of another vector
    void operator += (const Vector3D& Vec);

    // in-place subtraction of another vector
    void operator -= (const Vector3D& Vec);

    // скалярное произведение
    friend double Dot (const Vector3D& left, const Vector3D& right);

    // Норма (norm) вектора
    friend double Norm (const Vector3D& Vec);

    // Длина (magnitude) вектора
    friend double magnitude (const Vector3D &Vec);

    // scalar multiplication
    friend Vector3D operator * (double scalar, const Vector3D& Vec);
    friend Vector3D operator * (const Vector3D& Vec, double scalar);

    // scalar division
    friend Vector3D operator / (const Vector3D& Vec, double scalar);

    // unary minus of vector
    friend Vector3D operator - (const Vector3D& Vec);

    // addition of vectors
    friend Vector3D operator + (const Vector3D& left, const Vector3D& right);

    // subtraction of vectors
    friend Vector3D operator - (const Vector3D& left, const Vector3D& right);

    // векторное произведение
    friend Vector3D Cross (const Vector3D& left, const Vector3D& right);

    // matrix-vector product
    friend Vector3D operator * (const Matrix3D& Mat, const Vector3D& Vec);

    // vector-matrix product
    friend Vector3D operator * (const Vector3D& Vec, const Matrix3D& Mat);

    friend class Matrix3D;

};

void xyz2angle(const Vector3D &Vec, double &alf, double &delt);
void xyz2angle(double x, double y, double z, double &alf, double &delt);
void angle2xyz(double alf, double delt, double &x, double &y, double &z);
Vector3D angle2xyz(double alf, double delt);

//
// Matrix3D: 3 dimensional transformation matrices
//
// elementary rotations
Matrix3D CreateRX(double RotAngle);
Matrix3D CreateRY(double RotAngle);
Matrix3D CreateRZ(double RotAngle);

class Matrix3D
{
 // private:
  public:
    double m_Mat[3][3];  // matrix elements

  public:
    Matrix3D(); // Конструктор по умолчанию создает единичную матрицу

    // конструктор по значениям
    Matrix3D(double m11, double m12, double m13, double m21, double m22, double m23, double m31, double m32, double m33);

    // constructor for matrix from column vectors
    Matrix3D( const Vector3D& e_1, const Vector3D& e_2, const Vector3D& e_3 );

    double get_value(int y, int x);

    // component access
    friend Vector3D Col(Matrix3D Mat, int index);
    friend Vector3D Row(Matrix3D Mat, int index);

    // identity matrix
    friend Matrix3D CreateI3();

    // elementary rotations
    friend Matrix3D CreateRX(double RotAngle);
    friend Matrix3D CreateRY(double RotAngle);
    friend Matrix3D CreateRZ(double RotAngle);

    // transposed matrix
    friend Matrix3D Transp(const Matrix3D& Mat);

    // scalar multiplication
    friend Matrix3D operator * (double fScalar, const Matrix3D& Mat);
    friend Matrix3D operator * (const Matrix3D& Mat, double scalar);

    // scalar division
    friend Matrix3D operator / (const Matrix3D& Mat, double scalar);

    // matrix-vector product
    friend Vector3D operator * (const Matrix3D& Mat, const Vector3D& Vec);

    // vector-matrix product
    friend Vector3D operator * (const Vector3D& Vec, const Matrix3D &Mat);

    // unary minus of matrix
    friend Matrix3D operator - (const Matrix3D& Mat);

    // addition of matrices
    friend Matrix3D operator + (const Matrix3D& left, const Matrix3D& right);

    // subtraction of matrices
    friend Matrix3D operator - (const Matrix3D& left, const Matrix3D& right);

    // multiplication of matrices
    friend Matrix3D operator * (const Matrix3D& left, const Matrix3D& right);

};

#endif // GEOMETRY_SB_H
