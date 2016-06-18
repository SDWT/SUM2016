/* FILENAME: LOADOBJ.C
 * PROGRAMMER: DS1
 * DATE: 15.06.2016
 * PURPOSE: Sprite unit drawing module
 */

#include <stdio.h>
#include <string.h>

#include "anim.h"

/* FILE NAME: LOADPRIM.C
 * PROGRAMMER: DS1
 * DATE: 13.06.2016
 * PURPOSE: Render handle functions.
 */

#include <stdio.h>
#include <string.h>

#include "anim.h"

/* Load object from '*.g3d' file function.
 * ARGUMENTS:
 *   - object structure pointer:
 *       ds1OBJ *Obj;
 *   - file name:
 *       CHAR *FileName;
 * RETURNS:
 *   (BOOL) TRUE is success, FALSE otherwise.
 */
BOOL DS1_RndObjLoad( ds1OBJ *Obj, CHAR *FileName )
{
  FILE *F;
  DWORD Sign, size;
  INT NumOfPrimitives;
  CHAR MtlFile[300];
  INT NumOfV;
  INT NumOfI;
  CHAR Mtl[300];
  INT p;
  ds1VERTEX *V;
  INT *I;

  DS1_RndObjCreate(Obj);

  F = fopen(FileName, "rb");
  if (F == NULL)
    return FALSE;

  /* File structure:
   *   4b Signature: "G3D\0"    CHAR Sign[4];
   *   4b NumOfPrimitives       INT NumOfPrimitives;
   *   300b material file name: CHAR MtlFile[300];
   *   repeated NumOfPrimitives times:
   *     4b INT NumOfV; - vertex count
   *     4b INT NumOfI; - index (triangles * 3) count
   *     300b material name: CHAR Mtl[300];
   *     repeat NumOfV times - vertices:
   *         !!! float point -> FLT
   *       typedef struct
   *       {
   *         VEC  P;  - Vertex position
   *         VEC2 T;  - Vertex texture coordinates
   *         VEC  N;  - Normal at vertex
   *         VEC4 C;  - Vertex color
   *       } VERTEX;
   *     repeat (NumOfF / 3) times - facets (triangles):
   *       INT N0, N1, N2; - for every triangle (N* - vertex number)
   */
  fread(&Sign, 4, 1, F);
  if (Sign != *(DWORD *)"G3D")
  {
    fclose(F);
    return FALSE;
  }
  fread(&NumOfPrimitives, 4, 1, F);
  fread(MtlFile, 1, 300, F);
  DS1_RndLoadMaterials(MtlFile);

  /* Allocate memory for primitives */
  if ((Obj->Prims = malloc(sizeof(ds1PRIM) * NumOfPrimitives)) == NULL)
  {
    fclose(F);
    return FALSE;
  }
  Obj->NumOfPrims = NumOfPrimitives;

  for (p = 0; p < NumOfPrimitives; p++)
  {
    /* Read primitive info */
    fread(&NumOfV, 4, 1, F);
    fread(&NumOfI, 4, 1, F);
    fread(Mtl, 1, 300, F);

    /* Allocate memory for primitive */
    size = sizeof(ds1VERTEX) * NumOfV + sizeof(INT) * NumOfI;
    if ((V = malloc(size)) == NULL)
    {
      while (p-- > 0)
        DS1_RndPrimFree(&Obj->Prims[p]);
      free(Obj->Prims);
      memset(Obj, 0, sizeof(ds1OBJ));
      fclose(F);
      return FALSE;
    }
    memset(V, 0, size);
    I = (INT *)(V + NumOfV);
    /* Read primitive data */
    fread(V, 1, size, F);

    DS1_RndPrimCreate(&Obj->Prims[p], V, NumOfV, I, NumOfI);
    Obj->Prims[p].MtlNo = DS1_RndFindMaterial(Mtl);
    Obj->Prims[p].Id = p;

    free(V);
  }
  fclose(F);
  return TRUE;
} /* End of 'DS1_RndObjLoad' function */

/* END OF 'LOADOBJ.C' FILE */
