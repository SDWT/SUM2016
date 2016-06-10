Timer
Keyboard + Mouse

clock -> tick -> CLOCKS_PER_SEC
на старте программы:
StartTime = clock();

для Response на каждом кадре:

long t = clock();

TimeInSec = (t - StartTime) / (DBL)CLOCKS_PER_SEC;

High Resolution Timer:

/* Timer local data */
static UINT64
  VG4_StartTime,  /* Start program time */
  VG4_OldTime,    /* Time from program start to previous frame */
  VG4_OldTimeFPS, /* Old time FPS measurement */
  VG4_PauseTime,  /* Time during pause period */
  VG4_TimePerSec, /* Timer resolution */
  VG4_FrameCounter; /* Frames counter */

  /* Timer initialization */
  QueryPerformanceFrequency(&t);
  VG4_TimePerSec = t.QuadPart;
  QueryPerformanceCounter(&t);
  VG4_StartTime = VG4_OldTime = VG4_OldTimeFPS = t.QuadPart;
  VG4_PauseTime = 0;

добавляем в vg4ANIM тип:

  /* Timer data */
  DBL
    GlobalTime, GlobalDeltaTime, /* Global time and interframe interval */
    Time, DeltaTime,             /* Time with pause and interframe interval */
    FPS;                         /* Frames per seond value */
  BOOL
    IsPause;                     /* Pause flag */

  /*** Handle timer ***/
  VG4_FrameCounter++;
  QueryPerformanceCounter(&t);
  /* Global time */
  VG4_Anim.GlobalTime = (DBL)(t.QuadPart - VG4_StartTime) / VG4_TimePerSec;
  VG4_Anim.GlobalDeltaTime = (DBL)(t.QuadPart - VG4_OldTime) / VG4_TimePerSec;
  /* Time with pause */
  if (VG4_Anim.IsPause)
  {
    VG4_Anim.DeltaTime = 0;
    VG4_PauseTime += t.QuadPart - VG4_OldTime;
  }
  else
  {
    VG4_Anim.DeltaTime = VG4_Anim.GlobalDeltaTime;
    VG4_Anim.Time = (DBL)(t.QuadPart - VG4_PauseTime - VG4_StartTime) / VG4_TimePerSec;
  }
  /* FPS */
  if (t.QuadPart - VG4_OldTimeFPS > VG4_TimePerSec)
  {
    CHAR str[100];

    VG4_Anim.FPS = VG4_FrameCounter * VG4_TimePerSec /
                                         (DBL)(t.QuadPart - VG4_OldTimeFPS);
    VG4_OldTimeFPS = t.QuadPart;
    VG4_FrameCounter = 0;
    sprintf(str, "FPS: %.5f", VG4_Anim.FPS);
    SetWindowText(VG4_Anim.hWnd, str);
  }
  VG4_OldTime = t.QuadPart;
