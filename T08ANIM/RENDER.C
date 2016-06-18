/* FILENAME: RENDER.C
 * PROGRAMMER: DS1
 * DATE: 15.06.2016
 * PURPOSE: Animation system difinitions
 */

#include <stdio.h>

#include "anim.h"

/* Global transformation matrices */
MATR
  DS1_RndMatrWorld, /* World (object) transformation matrix */
  DS1_RndMatrView,  /* Camera view transform */
  DS1_RndMatrProj;  /* Projection transform */

/* Projection parameters */
DBL
  DS1_RndProjDist = 0.1, /* Near clip plane */
  DS1_RndFarClip = 1000,  /* Far clip plane */
  DS1_RndProjSize = 0.1; /* Project plane size */

/* Shader support */
UINT DS1_RndPrg;

INT DS1_IsNor = 1, DS1_IsPart = 0;
FLT DS1_Scale = 1;

/* Setup projection function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID DS1_RndSetProj( VOID )
{
  DBL ratio_x = 1, ratio_y = 1;

  if (DS1_Anim.W >= DS1_Anim.H)
    ratio_x = (DBL)DS1_Anim.W / DS1_Anim.H;
  else
    ratio_y = (DBL)DS1_Anim.H / DS1_Anim.W;

  DS1_RndMatrProj = MatrFrustum(-ratio_x * DS1_RndProjSize / 2,
                                 ratio_x * DS1_RndProjSize / 2,
                                -ratio_y * DS1_RndProjSize / 2,
                                 ratio_y * DS1_RndProjSize / 2,
                                 DS1_RndProjDist, DS1_RndFarClip);
  /*MatrOrtho*/
} /* End of 'DS1_RndSetProj' function */

/* END OF 'RENDER.C' FILE */
