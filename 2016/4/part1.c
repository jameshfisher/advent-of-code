/*
--- Day 4: Security Through Obscurity ---

Finally, you come across an information kiosk with a list of rooms. Of course,
the list is encrypted and full of decoy data, but the instructions to decode
the list are barely hidden nearby. Better remove the decoy data first.

Each room consists of an encrypted name (lowercase letters separated by dashes)
followed by a dash, a sector ID, and a checksum in square brackets.

A room is real (not a decoy) if the checksum is the five most common letters in
the encrypted name, in order, with ties broken by alphabetization. For example:

    aaaaa-bbb-z-y-x-123[abxyz] is a real room because the most common letters
    are a (5), b (3), and then a tie between x, y, and z, which are listed
    alphabetically.

    a-b-c-d-e-f-g-h-987[abcde] is a real room because although the letters are
    all tied (1 of each), the first five are listed alphabetically.

    not-a-real-room-404[oarel] is a real room.

    totally-real-room-200[decoy] is not.

Of the real rooms from the list above, the sum of their sector IDs is 1514.

What is the sum of the sector IDs of the real rooms?
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// returns NULL if finds EOF before it finds a digit
char* get_encrypted_name_vec(void)
{
  char* encrypted_name_vec = calloc(26, sizeof(char));

  int c;

  while (true)
  {
    c = getchar();

    if (c == EOF)
    {
      free(encrypted_name_vec);
      return NULL;
    }
    else if (c == '-' || c == '\n')
    {
      continue;
    }
    else if (isalpha(c))
    {
      encrypted_name_vec[c - 'a']++;
    }
    else if (isdigit(c))
    {
      ungetc(c, stdin);
      return encrypted_name_vec;
    }
    else
    {
      fprintf(stderr, "Unexpected character when parsing encrypted name: '%c'\n", c);
      exit(1);
    }
  }
}

int get_sector_id(void)
{
  int sector_id;
  if (scanf("%d", &sector_id) != 1)
  {
    fprintf(stderr, "Expected int after name\n");
    exit(1);
  }
  return sector_id;
}

// consumes "[abxyz]" etc from stdin; returns C-string "abxyz"
char* get_checksum(void)
{
  char* checksum = malloc(6);

  if (scanf("[%5[abcdefghijklmnopqrstuvwxyz]]", checksum) != 1)
  {
    fprintf(stderr, "Could not parse checksum\n");
    exit(1);
  }

  return checksum;
}

// consumes argument
// returns C-string
char* encrypted_name_vec_to_checksum(char* encrypted_name_vec)
{
  char* checksum = malloc(6 * sizeof(char));

  for (int i = 0; i < 5; i++)
  {
    int largest_index = 0;
    for (int j = 0; j < 26; j++)
    {
      if (encrypted_name_vec[largest_index] < encrypted_name_vec[j])
      {
        largest_index = j;
      }
    }
    checksum[i] = 'a' + largest_index;
    encrypted_name_vec[largest_index] = 0;
  }

  checksum[5] = '\0';

  free(encrypted_name_vec);

  return checksum;
}

// return -1 if line could not be consumed
// return 0 if consumed, but invalid checksum
// otherwise, returns sector_id of consumed line
int consume_line(void)
{
  char* name = get_encrypted_name_vec();

  if (name == NULL)
  {
    return -1;
  }

  int sector_id = get_sector_id();
  char* claimed_checksum = get_checksum();

  char* computed_checksum = encrypted_name_vec_to_checksum(name);

  bool eq = strcmp(claimed_checksum, computed_checksum) == 0;

  free(computed_checksum);
  free(claimed_checksum);

  return eq ? sector_id : 0;
}

int main(void)
{
  int sum_valid_sector_ids = 0;

  int sector_id;
  while ((sector_id = consume_line()) != -1)
  {
    sum_valid_sector_ids += sector_id;
  }

  printf("Sum of valid sector IDs: %d\n", sum_valid_sector_ids);

  return 0;
}
