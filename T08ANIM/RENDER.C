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
  INT loc;
  MATR M;

  /* Build transform matrix */
  M = MatrMulMatr(DS1_RndMatrWorld,
    MatrMulMatr(DS1_RndMatrView, DS1_RndMatrProj));
  glLoadMatrixf(M.A[0]);

  glUseProgram(DS1_RndPrg);

  /* Setup global variables */
  if ((loc = glGetUniformLocation(DS1_RndPrg, "MatrWorld")) != -1)
    glUniformMatrix4fv(loc, 1, FALSE, DS1_RndMatrWorld.A[0]);
  if ((loc = glGetUniformLocation(DS1_RndPrg, "MatrView")) != -1)
    glUniformMatrix4fv(loc, 1, FALSE, DS1_RndMatrView.A[0]);
  if ((loc = glGetUniformLocation(DS1_RndPrg, "MatrProj")) != -1)
    glUniformMatrix4fv(loc, 1, FALSE, DS1_RndMatrProj.A[0]);
  if ((loc = glGetUniformLocation(DS1_RndPrg, "Time")) != -1)
    glUniform1f(loc, DS1_Anim.Time);


  /* Activete primitive vertex array */
  glBindVertexArray(Pr->VA);
  /* Activete primitive index buffer */
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Pr->IBuf);
  /* Draw primitive */
  glDrawElements(GL_TRIANGLES, Pr->NumOfI, GL_UNSIGNED_INT, NULL);
  glUseProgram(0);
} /* End of 'DS1_RndPrimDraw' function */

/* Primitive free function.
 * ARGUMENTS:
 *   - primtive to free:
 *       ds1PRIM *Pr;
 * RETURNS: None.
 */
VOID DS1_RndPrimFree( ds1PRIM *Pr )
{
  glBindVertexArray(Pr->VA);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glDeleteBuffers(1, &Pr->VBuf);
  glBindVertexArray(0);
  glDeleteVertexArrays(1, &Pr->VA);
  glDeleteBuffers(1, &Pr->IBuf);
  memset(Pr, 0, sizeof(ds1PRIM));
} /* End of 'DS1_RndPrimFree' function */


/* END OF 'RENDER.C' FILE */