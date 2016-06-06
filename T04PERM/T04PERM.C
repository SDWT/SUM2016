/* FILENAME: T04PERM.C
 * PROGRAMMER: DS1
 * DATE: 04.06.2016
 * PURPOSE: 
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define N 5

int Parity = 0, P[N], PIs[N];
FILE *F;

/* Swap to int numbers function 
 * ARGUMENTS:
 *  - First number to swap:
 *      int *A;
 *  - Second number to swap:
 *      int *B 
 * RETURNS:
 *   None;
 */
void Swap( int *A, int *B )
{
  int tmp = *A;

  *A = *B;
  *B = tmp;
}/* End of 'Swap' function */

/* Write perseption to file function 
 * ARGUMENTS:
 *  - None;
 * RETURNS:
 *   None;
 */
void PermToFile( void )
{
  int i;
  static double count = 0;

  
  for (i = 0; i < N - 1; i++)
    {
      fprintf(F, "%d, ", P[i]);
    }
  fprintf(F, "%d; Parity Even Odd = %d\n", P[i], Parity % 2);
  count++;
}/* End of 'PermToFile' function */


/* Rec func perm 
 * ARGUMENTS:
 *  - Position in perseption:
 *      int Pos;
 * RETURNS:
 *   None;
 */
void Go( int Pos )
{
  int i, j;

  if (N == Pos)
    PermToFile();
  else
    for (i = Pos; i < N; i++)
    {
      j = (i == Pos) ? 0 : 1;
      Parity += j;
      Swap(&P[Pos], &P[i]);
      Go(Pos + 1);
      Parity -= j;
      Swap(&P[Pos], &P[i]);
    }

}/* End of 'Go' function */

/* Rec func perm 
 * ARGUMENTS:
 *  - Position in perseption:
 *      int Pos;
 * RETURNS:
 *   None;
 */
void Go2( int Pos )
{
  int i, j;

  if (N == Pos)
  {
    for (i = 0; i < N; i++)
      for (j = i + 1; j < N; j++)
        if (P[i] > P[j])
          Parity++;
    PermToFile();
    Parity = 0;
    return;
  }
  for (j = 0; j < N; j++)
  {
    i = j;
    while (i < N && PIs[i] == 1)
      i++;
    if (i == N)
      return;
    j = i;
    PIs[i] = 1;
    P[Pos] = i + 1;
    Go2(Pos+1);
    PIs[i] = 0;
  }
}/* End of 'Go2' function */

/* Rec func perm 
 * ARGUMENTS:
 *  - Position in perseption:
 *      int Pos;
 * RETURNS:
 *   None;
 */
void Go3( int Pos )
{
  int i, SaveParity, x;

  if (N == Pos)
  {
    PermToFile();
    return;
  }
  SaveParity = Parity;
  Go3(Pos + 1);
  for (i = Pos + 1; i < N; i++)
  {
    Swap(&P[Pos], &P[i]);
    Parity = !Parity;
    Go3(Pos + 1);
  }

  x = P[Pos];
  for (i = Pos + 1; i < N; i++)
    P[i - 1] = P[i];
  P[N - 1] = x;
  Parity = SaveParity;
}/* End of 'Go3' function */


/* Main program function 
 * ARGUMENTS:
 *  - None;
 * RETURNS:
 *   None;
 */
void main( void )
{
  int i;
  if ((F = fopen("perm.log", "w")) == NULL)
    return;

  for (i = 0; i < N; i++)
  {
    P[i] = i + 1;
    PIs[i] = 0;
  }
  Go3(0);
  fclose(F);
}/* End of 'main' function */

/* END OF 'T04PERM.C' FILE */
