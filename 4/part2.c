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

--- Part Two ---

With all the decoy data out of the way, it's time to decrypt this list and get
moving.

The room names are encrypted by a state-of-the-art shift cipher, which is nearly
unbreakable without the right software. However, the information kiosk designers
at Easter Bunny HQ were not expecting to deal with a master cryptographer like
yourself.

To decrypt a room name, rotate each letter forward through the alphabet a number
of times equal to the room's sector ID. A becomes B, B becomes C, Z becomes A,
and so on. Dashes become spaces.

For example, the real name for qzmt-zixmtkozy-ivhz-343 is very encrypted name.

What is the sector ID of the room where North Pole objects are stored?

*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>

typedef struct room {
  char* encrypted_name;
  int sector_id;
  char* checksum;
} room;

void free_room(room r)
{
  free(r.encrypted_name);
  free(r.checksum);
}

// returns C-string
char* encrypted_name_checksum(char_const_ptr encrypted_name)
{
  int * const encrypted_name_vec = calloc(26, sizeof(int));

  int c;

  for (
    char c = *encrypted_name;
    c != '\0';
    encrypted_name++, c = *encrypted_name
  )
  {
    if (isalpha(c))
    {
      encrypted_name_vec[c - 'a']++;
    }
  }

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

bool room_has_valid_checksum(room p)
{
  char* const computed_checksum = encrypted_name_checksum(p.encrypted_name);
  bool const eq = strcmp(p.checksum, computed_checksum) == 0;
  free(computed_checksum);
  return eq;
}

// assumes room has valid checksum
char* name_of_room(room const * const p)
{
  char* const decrypted_name = strdup(p->encrypted_name);
  assert(decrypted_name != NULL);

  int const sector_id = p->sector_id;

  for (int i = 0; decrypted_name[i] != '\0'; i++)
  {
    char c = decrypted_name[i];
    decrypted_name[i] = c == '-' ? ' ' : ((c - 'a' + sector_id) % 26) + 'a';
  }

  return decrypted_name;
}

room parse_room(char * const line)
{
  room r;

  r.checksum = malloc(6);

  int first_digit_index;
  for (first_digit_index = 0; !isdigit(line[first_digit_index]); first_digit_index++);

  if (sscanf(&line[first_digit_index], "%d[%5[abcdefghijklmnopqrstuvwxyz]]", &r.sector_id, r.checksum) != 2)
  {
    fprintf(stderr, "Could not parse checksum\n");
    exit(1);
  }

  // overwrite the separating hyphen.
  line[first_digit_index-1] = '\0';

  r.encrypted_name = realloc(line, first_digit_index);

  return r;
}

// returned line includes newline
char* get_line(void)
{
  char* lineptr = NULL;
  size_t n = 0;
  ssize_t num_chars_read = getline(&lineptr, &n, stdin);

  if (num_chars_read == -1)
  {
    free(lineptr);
    return NULL;
  }

  return lineptr;
}

bool consume_line(void)
{
  char* line = get_line();

  if (line == NULL)
  {
    return false;
  }

  room r = parse_room(line);

  if (room_has_valid_checksum(r))
  {
    char* room_name = name_of_room(&r);

    if (strcmp(room_name, "northpole object storage") == 0)
    {
      printf("Sector ID of northpole object storage: %d\n", r.sector_id);
    }

    free(room_name);
  }

  free_room(r);

  return true;
}

int main(void)
{
  while (consume_line());

  return 0;
}
