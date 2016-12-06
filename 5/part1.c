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
