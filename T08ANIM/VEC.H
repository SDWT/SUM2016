/* FILENAME: VEC.H
 * PROGRAMMER: DS1
 * DATE: 14.06.2016
 * PURPOSE: Vector module
 */

#ifndef __VEC_H_
#define __VEC_H_

#include <stdlib.h>
#include <math.h>

#pragma warning (disable:4244)
/* Base float-point types */
typedef float FLT;
typedef double DBL;

/* PI constant */
#define DS1_PI 3.14159265358979323846
#define DEGREE2RADIANL 0.01745329251994329576L
extern DBL MultiplierDegree2Radian;

/* Space vector point representation type */
typedef struct tagVEC
{
  FLT X, Y, Z;
} VEC;

/* Plane vector point representation type */
typedef struct tagVEC2
{
  FLT X, Y;
} VEC2;

/* Color representation type */
typedef struct tagds1COLOR
{
  FLT R, G, B, A;
} ds1COLOR;

/* Vector matrix representation type */
typedef struct tagMATR
{
  FLT A[4][4];
} MATR;


/***
 * Vector handle function group
 **/

/* Setup vector coordinates function.
 * ARGUMENTS:
 *   - vector coordinates:
 *       FLT X, Y, Z;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline VEC VecSet( FLT X, FLT Y, FLT Z )
{
  VEC r;
  r.X = X, r.Y = Y, r.Z = Z;
  return r;
} /* End of 'VecSet' function */

/* Setup vector coordinates function.
 * ARGUMENTS:
 *   - vector coordinates:
 *       FLT X, Y, Z;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline ds1COLOR Color4Set( FLT R, FLT G, FLT B, FLT A )
{
  ds1COLOR r;
  r.R = R, r.G = G, r.B = B, r.A = A;
  return r;
} /* End of 'Color4Set' function */

/* Sum of two vectors function.
 * ARGUMENTS:
 *   - vectors to be add:
 *       VEC A, B;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline VEC VecAddVec( VEC A, VEC B )
{
  return VecSet( A.X + B.X, A.Y + B.Y, A.Z + B.Z );
} /* End of 'VecAddVec' function */

/* Substruct of two vectors function.
 * ARGUMENTS:
 *   - vectors to be sub:
 *       VEC A, B;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline VEC VecSubVec( VEC A, VEC B )
{
  return VecSet( A.X - B.X, A.Y - B.Y, A.Z - B.Z );
} /* End of 'VecSubVec' function */

/* Negative vector function.
 * ARGUMENTS:
 *   - vector 1:
 *       VEC A;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline VEC VecNeg( VEC A )
{
  return VecSet( -A.X, -A.Y, -A.Z );
} /* End of 'VecNeg' function */

/* Mull number to vector function.
 * ARGUMENTS:
 *   - vector to be mull:
 *       VEC A;
 *   - number to be mull:
 *       FLT N;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline VEC VecMullNum( VEC A, FLT N )
{
  return VecSet( A.X * N, A.Y * N, A.Z * N );
} /* End of 'VecMullNum' function */

/* Div number to vector function.
 * ARGUMENTS:
 *   - vector to be div:
 *       VEC A;
 *   - number to be div:
 *       FLT N;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline VEC VecDivNum( VEC A, FLT N )
{
  return VecSet( A.X / N, A.Y / N, A.Z / N );
} /* End of 'VecDivNum' function */

/* Dot of two vectors function.
 * ARGUMENTS:
 *   - vectors to be dot:
 *       VEC A, B;
 * RETURNS:
 *   (FLT) result number.
 */
__inline FLT VecDotVec( VEC A, VEC B )
{
  return  A.X * B.X + A.Y * B.Y + A.Z * B.Z;
} /* End of 'VecDotVec' function */

/* Cross of two vectors function.
 * ARGUMENTS:
 *   - vectors to be cross:
 *       VEC A, B;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline VEC VecCrossVec( VEC A, VEC B )
{
  FLT 
    X = A.Y * B.Z - A.Z * B.Y,
    Y = A.Z * B.X - A.X * B.Z,
    Z = A.X * B.Y - A.Y * B.X;
  return  VecSet(X, Y, Z);
} /* End of 'VecCrossVec' function */

