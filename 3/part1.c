/*

--- Day 3: Squares With Three Sides ---

Now that you can think clearly, you move deeper into the labyrinth of hallways
and office furniture that makes up this part of Easter Bunny HQ. This must be a
graphic design department; the walls are covered in specifications for
triangles.

Or are they?

The design document gives the side lengths of each triangle it describes, but...
5 10 25? Some of these aren't triangles. You can't help but mark the impossible
ones.

In a valid triangle, the sum of any two sides must be larger than the remaining
side. For example, the "triangle" given above is impossible, because 5 + 10 is
not larger than 25.

In your puzzle input, how many of the listed triangles are possible?

*/

#include <stdio.h>
#include <stdlib.h>

int gt(const void * a, const void * b)
{
  return *((int*) a) > *((int*) b);
}

int main(void)
{
  int possible = 0;

  int l[3];

  while (scanf("%d %d %d", &l[0], &l[1], &l[2]) == 3)
  {
    qsort(l, 3, sizeof(int), &gt);
    if (l[0] + l[1] > l[2])
    {
      possible++;
    }
  }

  printf("The number of possible triangles is: %d\n", possible);

  return 0;
}
