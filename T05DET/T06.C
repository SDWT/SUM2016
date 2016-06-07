/* FILENAME: T06.C
 * PROGRAMMER: DS1
 * DATE: 07.06.2016
 * PURPOSE: Vector and matrix function
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX 10

typedef struct tagVEC
{
  double x, y, z;
} VEC;

typedef struct tagVEC
{
  double x, y, z;
} VEC;


/* Sum 2 vectors function 
 * ARGUMENTS:
 *  - First vector to sum:
 *      VEC *A;
 *  - Second vector to sum:
 *      VEC *B 
 * RETURNS:
 *   (VEC) vector sum vectors;
 */
VEC VecSumVec( VEC A, VEC B )
{
  VEC C;

  C.x = A.x + B.x;
  C.y = A.y + B.y;
  C.z = A.z + B.z;
  return C;
}/* End of 'VecSumVec' function */

/* Dot 2 vectors function 
 * ARGUMENTS:
 *  - First vector to dot:
 *      VEC *A;
 *  - Second vector to dot:
 *      VEC *B 
 * RETURNS:
 *   (double) ;
 */
double VecDotVec( VEC A, VEC B )
{
  return A.x * B.x + A.y * B.y + A.z * B.z;
}/* End of 'VecSumVec' function */


/* END OF 'T06.C' FILE */
