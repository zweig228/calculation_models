#include <math.h>
#include "geometry_sb.h"
#include "constants.h"

//
// Default constructor (used for creation of temporary Vec3D-objects)
//
Vector3D::Vector3D()
{
   x = 0.0;  y = 0.0;  z = 0.0;
}


//
// Constructor for component-wise initialization
//
Vector3D::Vector3D(double X, double Y, double Z)
{
   x = X;
   y = Y;
   z = Z;
}

/*
//
// Conversion constructor from polar components
//
Vec3D::Vec3D (const Polar& polar)
 : m_phi(polar.phi),
   m_theta(polar.theta),
   m_r(polar.r),
   m_bPolarValid(true)
{
  const double cosEl = cos(m_theta);

  m_Vec[0] = polar.r * cos(m_phi) * cosEl;
  m_Vec[1] = polar.r * sin(m_phi) * cosEl;
  m_Vec[2] = polar.r              * sin(m_theta);
}
*/

// Доступ к компонентам по индексу (index may be "x", "y", or "z")
double Vector3D::operator [] (int index) const
{
    double res = 0;
    switch (index)
    {
    case 0:
        res = x; break;
    case 1:
        res = y; break;
    case 2:
        res = z;
    }
  return res;
}


void Vector3D::set_value(int index, double value)
{
    switch (index)
    {
    case 0:
        x = value; break;
    case 1:
        y = value; break;
    case 2:
        z = value;
    }
}

void Vector3D::set_values(double X, double Y, double Z)
{
    x = X;  y = Y; z = Z;
}


// In-place addition of vector
void Vector3D::operator += (const Vector3D &Vec)
{
    x += Vec.x;
    y += Vec.y;
    z += Vec.z;
}


// In-place subtraction of vector
void Vector3D::operator -= (const Vector3D &Vec)
{
    x -= Vec.x;
    y -= Vec.y;
    z -= Vec.z;
}

void Vector3D::normalize()
{
    double magn = sqrt(x*x + y*y + z*z);
    if (magn < eps_zero_) return;

    x /= magn;
    y /= magn;
    z /= magn;
}

// Скалярное умножение
double Dot (const Vector3D &left, const Vector3D &right)
{
  return left.x * right.x + left.y * right.y + left.z * right.z;
}


// Норма (norm) вектора
double Norm (const Vector3D &Vec)
{
  return Dot(Vec, Vec);
}


// Длина (magnitude) вектора
double magnitude (const Vector3D &Vec)
{
  return sqrt(Dot(Vec, Vec));
}


// Умножение на скаляр
Vector3D operator * (double scalar, const Vector3D &Vec)
{
  return Vector3D(scalar * Vec.x, scalar * Vec.y, scalar * Vec.z);
}


// Умножение на скаляр
Vector3D operator * (const Vector3D &Vec, double scalar)
{
  return scalar * Vec;
}


// Деление на скаляр
Vector3D operator / (const Vector3D &Vec, double scalar)
{
  return Vector3D(Vec.x / scalar, Vec.y / scalar, Vec.z / scalar );
}


// Унарный минус
Vector3D operator - (const Vector3D &Vec)
{
  return Vector3D( -Vec.x, -Vec.y, -Vec.z );
}


// Сложение векторов
Vector3D operator + (const Vector3D &left, const Vector3D &right)
{
  return Vector3D( left.x + right.x, left.y + right.y, left.z + right.z );
}


// Вычитание векторов
Vector3D operator - (const Vector3D &left, const Vector3D &right)
{
  return Vector3D( left.x - right.x, left.y - right.y, left.z - right.z );
}

// Векторное умножение
Vector3D Cross(const Vector3D &left, const Vector3D &right)
{
  Vector3D Res;
  Res.x = left.y * right.z - left.z * right.y;
  Res.y = left.z * right.x - left.x * right.z;
  Res.z = left.x * right.y - left.y * right.x;
  return Res;
}


//
// Implementation of class Mat3D
//

