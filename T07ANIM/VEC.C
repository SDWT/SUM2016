/* FILENAME: VEC.C
 * PROGRAMMER: DS1
 * DATE: 13.06.2016
 * PURPOSE: Vector module
 */

#include "vec.h"

/*
 *
 */
MATR MatrView( VEC Loc, VEC At, VEC Up1 )
{
  VEC Dir = VecNormalize(VecSubVec(At, Loc)),
    Right = VecNormalize(VecCrossVec(Dir, Up1)),
    Up = VecNormalize(VecCrossVec(Right, Dir));
  MATR m = 
  {
    {
      {Right.X, Up.X, -Dir.X, 0},
      {Right.Y, Up.Y, -Dir.Y, 0},
      {Right.Z, Up.Z, -Dir.Z, 0},
      {-VecDotVec(Loc, Right), -VecDotVec(Loc, Up), VecDotVec(Loc, Dir), 1}
    }
  };

  return m;
}

/*
 *
 */
MATR MatrFrustum( FLT l, FLT r, FLT b, FLT t, FLT n, FLT f )
{
  MATR m = 
  {
    {
      {  2 * n / (r - l),                    0,                    0,  0},
      {                0,      2 * n / (t - b),                    0,  0},
      {(r + l) / (r - l),    (t + b) / (t - b),   -(f + n) / (f - n), -1},
      {                0,                    0, -2 * n * f / (f - n),  0}
    }
  };

  return m;
}

MATR MatrOrtho( FLT l, FLT r, FLT b, FLT t, FLT n, FLT f )
{
  MATR m = 
  {
    {
      {       2 / (r - l),                  0,                  0, 0},
      {                 0,        2 / (t - b),                  0, 0},
      {                 0,                  0,      -2  / (f - n), 0},
      {-(r + l) / (r - l), -(t + b) / (t - b), -(f + n) / (f - n), 1}
    }
  };

  return m;
}
/* END OF 'VEC.C' FILE */
