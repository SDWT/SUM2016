/* FILENAME: RENDER.H
 * PROGRAMMER: DS1
 * DATE: 15.06.2016
 * PURPOSE: Animation system difinitions
 */

#ifndef __RENDER_H_
#define __RENDER_H_

#include "def.h"

/* Vertex representation type */
typedef struct
{
  VEC  P;  /* Vertex position */
  VEC2 T;  /* Vertex texture coordinates */
  VEC  N;  /* Normal at vertex */
  ds1COLOR C;  /* Vertex color */
} ds1VERTEX;

/* Primitive representation type */
typedef struct
{
  /* OpenGL buffers */
  INT
    VA,   /* Vertex array */
    VBuf, /* Vertex buffer */
    IBuf; /* Index buffer */
  INT NumOfI;       /* Facets index array size */
  MATR M; /* Primitive transformation matrix */
} ds1PRIM;

/* Object representation type */
typedef struct
{
  ds1PRIM *Prims;
  INT NumOfPrims;
} ds1OBJ;


extern MATR DS1_RndMatrWorld, DS1_RndMatrView, DS1_RndMatrProj;
extern DBL DS1_RndProjSize, DS1_RndProjDist, DS1_RndFarClip;
extern UINT DS1_RndPrg;

/* Setup projection function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID DS1_RndSetProj( VOID );

/* Object draw function.
 * ARGUMENTS:
 *   - object structure pointer:
 *       ds1OBJ *Obj;
 * RETURNS: None.
 */
VOID DS1_RndObjDraw( ds1OBJ *Obj );

/* Load object from '*.g3d' file function.
 * ARGUMENTS:
 *   - object structure pointer:
 *       ds1OBJ *Obj;
 *   - file name:
 *       CHAR *FileName;
 * RETURNS:
 *   (BOOL) TRUE is success, FALSE otherwise.
 */
BOOL DS1_RndObjLoad( ds1OBJ *Obj, CHAR *FileName );

/* Object free function.
 * ARGUMENTS:
 *   - object structure pointer:
 *       ds1OBJ *Obj;
 * RETURNS: None.
 */
VOID DS1_RndObjFree( ds1OBJ *Obj );

/* Load primitive from '*.g3d' file function.
 * ARGUMENTS:
 *   - primitive structure pointer:
 *       ds1PRIM *Pr;
 *   - file name:
 *       CHAR *FileName;
 * RETURNS:
 *   (BOOL) TRUE is success, FALSE otherwise.
 */
BOOL DS1_RndPrimLoad( ds1PRIM *Pr, CHAR *FileName );

/* Shader program load function.
 * ARGUMENTS:
 *   - shader program Id:
 *       UINT Prg;
 * RETURNS: None.
 */
VOID DS1_RndShaderFree( UINT Prg );

/* Shader program load function.
 * ARGUMENTS:
 *   - shader files prefix:
 *       CHAR *FileNamePrefix;
 * RETURNS:
 *   (UINT) shader program index or 0 if error is occured.
 */
UINT DS1_RndShaderLoad( CHAR *FileNamePrefix );



#endif /* __RENDER_H_ */

/* END OF 'RENDER.H' FILE */
