#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct LinkNode {
  int data;
  struct LinkNode *next;
} *LiStack;

void initStack(LiStack s) {

  printf("address of s: \t\t%p\n", (void *)&s);
  printf("point address of s: \t%p\n", (void *)s);

  if (s == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    exit(EXIT_FAILURE);
  }
  s->next = NULL;
}

bool isEmpty(LiStack s) { return s->next == NULL; }

bool push(LiStack s, int e) {
  LiStack newNode = (LiStack)malloc(sizeof(struct LinkNode));
  if (newNode == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    return false;
  }
  newNode->data = e;
  newNode->next = s->next;
  s->next = newNode;
  return true;
}

bool pop(LiStack s, int *e) {
  if (isEmpty(s)) {
    fprintf(stderr, "Stack is empty\n");
    return false;
  }
  LiStack temp = s->next;
  *e = temp->data;
  s->next = temp->next;
  free(temp);
  return true;
}

void printStack(LiStack s) {
  LiStack current = s->next;
  while (current != NULL) {
    printf("%d ", current->data);
    current = current->next;
  }
  printf("\n");
}

int main() {
  LiStack s;
  s = (LiStack)malloc(sizeof(struct LinkNode));
  printf("address of s: \t\t%p\n", (void *)&s);
  printf("point address of s: \t%p\n", (void *)s);
  initStack(s);
  push(s, 10);
  push(s, 20);
  printStack(s);
  return 0;
}