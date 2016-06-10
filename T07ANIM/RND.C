/* Random number obtain in range [0.0 .. 1.0] function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (DBL) result random number.
 */
__inline DBL Rnd0( VOID )
{
  return (DBL)rand() / RAND_MAX;
} /* End of 'Rnd0' function */

/* Random number obtain in range [-1.0 .. 1.0] function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (DBL) result random number.
 */
__inline DBL Rnd1( VOID )
{
  return 2.0 * rand() / RAND_MAX - 1;
} /* End of 'Rnd1' function */