/* Square length of vector function.
 * ARGUMENTS:
 *   - vector:
 *       VEC A;
 * RETURNS:
 *   (FLT) result number.
 */
__inline FLT VecLen2( VEC A )
{
  return  VecDotVec(A, A);
} /* End of 'VecLen2' function */

/* Length of vector function.
 * ARGUMENTS:
 *   - vector:
 *       VEC A;
 * RETURNS:
 *   (FLT) result number.
 */
__inline FLT VecLen( VEC A )
{
  FLT Len = VecLen2(A);
  return  ((Len == 1) || (Len == 0)) ? Len : sqrtf(Len);
} /* End of 'VecLen' function */

/* Length of vector function.
 * ARGUMENTS:
 *   - vector to normalize:
 *       VEC A;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline VEC VecNorlize( VEC A )
{
  FLT len = VecLen2(A);

  if (len != 0 && len != 1)
    len = sqrtf(len), A.X /= len, A.Y /= len, A.Z /= len;
  return A;
} /* End of 'VecNorlize' function */

/* Vector normalization function.
 * ARGUMENTS:
 *   - vector to be normalize:
 *       VEC V;
 * RETURNS:
 *   (VEC) normalized vector value.
 */
__inline VEC VecNormalize( VEC V )
{
  FLT len = VecDotVec(V, V);

  if (len != 1 && len != 0)
    len = sqrtf(len), V.X /= len, V.Y /= len, V.Z /= len;
  return V;
} /* End of 'VecNormalize' function */

 /***
 * Matrix handle function group
 **/

/* Return unit matrix function.
 * ARGUMENTS: none;
 * RETURNS:
 *   (MATR) result matrix.
 */
__inline MATR MatrixIdentity( VOID )
{
  /* Declaration unit matrix */
  static MATR UnitMatrix =
  {
    {
      {1, 0, 0, 0},
      {0, 1, 0, 0},
      {0, 0, 1, 0},
      {0, 0, 0, 1}
    }
  };
  return UnitMatrix;
} /* End of 'MatrixIdentity' function */

/* Translate matrix function.
 * ARGUMENTS:
 *   - matrix numbers to translate:
 *       FLT DX, DY, DZ;
 * RETURNS:
 *   (MATR) result matrix.
 */
__inline MATR MatrixTranslate( FLT DX, FLT DY, FLT DZ )
{
  MATR m = MatrixIdentity();

  m.A[3][0] = DX;
  m.A[3][1] = DY;
  m.A[3][2] = DZ;
  return m;
} /* End of 'MatrixTranslate' function */


/* Scale matrix function.
 * ARGUMENTS:
 *   - matrix numbers to scale:
 *       FLT DX, DY, DZ;
 * RETURNS:
 *   (MATR) result matrix.
 */
__inline MATR MatrixScale( FLT SX, FLT SY, FLT SZ )
{
  MATR m = MatrixIdentity();

  m.A[0][0] = SX;
  m.A[1][1] = SY;
  m.A[2][2] = SZ;
  return m;
} /* End of 'MatrixScale' function */


/* Rotate by x matrix function.
 * ARGUMENTS:
 *   - avengle to rotate by x:
 *       FLT AngleInDegree;
 * RETURNS:
 *   (MATR) result matrix.
 */
__inline MATR MatrixRotateX( DBL AngleInDegree )
{
  MATR m = MatrixIdentity();
  DBL CosA, SinA, MultiplierD2R;

  MultiplierD2R = (AngleInDegree * DS1_PI  / 180);
  __asm 
  {
    fld AngleInDegree
    fmul MultiplierD2R
    fsincos
    fstp CosA
    fstp SinA
  }
  m.A[1][1] = CosA;
  m.A[1][2] = SinA;
  m.A[2][1] = -SinA;
  m.A[2][2] = CosA;
  return m;
} /* End of 'MatrixRotateX' function */

/* Rotate by y matrix function.
 * ARGUMENTS:
 *   - avengle to rotate by y:
 *       FLT AngleInDegree;
 * RETURNS:
 *   (MATR) result matrix.
 */
