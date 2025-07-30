#include <stdio.h>
#include <stdlib.h>

struct Node {
  int data;
  struct Node *next;
};

struct Node *createNode(int data);
void printList(struct Node *head);
void freeList(struct Node *head);

void insertNode(struct Node **head, int data, int position) {
  struct Node *newNode = createNode(data);
  if (*head == NULL || position == 0) {
    newNode->next = *head;
    *head = newNode;
    return;
  }

  struct Node *current = *head;
  for (int i = 0; i < position - 1 && current->next != NULL; i++) {
    current = current->next;
  }

  newNode->next = current->next;
  current->next = newNode;
}

int main() {
  struct Node *head = NULL;

  // 插入节点
  insertNode(&head, 10, 0);
  insertNode(&head, 20, 1);
  insertNode(&head, 30, 0);
  insertNode(&head, 40, 0);
  insertNode(&head, 50, 2);

  // 打印链表
  printf("Linked List: ");
  printList(head);

  freeList(head);
  return 0;
}

struct Node *createNode(int data) {
  struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
  if (newNode == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    exit(EXIT_FAILURE);
  }
  newNode->data = data;
  newNode->next = NULL;
  return newNode;
}

void freeList(struct Node *head) {
  struct Node *current = head;
  struct Node *nextNode;
  while (current != NULL) {
    nextNode = current->next;
    free(current);
    current = nextNode;
  }
}

void printList(struct Node *head) {
  if (head == NULL) {
    printf("List is empty.\n");
    return;
  }
  struct Node *current = head;
  while (current != NULL) {
    printf("%d ", current->data);
    current = current->next;
  }
  printf("\n");
}