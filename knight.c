#include <stdio.h>

#define XSIZE 8
#define YSIZE 8
int board[YSIZE][XSIZE] = { {0} };

int moves[8][2] = {
  { -2,  1}, { -1,  2}, {  1,  2}, {  2,  1},
  {  2, -1}, {  1, -2}, { -1, -2}, { -2, -1}
};

void print_board ();
int valid (int x, int y);
int solve_board (int x, int y, int n);

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
	printf ("% 3d ", board[y][x]);
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

int solve_board (int x, int y, int n)
{
  board[y][x] = n;
  if (n == XSIZE * YSIZE)
    return 1;

  int i;
  for (i = 0; i < 8; i++)
    {
      int xx = x + moves[i][0];
      int yy = y + moves[i][1];
      if (valid(xx, yy))
	if (solve_board(xx, yy, n + 1))
	  return 1;
    }

  board[y][x] = 0;
  return 0;
}