__inline MATR MatrixRotateY( DBL AngleInDegree )
{
  MATR m = MatrixIdentity();
  DBL CosA, SinA, MultiplierD2R;

  MultiplierD2R = (AngleInDegree * DS1_PI  / 180);
  __asm 
  {
    fld AngleInDegree
    fmul MultiplierD2R
    fsincos
    fstp CosA
    fstp SinA
  }
  m.A[0][0] = CosA;
  m.A[2][0] = SinA;
  m.A[0][2] = -SinA;
  m.A[2][2] = CosA;
  return m;
} /* End of 'MatrixRotateY' function */

/* Rotate by z matrix function.
 * ARGUMENTS:
 *   - avengle to rotate by z:
 *       FLT AngleInDegree;
 * RETURNS:
 *   (MATR) result matrix.
 */
__inline MATR MatrixRotateZ( DBL AngleInDegree )
{
  MATR m = MatrixIdentity();
  DBL CosA, SinA, MultiplierD2R;

  MultiplierD2R = (AngleInDegree * DS1_PI  / 180);
  __asm 
  {
    fld AngleInDegree
    fmul MultiplierD2R
    fsincos
    fstp CosA
    fstp SinA
  }
  m.A[0][0] = CosA;
  m.A[0][1] = SinA;
  m.A[1][0] = -SinA;;
  m.A[1][1] = CosA;
  return m;
} /* End of 'MatrixRotateZ' function */

/* Rotate matrix function.
 * ARGUMENTS:
 *   - avengle to rotate by z:
 *       FLT AngleInDegree;
 *   - vector numbers to Rotate:
 *       FLT x, y, z;
 * RETURNS:
 *   (MATR) result matrix.
 */
__inline MATR MatrixRotate( DBL AngleInDegree, FLT x, FLT y, FLT z )
{
  MATR m = MatrixIdentity();
  DBL X, Y, Z, CosA, SinA, MultiplierD2R;

  MultiplierD2R = (AngleInDegree * DS1_PI  / 180);
  __asm 
  {
    fld AngleInDegree
    fmul MultiplierD2R
    fsincos
    fstp CosA
    fstp SinA
  }
  X = x * SinA;
  Y = y * SinA;
  Z = z * SinA;

  m.A[0][0] = 1 - 2 * (Y * Y + Z * Z);
  m.A[0][1] = 2 * X * Y - 2 * Z * CosA;
  m.A[0][2] = 2 * X * Z + 2 * Y * CosA;

  m.A[1][0] = 2 * X * Y + 2 * Z * CosA;
  m.A[1][1] = 1 - 2 * (X * X + Z * Z);
  m.A[1][2] = 2 * Y * Z - 2  * X * CosA;

  m.A[2][0] = 2 * X * Z - 2 * Y * CosA;
  m.A[2][1] = 2 * Y * Z + 2  * X * CosA;
  m.A[2][2] = 1 - 2 * (X * X + Z * Z);
  return m;
} /* End of 'MatrixRotate' function */

/* Rotation around X axis transformation matrix setup function.
 * ARGUMENTS:
 *   - rotation ange in degrees:
 *       FLT AngleInDegree;
 * RETURNS:
 *   (MATR) result matrix.
 */
__inline MATR MatrRotateX( FLT AngleInDegree )
{
  FLT sine, cosine;
  MATR m = MatrixIdentity();

  __asm {
    /* FST(0) Angle (from degree to radian) */
    fld  AngleInDegree
    fmul MultiplierDegree2Radian

    /* FST(0) - cos, FST(1) - sin */
    fsincos

    fstp cosine /* cos -> cosine */
    fstp sine   /* sin -> sine */
  }
  m.A[1][1] = cosine;
  m.A[2][2] = cosine;
  m.A[1][2] = sine;
  m.A[2][1] = -sine;
  return m;
} /* End of 'MatrRotateX' function */

/* Rotation around Y axis transformation matrix setup function.
 * ARGUMENTS:
 *   - rotation ange in degrees:
 *       FLT AngleInDegree;
 * RETURNS:
 *   (MATR) result matrix.
 */
