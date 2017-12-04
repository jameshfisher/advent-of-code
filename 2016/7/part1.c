/*

--- Day 7: Internet Protocol Version 7 ---

While snooping around the local network of EBHQ, you compile a list of IP
addresses (they're IPv7, of course; IPv6 is much too limited). You'd like to
figure out which IPs support TLS (transport-layer snooping).

An IP supports TLS if it has an Autonomous Bridge Bypass Annotation, or ABBA. An
ABBA is any four-character sequence which consists of a pair of two different
characters followed by the reverse of that pair, such as xyyx or abba. However,
the IP also must not have an ABBA within any hypernet sequences, which are
contained by square brackets.

For example:

- abba[mnop]qrst supports TLS (abba outside square brackets).

- abcd[bddb]xyyx does not support TLS (bddb is within square brackets, even
  though xyyx is outside square brackets).

- aaaa[qwer]tyui does not support TLS (aaaa is invalid; the interior characters
  must be different).

- ioxxoj[asdfgh]zxcvbn supports TLS (oxxo is outside square brackets, even
  though it's within a larger string).

How many IPs in your puzzle input support TLS?
*/

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include <ctype.h>

int main(void)
{
  uint32_t num_tls = 0;

  char history[3] = { 0, 0, '\n' };
  bool in_brackets = false;

  bool tls_in_brackets = false;
  bool tls_out_brackets = false;

  while (true)
  {
    int c = getchar();
    if (c == EOF)
    {
      break;
    }

    if (c == '\n')
    {
      assert(!in_brackets);
      if (tls_out_brackets && !tls_in_brackets)
      {
        num_tls++;
      }
      tls_in_brackets = false;
      tls_out_brackets = false;
    }
    else if (c == '[')
    {
      assert(!in_brackets);
      in_brackets = true;
    }
    else if (c == ']')
    {
      assert(in_brackets);
      in_brackets = false;
    }
    else
    {
      if (
        isalpha(history[0]) &&
        isalpha(history[1]) &&
        isalpha(history[2]) &&
        isalpha(c) &&
        history[0] != history[1] &&
        history[1] == history[2] &&
        history[0] == c)
      {
        if (in_brackets)
        {
          tls_in_brackets = true;
        }
        else
        {
          tls_out_brackets = true;
        }
      }
    }

    // TODO use a bit-shift
    history[0] = history[1];
    history[1] = history[2];
    history[2] = c;
  }

  printf("Number of IPs supporting TLS: %d\n", num_tls);

  return EXIT_SUCCESS;
}
