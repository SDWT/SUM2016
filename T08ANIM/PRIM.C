/* FILENAME: PRIM.C
 * PROGRAMMER: DS1
 * DATE: 18.06.2016
 * PURPOSE: Primitive functions
 */

#include "anim.h"

/* Primitive create function.
 * ARGUMENTS:
 *   - primitive structure pointer:
 *       ds1PRIM *Pr;
 *   - vertex array:
 *       ds1VERTEX *V;
 *   - vertex array size:
 *       INT NumOfV;
 *   - index array:
 *       INT *I;
 *   - INT array size:
 *       INT NumOfI;
 * RETURNS: None.
 */
VOID DS1_RndPrimCreate( ds1PRIM *Pr, ds1VERTEX *V, INT NumOfV, INT *I, INT NumOfI )
{
  memset(Pr, 0, sizeof(ds1PRIM));

  Pr->M = MatrixIdentity();
  Pr->NumOfI = NumOfI;

  /* Create OpenGL buffers */
  glGenVertexArrays(1, &Pr->VA);
  glGenBuffers(1, &Pr->VBuf);
  glGenBuffers(1, &Pr->IBuf);

  /* Activate vertex array */
  glBindVertexArray(Pr->VA);
  /* Activate vertex buffer */
  glBindBuffer(GL_ARRAY_BUFFER, Pr->VBuf);
  /* Store vertex data */
  glBufferData(GL_ARRAY_BUFFER, sizeof(ds1VERTEX) * NumOfV, V, GL_STATIC_DRAW);

  /* Setup data order */
  /*                    layout,
   *                      components count,
   *                          type
   *                                    should be normalize,
   *                                           vertex structure size in bytes (stride),
   *                                               offset in bytes to field start */
  glVertexAttribPointer(0, 3, GL_FLOAT, FALSE, sizeof(ds1VERTEX),
                        (VOID *)0); /* position */
  glVertexAttribPointer(1, 2, GL_FLOAT, FALSE, sizeof(ds1VERTEX),
                        (VOID *)sizeof(VEC)); /* texture coordinates */
  glVertexAttribPointer(2, 3, GL_FLOAT, FALSE, sizeof(ds1VERTEX),
                        (VOID *)(sizeof(VEC) + sizeof(VEC2))); /* normal */
  glVertexAttribPointer(3, 4, GL_FLOAT, FALSE, sizeof(ds1VERTEX),
                        (VOID *)(sizeof(VEC) * 2 + sizeof(VEC2))); /* color */

  /* Enable used attributes */
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);
  glEnableVertexAttribArray(3);

  /* Indices */
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Pr->IBuf);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(INT) * NumOfI, I, GL_STATIC_DRAW);

  /* Disable vertex array */
  glBindVertexArray(0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
} /* End of 'DS1_RndPrimCreate' function */

/* Primitive draw function.
 * ARGUMENTS:
 *   - primitive structure pointer:
 *       ds1PRIM *Pr;
 * RETURNS: None.
 */
VOID DS1_RndPrimDraw( ds1PRIM *Pr )
{
  INT loc, mtl;
  MATR M, MSave;

  /* Build transform matrix */
  MSave = DS1_RndMatrWorld;
  DS1_RndMatrWorld = MatrMulMatr(DS1_RndMatrWorld, Pr->M);
  M = MatrMulMatr(DS1_RndMatrWorld, MatrMulMatr(DS1_RndMatrView, DS1_RndMatrProj));
  glLoadMatrixf(M.A[0]);

  /* Enable base shader */
  glUseProgram(DS1_RndPrg);

  mtl = Pr->MtlNo;
  if (mtl == -1)
    mtl = 0;
  if (DS1_RndMaterials[mtl].TexNo != 0)
  {
    glBindTexture(GL_TEXTURE_2D, DS1_RndMaterials[mtl].TexNo);
    if ((loc = glGetUniformLocation(DS1_RndPrg, "IsTexture")) != -1)
      glUniform1i(loc, 1);
  }
  else
    if ((loc = glGetUniformLocation(DS1_RndPrg, "IsTexture")) != -1)
      glUniform1i(loc, 0);
  if ((loc = glGetUniformLocation(DS1_RndPrg, "Ka")) != -1)
    glUniform3fv(loc, 1, &DS1_RndMaterials[mtl].Ka.X);
  if ((loc = glGetUniformLocation(DS1_RndPrg, "Kd")) != -1)
    glUniform3fv(loc, 1, &DS1_RndMaterials[mtl].Kd.X);
  if ((loc = glGetUniformLocation(DS1_RndPrg, "Ks")) != -1)
    glUniform3fv(loc, 1, &DS1_RndMaterials[mtl].Ks.X);
  if ((loc = glGetUniformLocation(DS1_RndPrg, "Ph")) != -1)
    glUniform1f(loc, DS1_RndMaterials[mtl].Ph);
  if ((loc = glGetUniformLocation(DS1_RndPrg, "Trans")) != -1)
    glUniform1f(loc, DS1_RndMaterials[mtl].Trans);
  if ((loc = glGetUniformLocation(DS1_RndPrg, "Id")) != -1)
    glUniform1i(loc, Pr->Id);

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
  /*if ((loc = glGetUniformLocation(DS1_RndPrg, "PartNo")) != -1)
    glUniform1i(loc, i);
    */
  if ((loc = glGetUniformLocation(DS1_RndPrg, "IsPart")) != -1)
    glUniform1i(loc, DS1_IsPart);    
  if ((loc = glGetUniformLocation(DS1_RndPrg, "IsNor")) != -1)
    glUniform1i(loc, DS1_IsNor);

  /* Activete primitive vertex array */
  glBindVertexArray(Pr->VA);
  /* Activete primitive index buffer */
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Pr->IBuf);
  /* Draw primitive */
  glDrawElements(GL_TRIANGLES, Pr->NumOfI, GL_UNSIGNED_INT, NULL);

  glBindTexture(GL_TEXTURE_2D, 0);
  glBindVertexArray(0);;
  glUseProgram(0);
  DS1_RndMatrWorld = MSave;
} /* End of 'DS1_RndPrimDraw' function */

/* Primitive free function.
 * ARGUMENTS:
 *   - primitive structure pointer:
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

/* END OF 'PRIM.C' FILE */
