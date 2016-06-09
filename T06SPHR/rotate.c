/* PI constant */
#define PI 3.14159265358979

/* Base float point type */
typedef double DBL;

/* Space vector representation type */
typedef struct
{
  DBL X, Y, Z; /* Vector coordinates */
} VEC;

/* Dot product of two vectors function.
 * ARGUMENTS:
 *   - vectors to be dot producted:
 *       VEC A, B;
 * RETURNS:
 *   (DBL) dot product value.
 */
DBL VecDotVec( VEC A, VEC B )
{
  return A.X * B.X + A.Y * B.Y + A.Z * B.Z;
} /* End of 'VecDotVec' function */

/* Vector set by components function.
 * ARGUMENTS:
 *   - vector components:
 *       DBL A, B, C;
 * RETURNS:
 *   (VEC) constructed vector.
 */
VEC VecSet( DBL A, DBL B, DBL C )
{
  VEC r = {A, B, C};

  return r;
} /* End of 'VecSet' function */

/* Vector normalization function.
 * ARGUMENTS:
 *   - vector to be normalize:
 *       VEC V;
 * RETURNS:
 *   (VEC) normalized vector value.
 */
VEC VecNormalize( VEC V )
{
  DBL len = VecDotVec(V, V);

  if (len != 1 && len != 0)
    len = sqrt(len), V.X /= len, V.Y /= len, V.Z /= len;
  return V;
} /* End of 'VecNormalize' function */

/* Rotate vector function.
 * ARGUMENTS:
 *   - vector to be rotated:
 *       VEC P;
 *   - vector rotated around:
 *       VEC A;
 *   - rotation angle in degree:
 *       DBL Angle;
 * RETURNS:
 *   (VEC) rotated vector value.
 */
VEC Rotate( VEC P, VEC A, DBL Angle )
{
  DBL si, co;

  A = VecNormalize(A);

  Angle *= PI / 180;
  si = sin(Angle);
  co = cos(Angle);

  return VecSet(P.X * (co + A.X * A.X * (1 - co)) +
                P.Y * (A.Y * A.X * (1 - co) + A.Z * si) +
                P.Z * (A.Z * A.X * (1 - co) - A.Y * si),
                P.X * (A.X * A.Y * (1 - co) - A.Z * si) +
                P.Y * (co + A.Y * A.Y * (1 - co)) + 
                P.Z * (A.Z * A.Y * (1 - co) + A.X * si),
                P.X * (A.X * A.Z * (1 - co) + A.Y * si) +
                P.Y * (A.Y * A.Z * (1 - co) - A.X * si) + 
                P.Z * (co + A.Z * A.Z * (1 - co)));
} /* End of 'Rotate' function */

/* Rotate vector function.
 * ARGUMENTS:
 *   - vector to be rotated:
 *       VEC V;
 *   - rotation angle in degree:
 *       DBL Angle;
 * RETURNS:
 *   (VEC) rotated vector value.
 */
VEC Rot( VEC V, DBL Angle )
{
  DBL A = Angle * PI / 180;
  VEC r;

  r.X = V.X;
  r.Y = V.Y * cos(A) - V.Z * sin(A);
  r.Z = V.Y * sin(A) + V.Z * cos(A);
  return r;
} /* End of 'Rot' function */

