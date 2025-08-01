#include <stdio.h>
#include <string.h>

void get_next(char *T, int next[]) {
  int i = 1, j = 0;
  next[1] = 0;
  while (i < strlen(T)) {
    if (j == 0 || T[i] == T[j]) {
      i++;
      j++;
      next[i] = j;
    } else {
      j = next[j];
    }
  }
}

void get_nextval(char *T, int nextval[]) {
  int i = 1, j = 0;
  nextval[1] = 0;
  while (i < strlen(T)) {
    if (j == 0 || T[i] == T[j]) {
      i++;
      j++;
      if (T[i] != T[j]) {
        nextval[i] = j;
      } else {
        nextval[i] = nextval[j];
      }
    } else {
      j = nextval[j];
    }
  }
}

int main() {
  char *T = " AAABABD";
  int next[strlen(T) + 1];
  for (int i = 1; i < strlen(T); i++) {
    printf("%c ", T[i]);
  }
  printf("\n");
  for (int i = 1; i < strlen(T); i++) {
    printf("%d ", i);
  }
  printf("\n");
  get_next(T, next);
  for (int i = 1; i < strlen(T); i++) {
    printf("%d ", next[i]);
  }
  printf("\n");
  int nextval[strlen(T) + 1];
  get_nextval(T, nextval);
  for (int i = 1; i < strlen(T); i++) {
    printf("%d ", nextval[i]);
  }
  return 0;
}