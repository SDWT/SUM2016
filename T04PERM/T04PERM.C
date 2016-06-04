/* FILENAME: T03POLE.C
 * PROGRAMMER: DS1
 * DATE: 03.06.2016
 * PURPOSE: Magnetic pole to cursor
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define N 10

int Parity = 0, P[N], PIs[N];
FILE *F;

void Swap( int *A, int *B )
{
  int tmp = *A;

  *A = *B;
  *B = tmp;
}/* End of 'Swap' function */


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


/* Rec func perm */
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

/* Rec func perm */
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

}/* End of 'Go' function */


/* Main program function */
void main( void )
{
  int i;
  char Str1[100], Str2[100];
  FILE *F2;
  if ((F = fopen("perm.log", "w")) == NULL)
    return;

  for (i = 0; i < N; i++)
  {
    P[i] = i + 1;
    PIs[i] = 0;
  }
  Go2(0);
  fclose(F);
  /*
  if ((F = fopen("perm2.log", "w")) == NULL)
    return;
  for (i = 0; i < N; i++)
  {
    P[i] = i + 1;
    PIs[i] = 0;
  }
  Go(0);
  fclose(F);
  */

}/* End of 'main' function */


/* END OF 'T01EYES.C' FILE */
