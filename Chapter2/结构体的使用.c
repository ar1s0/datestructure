#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_SIZE 5

struct student {
  int id;
  char name[50];
  float score;
  struct student *next;
} *student_list;

void init() {
  student_list = NULL;
  srand((unsigned int)time(NULL));
  for (int i = 0; i < MAX_SIZE; i++) {
    struct student *new_student =
        (struct student *)malloc(sizeof(struct student));
    if (new_student == NULL) {
      fprintf(stderr, "Memory allocation failed\n");
      exit(EXIT_FAILURE);
    }
    new_student->id = rand() % 1000; // Random ID
    snprintf(new_student->name, sizeof(new_student->name), "Student%d", i + 1);
    new_student->score =
        (float)(rand() % 101); // Random score between 0 and 100
    new_student->next = student_list;
    student_list = new_student;
  }
}

void printStudentList() {
  struct student *current = student_list;
  while (current != NULL) {
    printf("ID: %d, Name: %s, Score: %.2f\n", current->id, current->name,
           current->score);
    current = current->next;
  }
}

void freeStudentList() {
  struct student *current = student_list;
  while (current != NULL) {
    struct student *temp = current;
    current = current->next;
    free(temp);
  }
}

int main() {
  init();
  printStudentList();
  freeStudentList();
  return 0;
}