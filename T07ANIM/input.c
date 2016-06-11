Программирование устройств ввода. Мышь. Клавиатура. Джойстик.

1.Mouse

POINT pt;

GetCursorPos(&pt);
ScreenToClient(VG4_Anim.hWnd, &pt);
VG4_Anim.Mx = pt.x;
VG4_Anim.My = pt.y;
можно получать движение:
VG4_Anim.Mdx = pt.x - VG4_Anim.MOldx;
VG4_Anim.Mdy = pt.y - VG4_Anim.MOldy;
VG4_Anim.MOldx = VG4_Anim.Mx;
VG4_Anim.MOldy = VG4_Anim.My;

Кнопки - buttons - в обработке клавиатуры:

ANIM:
  BYTE Keys[256];

GetKeyboardState(VG4_Anim.Keys);
мышиные кнопки: VG4_Anim.Keys[VK_LBUTTON] R M
старший бит == 1 -> кнопка нажата:
if (VG4_Anim.Keys[VK_MBUTTON] & 0x80)
  нажато колесо

опрос колеса
ANIM:
  INT
    Mx, My, Mz, Mdx, Mdy, Mdz;

глобальная переменная:
INT VG4_MouseWheel;

WM_MOUSEWHEEL:
  VG4_MouseWheel += (SHORT)HIWORD(wParam);

VG4_AnimRender:
  . . .  
  VG4_Anim.Mdz = VG4_MouseWheel;
  VG4_Anim.Mz += VG4_MouseWheel;
  VG4_MouseWheel = 0;

2.Keyboard

опрос клавы - как в мыше.

Отслеживание однократного нажатия

ANIM:
  BYTE
    Keys[256], OldKeys[256], KeysClick[256];
   
VG4_AnimRender:
  GetKeyboardState(VG4_Anim.Keys);
  for (i = 0; i < 256; i++)
  {
    VG4_Anim.Keys[i] >>= 7;
    if (!VG4_Anim.KeysOld[i] && VG4_Anim.Keys[i])
      VG4_Anim.KeysClick[i] = 1;
    else
      VG4_Anim.KeysClick[i] = 0;
  }
  memcpy(VG4_Anim.KeysOld, VG4_Anim.Keys, 256);

3.Joystick
 

доп библиотеки:
#include <mmsystem.h> (после windows.h)
+ подключаем библиотеку: /* winmm.lib */
#pragma comment(lib, "winmm")

/* Joystic axis value obtain macro function */
#define VG4_GET_JOYSTIC_AXIS(A) \
  (2.0 * (ji.dw##A##pos - jc.w##A##min) / (jc.w##A##max - jc.w##A##min - 1) - 1)
ANIM:
  BYTE
    JBut[32];                    /* Joystick button state */
  INT JPov;                      /* Joystick point-of-view control [0,1..8] */
  DBL
    JX, JY, JZ, JR;              /* Joystick axes */
  /* Joystick */
  if (joyGetNumDevs() > 0)
  {
    JOYCAPS jc;

    /* Get joystick info */
    if (joyGetDevCaps(JOYSTICKID1, &jc, sizeof(jc)) == JOYERR_NOERROR)
    {
      JOYINFOEX ji;

      ji.dwSize = sizeof(JOYINFOEX);
      ji.dwFlags = JOY_RETURNALL;
      if (joyGetPosEx(JOYSTICKID1, &ji) == JOYERR_NOERROR)
      {
        /* Buttons */
        for (i = 0; i < 32; i++)
          VG4_Anim.JBut[i] = (ji.dwButtons >> i) & 1;

        /* Axes */
        VG4_Anim.JX = VG4_GET_JOYSTIC_AXIS(X);
        VG4_Anim.JY = VG4_GET_JOYSTIC_AXIS(Y);
        VG4_Anim.JZ = VG4_GET_JOYSTIC_AXIS(Z);
        VG4_Anim.JR = VG4_GET_JOYSTIC_AXIS(R);

        /* Point of view */
        VG4_Anim.JPov = ji.dwPOV == 0xFFFF ? 0 : ji.dwPOV / 4500 + 1;
      }
    }
  }
