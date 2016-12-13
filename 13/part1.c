#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>

#define TIMES(X, N) for(int X = 0; X < (N); X++)

#define UNKNOWN_DIST (-1)

int favorite_number;  // from process args

int width;
int* grid;  // of size width*width

int last_dist;

int* blank_grid(int new_width)
{
  int num_cells = new_width * new_width;
  int* new_grid = malloc(sizeof(int) * num_cells);

  TIMES(i, num_cells)
  {
    new_grid[i] = UNKNOWN_DIST;
  }

  return new_grid;
}

void expand_grid(void)
{
  int new_width = width * 2;

  // we can't just realloc because the indexes are different for a larger grid
  int* new_grid = blank_grid(new_width);

  // copy old grid to new grid
  TIMES(x, width)
  {
    TIMES(y, width)
    {
      size_t old_ix = (y * width) + x;
      size_t new_ix = (y * new_width) + x;
      new_grid[new_ix] = grid[old_ix];
    }
  }

  free(grid);

  width = new_width;
  grid = new_grid;
}

int get_dist(int x, int y)
{
  assert(0 <= x);
  assert(0 <= y);

  if (x < width && y < width)
  {
    size_t ix = (y * width) + x;
    return grid[ix];
  }

  return UNKNOWN_DIST;
}

void set_dist(int x, int y, int dist)
{
  assert(0 <= x);
  assert(0 <= y);

  // We may need to expand the grid!
  while ((width <= x) || (width <= y))
  {
    expand_grid();
  }

  size_t ix = (y * width) + x;
  grid[ix] = dist;
}

bool is_wall(int x, int y)
{
  int bin = (x*x + 3*x + 2*x*y + y + y*y) + favorite_number;

  int num_bits = 0;
  while (bin != 0)
  {
    if (bin & 1) { num_bits++; }
    bin = bin >> 1;
  }

  return num_bits & 1;
}

void visit_cell(int x, int y)
{
  if (0 <= x && 0 <= y && get_dist(x,y) == UNKNOWN_DIST && !is_wall(x, y))
  {
    set_dist(x, y, last_dist+1);
  }
}

void iter_grid(void)
{
  TIMES (x, width)
  {
    TIMES (y, width)
    {
      if (get_dist(x, y) == last_dist)
      {
        visit_cell(x+1, y);
        visit_cell(x-1, y);
        visit_cell(x, y+1);
        visit_cell(x, y-1);
      }
    }
  }
  // FIXME this does not check that we made progress ...

  last_dist++;
}

int main(int argc, char* argv[])
{
  if (argc < 2)
  {
    fprintf(stderr, "Usage: %s <favorite_number>\n", argv[0]);
    return EXIT_FAILURE;
  }

  if (sscanf(argv[1], "%d", &favorite_number) != 1)
  {
    fprintf(stderr, "Could not parse favorite number: %s\n", argv[1]);
    return EXIT_FAILURE;
  }

  width = 2;
  grid = blank_grid(width);

  set_dist(1, 1, 0);  // 0 steps from current location
  last_dist = 0;

  while (get_dist(31,39) == UNKNOWN_DIST)
  {
    iter_grid();
  }

  printf("Distance to (31,39) is: %d\n", get_dist(31,39));

  return EXIT_SUCCESS;
}
