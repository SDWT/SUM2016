/* FILENAME: GRID.C
 * PROGRAMMER: DS1
 * DATE: 17.06.2016
 * PURPOSE: Sprite unit drawing module
 */

#include <stdlib.h>
#include <string.h>

#include "anim.h"

/* Create grid function.
 * ARGUMENTS:
 *   - Grid structure pointer:
 *       ds1OBJ *Obj;
 *   - counter vertex on width and hight:
 *       INT N, M;
 * RETURNS: 
 *   (BOOL) TRUE is success, FALSE otherwise.
 */
BOOL DS1_GridCreate( ds1GRID *G, INT N, INT M )
{
  INT i, j;

  if ((G->P = malloc(sizeof(ds1VERTEX) * N * M)) == NULL)
    return FALSE;

  for (i = 0; i < N; i++)
    for (j = 0; j < M; j++)
    {
      G->P[M * i + j].T = Vec2Set((FLT)j / (M - 1), (FLT)i / (N - 1));
      G->P[M * i + j].C = Color4Set(1, 1, 1, 1);
    }
  G->M = M;
  G->N = N;
  return TRUE;
} /* End of 'DS1_GridCreate' function */

/* Create grid plane function.
 * ARGUMENTS:
 *   - Grid structure pointer:
 *       ds1OBJ *Obj;
 *   - counter vertex on width and hight:
 *       INT N, M;
 *   - Vectors directions grid:
 *       VEC Dir, Right;
 * RETURNS: 
 *   (BOOL) TRUE is success, FALSE otherwise.
 */
BOOL DS1_GridCreatePlane( ds1GRID *G, INT N, INT M, VEC Dir, VEC Right )
{
  INT i, j;
  VEC
    DirN = VecNormalize(Dir), 
    RigN = VecNormalize(Right),
    Up = VecNormalize(VecCrossVec(DirN, RigN));
  DirN = VecDivNum(DirN, M);
  RigN = VecDivNum(RigN, N);

  if (!DS1_GridCreate(G, N, M))
    return FALSE;

  for (i = 0; i < N; i++)
    for (j = 0; j < M; j++)
    {
      G->P[M * i + j].P = VecAddVec(VecMullNum(VecSet(0, 0, 1), i), VecMullNum(VecSet(1, 0, 0), j));
      G->P[M * i + j].N = VecSet(0, 1, 0);

      G->P[M * i + j].P = VecAddVec(VecMullNum(DirN, i), VecMullNum(RigN, j));
      G->P[M * i + j].N = Up;
    }

    return TRUE;
} /* End of 'DS1_GridCreatePlane' function */

/* Create grid sphere function.
 * ARGUMENTS:
 *   - Grid structure pointer:
 *       ds1OBJ *Obj;
 *   - counter vertex on width and hight:
 *       INT N, M;
 * RETURNS: 
 *   (BOOL) TRUE is success, FALSE otherwise.
 */
BOOL DS1_GridCreateSphere( ds1GRID *G, INT N, INT M, INT R )
{
  INT i, j;

  if (!DS1_GridCreate(G, N, M))
    return FALSE;

  for (i = 0; i < N; i++)
  {
    DBL theta = DS1_PI * i / (N - 1);
    for (j = 0; j < M; j++)
    {
      DBL r = R , phi = 2 * DS1_PI * j / (M - 1);
      VEC A = VecSet(sin(theta) * cos(phi), cos(theta), sin(theta) * sin(phi));

      G->P[M * i + j].N = A;
      G->P[M * i + j].P = VecMullNum(A, R);
    }
  }

  return TRUE;
} /* End of 'DS1_GridCreateSphere' function */

/* Create grid plane function.
 * ARGUMENTS:
 *   - Grid structure pointer:
 *       ds1OBJ *Obj;
 * RETURNS: 
 *   (BOOL) TRUE is success, FALSE otherwise.
 */
BOOL DS1_GridCreateObj( ds1GRID *G, ds1OBJ *Obj, INT MtlNumber )
{
  INT i, j, p;
  INT *Index;
  INT NumOfI;
  INT NumOfV;

  if ((Index = malloc(sizeof(INT) * (G->N - 1) * (G->M - 1))) == NULL)
    return FALSE;

  /* Allocate memory for primitives */
  if ((Obj->Prims = malloc(sizeof(ds1PRIM) * 1)) == NULL)
  {
    return FALSE;
  }
  Obj->NumOfPrims = 1;

  /* Read primitive info */
  NumOfI = 3 * 2 * (G->N - 1) * (G->M - 1);
  NumOfV = G->N * G->M;
  /* Allocate memory for primitive */
  if ((Index = malloc(sizeof(INT) * NumOfI)) == NULL)
  {
    free(Obj->Prims);
    memset(Obj, 0, sizeof(ds1OBJ));
    return FALSE;
  }
  Obj->Prims[0].NumOfI = NumOfI;
  Obj->Prims[0].M = MatrixIdentity();
  Obj->Prims[0].MtlNo = MtlNumber;

  /*fread(Index, sizeof(IndexNT), NumOfIndex, F);*/
  p = 0;
  for (i = 0; i < G->N - 1; i++)
    for (j = 0; j < G->M - 1; j++)
    {
      Index[p++] = i * G->M + j;
      Index[p++] = (i + 1) * G->M + j + 1;
      Index[p++] = (i + 1) * G->M + j;

      Index[p++] = i * G->M + j;
      Index[p++] = i * G->M + j + 1;
      Index[p++] = (i + 1) * G->M + j + 1;
    }

  /* Create OpenGL buffers */
  glGenVertexArrays(1, &Obj->Prims[0].VA);
  glGenBuffers(1, &Obj->Prims[0].VBuf);
  glGenBuffers(1, &Obj->Prims[0].IBuf);

  /* Activate vertex array */
  glBindVertexArray(Obj->Prims[0].VA);
  /* Activate vertex buffer */
  glBindBuffer(GL_ARRAY_BUFFER, Obj->Prims[0].VBuf);
  /* Store vertex data */
  glBufferData(GL_ARRAY_BUFFER, sizeof(ds1VERTEX) * NumOfV, G->P, GL_STATIC_DRAW);

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

  /* Indexndices */
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Obj->Prims[p].IBuf);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(INT) * NumOfI, Index, GL_STATIC_DRAW);

  /* Disable vertex array */
  glBindVertexArray(0);

  Obj->NumOfPrims = 1;
  return TRUE;
} /* End of 'DS1_GridCreateObj' function */

/* Free grid function.
 * ARGUMENTS:
 *   - Grid structure pointer:
 *       ds1OBJ *Obj;
 *   - counter vertex on width and hight:
 *       INT N, M;
 * RETURNS: None.
 */
VOID DS1_GridFree( ds1GRID *G )
{
  free(G->P);
  G->N = G->M = 0;
} /* End of 'DS1_GridFree' function */

/* END OF 'GRID.C' FILE */
