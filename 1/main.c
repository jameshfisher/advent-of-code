/*
--- Day 1: No Time for a Taxicab ---

Santa's sleigh uses a very high-precision clock to guide its movements, and the
clock's oscillator is regulated by stars. Unfortunately, the stars have been
stolen... by the Easter Bunny. To save Christmas, Santa needs you to retrieve
all fifty stars by December 25th.

Collect stars by solving puzzles. Two puzzles will be made available on each day
in the advent calendar; the second puzzle is unlocked when you complete the
first. Each puzzle grants one star. Good luck!

You're airdropped near Easter Bunny Headquarters in a city somewhere. "Near",
unfortunately, is as close as you can get - the instructions on the Easter Bunny
Recruiting Document the Elves intercepted start here, and nobody had time to
work them out further.

The Document indicates that you should start at the given coordinates (where you
just landed) and face North. Then, follow the provided sequence: either turn
left (L) or right (R) 90 degrees, then walk forward the given number of blocks,
ending at a new intersection.

There's no time to follow such ridiculous instructions on foot, though, so you
take a moment and work out the destination. Given that you can only walk on the
street grid of the city, how far is the shortest path to the destination?

For example:

- Following R2, L3 leaves you 2 blocks East and 3 blocks North, or 5 blocks away.
- R2, R2, R2 leaves you 2 blocks due South of your starting position, which is 2
  blocks away.
- R5, L5, R5, R3 leaves you 12 blocks away.

How many blocks away is Easter Bunny HQ?
*/

// Example instruction string: "L5, R1, R4, L5, L4, R3, R1, L1, R4, R5, L1, L3, R4, L2, L4, R2, L4, L1, R3, R1, R1, L1, R1, L5, R5, R2, L5, R2, R1, L2, L4, L4, R191, R2, R5, R1, L1, L2, R5, L2, L3, R4, L1, L1, R1, R50, L1, R1, R76, R5, R4, R2, L5, L3, L5, R2, R1, L1, R2, L3, R4, R2, L1, L1, R4, L1, L1, R185, R1, L5, L4, L5, L3, R2, R3, R1, L5, R1, L3, L2, L2, R5, L1, L1, L3, R1, R4, L2, L1, L1, L3, L4, R5, L2, R3, R5, R1, L4, R5, L3, R3, R3, R1, R1, R5, R2, L2, R5, L5, L4, R4, R3, R5, R1, L3, R1, L2, L2, R3, R4, L1, R4, L1, R4, R3, L1, L4, L1, L5, L2, R2, L1, R1, L5, L3, R4, L1, R5, L5, L5, L1, L3, R1, R5, L2, L4, L5, L1, L1, L2, R5, R5, L4, R3, L2, L1, L3, L4, L5, L5, L2, R4, R3, L5, R4, R2, R1, L5";

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int mod(int a, int b)
{
    int r = a % b;
    return r < 0 ? r + b : r;
}

int main(int argc, char* argv[])
{
  if (argc < 2)
  {
    fprintf(stderr, "Usage: %s instruction_string\n", argv[0]);
    return 1;
  }

  int px = 0; int py = 0;

  // dir: 0 = NORTH, 1 = EAST, 2 = SOUTH, 3 = WEST
  int dir = 0;

  char* instrs = argv[1];


  while (1)
  {
    char next = *instrs;

    if (next == '\0')
    {
      break;
    }
    else if (next == ' ' || next == ',')
    {
      printf("Skipping char: %c\n", next);
      instrs++;
    }
    else if (next == 'L')
    {
      dir = mod(dir-1, 4);
      printf("Turned left; now facing %d.\n", dir);
      instrs++;
    }
    else if (next == 'R')
    {
      dir = mod(dir+1, 4);
      printf("Turned right; now facing %d.\n", dir);
      instrs++;
    }
    else if (isdigit(next))
    {
      printf("Found digit %c; getting distance.\n", next);
      char* after;
      long int dist_l = strtol(instrs, &after, 10);
      instrs = after;

      int dist = dist_l;

      printf("Got distance %d.\n", dist);

      switch (dir) {
        case 0: py -= dist; break;
        case 1: px += dist; break;
        case 2: py += dist; break;
        case 3: px -= dist; break;
        default:
          fprintf(stderr, "Error: invalid direction %d.\n", dir);
          return 1;
      }

      printf("Walked to (%d,%d).\n", px, py);
    }
    else {
      fprintf(stderr, "Unrecognized character in string: %c\n", next);
      return 1;
    }
  }

  printf("We've walked to (%d,%d) which is %d steps away.\n", px, py, abs(px)+abs(py));
  return 0;
}