__inline MATR MatrRotateY( FLT AngleInDegree )
{
  FLT sine, cosine;
  MATR m = MatrixIdentity();

  __asm {
    /* FST(0) Angle (from degree to radian) */
    fld  AngleInDegree
    fmul MultiplierDegree2Radian

    /* FST(0) - cos, FST(1) - sin */
    fsincos

    fstp cosine /* cos -> cosine */
    fstp sine   /* sin -> sine */
  }
  m.A[0][0] = cosine;
  m.A[2][2] = cosine;
  m.A[2][0] = sine;
  m.A[0][2] = -sine;
  return m;
} /* End of 'MatrRotateY' function */

/* Rotation around Z axis transformation matrix setup function.
 * ARGUMENTS:
 *   - rotation ange in degrees:
 *       FLT AngleInDegree;
 * RETURNS:
 *   (MATR) result matrix.
 */
__inline MATR MatrRotateZ( FLT AngleInDegree )
{
  FLT sine, cosine;
  MATR m = MatrixIdentity();

  __asm {
    /* FST(0) Angle (from degree to radian) */
    fld  AngleInDegree
    fmul MultiplierDegree2Radian

    /* FST(0) - cos, FST(1) - sin */
    fsincos

    fstp cosine /* cos -> cosine */
    fstp sine   /* sin -> sine */
  }
  m.A[0][0] = cosine;
  m.A[1][1] = cosine;
  m.A[0][1] = sine;
  m.A[1][0] = -sine;
  return m;
} /* End of 'MatrRotateZ' function */

/* Rotation around arbitrary radius-vector transformation matrix setup function.
 * ARGUMENTS:
 *   - rotation ange in degrees:
 *       FLT AngleInDegree;
 *   - vector rotate around:
 *       VEC R;
 * RETURNS:
 *   (MATR) result matrix.
 */
__inline MATR MatrRotate( FLT AngleInDegree, VEC R )
{
  FLT sine, cosine;
  MATR m;

  __asm {
    /* FST(0) Angle (from degree to radian) */
    fld  AngleInDegree
    fmul MultiplierDegree2Radian

    /* FST(0) - cos, FST(1) - sin */
    fsincos

    fstp cosine /* cos -> cosine */
    fstp sine   /* sin -> sine */
  }
  R = VecNormalize(R);
  m.A[0][0] = cosine + R.X * R.X * (1 - cosine);
  m.A[0][1] = R.X * R.Y * (1 - cosine) - R.Z * sine;
  m.A[0][2] = R.X * R.Z * (1 - cosine) + R.Y * sine;
  m.A[0][3] = 0;
  m.A[1][0] = R.Y * R.X * (1 - cosine) + R.Z * sine;
  m.A[1][1] = cosine + R.Y * R.Y * (1 - cosine);
  m.A[1][2] = R.Y * R.Z * (1 - cosine) - R.X * sine;
  m.A[1][3] = 0;
  m.A[2][0] = R.Z * R.X * (1 - cosine) - R.Y * sine;
  m.A[2][1] = R.Z * R.Y * (1 - cosine) + R.X * sine;
  m.A[2][2] = cosine + R.Z * R.Z * (1 - cosine);
  m.A[2][3] = 0;
  m.A[3][0] = 0;
  m.A[3][1] = 0;
  m.A[3][2] = 0;
  m.A[3][3] = 1;
  return m;
} /* End of 'MatrRotate' function */

/* Mull of two matrixs function.
 * ARGUMENTS:
 *   - matrixs to be mull:
 *       MATR M1, M2;
 * RETURNS:
 *   (MATR) result matrix.
 */
__inline MATR MatrMulMatr( MATR M1, MATR M2 )
{
  int i, j, k;
  MATR m = MatrixIdentity();

  for (i = 0; i < 4; i++)
    for (j = 0; j < 4; j++)
    {
      m.A[i][j] = 0;
      for (k = 0; k < 4; k++)
        m.A[i][j] += M1.A[i][k] * M2.A[k][j];
    }
  return m;
} /* End of 'MatrMullMatr' function */

/* Matrix 3x3 determ function.
 * ARGUMENTS:
 *   - matrix numbers:
 *       FLT A11, A12, A13,
             A21, A22, A23,
             A31, A32, A33;
 * RETURNS:
 *   (FLT) result Determ 3x3.
 */
