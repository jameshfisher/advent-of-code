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

--- Part Two ---

You would also like to know which IPs support SSL (super-secret listening).

An IP supports SSL if it has an Area-Broadcast Accessor, or ABA, anywhere in the
supernet sequences (outside any square bracketed sections), and a corresponding
Byte Allocation Block, or BAB, anywhere in the hypernet sequences. An ABA is any
three-character sequence which consists of the same character twice with a
different character between them, such as xyx or aba. A corresponding BAB is the
same characters but in reversed positions: yxy and bab, respectively.

For example:

- aba[bab]xyz supports SSL (aba outside square brackets with corresponding bab
  within square brackets).

- xyx[xyx]xyx does not support SSL (xyx, but no corresponding yxy).

- aaa[kek]eke supports SSL (eke in supernet with corresponding kek in hypernet;
  the aaa sequence is not related, because the interior character must be
  different).

- zazbz[bzb]cdb supports SSL (zaz has no corresponding aza, but zbz has a
  corresponding bzb, even though zaz and zbz overlap).

How many IPs in your puzzle input support SSL?

*/

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include <ctype.h>

#include "deps/vec/vec.c"

typedef struct aba {
  char a;
  char b;
} aba;

typedef vec_t(aba) vec_aba_t;

int main(void)
{
  uint32_t num_ssl = 0;

  aba history = { 0, '\n' };
  bool in_brackets = false;

  vec_aba_t aba_in_brackets;
  vec_init(&aba_in_brackets);

  vec_aba_t aba_out_brackets;
  vec_init(&aba_out_brackets);

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

      for (size_t i = 0; i < aba_in_brackets.length; i++)
      {
        aba aba_in = aba_in_brackets.data[i];
        for (size_t j = 0; j < aba_out_brackets.length; j++)
        {
          aba aba_out = aba_out_brackets.data[j];
          if (aba_in.a == aba_out.b && aba_in.b == aba_out.a)
          {
            num_ssl++;
            goto searched_abas;
          }
        }
      }
      searched_abas:

      vec_clear(&aba_in_brackets);
      vec_clear(&aba_out_brackets);
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
        isalpha(history.a) &&
        isalpha(history.b) &&
        isalpha(c) &&
        history.a != history.b &&
        history.a == c)
      {
        // Found an ABA.
        if (in_brackets)
        {
          vec_push(&aba_in_brackets, history);
        }
        else
        {
          vec_push(&aba_out_brackets, history);
        }
      }
    }

    history.a = history.b;
    history.b = c;
  }

  printf("Number of IPs supporting SSL: %d\n", num_ssl);

  return EXIT_SUCCESS;
}
