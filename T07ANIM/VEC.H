/* FILENAME: VEC.H
* PROGRAMMER: DS1
* DATE: 07.06.2016
* PURPOSE: Vector module
*/

#ifndef __VEC_H_
#define __VEC_H_

#include <math.h>

/* PI constant */
#define PI 3.14159265358979323846

/* Base float-point types */
typedef DOUBLE DBL;
typedef FLOAT FLT;

/* Space vector point representation type */
typedef struct tagVEC
{
  DBL X, Y, Z;
} VEC;

/* Vector matrix representation type */
typedef struct tagMATR
{
  DBL A[4][4];
} MATR;


/***
 * Vector handle function group
 **/

/* Setup vector coordinates function.
 * ARGUMENTS:
 *   - vector coordinates:
 *       DBL X, Y, Z;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline VEC VecSet( DBL X, DBL Y, DBL Z )
{
  VEC r;
  r.X = X, r.Y = Y, r.Z = Z;
  return r;
} /* End of 'VecSet' function */

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
 *       DBL N;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline VEC VecMullNum( VEC A, DBL N )
{
  return VecSet( A.X * N, A.Y * N, A.Z * N );
} /* End of 'VecMullNum' function */

/* Div number to vector function.
 * ARGUMENTS:
 *   - vector to be div:
 *       VEC A;
 *   - number to be div:
 *       DBL N;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline VEC VecDivNum( VEC A, DBL N )
{
  return VecSet( A.X / N, A.Y / N, A.Z / N );
} /* End of 'VecDivNum' function */

/* Dot of two vectors function.
 * ARGUMENTS:
 *   - vectors to be dot:
 *       VEC A, B;
 * RETURNS:
 *   (DBL) result number.
 */
__inline DBL VecDotVec( VEC A, VEC B )
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
  DBL 
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
 *   (DBL) result number.
 */
__inline DBL VecLen2( VEC A )
{
  return  VecDotVec(A, A);
} /* End of 'VecLen2' function */

/* Length of vector function.
 * ARGUMENTS:
 *   - vector:
 *       VEC A;
 * RETURNS:
 *   (DBL) result number.
 */
__inline DBL VecLen( VEC A )
{
  DBL Len = VecLen2(A);
  return  ((Len == 1) || (Len == 0)) ? Len : sqrt(Len);
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
  DBL len = VecLen2(A);

  if (len != 0 && len != 1)
    len = sqrt(len), A.X /= len, A.Y /= len, A.Z /= len;
  return A;
} /* End of 'VecNorlize' function */


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
 *       DBL DX, DY, DZ;
 * RETURNS:
 *   (MATR) result matrix.
 */
__inline MATR MatrixTranslate( DBL DX, DBL DY, DBL DZ )
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
 *       DBL DX, DY, DZ;
 * RETURNS:
 *   (MATR) result matrix.
 */
__inline MATR MatrixScale( DBL SX, DBL SY, DBL SZ )
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
 *       DBL AngleInDegree;
 * RETURNS:
 *   (MATR) result matrix.
 */
__inline MATR MatrixRotateX( DBL AngleInDegree )
{
  MATR m = MatrixIdentity();
  DBL CosA, SinA, MultiplierD2R;

  MultiplierD2R = (AngleInDegree * PI  / 180);
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
 *       DBL AngleInDegree;
 * RETURNS:
 *   (MATR) result matrix.
 */
__inline MATR MatrixRotateY( DBL AngleInDegree )
{
  MATR m = MatrixIdentity();
  DBL CosA, SinA, MultiplierD2R;

  MultiplierD2R = (AngleInDegree * PI  / 180);
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
 *       DBL AngleInDegree;
 * RETURNS:
 *   (MATR) result matrix.
 */
__inline MATR MatrixRotateZ( DBL AngleInDegree )
{
  MATR m = MatrixIdentity();
  DBL CosA, SinA, MultiplierD2R;

  MultiplierD2R = (AngleInDegree * PI  / 180);
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
 *       DBL AngleInDegree;
 *   - vector numbers to Rotate:
 *       DBL x, y, z;
 * RETURNS:
 *   (MATR) result matrix.
 */
__inline MATR MatrixRotate( DBL AngleInDegree, DBL x, DBL y, DBL z )
{
  MATR m = MatrixIdentity();
  DBL X, Y, Z, CosA, SinA, MultiplierD2R;

  MultiplierD2R = (AngleInDegree * PI  / 180);
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

/* Mull of two matrixs function.
 * ARGUMENTS:
 *   - matrixs to be mull:
 *       MATR M1, M2;
 * RETURNS:
 *   (MATR) result matrix.
 */
__inline MATR MatrMullMatr( MATR M1, MATR M2 )
{
  MATR m = MatrixIdentity();
  INT i, j, k;

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
 *       DBL A11, A12, A13,
             A21, A22, A23,
             A31, A32, A33;
 * RETURNS:
 *   (DBL) result Determ 3x3.
 */
__inline DBL MatrDeterm3x3( DBL A11, DBL A12, DBL A13,
                            DBL A21, DBL A22, DBL A23,
                            DBL A31, DBL A32, DBL A33)
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
 *   (DBL) result Determ.
 */
__inline DBL MatrDeterm( MATR M )
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
  INT i, j;
  MATR r;
  INT p[4][3] =
  {
    {1, 2, 3},
    {0, 2, 3},
    {0, 1, 3},
    {0, 1, 2}
  };
  DBL det = MatrDeterm(M);
  
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
  DBL w = V.X * M.A[0][3] + V.Y * M.A[1][3] + V.Z * M.A[2][3];
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
  INT i, j;
  DBL tmp, w = V.X * M.A[0][3] + V.Y * M.A[1][3] + V.Z * M.A[2][3] + M.A[3][3];
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
  INT i, j;
  DBL w, tmp;
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

#endif /* __VEC_H_ */

/* END OF 'VEC.H' FILE */