__inline FLT MatrDeterm3x3( FLT A11, FLT A12, FLT A13,
                            FLT A21, FLT A22, FLT A23,
                            FLT A31, FLT A32, FLT A33)
{
  return  A11 * A22 * A33 + A12 * A23 * A31 + 
          A13 * A21 * A32 - A11 * A23 * A32 - 
          A12 * A21 * A33 - A13 * A22 * A31;
} /* End of 'MatrDeter3x3' function */

/* Matrix determ function.
 * ARGUMENTS:
 *   - matrixs to be mull:
 *       MATR A;
 * RETURNS:
 *   (FLT) result Determ.
 */
__inline FLT MatrDeterm( MATR M )
{
  return
    M.A[0][0] * MatrDeterm3x3(M.A[1][1], M.A[1][2], M.A[1][3],
                              M.A[2][1], M.A[2][2], M.A[2][3],
                              M.A[3][1], M.A[3][2], M.A[3][3]) -
    M.A[0][1] * MatrDeterm3x3(M.A[1][0], M.A[1][2], M.A[1][3],
                              M.A[2][0], M.A[2][2], M.A[2][3],
                              M.A[3][0], M.A[3][2], M.A[3][3]) +
    M.A[0][2] * MatrDeterm3x3(M.A[1][0], M.A[1][1], M.A[1][3],
                              M.A[2][0], M.A[2][1], M.A[2][3],
                              M.A[3][0], M.A[3][1], M.A[3][3]) -
    M.A[0][3] * MatrDeterm3x3(M.A[1][0], M.A[1][1], M.A[1][2],
                              M.A[2][0], M.A[2][1], M.A[2][2],
                              M.A[3][0], M.A[3][1], M.A[3][2]);
} /* End of 'MatrDeterm' function */

/* Inverse matrix function.
 * ARGUMENTS:
 *   - matrixs to be mull:
 *       MATR M;
 * RETURNS:
 *   (MATR) result matrix.
 */
__inline MATR MatrInverse( MATR M )
{
  int i, j;
  MATR r;
  int p[4][3] =
  {
    {1, 2, 3},
    {0, 2, 3},
    {0, 1, 3},
    {0, 1, 2}
  };
  FLT det = MatrDeterm(M);
  
  if (det == 0)
    return MatrixIdentity();
  
  for (i = 0; i < 4; i++)
    for (j = 0; j < 4; j++)
    {
      r.A[i][j] =
        MatrDeterm3x3(M.A[p[i][0]][p[j][0]], M.A[p[i][1]][p[j][0]],
                      M.A[p[i][2]][p[j][0]],
                      M.A[p[i][0]][p[j][1]], M.A[p[i][1]][p[j][1]],
                      M.A[p[i][2]][p[j][1]],
                      M.A[p[i][0]][p[j][2]], M.A[p[i][1]][p[j][2]],
                      M.A[p[i][2]][p[j][2]]) / det;
    }
  return r;
} /* End of 'MatrInverse' function */


/***
 * Matr and vector functions
 **/


/* Transform vector function.
 * ARGUMENTS:
 *   - vectors to be add:
 *       VEC V;
 *   - matrix:
 *       MATR M;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline VEC VecTransform( VEC V, MATR M )
{
  FLT w = V.X * M.A[0][3] + V.Y * M.A[1][3] + V.Z * M.A[2][3];
  VEC Vres;

  Vres.X = (V.X * M.A[0][0] + V.Y * M.A[1][0] + V.Z * M.A[2][0]) / w;
  Vres.Y = (V.X * M.A[0][1] + V.Y * M.A[1][1] + V.Z * M.A[2][1]) / w;
  Vres.Z = (V.X * M.A[0][2] + V.Y * M.A[1][2] + V.Z * M.A[2][2]) / w;

return Vres;
} /* End of 'VecTransform' function */

/* Transform point function.
 * ARGUMENTS:
 *   - vectors to be add:
 *       VEC V;
 *   - matrix:
 *       MATR M;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline VEC PointTransform( VEC V, MATR M )
{
  int i, j;
  FLT tmp, w = V.X * M.A[0][3] + V.Y * M.A[1][3] + V.Z * M.A[2][3] + M.A[3][3];
  VEC Vres;

  M = MatrInverse(M);
  for (i = 0; i < 4; i++)
    for (j = i + 1; j < 4; j++)
    {
      tmp = M.A[i][j];
      M.A[i][j] = M.A[j][i];
      M.A[j][i] = tmp;
    }

    Vres.X = (V.X * M.A[0][0] + V.Y * M.A[1][0] + V.Z * M.A[2][0] + M.A[3][0]) / w;
  Vres.Y = (V.X * M.A[0][1] + V.Y * M.A[1][1] + V.Z * M.A[2][1] + M.A[3][1]) / w;
  Vres.Z = (V.X * M.A[0][2] + V.Y * M.A[1][2] + V.Z * M.A[2][2] + M.A[3][2]) / w;

return Vres;

} /* End of 'PointTransform' function */

