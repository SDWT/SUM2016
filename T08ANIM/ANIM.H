/* FILENAME: ANIM.H
 * PROGRAMMER: DS1
 * DATE: 14.06.2016
 * PURPOSE: Animation system difinitions
 */

#ifndef __ANIM_H_
#define __ANIM_H_

#include "def.h"
#include "image.h"
#include "render.h"

#define DS1_MAX_UNITS 100

/* Forward reference to unit type*/
typedef struct tagds1UNIT ds1UNIT;

/* Animation type */
typedef struct
{
  HWND hWnd;                       /* window */
  HDC hDC;                         /* Drawing window context */
  HGLRC hGLRC;                     /* Rendering context */

  INT W, H;                        /* window size */
  HBITMAP hFrame;                  /* picture frame */
  ds1UNIT *Units[DS1_MAX_UNITS];   /* animation object array */
  INT NumOfUnits;                  /* is now number animation object */
  /* Timer data */
  DBL GlobalTime, GlobalDeltaTime, /* Global time and interframe interval */
      Time, DeltaTime,             /* Time with pause and interframe interval */
      FPS;                         /* Frames per seond value */
  BOOL IsPause;                    /* Pause flag */
  /* Input system */
  INT Mx, My,                      /* Mouse cursor position */
      Mz,                          /* Mouse wheel absolute value */
      Mdx, Mdy, Mdz;               /* Delta values of mouse axes */
  BYTE Keys[256],                  /* Current key state */
       KeysOld[256],               /* Previous frame key state */
       KeysClick[256],             /* Click key flags */
       JBut[32];                   /* Joystick button state */
  INT JPov;                        /* Joystick point-of-view control [0,1..8] */
  DBL JX, JY, JZ, JR;              /* Joystick axes */

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

/* Global mouse wheel delta value */
extern INT DS1_MouseWheel;

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
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID DS1_AnimCopyFrame( VOID );
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

/* Set/reset full screen mode function */
VOID DS1_FlipFullScreen( VOID );

#endif /* __ANIM_H_ */

/* END OF 'ANIM.H' FILE */
