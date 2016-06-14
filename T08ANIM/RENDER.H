/* FILENAME: RENDER.H
 * PROGRAMMER: DS1
 * DATE: 14.06.2016
 * PURPOSE: Animation system difinitions
 */

#ifndef __RENDER_H_
#define __RENDER_H_

#include "def.h"

/* Vertex representation type */
typedef struct
{
  VEC  P;  /* Vertex position */
  VEC2 T;  /* Vertex texture coordinates */
  VEC  N;  /* Normal at vertex */
  ds1COLOR C;  /* Vertex color */
} ds1VERTEX;

/* Primitive representation type */
typedef struct
{
  ds1VERTEX *V;  /* Primitive vertex array */
  INT NumOfV;    /* Point array size */
  INT *I;        /* Facets index array */
  INT NumOfI;    /* Facets index array size */
} ds1PRIM;

extern MATR DS1_RndMatrWorld, DS1_RndMatrView, DS1_RndMatrProj;
extern DBL DS1_RndProjSize, DS1_RndProjDist, DS1_RndFarClip;


/* Setup projection function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID DS1_RndSetProj( VOID );

/* Primitive draw function.
 * ARGUMENTS:
 *   - primtive to draw:
 *       ds1PRIM *Pr;
 * RETURNS: None.
 */
VOID DS1_RndPrimDraw( ds1PRIM *Pr );

/* Primitive free function.
 * ARGUMENTS:
 *   - primtive to free:
 *       ds1PRIM *Pr;
 * RETURNS: None.
 */
VOID DS1_RndPrimFree( ds1PRIM *Pr );

/* Load primitive from '*.g3d' file function.
 * ARGUMENTS:
 *   - primitive structure pointer:
 *       ds1PRIM *Pr;
 *   - file name:
 *       CHAR *FileName;
 * RETURNS:
 *   (BOOL) TRUE is success, FALSE otherwise.
 */
BOOL DS1_RndPrimLoad( ds1PRIM *Pr, CHAR *FileName );

#endif /* __RENDER_H_ */

/* END OF 'RENDER.H' FILE */
