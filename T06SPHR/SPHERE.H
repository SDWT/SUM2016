/* FILENAME: SPHERE.H
 * PROGRAMMER: DS1
 * DATE: 07.06.2016
 * PURPOSE: Sphere drawing header file
 */

#ifndef _SPHERE_H_ /**/
#define _SPHERE_H_

#include <windows.h>

typedef DOUBLE DBL;
typedef FLOAT FLT;

/* Space vector representation */
/*
typedef struct tagVEC
{
  DBL X, Y, Z;
} VEC;
*/


VOID SphereDrawEllipse( HDC hDC, INT Xc, INT Yc, INT R );
VOID SphereDrawLines( HDC hDC, INT Xc, INT Yc, INT R );


#endif /*_SPHERE_H_*/

/* END OF 'SPHERE.H' FILE */
