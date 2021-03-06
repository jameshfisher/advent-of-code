/*
--- Day 5: How About a Nice Game of Chess? ---

You are faced with a security door designed by Easter Bunny engineers that
seem to have acquired most of their security knowledge by watching hacking
movies.

The eight-character password for the door is generated one character at a time
by finding the MD5 hash of some Door ID (your puzzle input) and an increasing
integer index (starting with 0).

A hash indicates the next character in the password if its hexadecimal
representation starts with five zeroes. If it does, the sixth character in the
hash is the next character of the password.

For example, if the Door ID is abc:

- The first index which produces a hash that starts with five zeroes is 3231929,
  which we find by hashing abc3231929; the sixth character of the hash, and thus
  the first character of the password, is 1.

- 5017308 produces the next interesting hash, which starts with 000008f82..., so
  the second character of the password is 8.

- The third time a hash starts with five zeroes is for abc5278568, discovering the
  character f.

In this example, after continuing this search a total of eight times, the
password is 18f47a30.

Given the actual Door ID, what is the password?
*/

#include <stdio.h>
#include <openssl/md5.h>
#include <string.h>

#define PASSWORD_LENGTH 8

int main(int argc, char* argv[])
{
  if (argc < 2)
  {
    fprintf(stderr, "Usage: %s <door_id>\n", argv[0]);
    return 1;
  }

  char* door_id = argv[1];
  size_t prefix_len = strlen(door_id);

  char candidate[50];
  strcpy(candidate, door_id);

  unsigned char md5_buf[MD5_DIGEST_LENGTH];

  printf("The password is: ");

  int done_chars = 0;
  for (int i = 0; done_chars < PASSWORD_LENGTH; i++)
  {
    sprintf(&candidate[prefix_len], "%d", i);

    MD5((unsigned char *) candidate, strlen(candidate), md5_buf);

    if (md5_buf[0] == 0 && md5_buf[1] == 0 && (md5_buf[2] >> 4) == 0)
    {
      unsigned char v = (md5_buf[2] << 4) >> 4;
      char pwd_char = v < 10 ? '0' + v : 'a' + (v-10);
      printf("%c", pwd_char); fflush(stdout);
      done_chars++;
    }
  }

  printf("\n");

  return 0;
}
