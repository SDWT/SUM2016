/* FILENAME: DEF.H
 * PROGRAMMER: DS1
 * DATE: 14.06.2016
 * PURPOSE: base difinitions
 */

#ifndef __DEF_H_
#define __DEF_H_


#include <windows.h>

#pragma warning (disable:4244)
#pragma warning (disable:4305)

/* Debug memory allocation support */
#ifdef _DEBUG
#  define _CRTDBG_MAP_ALLOC
#  include <crtdbg.h>
#  define SetDbgMemHooks() \
     _CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF | \
       _CRTDBG_ALLOC_MEM_DF | _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG))
#else /* _DEBUG */
#  define SetDbgMemHooks() ((VOID)0)
#endif /* _DEBUG */

#include <stdlib.h>

#define GLEW_STATIC
#include <glew.h>
#include <gl/gl.h>
#include <gl/glu.h>


#include "vec.h"
/*...*/

#endif /* __DEF_H_ */

/* END OF 'DEF.H' FILE */
