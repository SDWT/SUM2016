/* FILENAME: OBJ3D.C
 * PROGRAMMER: DS1
 * DATE: 18.06.2016
 * PURPOSE: Object functions
 */

#include "anim.h"

/* function
 * 
 */
VOID DS1_ObjCreate( ds1OBJ *Obj )
{
}/* End of 'DS1_PrimDraw' function */

/* function
 * 
 */
VOID DS1_ObjFree( ds1OBJ *Obj )
{
}/* End of 'DS1_PrimDraw' function */


/* function
 * 
 */
VOID DS1_ObjDraw( ds1OBJ *Obj )
{
  MATR MSave;

  MSave = DS1_RndMatrWorld;


  DS1_RndMatrWorld = MSave;
}/* End of 'DS1_PrimDraw' function */

/* END OF 'OBJ3D.C' FILE */