/* FILENAME: PRIM.C
 * PROGRAMMER: DS1
 * DATE: 18.06.2016
 * PURPOSE: Primitive functions
 */

#include "anim.h"
/* function
 * 
 */
VOID DS1_PrimCreate( ds1OBJ *Obj )
{
}/* End of 'DS1_PrimCreate' function */

/* function
 * 
 */
VOID DS1_PrimFree( ds1OBJ *Obj )
{
}/* End of 'DS1_PrimFree' function */


/* function
 * 
 */
VOID DS1_PrimDraw( ds1OBJ *Obj )
{
  MATR MSave;

  MSave = DS1_RndMatrWorld;


  DS1_RndMatrWorld = MSave;
}/* End of 'DS1_PrimDraw' function */

/* END OF 'PRIM.C' FILE */
