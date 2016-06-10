/* FILENAME: ANIM.H
 * PROGRAMMER: DS1
 * DATE: 10.06.2016
 * PURPOSE: Animation system difinitions
*/

#ifndef __ANIM_H_
#define __ANIM_H_

#include "def.h"

#define DS1_MAX_UNITS 100

/* Forward reference to unit type*/
typedef struct tagds1UNIT ds1UNIT;

/* Animation  */
typedef struct
{
  HWND hWnd; /* window */
  HDC hDC;   /* context in memory */
  INT W, H;  /* window size */
  HBITMAP hFrame; /* picture frame */
  ds1UNIT *Units[DS1_MAX_UNITS]; /* animation object array */
  INT NumOfUnits; /* is now number animation object */
  /*. . .*/
} ds1ANIM;

struct tagds1UNIT
{
  /* Unit initialization function.
   * ARGUMENTS:
   *   - self-pointer to unit object:
   *       ds1UNIT *Uni;
   *   - animation context:
   *       ds1ANIM *Ani;
   * RETURNS: None.
   */
  VOID (* Init)(ds1UNIT *Uni, ds1ANIM *Ani);
  /* Unit deinitialization function.
   * ARGUMENTS:
   *   - self-pointer to unit object:
   *       ds1UNIT *Uni;
   *   - animation context:
   *       ds1ANIM *Ani;
   * RETURNS: None.
   */
  VOID (* Close)(ds1UNIT *Uni, ds1ANIM *Ani);
  /* Unit inter frame events handle function.
   * ARGUMENTS:
   *   - self-pointer to unit object:
   *       ds1UNIT *Uni;
   *   - animation context:
   *       ds1ANIM *Ani;
   * RETURNS: None.
   */
  VOID (* Response)(ds1UNIT *Uni, ds1ANIM *Ani);
  /* Unit render function.
   * ARGUMENTS:
   *   - self-pointer to unit object:
   *       ds1UNIT *Uni;
   *   - animation context:
   *       ds1ANIM *Ani;
   * RETURNS: None.
   */
  VOID (* Render)(ds1UNIT *Uni, ds1ANIM *Ani);
};

/*** 
 * Animation system support 
 ***/
extern ds1ANIM DS1_Anim;
/* Animation initialization function.
 * ARGUMENTS:
 *   - window:
 *       HWND hWnd;
 * RETURNS: None.
 */
VOID DS1_AnimInit( HWND hWnd );
/* Animation deinitialization function.
 * ARGUMENTS: None;
 * RETURNS: None.
 */
VOID DS1_AnimClose( VOID );
/* Animation initialization function.
 * ARGUMENTS:
 *   - width, height window size:
 *       INT W, H;
 * RETURNS: None.
 */
VOID DS1_AnimResize( INT W, INT H );
/* Double buffer frame copy function.
 * ARGUMENTS:
 *   - window:
 *       HWND hWnd;
 * RETURNS: None.
 */
VOID DS1_AnimCopyFrame( HDC hDc );
/* Animation render function.
 * ARGUMENTS: None;
 * RETURNS: None.
 */
VOID DS1_AnimRender( VOID );
/* Animation initialization function.
 * ARGUMENTS:
 *   - Animation parameters:
 *       ds1ANIM *Ani;
 * RETURNS: None.
 */
VOID DS1_AnimAddUnit( ds1UNIT *Uni );
/* Unit creation function.
 * ARGUMENTS:
 *   - unit structure size in bytes:
 *       INT Size;
 * RETURNS:
 *   (ds1UNIT *) pointer to created unit.
 */
ds1UNIT * DS1_AnimUnitCreate( INT Size );

/* Unit samples */
ds1UNIT * DS1_UnitCreateGlobe( INT X, INT Y, INT R );


#endif /* __ANIM_H_ */

/* END OF 'ANIM.H' FILE */
