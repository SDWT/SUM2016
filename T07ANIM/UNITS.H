/* FILENAME: UNITS.H
 * PROGRAMMER: DS1
 * DATE: 11.06.2016
 * PURPOSE: Units difinitions
*/

#ifndef __UNITS_H_
#define __UNITS_H_

#include "anim.h"

/* Unit samples */
ds1UNIT * DS1_UnitCreateGlobe( INT X, INT Y, INT R );
VOID LoadSphere( VOID );

/* Unit ball creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (ds1UNIT *) pointer to created unit.
 */
ds1UNIT * DS1_UnitCreateSprite( INT X, INT Y, CHAR *FileAnd, CHAR *FileXor );

/* Unit cube creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (ds1UNIT *) pointer to created unit.
 */
ds1UNIT * DS1_UnitCreateCube( VOID );

#endif /* __UNITS_H_ */

/* END OF 'UNITS.H' FILE */
