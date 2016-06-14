/* FILENAME: LOADOBJ.C
 * PROGRAMMER: DS1
 * DATE: 07.06.2016
 * PURPOSE: Sprite unit drawing module
 */

#include <stdio.h>

#include "render.h"

/* Vertex representation type */
typedef struct
{
  VEC  P;      /* Vertex position */
  VEC2 T;      /* Vertex texture coordinates */
  VEC  N;      /* Normal at vertex */
  ds1COLOR C;  /* Vertex color */
} ds1VERTEX;

/* Load primitive from '*.g3d' file function.
 * ARGUMENTS:
 *   - primitive structure pointer:
 *       ds1PRIM *Pr;
 *   - file name:
 *       CHAR *FileName;
 * RETURNS:
 *   (BOOL) TRUE is success, FALSE otherwise.
 */
BOOL DS1_RndPrimLoad( ds1PRIM *Pr, CHAR *FileName )
{
  FILE *F;
  DWORD Sign;
  INT NumOfPrimitives;
  CHAR MtlFile[300];
  INT NumOfP;
  INT NumOfF;
  CHAR Mtl[300];
  ds1VERTEX V;
  INT p, N0, N1, N2;

  memset(Pr, 0, sizeof(ds1PRIM));

  F = fopen(FileName, "rb");
  if (F == NULL)
    return FALSE;

  /* Read signature */
  fread(&Sign, 4, 1, F);
  if (Sign != *(DWORD *)"G3D")
  {
    fclose(F);
    return FALSE;
  }
  fread(&NumOfPrimitives, 4, 1, F);
  fread(MtlFile, 1, 300, F);
  for (p = 0; p < NumOfPrimitives; p++)
  {
    INT i;

    /* Read primitive info */
    fread(&NumOfP, 4, 1, F);
    fread(&NumOfF, 4, 1, F);
    fread(Mtl, 1, 300, F);

    /* Allocate memory for primitive */
    if ((Pr->P = malloc(sizeof(VEC) * NumOfP)) == NULL)
    {
      fclose(F);
      return FALSE;
    }
    if ((Pr->Edges = malloc(sizeof(INT [2]) * NumOfF)) == NULL)
    {
      free(Pr->P);
      Pr->P = NULL;
      fclose(F);
      return FALSE;
    }
    Pr->NumOfP = NumOfP;
    Pr->NumOfE = NumOfF;
    for (i = 0; i < NumOfP; i++)
    {
      fread(&V, sizeof(ds1VERTEX), 1, F);
      Pr->P[i] = V.P;
    }
    for (i = 0; i < NumOfF / 3; i++)
    {
      fread(&N0, 4, 1, F);
      fread(&N1, 4, 1, F);
      fread(&N2, 4, 1, F);
      Pr->Edges[i * 3 + 0][0] = N0;
      Pr->Edges[i * 3 + 0][1] = N1;
      Pr->Edges[i * 3 + 1][0] = N1;
      Pr->Edges[i * 3 + 1][1] = N2;
      Pr->Edges[i * 3 + 2][0] = N2;
      Pr->Edges[i * 3 + 2][1] = N0;
    }
    break;
  }
  fclose(F);
  return TRUE;
} /* End of 'DS1_RndPrimLoad' function */

/* END OF 'LOADOBJ.C' FILE */
