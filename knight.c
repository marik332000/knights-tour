#include <stdio.h>
#include <stdlib.h>

#define XSIZE 8
#define YSIZE 8
int board[YSIZE][XSIZE] = { {0} };

int moves[8][2] = {
  { -2,  1 }, { -1,  2 }, {  1,  2 }, {  2,  1 },
  {  2, -1 }, {  1, -2 }, { -1, -2 }, { -2, -1 }
};

void print_board ();
int valid (int x, int y);
int solve_board (int x, int y, int n);
int compar (const void *a, const void *b);

int main ()
{
  if (solve_board (0, 0, 1))
    print_board ();
  else
    printf ("No solution.\n");
  return 0;
}

void print_board ()
{
  int x, y;
  for (y = 0; y < YSIZE; y++)
    {
      for (x = 0; x < XSIZE; x++)
	printf ("% 6d ", board[y][x]);
      printf ("\n");
    }
}

int valid (int x, int y)
{
  return
    x >= 0 && x < XSIZE &&
    y >= 0 && y < YSIZE &&
    board[y][x] == 0;
}

int compar (const void *a, const void *b)
{
  return ((int *) a)[0] - ((int *) b)[0];
}

int solve_board (int x, int y, int n)
{
  board[y][x] = n;
  if (n == XSIZE * YSIZE)
    return 1;

  /* Gather valid moves and count their "loneliness". */
  int i, j, valids[8][3];
  for (i = 0; i < 8; i++)
    {
      valids[i][0] = 0;
      valids[i][1] = x + moves[i][0];
      valids[i][2] = y + moves[i][1];
      if (valid (valids[i][1], valids[i][2]))
	for (j = 0; j < 8; j++)
	  if (valid (valids[i][1] + moves[j][0],
		     valids[i][2] + moves[j][1]))
	    valids[i][0]++;
    }

  /* Sort and try each one. */
  qsort (&valids[0][0], 8, 3 * sizeof (int), &compar);
  for (i = 0; i < 8; i++)
    if (valid (valids[i][1], valids[i][2]) &&
	solve_board (valids[i][1], valids[i][2], n + 1))
      return 1;

  /* Dead end: back off. */
  board[y][x] = 0;
  return 0;
}
