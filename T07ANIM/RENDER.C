/* FILENAME: RENDER.C
 * PROGRAMMER: DS1
 * DATE: 13.06.2016
 * PURPOSE: Animation system difinitions
*/

#include "anim.h"

MATR DS1_RndMatrWorld, 
     DS1_RndMatrView, 
     DS1_RndMatrProj;
DBL DS1_RndProjSize = 0.1, DS1_RndProjDist = 0.1, DS1_RndFarClip = 100;

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


/* Primitive draw function.
 * ARGUMENTS:
 *   - primtive to draw:
 *       ds1PRIM *Pr;
 * RETURNS: None.
 */
VOID DS1_RndPrimDraw( ds1PRIM *Pr )
{
  INT i;
  MATR M;
  POINT *pts;

  /* Build transform matrix */
  M = MatrMulMatr(DS1_RndMatrWorld,
    MatrMulMatr(DS1_RndMatrView, DS1_RndMatrProj));

  /* Transform all points */
  pts = malloc(sizeof(POINT) * Pr->NumOfP);
  if (pts == NULL)
    return;
  
  for (i = 0; i < Pr->NumOfP; i++)
  {
    /* NDC */
    VEC p = PointTransform4(Pr->P[i], M);

    pts[i].x = (LONG)((p.X + 1) * DS1_Anim.W / 2);
    pts[i].y = (LONG)((-p.Y + 1) * DS1_Anim.H / 2);
  }

  SelectObject(DS1_Anim.hDC, GetStockObject(DC_PEN));
  /* Draw all lines */
  for (i = 0; i < Pr->NumOfE; i++)
  {
    INT n0 = Pr->Edges[i][0], n1 = Pr->Edges[i][1];

    SetDCPenColor(DS1_Anim.hDC, RGB(i * 255 / Pr->NumOfE, 0, 255 - i * 255 / Pr->NumOfE));

    MoveToEx(DS1_Anim.hDC, pts[n0].x, pts[n0].y, NULL);
    LineTo(DS1_Anim.hDC, pts[n1].x, pts[n1].y);
  }
  free(pts);
} /* End of 'DS1_RndPrimDraw' function */

/* Primitive free function.
 * ARGUMENTS:
 *   - primtive to free:
 *       ds1PRIM *Pr;
 * RETURNS: None.
 */
VOID DS1_RndPrimFree( ds1PRIM *Pr )
{
  if (Pr->P != NULL)
    free(Pr->P);
  if (Pr->Edges != NULL)
    free(Pr->Edges);
  memset(Pr, 0, sizeof(ds1PRIM));
} /* End of 'DS1_RndPrimFree' function */


/* END OF 'RENDER.C' FILE */