//
// Default constructor (sets null matrix)
//
Matrix3D::Matrix3D()
{
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      m_Mat[i][j] = 0.0;
    }
  }
  m_Mat[0][0] = 1.0;  m_Mat[1][1] = 1.0;  m_Mat[2][2] = 1.0;
}

    // конструктор по значениям
Matrix3D::Matrix3D(double m11, double m12, double m13, double m21, double m22, double m23, double m31, double m32, double m33)
{
    m_Mat[0][0] = m11;   m_Mat[0][1] = m12;	  m_Mat[0][2] = m13;
    m_Mat[1][0] = m21;   m_Mat[1][1] = m22;	  m_Mat[1][2] = m23;
    m_Mat[2][0] = m31;   m_Mat[2][1] = m32;	  m_Mat[2][2] = m33;
}

//
// Constructor for matrix from column vectors
//
Matrix3D::Matrix3D(const Vector3D &C1, const Vector3D &C2, const Vector3D &C3 )
{
  for (int i = 0; i < 3; i++)
  {
    m_Mat[i][0]=C1[i];
    m_Mat[i][1]=C2[i];
    m_Mat[i][2]=C3[i];
  }
}

/*
//
// Component access: retrieve given column of Matrix Mat
//
Vector3D Col(const Matrix3D &Mat, Matrix3D Index)
{
  Vector3D Res;

  for (int i = 0; i < 3; i++)
  {
    Res.m_Vec[i] = Mat.m_Mat[i][Index];
  }
  return Res;
}


//
// Component access: retrieve given row of Matrix Mat
//
Vector3D Row(const Matrix3D &Mat, Matrix3D Index)
{
  Vector3D Res;

  for (int j = 0; j < 3; j++)
  {
    Res.m_Vec[j] = Mat.m_Mat[Index][j];
  }
  return Res;
}
*/

void xyz2angle(const Vector3D& Vec, double &alf, double &delt)
{
    double r = Norm(Vec);
    delt = asin(Vec.z/r);
    alf  = asin(Vec.y/(r*cos(delt)));
}

void xyz2angle(double x, double y, double z, double &alf, double &delt)
{
    double r = sqrt(x*x + y*y + z*z);
    delt = asin(z/r);
    alf  = asin(y/(r*cos(delt)));
}

void angle2xyz(double alf, double delt, double &x, double &y, double &z)
{
    x = cos(delt)*cos(alf);
    y = cos(delt)*sin(alf);
    z = sin(delt);
}

Vector3D angle2xyz(double alf, double delt)
{
    double x,y,z;
    x = cos(delt)*cos(alf);
    y = cos(delt)*sin(alf);
    z = sin(delt);
    return Vector3D(x,y,z);
}


//
// Create identity matrix
//
Matrix3D CreateI3()
{
  Matrix3D Id;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      Id.m_Mat[i][j] = (i==j) ? 1 : 0;

  return Id;
}


//
// Elementary rotation matrices
//
Matrix3D CreateRX(double RotAngle)
{
  const double S = sin (RotAngle);
  const double C = cos (RotAngle);
  Matrix3D U;

  U.m_Mat[0][0] = 1.0;  U.m_Mat[0][1] = 0.0;  U.m_Mat[0][2] = 0.0;
  U.m_Mat[1][0] = 0.0;  U.m_Mat[1][1] =  +C;  U.m_Mat[1][2] =  +S;
  U.m_Mat[2][0] = 0.0;  U.m_Mat[2][1] =  -S;  U.m_Mat[2][2] =  +C;

  return U;
}


Matrix3D CreateRY(double RotAngle)
{
  const double S = sin (RotAngle);
  const double C = cos (RotAngle);
  Matrix3D U;

  U.m_Mat[0][0] =  +C;  U.m_Mat[0][1] = 0.0;  U.m_Mat[0][2] =  -S;
  U.m_Mat[1][0] = 0.0;  U.m_Mat[1][1] = 1.0;  U.m_Mat[1][2] = 0.0;
  U.m_Mat[2][0] =  +S;  U.m_Mat[2][1] = 0.0;  U.m_Mat[2][2] =  +C;

  return U;
}


