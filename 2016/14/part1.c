#include <stdlib.h>
#include <stdio.h>
#include <openssl/md5.h>

// Hex char = 4 bits
#define MD5_HEX_LENGTH (MD5_DIGEST_LENGTH * 2)

// not quite hex but isomorphic
char get_hex_at(char* buf, unsigned int index)
{
  unsigned char byte = buf[index >> 1];
  return (index & 1) ? (byte & (1+2+4+8)) : (byte >> 4);
}

int main(int argc, char* argv[])
{
  if (argc < 2)
  {
    fprintf(stderr, "Usage: %s <salt>\n", argv[0]);
    return EXIT_FAILURE;
  }

  char const * const salt = argv[1];
  int const salt_len = strlen(salt);

  char candidate[100];
  strcpy(candidate, salt);

  char* const index_start = &candidate[salt_len];

  int found = 0;

  unsigned char md5_buf[MD5_DIGEST_LENGTH];

  for (int index = 0; found < 64; index++)
  {
    sprintf(index_start, "%d", index);

    MD5(candidate, strlen(candidate), md5_buf);

    for (int hi = 0; hi < MD5_HEX_LENGTH; hi++)
    {
      if (hi % 2)
      {
        hi 
      }
    }

    if (ok(md5_buf))
    {
      found++;
    }
  }

  printf("Index producing 64th one-time pad key: %d\n", index);

  return EXIT_SUCCESS;
}
