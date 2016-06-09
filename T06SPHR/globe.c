/***
 * Sphere handle functions
 ***/

/* Image representation type */
typedef struct
{
  HBITMAP hBmGlobe;
  DWORD *Bits;
  INT W, H;
} IMG;

IMG Globe;

/* Load sphere texture function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID LoadSphere( VOID )
{
  HDC hDC = GetDC(NULL), hMemDC, hMemDC1;
  HBITMAP hBm;
  BITMAP bm;
  BITMAPINFOHEADER bmih;

  /* Load image from file */
  hMemDC = CreateCompatibleDC(hDC);
  hBm = LoadImage(NULL, "GLOBE.BMP", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
  GetObject(hBm, sizeof(bm), &bm);
  Globe.W = bm.bmWidth;
  Globe.H = bm.bmHeight;
  SelectObject(hMemDC, hBm);

  /* Fill DIB info */
  memset(&bmih, 0, sizeof(bmih));
  bmih.biSize = sizeof(BITMAPINFOHEADER);
  bmih.biBitCount = 32;                   /* BGRx - DWORD */
  bmih.biPlanes = 1;                      /* always */
  bmih.biCompression = BI_RGB;            /* 0 - no compression */
  bmih.biWidth = bm.bmWidth;              /* width */
  bmih.biHeight = -bm.bmHeight;           /* height + first coded row is 0 */
  bmih.biSizeImage = bm.bmWidth * bm.bmHeight * 4;  /* image size in bytes */

  Globe.hBmGlobe = CreateDIBSection(NULL, (BITMAPINFO *)&bmih, DIB_RGB_COLORS,
                 (VOID **)&Globe.Bits, NULL, 0);
  hMemDC1 = CreateCompatibleDC(hDC);
  SelectObject(hMemDC1, Globe.hBmGlobe);

  BitBlt(hMemDC1, 0, 0, Globe.W, Globe.H, hMemDC, 0, 0, SRCCOPY);

  DeleteDC(hMemDC);
  DeleteDC(hMemDC1);
  DeleteObject(hBm);

  ReleaseDC(NULL, hDC);
} /* End of 'LoadSphere' function */


. . .
      INT img_x, img_y;
      COLORREF c;

. . .
      img_x = j * (Globe.W - 1) / (M - 1);
      img_y = i * (Globe.H - 1) / (N - 1);
      c = Globe.Bits[img_x + img_y * Globe.W]; /* GetPixel(Globe.hDC, img_x, img_y); */
      SetPixelV(hDC, x, y, c);
