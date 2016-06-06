/* FILENAME: T05DET.C
 * PROGRAMMER: DS1
 * DATE: 06.06.2016
 * PURPOSE: Eval determinant
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX 10

int Parity = 0, P[MAX], PIs[MAX], N = 0;
double A[MAX][MAX], Sum = 0;

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

/* Load matrix function
 * ARGUMENTS:
 *  - :
 *    char *FileName
 * RETURNS:
 *   (int);
 */
int LoadMatrix( char *FileName )
{
  int i, j;
  FILE *F;

  printf("File: %s\n", FileName);
  if ((F = fopen(FileName, "r")) == NULL)
  {
    printf("Error reading file.\n");
    return 0;
  }
  fscanf(F, "%d", &N);
  printf("Matrix:\n");
  for (i = 0; i < N; i++, printf("\n"))
    for (j = 0; j < N; j++)
    {
      fscanf(F, "%lf", &A[i][j]);
      printf("%8.6lf ", A[i][j]);
    }
  return 1;
}/* End of 'LoadMatrix' function */

/* Load matrix function
 * ARGUMENTS:
 *  - :
 *    char *FileName
 * RETURNS:
 *   (int);
 */
void CountDeterminant( void )
{
  int i;
  double prod = 1;

  for (i = 0; i < N; i++)
    prod *= A[i][P[i]];
  Sum += (Parity % 2) ? -prod : prod;
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
  {
    CountDeterminant();
  }
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

    CountDeterminant();
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
    P[Pos] = i;
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
    CountDeterminant();
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

double EvalDeterminant( char *FileName )
{
  int i;
  Sum  = 0;
  Parity = 0;
  if (LoadMatrix(FileName) == 0)
    return -0;
  for (i = 0; i < N; i++)
  {
    P[i] = i;
    PIs[i] = 0;
  }
  Go3(0);
  return Sum;
}

/* Main program function 
 * ARGUMENTS:
 *  - None;
 * RETURNS:
 *   None;
 */
void main( void )
{
  int i, k;
  double d = 0;
  char *M[] = {"mat1.txt", "mat2.txt", "mat3.txt", "mat4.txt", 
               "m.txt", "m1.txt", "m2.txt", "m3.txt", "m4.txt", 
                        "m5.txt", "m6.txt", "m7.txt", "m8.txt"};
  FILE *F;

  k = sizeof(M) / sizeof(M[0]);
  if ((F = fopen("ds1_answers2.txt", "w")) == NULL)
    return;
  for (i = 0; i < k; i++)
  {
    printf("File: %s, Determinant: %lf\n\n", M[i], d = EvalDeterminant(M[i]));
    fprintf(F, "File: %10s, Determinant: %20.6lf\n", M[i], d);
  }
  i = 0;
  fclose(F);
}/* End of 'main' function */

/* END OF 'T05DET.C' FILE */
