/*

--- Day 8: Two-Factor Authentication ---

 You come across a door implementing what you can only assume is an
implementation of two-factor authentication after a long game of requirements
telephone.

To get past the door, you first swipe a keycard (no problem; there was one on a
nearby desk). Then, it displays a code on a little screen, and you type that
code on a keypad. Then, presumably, the door unlocks.

Unfortunately, the screen has been smashed. After a few minutes, you've taken
everything apart and figured out how it works. Now you just have to work out
what the screen would have displayed.

The magnetic strip on the card you swiped encodes a series of instructions for
the screen; these instructions are your puzzle input. The screen is 50 pixels
wide and 6 pixels tall, all of which start off, and is capable of three somewhat
peculiar operations:

- rect AxB turns on all of the pixels in a rectangle at the top-left of the
  screen which is A wide and B tall.

- rotate row y=A by B shifts all of the pixels in row A (0 is the top row) right
  by B pixels. Pixels that would fall off the right end appear at the left end
  of the row.

- rotate column x=A by B shifts all of the pixels in column A (0 is the left
  column) down by B pixels. Pixels that would fall off the bottom appear at the
  top of the column.


For example, here is a simple sequence on a smaller screen:

- rect 3x2 creates a small rectangle in the top-left corner:

    ###....
    ###....
    .......

- rotate column x=1 by 1 rotates the second column down by one pixel:

    #.#....
    ###....
    .#.....

- rotate row y=0 by 4 rotates the top row right by four pixels:

    ....#.#
    ###....
    .#.....

- rotate column x=1 by 1 again rotates the second column down by one pixel,
  causing the bottom pixel to wrap back to the top:

    .#..#.#
    #.#....
    .#.....

As you can see, this display technology is extremely powerful, and will soon
dominate the tiny-code-displaying-screen market. That's what the advertisement
on the back of the display tries to convince you, anyway.

There seems to be an intermediate check of the voltage used by the display:
after you swipe your card, if the screen did work, how many pixels should be
lit?

*/

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define SCREEN_WIDTH 50
#define SCREEN_HEIGHT 6

#define FOR(X, START, COUNT) for(int X = START; X < COUNT; X++)
#define FOR_DOWN(X, START, COUNT) for(int X = START; 0 < X; X--)
#define STR_PREFIX(TEST, PREFIX) (strncmp(TEST, PREFIX, strlen(PREFIX)) == 0)

char screen[SCREEN_WIDTH][SCREEN_HEIGHT];

void print_screen()
{
  FOR(y,0,SCREEN_HEIGHT)
  {
    FOR(x,0,SCREEN_WIDTH)
    {
      printf("%c", screen[x][y]);
    }
    printf("\n");
  }
}

int main(void)
{
  memset(screen, '.', SCREEN_WIDTH * SCREEN_HEIGHT);

  char * line_buf = NULL;
  size_t buf_size = 0;

  while (true)
  {
    size_t num_read = getline(&line_buf, &buf_size, stdin);

    if (STR_PREFIX(line_buf, "rect "))
    {
      // e.g. "rect 9x1"
      int rect_width, rect_height;
      sscanf(&line_buf[strlen("rect ")], "%dx%d", &rect_width, &rect_height);

      for (size_t x = 0; x < rect_width; x++)
      {
        for (size_t y = 0; y < rect_height; y++)
        {
          screen[x][y] = '#';
        }
      }
    }
    else if (STR_PREFIX(line_buf, "rotate row "))
    {
      // e.g. "rotate row y=4 by 38"
      int row_index, shift_by;
      sscanf(&line_buf[strlen("rotate row ")], "y=%d by %d", &row_index, &shift_by);

      FOR(s, 0, shift_by)
      {
        char swp = screen[SCREEN_WIDTH-1][row_index];
        FOR_DOWN(x, SCREEN_WIDTH-1, SCREEN_WIDTH-1)
        {
          screen[x][row_index] = screen[x-1][row_index];
        }
        screen[0][row_index] = swp;
      }
    }
    else if (STR_PREFIX(line_buf, "rotate column "))
    {
      // e.g. "rotate column x=10 by 3"
      int col_index, shift_by;
      sscanf(&line_buf[strlen("rotate column ")], "x=%d by %d", &col_index, &shift_by);

      FOR(s, 0, shift_by)
      {
        char swp = screen[col_index][SCREEN_HEIGHT-1];
        FOR_DOWN(x, SCREEN_HEIGHT-1, SCREEN_HEIGHT-1)
        {
          screen[col_index][x] = screen[col_index][x-1];
        }
        screen[col_index][0] = swp;
      }
    }
    else {
      break;
    }
  }

  uint64_t lit = 0;

  for (size_t x = 0; x < SCREEN_WIDTH; x++)
  {
    for (size_t y = 0; y < SCREEN_HEIGHT; y++)
    {
      if (screen[x][y] == '#')
      {
        lit++;
      }
    }
  }

  print_screen();

  return EXIT_SUCCESS;
}