Matrix3D CreateRZ(double RotAngle)
{
  const double S = sin (RotAngle);
  const double C = cos (RotAngle);
  Matrix3D U;

  U.m_Mat[0][0] =  +C;  U.m_Mat[0][1] =  +S;  U.m_Mat[0][2] = 0.0;
  U.m_Mat[1][0] =  -S;  U.m_Mat[1][1] =  +C;  U.m_Mat[1][2] = 0.0;
  U.m_Mat[2][0] = 0.0;  U.m_Mat[2][1] = 0.0;  U.m_Mat[2][2] = 1.0;

  return U;
}


//
// Transpose of matrix
//
Matrix3D Transp(const Matrix3D &Mat)
{
  Matrix3D T;

  for ( int i = 0; i < 3; i++ )
    for ( int j = 0; j < 3; j++ )
      T.m_Mat[i][j] = Mat.m_Mat[j][i];

  return T;
}


//
// Scalar multiplication
//
Matrix3D operator * (double scalar, const Matrix3D &Mat)
{
  Matrix3D Result;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      Result.m_Mat[i][j] = scalar * Mat.m_Mat[i][j];

  return Result;
}


Matrix3D operator * (const Matrix3D &Mat, double scalar)
{
  return scalar * Mat;
}


//
// Scalar division
//
Matrix3D operator / (const Matrix3D &Mat, double scalar)
{
  Matrix3D Result;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      Result.m_Mat[i][j] = Mat.m_Mat[i][j]/scalar;

  return Result;
}


//
// Matrix-vector product
//
Vector3D operator * (const Matrix3D &Mat, const Vector3D &Vec)
{
    Vector3D Result;
    double   Scalp;

  for (int i = 0; i < 3; i++)
  {
    Scalp = 0.0;
    for (int j = 0; j < 3; j++)
    {
      Scalp += Mat.m_Mat[i][j] * Vec[j];
    }
    switch (i)
    {
    case 0:
        Result.x = Scalp; break;
    case 1:
        Result.y = Scalp; break;
    case 2:
        Result.z = Scalp;
    }
  }

  return Result;
}


//
// Vector-matrix product
//
Vector3D operator * (const Vector3D &Vec, const Matrix3D &Mat)
{
  Vector3D Result;
  for (int j = 0; j < 3; j++)
  {
    double Scalp = 0.0;
    for (int i = 0; i < 3; i++)
    {
      Scalp += Vec[i] * Mat.m_Mat[i][j] ;
    }
    switch (j)
    {
    case 0:
        Result.x = Scalp; break;
    case 1:
        Result.y = Scalp; break;
    case 2:
        Result.z = Scalp;
    }
  }

  return Result;
}


//
// Unary minus of matrix
//
Matrix3D operator - (const Matrix3D &Mat)
{
  Matrix3D Result;

  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      Result.m_Mat[i][j] = -Mat.m_Mat[i][j];

  return Result;
}


//
// Addition of matrices
//
Matrix3D operator + (const Matrix3D &left, const Matrix3D &right)
{
  Matrix3D Result;
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      Result.m_Mat[i][j] = left.m_Mat[i][j] + right.m_Mat[i][j];
    }
  }
  return Result;
}


//
// Subtraction of matrices
//
Matrix3D operator - (const Matrix3D &left, const Matrix3D &right)
{
  Matrix3D Result;
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      Result.m_Mat[i][j] = left.m_Mat[i][j] - right.m_Mat[i][j];
    }
  }
  return Result;
}


//
// Matrix product
//
Matrix3D operator * (const Matrix3D &left, const Matrix3D &right)
{
  Matrix3D Result;
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      double Scalp = 0.0;
      for (int k = 0; k < 3; k++)
        Scalp += left.m_Mat[i][k] * right.m_Mat[k][j];

      Result.m_Mat[i][j] = Scalp;
    }
  }

  return Result;
}

