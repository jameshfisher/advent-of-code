/*
--- Day 6: Signals and Noise ---

 Something is jamming your communications with Santa. Fortunately, your signal
is only partially jammed, and protocol in situations like this is to switch to
a simple repetition code to get the message through.

In this model, the same message is sent repeatedly. You've recorded the
repeating message signal (your puzzle input), but the data seems quite corrupted -
almost too badly to recover. Almost.

All you need to do is figure out which character is most frequent for each
position. For example, suppose you had recorded the following messages:

    eedadn
    drvtee
    eandsr
    raavrd
    atevrs
    tsrnev
    sdttsa
    rasrtv
    nssdts
    ntnada
    svetve
    tesnvt
    vntsnd
    vrdear
    dvrsen
    enarar

The most common character in the first column is e; in the second, a; in the
third, s, and so on. Combining these characters returns the error-corrected
message, easter.

Given the recording in your puzzle input, what is the error-corrected version of
the message being sent?
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

int main(void)
{

  char* line_buffer = NULL;
  size_t line_buffer_size = 0;
  size_t const first_line_length = getline(&line_buffer, &line_buffer_size, stdin);

  size_t const num_chars = first_line_length - 1;  // We also got a newline char, which we ignore.

  uint32_t counters[num_chars][26];
  memset(counters, 0, sizeof(uint32_t) * num_chars * 26);

  // Consume all lines.
  while (true)
  {
    for (size_t i = 0; i < num_chars; i++)
    {
      int c = line_buffer[i] - 'a';
      assert(0 <= c && c < 26);
      if (c != '\n')
      {
        counters[i][c]++;
      }
    }

    size_t new_line_length = getline(&line_buffer, &line_buffer_size, stdin);
    if (new_line_length != first_line_length) {
      printf("New line length %zu is not %zu.\n", new_line_length, first_line_length);
      break;
    }
  }

  // Run through characters, printing out the most popular.
  for (size_t char_index = 0; char_index < num_chars; char_index++)
  {
    char best_char;
    uint32_t best_count = 0;
    for (size_t chr = 0; chr < 26; chr++)
    {
      uint32_t this_count = counters[char_index][chr];
      if (best_count < this_count)
      {
        best_char = chr;
        best_count = this_count;
      }
    }

    printf("%c", 'a' + best_char);
  }

  printf("\n");

  free(line_buffer);

  return EXIT_SUCCESS;
}
