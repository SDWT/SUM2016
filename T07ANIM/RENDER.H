/* FILENAME: RENDER.H
 * PROGRAMMER: DS1
 * DATE: 13.06.2016
 * PURPOSE: Animation system difinitions
*/

#ifndef __RENDER_H_
#define __RENDER_H_

#include "def.h"

/* Primitive representation type */
typedef struct
{
  VEC *P;          /* Primitive points array */
  INT NumOfP;      /* Point array size */
  INT (*Edges)[2]; /* Edges array - array of point pairs */
  INT NumOfE;      /* Edges array size */
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


#endif /* __RENDER_H_ */

/* END OF 'RENDER.H' FILE */
