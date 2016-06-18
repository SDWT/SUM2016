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
  INT i, j, size = N * M * sizeof(ds1VERTEX);

  memset(G, 0, sizeof(ds1GRID));
  if ((G->P = malloc(size)) == NULL)
    return FALSE;
  memset(G, 0, size);

  for (i = 0; i < N; i++)
    for (j = 0; j < M; j++)
    {
      G->P[M * i + j].P = VecSet(2.0 * i / (N - 1.0) - 1, 0, 2.0 * j / (M - 1.0) - 1);
      G->P[M * i + j].N = VecSet(0, 1, 0);
      G->P[M * i + j].T = Vec2Set(j / (M - 1.0), (FLT)i / (N - 1.0));
      G->P[M * i + j].C = Color4Set(1, 1, 1, 1);
    }
  G->M = M;
  G->N = N;
  return TRUE;
} /* End of 'DS1_GridCreate' function */

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
  if (G->P != NULL)
    free(G->P);
  G->N = G->M = 0;
} /* End of 'DS1_GridFree' function */

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

/* Prim create to grid function.
 * ARGUMENTS:
 *   - Grid structure pointer:
 *       ds1OBJ *Obj;
 * RETURNS: 
 *   (BOOL) TRUE is success, FALSE otherwise.
 */
BOOL DS1_Grid2Prim( ds1GRID *G, ds1PRIM *Pr )
{
  INT i, j, p, n = 3 * 2 * (G->N - 1) * (G->M - 1), size = n * sizeof(INT);

  INT *Index;
  INT NumOfI;
  INT NumOfV;

  memset(Pr, 0, sizeof(ds1PRIM));
  if ((Index = malloc(size)) == NULL)
    return FALSE;
  memset(Index, 0, size);
  
  /* Allocate memory for primitives */
  if ((Pr = malloc(sizeof(ds1PRIM) * 1)) == NULL)
  {
    return FALSE;
  }

  /* Read primitive info */
  NumOfI = n;
  NumOfV = G->N * G->M;
  /* Allocate memory for primitive */
  if ((Index = malloc(sizeof(INT) * NumOfI)) == NULL)
  {
    free(Pr);
    memset(Pr, 0, sizeof(ds1PRIM));
    return FALSE;
  }
  /*fread(Index, sizeof(IndexNT), NumOfIndex, F);*/
  for (i = 0, p = 0; i < G->N - 1; i++)
    for (j = 0; j < G->M - 1; j++)
    {
      Index[p++] = i * G->M + j;
      Index[p++] = (i + 1) * G->M + j + 1;
      Index[p++] = (i + 1) * G->M + j;

      Index[p++] = i * G->M + j;
      Index[p++] = i * G->M + j + 1;
      Index[p++] = (i + 1) * G->M + j + 1;
    }

  Pr->NumOfI = NumOfI;
  Pr->M = MatrixIdentity();


  DS1_RndPrimCreate(Pr, G->P, NumOfV, Index, NumOfI);
  free(Index);
  return TRUE;
} /* End of 'DS1_GridCreateObj' function */

/* Create grid plane function.
 * ARGUMENTS:
 *   - Triangle points:
 *       VEC P0, P1, P2;
 * RETURNS: 
 *   (VEC) normal.
 */
VEC DS1_TriangleNormal( VEC P0, VEC P1, VEC P2 )
{
  return VecNormalize(VecCrossVec(VecSubVec(P1, P0), VecSubVec(P2, P0)));

} /* End of 'DS1_TriangleNormal' function */

/* Create grid plane function.
 * ARGUMENTS:
 *   - Grid structure pointer:
 *       ds1OBJ *Obj;
 * RETURNS: 
 *   (BOOL) TRUE is success, FALSE otherwise.
 */
BOOL DS1_GridEvalNormals( ds1GRID *G )
{
  INT i, j, p, n = 3 * 2 * (G->N - 1) * (G->M - 1), size = n * sizeof(INT);
  INT n0, n1, n2;
  VEC N;

  /* Set to zero all point normal */
  for (p = 0; p < G->N - 1; p++)
    G->P[p].N = VecSet(0, 0, 0);


  /*fread(Index, sizeof(IndexNT), NumOfIndex, F);*/
  for (i = 0, p = 0; i < G->N - 1; i++, p++)
    for (j = 0; j < G->M - 1; j++, p++)
    {
      /* 0 triangle */
      n0 = p;
      n1 = p + G->M + 1;
      n2 = p + G->M;
      N = DS1_TriangleNormal(G->P[n0].P, G->P[n1].P, G->P[n2].P);
      G->P[n0].N = VecAddVec( G->P[n0].N, N);
      G->P[n1].N = VecAddVec( G->P[n1].N, N);
      G->P[n2].N = VecAddVec( G->P[n2].N, N);

      /* 1 triangle */
      n0 = p;
      n1 = p + 1;
      n2 = p + G->M + 1;
      N = DS1_TriangleNormal(G->P[n0].P, G->P[n1].P, G->P[n2].P);
      G->P[n0].N = VecAddVec( G->P[n0].N, N);
      G->P[n1].N = VecAddVec( G->P[n1].N, N);
      G->P[n2].N = VecAddVec( G->P[n2].N, N);

    }

  /* Normalize all point normal */
  for (p = 0; p < G->N - 1; p++)
    G->P[p].N = VecNormalize(G->P[p].N);
  return TRUE;
} /* End of 'DS1_GridCreateObj' function */

/* Prim create from image file function.
 * ARGUMENTS:
 *   - Prim structure pointer:
 *       ds1PRIM *Pr;
 *   - Image file name:
 *       CHAR *FileName;
 * RETURNS: 
 *   (BOOL) TRUE is success, FALSE otherwise.
 */
BOOL DS1_RndPrimImageLandscape( ds1PRIM *Pr, CHAR *FileName )
{
  INT i, j, p;
  ds1IMG Im;
  ds1GRID G;

  if (!DS1_ImageLoad(&Im, FileName))
    return FALSE;
  if (!DS1_GridCreate(&G, Im.W, Im.H))
  {
    DS1_ImageFree(&Im);
    return FALSE;
  }

  for (i = 0, p = 0; i < G.N - 1; i++, p++)
    for (j = 0; j < G.M - 1; j++, p++)
    {
      DWORD c = (DS1_ImageGetP(&Im, i, j) >> 8) & 0xFF;

      G.P[p].P.Y = c / 255.0 / 30;
    }
  return TRUE;
} /* End of 'DS1_GridCreateObj' function */


/* END OF 'GRID.C' FILE */
