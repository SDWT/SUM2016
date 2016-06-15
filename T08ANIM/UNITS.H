/* FILENAME: UNITS.H
 * PROGRAMMER: DS1
 * DATE: 14.06.2016
 * PURPOSE: Units difinitions
 */

#ifndef __UNITS_H_
#define __UNITS_H_

#include "anim.h"

/* Unit cube creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (ds1UNIT *) pointer to created unit.
 */
ds1UNIT * DS1_UnitCreateCube( VOID );

/* Unit ball creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (ds1UNIT *) pointer to created unit.
 */
ds1UNIT * DS1_UnitCreateControl( VOID );

#endif /* __UNITS_H_ */

/* END OF 'UNITS.H' FILE */