/* Transform point function.
 * ARGUMENTS:
 *   - vectors to be add:
 *       VEC V;
 *   - matrix:
 *       MATR M;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline VEC PointTransform4( VEC V, MATR M )
{
  FLT w = V.X * M.A[0][3] + V.Y * M.A[1][3] + V.Z * M.A[2][3] + M.A[3][3];
  VEC Vres;

  Vres.X = (V.X * M.A[0][0] + V.Y * M.A[1][0] + V.Z * M.A[2][0] + M.A[3][0]) / w;
  Vres.Y = (V.X * M.A[0][1] + V.Y * M.A[1][1] + V.Z * M.A[2][1] + M.A[3][1]) / w;
  Vres.Z = (V.X * M.A[0][2] + V.Y * M.A[1][2] + V.Z * M.A[2][2] + M.A[3][2]) / w;

return Vres;

} /* End of 'PointTransform' function */

/* Vector by matrix multiplication (without projection) function.
 * ARGUMENTS:
 *   - source vector:
 *       VEC V;
 *   - multiple matrix:
 *       MATR M;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline VEC VecTransform43( VEC V, MATR M )
{
  return VecSet(V.X * M.A[0][0] + V.Y * M.A[1][0] + V.Z * M.A[2][0] + M.A[3][0],
                V.X * M.A[0][1] + V.Y * M.A[1][1] + V.Z * M.A[2][1] + M.A[3][1],
                V.X * M.A[0][2] + V.Y * M.A[1][2] + V.Z * M.A[2][2] + M.A[3][2]);
} /* End of 'VecTransform43' function */

/* Transform Normal function.
 * ARGUMENTS:
 *   - vectors to be add:
 *       VEC V;
 *   - matrix:
 *       MATR M;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline VEC NormalTransform( VEC V, MATR InvM )
{
  int i, j;
  FLT w, tmp;
  VEC Vres;

  InvM = MatrInverse(InvM);
  for (i = 0; i < 4; i++)
    for (j = i + 1; j < 4; j++)
    {
      tmp = InvM.A[i][j];
      InvM.A[i][j] = InvM.A[j][i];
      InvM.A[j][i] = tmp;
    }
  w = V.X * InvM.A[0][3] + V.Y * InvM.A[1][3] + V.Z * InvM.A[2][3];

  Vres.X = (V.X * InvM.A[0][0] + V.Y * InvM.A[1][0] + V.Z * InvM.A[2][0]) / w;
  Vres.Y = (V.X * InvM.A[0][1] + V.Y * InvM.A[1][1] + V.Z * InvM.A[2][1]) / w;
  Vres.Z = (V.X * InvM.A[0][2] + V.Y * InvM.A[1][2] + V.Z * InvM.A[2][2]) / w;

return Vres;
} /* End of 'NormalTransform' function */

/* Random number obtain in range [0.0 .. 1.0] function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (FLT) result random number.
 */
__inline FLT Rnd0( VOID )
{
  return (FLT)rand() / RAND_MAX;
} /* End of 'Rnd0' function */

/* Random number obtain in range [-1.0 .. 1.0] function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (FLT) result random number.
 */
__inline FLT Rnd1( VOID )
{
  return 2.0f * rand() / RAND_MAX - 1;
} /* End of 'Rnd1' function */


/**/
MATR MatrView( VEC Loc, VEC At, VEC Up1 );
/**/
MATR MatrFrustum( FLT l, FLT r, FLT b, FLT t, FLT n, FLT f );
MATR MatrOrtho( FLT l, FLT r, FLT b, FLT t, FLT n, FLT f );

#endif /* __VEC_H_ */

/* END OF 'VEC.H' FILE */
