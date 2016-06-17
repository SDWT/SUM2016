/* FILENAME: GRID.H
 * PROGRAMMER: DS1
 * DATE: 17.06.2016
 * PURPOSE: Units difinitions
 */

#ifndef __GRID_H_
#define __GRID_H_

/* Grid representation type */
typedef struct
{
  ds1VERTEX *P;
  INT N, M;
} ds1GRID;

/* Create grid function.
 * ARGUMENTS:
 *   - Grid structure pointer:
 *       ds1OBJ *Obj;
 *   - counter vertex on width and hight:
 *       INT N, M;
 * RETURNS: 
 *   (BOOL) TRUE is success, FALSE otherwise.
 */
BOOL DS1_GridCreate( ds1GRID *G, INT N, INT M );

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
BOOL DS1_GridCreatePlane( ds1GRID *G, INT N, INT M, VEC Dir, VEC Right );

/* Create grid sphere function.
 * ARGUMENTS:
 *   - Grid structure pointer:
 *       ds1OBJ *Obj;
 *   - counter vertex on width and hight:
 *       INT N, M;
 * RETURNS: 
 *   (BOOL) TRUE is success, FALSE otherwise.
 */
BOOL DS1_GridCreateSphere( ds1GRID *G, INT N, INT M, INT R );

/* Create grid plane function.
 * ARGUMENTS:
 *   - Grid structure pointer:
 *       ds1OBJ *Obj;
 * RETURNS: 
 *   (BOOL) TRUE is success, FALSE otherwise.
 */
BOOL DS1_GridCreateObj( ds1GRID *G, ds1OBJ *Obj, INT MtlNumber );

/* Free grid function.
 * ARGUMENTS:
 *   - Grid structure pointer:
 *       ds1OBJ *Obj;
 *   - counter vertex on width and hight:
 *       INT N, M;
 * RETURNS: 
 *   (BOOL) TRUE is success, FALSE otherwise.
 */
VOID DS1_GridFree( ds1GRID *G );

#endif /* __GRID_H_ */

/* END OF 'GRID.H' FILE */
