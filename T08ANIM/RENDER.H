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
    VA,       /* Vertex array */
    VBuf,     /* Vertex buffer */
    IBuf;     /* Index buffer */
  INT NumOfI; /* Facets index array size */
  MATR M;     /* Primitive transformation matrix */
  INT MtlNo;  /* Material number */
  INT Id;     /* Primitive Id */
} ds1PRIM;

/* Object representation type */
typedef struct
{
  ds1PRIM *Prims; /* Primitives array */
  INT NumOfPrims; /* Primitives array size */
  MATR M;         /* Object transformation matrix */
} ds1OBJ;

/* Material representation type */
typedef struct
{
  CHAR Name[300]; /* Material name */
  VEC Ka, Kd, Ks; /* Illumination coefficients */
  FLT Ph, Trans;  /* Shininess and Phong, transparency */
  INT TexW, TexH; /* Textiure image size */
  INT TexNo;      /* For load: bytes per pixel, in use: OpenGL texture no */
} ds1MTL;

extern MATR DS1_RndMatrWorld, DS1_RndMatrView, DS1_RndMatrProj;
extern DBL DS1_RndProjSize, DS1_RndProjDist, DS1_RndFarClip;
extern UINT DS1_RndPrg;

/* Materials array */
#define DS1_MAX_MATERIALS 10000
extern ds1MTL DS1_RndMaterials[DS1_MAX_MATERIALS];
extern INT DS1_RndNumOfMaterials;

/* Setup projection function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID DS1_RndSetProj( VOID );

/*** 
 * Shader handle funclion difinition
 ***/

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

/*** 
 * Material handle funclion difinition
 ***/

/* Material find by name function.
 * ARGUMENTS:
 *   - material name:
 *       CHAR *Name;
 * RETURNS:
 *   (INT) number of found material or -1 if no result.
 */
INT DS1_RndFindMaterial( CHAR *Name );

/* Material load function.
 * ARGUMENTS:
 *   - material file name:
 *       CHAR *FileName;
 * RETURNS: None.
*/
VOID DS1_RndLoadMaterials( CHAR *FileName );

/*** 
 * Object handle funclion difinition
 ***/

/* Object create function.
 * ARGUMENTS:
 *   - object structure pointer:
 *       ds1OBJ *Obj;
 * RETURNS: None.
 */
VOID DS1_RndObjCreate( ds1OBJ *Obj );

/* Object free function.
 * ARGUMENTS:
 *   - object structure pointer:
 *       ds1OBJ *Obj;
 * RETURNS: None.
 */
VOID DS1_RndObjFree( ds1OBJ *Obj );

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

/* Object draw function.
 * ARGUMENTS:
 *   - object structure pointer:
 *       ds1OBJ *Obj;
 * RETURNS: None.
 */
VOID DS1_RndObjDraw( ds1OBJ *Obj );

/*** 
 * Primitive handle funclion difinition
 ***/

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
VOID DS1_RndPrimCreate( ds1PRIM *Pr, ds1VERTEX *V, INT NumOfV, INT *I, INT NumOfI );

/* Primitive free function.
 * ARGUMENTS:
 *   - primitive structure pointer:
 *       ds1PRIM *Pr;
 * RETURNS: None.
 */
VOID DS1_RndPrimFree( ds1PRIM *Pr );

/* Primitive draw function.
 * ARGUMENTS:
 *   - primitive structure pointer:
 *       ds1PRIM *Pr;
 * RETURNS: None.
 */
VOID DS1_RndPrimDraw( ds1PRIM *Pr );

#endif /* __RENDER_H_ */

/* END OF 'RENDER.H' FILE */
