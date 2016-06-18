/* FILENAME: RENDER.C
 * PROGRAMMER: DS1
 * DATE: 15.06.2016
 * PURPOSE: Animation system difinitions
 */

#include <stdio.h>

#include "anim.h"

MATR DS1_RndMatrWorld, 
     DS1_RndMatrView, 
     DS1_RndMatrProj;
DBL DS1_RndProjSize = 1, DS1_RndProjDist = 1, DS1_RndFarClip = 1000;
UINT DS1_RndPrg = 0;

INT DS1_IsNor = 1, DS1_IsPart = 0;
FLT DS1_Scale = 1;

/* Materials array */
ds1MTL DS1_RndMaterials[DS1_MAX_MATERIALS];
INT DS1_RndNumOfMaterials;


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
  INT loc, mtl;
  MATR M, MSave;

  for (i = 0; i < Obj->NumOfPrims; i++)
  {
    /* Build transform matrix */
    MSave = DS1_RndMatrWorld;
    DS1_RndMatrWorld = MatrMulMatr(DS1_RndMatrWorld, Obj->Prims[i].M);
    M = MatrMulMatr(DS1_RndMatrWorld,
      MatrMulMatr(DS1_RndMatrView, DS1_RndMatrProj));
    glLoadMatrixf(M.A[0]);
    /*
    glBegin(GL_LINES);
      glColor3d(1, 0, 0);
      glVertex3d(0, 0, 0);
      glVertex4d(1, 0, 0, 0);
      glColor3d(0, 1, 0);
      glVertex3d(0, 0, 0);
      glVertex4d(0, 1, 0, 0);
      glColor3d(0, 0, 1);
      glVertex3d(0, 0, 0);
      glVertex4d(0, 0, 1, 0);
    glEnd();
    */

    glUseProgram(DS1_RndPrg);

    mtl = Obj->Prims[i].MtlNo;
    if (mtl != -1)
    {
      if (DS1_RndMaterials[mtl].TexNo != 0)
      {
        glBindTexture(GL_TEXTURE_2D, DS1_RndMaterials[mtl].TexNo);
        if ((loc = glGetUniformLocation(DS1_RndPrg, "IsTexture")) != -1)
          glUniform1i(loc, 1);
      }
      else
      {
        if ((loc = glGetUniformLocation(DS1_RndPrg, "IsTexture")) != -1)
          glUniform1i(loc, 0);
      }
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
    }

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
    if ((loc = glGetUniformLocation(DS1_RndPrg, "IsPart")) != -1)
      glUniform1i(loc, DS1_IsPart);    
    if ((loc = glGetUniformLocation(DS1_RndPrg, "IsNor")) != -1)
      glUniform1i(loc, DS1_IsNor);

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

/* Material find by name function.
 * ARGUMENTS:
 *   - material name:
 *       CHAR *Name;
 * RETURNS:
 *   (INT) number of found material or -1 if no result.
 */
INT DS1_RndFindMaterial( CHAR *Name )
{
  INT i;

  for (i = 0; i < DS1_RndNumOfMaterials; i++)
    if (strcmp(Name, DS1_RndMaterials[i].Name) == 0)  /* #include <string.h> */
      return i;
  return -1;
} /* End of 'DS1_RndFindMaterial' function */

/* Material load function.
 * ARGUMENTS:
 *   - material file name:
 *       CHAR *FileName;
 * RETURNS: None.
*/
VOID DS1_RndLoadMaterials( CHAR *FileName )
{
  INT i, NumOfMaterials;
  UINT t;
  DWORD Sign;
  FILE *F;
  ds1MTL M;
  BYTE *Image;

  if ((F = fopen(FileName, "rb")) == NULL)
    return;
  /* Read and check file signature */
  fread(&Sign, 4, 1, F);
  if (Sign != *(DWORD *)"GMT")
  {
    fclose(F);
    return;
  }

  /* Read all materials */
  fread(&NumOfMaterials, 4, 1, F);
  for (i = 0; i < NumOfMaterials; i++)
  {
    if (DS1_RndNumOfMaterials >= DS1_MAX_MATERIALS)
      break;

    /* Read illumination coefficients and texture parameters */
    fread(&M, sizeof(ds1MTL), 1, F);
    
    /* Read image */
    if (M.TexW != 0 && M.TexH != 0 && M.TexNo != 0)
    {
      /* Allocate memory for texture image */
      if ((Image = malloc(M.TexW * M.TexH * M.TexNo)) == NULL)
      {
        fclose(F);
        return;
      }
      fread(Image, M.TexNo, M.TexW * M.TexH, F);
      glGenTextures(1, &t);
      glBindTexture(GL_TEXTURE_2D, t);
      gluBuild2DMipmaps(GL_TEXTURE_2D, M.TexNo, M.TexW, M.TexH,
        M.TexNo == 3 ? GL_BGR_EXT : GL_BGRA, GL_UNSIGNED_BYTE, Image);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glBindTexture(GL_TEXTURE_2D, 0);
      M.TexNo = t;
      free(Image);
    }
    else
      M.TexNo = 0;
    /* Add material to animation and OpenGL */
    DS1_RndMaterials[DS1_RndNumOfMaterials++] = M;
  }
  fclose(F);
} /* End of 'DS1_RndLoadMaterials' function */

/*
Prim +Id,

(BOOL) PrimCreate(ds1Prim *Prim, *V, NumOfV, *I, NumOfI ...)
(VOID) PrimDraw(ds1Prim *Prim)
(VOID) PrimFree(ds1Prim *Prim)
*/

/*
Obj
(VOID) ObjCreate(ds1Obj *Obj)
(VOID) ObjAddPrim(ds1Obj *Obj, ds1Prim *Prim)
(VOID) ObjDraw(ds1Obj *Obj)
(VOID) ObjFree(ds1Obj *Obj)
*/

/* END OF 'RENDER.C' FILE */
