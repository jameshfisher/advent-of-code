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

--- Part Two ---

 Then, you notice the instructions continue on the back of the Recruiting
Document. Easter Bunny HQ is actually at the first location you visit twice.

For example, if your instructions are R8, R4, R4, R8, the first location you
visit twice is 4 blocks away, due East.

How many blocks away is the first location you visit twice?
*/

// Example instruction string: "L5, R1, R4, L5, L4, R3, R1, L1, R4, R5, L1, L3, R4, L2, L4, R2, L4, L1, R3, R1, R1, L1, R1, L5, R5, R2, L5, R2, R1, L2, L4, L4, R191, R2, R5, R1, L1, L2, R5, L2, L3, R4, L1, L1, R1, R50, L1, R1, R76, R5, R4, R2, L5, L3, L5, R2, R1, L1, R2, L3, R4, R2, L1, L1, R4, L1, L1, R185, R1, L5, L4, L5, L3, R2, R3, R1, L5, R1, L3, L2, L2, R5, L1, L1, L3, R1, R4, L2, L1, L1, L3, L4, R5, L2, R3, R5, R1, L4, R5, L3, R3, R3, R1, R1, R5, R2, L2, R5, L5, L4, R4, R3, R5, R1, L3, R1, L2, L2, R3, R4, L1, R4, L1, R4, R3, L1, L4, L1, L5, L2, R2, L1, R1, L5, L3, R4, L1, R5, L5, L5, L1, L3, R1, R5, L2, L4, L5, L1, L1, L2, R5, R5, L4, R3, L2, L1, L3, L4, L5, L5, L2, R4, R3, L5, R4, R2, R1, L5";

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

struct Point {
  int x;
  int y;
};

bool eq_points(struct Point p1, struct Point p2)
{
  return p1.x == p2.x && p1.y == p2.y;
}

int mod(int a, int b)
{
    int r = a % b;
    return r < 0 ? r + b : r;
}

int dist_to_point(struct Point p)
{
  return abs(p.x) + abs(p.y);
}

int main(int argc, char* argv[])
{
  if (argc < 2)
  {
    fprintf(stderr, "Usage: %s instruction_string\n", argv[0]);
    return 1;
  }

  char* instrs = argv[1];

  struct Point pos = { 0, 0 };

  // dir: 0 = NORTH, 1 = EAST, 2 = SOUTH, 3 = WEST
  int dir = 0;

  size_t trail_length = 1;
  struct Point * trail = malloc(trail_length * sizeof(struct Point));
  trail[0] = pos;

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

      for (int i = 0; i < dist; i++)
      {
        switch (dir)
        {
          case 0: pos.y -= 1; break;
          case 1: pos.x += 1; break;
          case 2: pos.y += 1; break;
          case 3: pos.x -= 1; break;
          default:
            fprintf(stderr, "Error: invalid direction %d.\n", dir);
            return 1;
        }

        trail_length++;
        trail = realloc(trail, trail_length * sizeof(struct Point));
        trail[trail_length-1].x = pos.x;
        trail[trail_length-1].y = pos.y;

        printf("Walked to (%d,%d).\n", pos.x, pos.y);
      }
    }
    else
    {
      fprintf(stderr, "Unrecognized character in string: %c\n", next);
      return 1;
    }
  }

  printf("We walked to (%d,%d), which is %d steps away.\n", pos.x, pos.y, dist_to_point(pos));

  printf("Checking for repeated visits.\n");
  for (size_t i = 0; i < trail_length; i++)
  {
    for (size_t j = 0; j < i; j++)
    {
      if (eq_points(trail[j], trail[i]))
      {
        printf("The first place we visited twice is (%d,%d), which is %d blocks away.\n", trail[i].x, trail[i].y, dist_to_point(trail[i]));
        goto end;
      }
    }
  }
  printf("We visited nowhere twice!\n");
  end:

  return 0;
}
