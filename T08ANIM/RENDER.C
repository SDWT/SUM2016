/* FILENAME: RENDER.C
 * PROGRAMMER: DS1
 * DATE: 15.06.2016
 * PURPOSE: Animation system difinitions
 */

#include "anim.h"

MATR DS1_RndMatrWorld, 
     DS1_RndMatrView, 
     DS1_RndMatrProj;
DBL DS1_RndProjSize = 1, DS1_RndProjDist = 1, DS1_RndFarClip = 1000;
UINT DS1_RndPrg = 0;

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


/* Object draw function.
 * ARGUMENTS:
 *   - object structure pointer:
 *       ds1OBJ *Obj;
 * RETURNS: None.
 */
VOID DS1_RndObjDraw( ds1OBJ *Obj )
{
  INT i;
  INT loc;
  MATR M, MSave;

  for (i = 0; i < Obj->NumOfPrims; i++)
  {
    /* Build transform matrix */
    MSave = DS1_RndMatrWorld;
    DS1_RndMatrWorld = MatrMulMatr(DS1_RndMatrWorld, Obj->Prims[i].M);
    M = MatrMulMatr(DS1_RndMatrWorld,
      MatrMulMatr(DS1_RndMatrView, DS1_RndMatrProj));
    glLoadMatrixf(M.A[0]);

    glUseProgram(DS1_RndPrg);

    /* Setup global variables */
    if ((loc = glGetUniformLocation(DS1_RndPrg, "MatrWVP")) != -1)
      glUniformMatrix4fv(loc, 1, FALSE, M.A[0]);
    if ((loc = glGetUniformLocation(DS1_RndPrg, "MatrWorld")) != -1)
      glUniformMatrix4fv(loc, 1, FALSE, DS1_RndMatrWorld.A[0]);
    if ((loc = glGetUniformLocation(DS1_RndPrg, "MatrView")) != -1)
      glUniformMatrix4fv(loc, 1, FALSE, DS1_RndMatrView.A[0]);
    if ((loc = glGetUniformLocation(DS1_RndPrg, "MatrProj")) != -1)
      glUniformMatrix4fv(loc, 1, FALSE, DS1_RndMatrProj.A[0]);
    if ((loc = glGetUniformLocation(DS1_RndPrg, "Time")) != -1)
      glUniform1f(loc, DS1_Anim.Time);
    if ((loc = glGetUniformLocation(DS1_RndPrg, "PartNo")) != -1)
      glUniform1i(loc, i);
    if ((loc = glGetUniformLocation(DS1_RndPrg, "IsNor")) != -1)
      glUniform1i(loc, DS1_IsNor);
    if ((loc = glGetUniformLocation(DS1_RndPrg, "IsPart")) != -1)
      glUniform1i(loc, DS1_IsPart);

    /* Activete primitive vertex array */
    glBindVertexArray(Obj->Prims[i].VA);
    /* Activete primitive index buffer */
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Obj->Prims[i].IBuf);
    /* Draw primitive */
    glDrawElements(GL_TRIANGLES, Obj->Prims[i].NumOfI, GL_UNSIGNED_INT, NULL);
    glUseProgram(0);
    DS1_RndMatrWorld = MSave;
  }
} /* End of 'DS1_RndObjDraw' function */

/* Object free function.
 * ARGUMENTS:
 *   - object structure pointer:
 *       ds1OBJ *Obj;
 * RETURNS: None.
 */
VOID DS1_RndObjFree( ds1OBJ *Obj )
{
  INT i;

  for (i = 0; i < Obj->NumOfPrims; i++)
  {
    glBindVertexArray(Obj->Prims[i].VA);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &Obj->Prims[i].VBuf);
    glBindVertexArray(0);
    glDeleteVertexArrays(1, &Obj->Prims[i].VA);
    glDeleteBuffers(1, &Obj->Prims[i].IBuf);
  }
  free(Obj->Prims);
  memset(Obj, 0, sizeof(ds1OBJ));
} /* End of 'DS1_RndObjFree' function */

/* END OF 'RENDER.C' FILE */