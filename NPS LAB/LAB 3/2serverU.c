#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>

#define PORT 1234

void swap(char *x, char *y) {
  char temp;
  temp = *x;
  *x = *y;
  *y = temp;
}

void permute(char *a, int l, int r) {
  int i;
  if (l == r)
    printf("%s\n", a);
  else {
    for (i = l; i <= r; i++) {
      swap((a + l), (a + i));
      permute(a, l + 1, r);
      swap((a + l), (a + i)); //backtrack
    }
  }
}

int main() {
  int s, r, recb, ca;
  struct sockaddr_in server, client;
  char buff[50];
  socklen_t len = sizeof(client);

  s = socket(AF_INET, SOCK_DGRAM, 0);
  if (s == -1) {
    printf("\nSocket creation error.");
    exit(0);
  }
  printf("\nSocket created.\n");

  server.sin_family = AF_INET;
  server.sin_port = htons(PORT);
  server.sin_addr.s_addr = htonl(INADDR_ANY);

  r = bind(s, (struct sockaddr *)&server, sizeof(server));
  if (r == -1) {
    printf("\nBinding error.");
    exit(0);
  }
  printf("\nSocket binded.\n");

  while (1) {
    recb = recvfrom(s, buff, sizeof(buff), 0, (struct sockaddr *)&client, &len);
    if (recb == -1) {
      printf("\nMessage Receiving Failed");
      close(s);
      exit(0);
    }
    printf("\nMessage Received: %s", buff);
    if (!strcmp(buff, "stop"))
      break;
    printf("\nPermutations of the string are: \n");
    int n = strlen(buff);
    permute(buff, 0, n - 1);
  }
  close(s);
  return 0;
}

