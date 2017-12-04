#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#define TIMES(X) for (int x = 0; x < X; x++)

int main(void)
{
  uint64_t out_len = 0;

  while (true)
  {
    int c = getchar();
    if (c == EOF)
    {
      break;
    }
    else if (c == '(')
    {
      int num_chars;
      int num_repeats;
      int num_read = scanf("%dx%d)", &num_chars, &num_repeats);
      printf("Got (%dx%d)\n", num_chars, num_repeats);
      int skip = num_chars * num_repeats;
      TIMES(num_chars) getchar();  // assumes will not EOF
      out_len += skip;
    }
    else if (c == ' ' || c == '\n' || c == '\t')
    {
      // Whitespace is ignored
    }
    else {
      printf("Single char: '%c'\n", c);
      out_len++;
    }
  }

  printf("Decompressed length: %llu\n", out_len);

  return EXIT_SUCCESS;
}
