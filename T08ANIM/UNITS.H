/* FILENAME: UNITS.H
 * PROGRAMMER: DS1
 * DATE: 15.06.2016
 * PURPOSE: Units difinitions
 */

#ifndef __UNITS_H_
#define __UNITS_H_

#include "anim.h"

/* Unit model creation function.
 * ARGUMENTS: 
 *   - Model file:
 *     CHAR *FileName;
 * RETURNS:
 *   (ds1UNIT *) pointer to created unit.
 */
ds1UNIT * DS1_UnitCreateModel( CHAR *FileName );

/* Unit ball creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (ds1UNIT *) pointer to created unit.
 */
ds1UNIT * DS1_UnitCreateControl( VOID );

/* Unit port creation function.
 * ARGUMENTS: 
 *   - Port file:
 *     CHAR *FileNameObj; 
 *   - Runway landing file:
 *     CHAR *FileNameRWI;
 *   - Runway taxi file:
 *     CHAR *FileNameRWT;
 *   - Runway takeoff file:
 *     CHAR *FileNameRWO;
 * RETURNS:
 *   (ds1UNIT *) pointer to created unit.
 */
ds1UNIT * DS1_UnitCreatePort( CHAR *FileNameObj, CHAR *FileNameRWI, CHAR *FileNameRWT, CHAR *FileNameRWO );

/* Unit plane creation function.
 * ARGUMENTS: 
 *   - Plane file:
 *     CHAR *FileName;
 * RETURNS:
 *   (ds1UNIT *) pointer to created unit.
 */
ds1UNIT * DS1_UnitCreatePlane( CHAR *FileName );

/* Unit scene creation function.
 * ARGUMENTS: 
 *   - Scene file:
 *     CHAR *FileName;
 * RETURNS:
 *   (ds1UNIT *) pointer to created unit.
 */
ds1UNIT * DS1_UnitCreateScene( VOID );

#endif /* __UNITS_H_ */

/* END OF 'UNITS.H' FILE */
