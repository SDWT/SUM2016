/* Draw quadrilateral function.
 * ARGUMENTS:
 *   - drawing device context:
 *       HDC hDC;
 *   - corner points:
 *       POINT P0, P1, P2, P3;
 *   - color:
 *       DWORD Color;
 * RETURNS: None.
 */
VOID DrawQuad( HDC hDC, POINT P0, POINT P1, POINT P2, POINT P3, DWORD Color )
{
  INT s =
    (P0.x - P1.x) * (P0.y + P1.y) +
    (P1.x - P2.x) * (P1.y + P2.y) +
    (P2.x - P3.x) * (P2.y + P3.y) +
    (P3.x - P0.x) * (P3.y + P0.y);

  if (s > 0)
  {
    POINT pts[4];
    
    pts[0] = P0;
    pts[1] = P1;
    pts[2] = P2;
    pts[3] = P3;

    Polygon(hDC, pts, 4);
  }
} /* End of 'DrawQuad' function */

