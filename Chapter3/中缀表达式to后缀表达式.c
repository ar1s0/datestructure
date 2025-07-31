#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Stack implementation for operators
typedef struct {
  char *items;
  int top;
  int capacity;
} Stack;

Stack *createStack(int capacity) {
  Stack *stack = (Stack *)malloc(sizeof(Stack));
  stack->capacity = capacity;
  stack->top = -1;
  stack->items = (char *)malloc(capacity * sizeof(char));
  return stack;
}

bool isEmpty(Stack *stack) { return stack->top == -1; }

char peek(Stack *stack) { return stack->items[stack->top]; }

void push(Stack *stack, char item) { stack->items[++stack->top] = item; }

char pop(Stack *stack) {
  if (isEmpty(stack))
    return '\0';
  return stack->items[stack->top--];
}

bool isOperator(char c) {
  return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

int precedence(char op) {
  switch (op) {
  case '^':
    return 4;
  case '*':
  case '/':
    return 3;
  case '+':
  case '-':
    return 2;
  default:
    return 0;
  }
}

bool toPostfix(const char *infix, char *postfix) {
  Stack *stack = createStack(strlen(infix));
  if (!stack)
    return false;

  int j = 0;
  for (int i = 0; infix[i]; i++) {
    char c = infix[i];

    if (isalnum(c)) {
      postfix[j++] = c;
    } else if (c == '(') {
      push(stack, c);
    } else if (c == ')') {
      while (!isEmpty(stack) && peek(stack) != '(') {
        postfix[j++] = pop(stack);
      }
      if (!isEmpty(stack) && peek(stack) != '(') {
        // Mismatched parentheses
        free(stack->items);
        free(stack);
        return false;
      } else {
        pop(stack); // Remove '(' from stack
      }
    } else if (isOperator(c)) {
      while (!isEmpty(stack) && precedence(peek(stack)) >= precedence(c)) {
        postfix[j++] = pop(stack);
      }
      push(stack, c);
    }
  }

  // Pop all remaining operators from stack
  while (!isEmpty(stack)) {
    char op = pop(stack);
    if (op == '(') {
      // Mismatched parentheses
      free(stack->items);
      free(stack);
      return false;
    }
    postfix[j++] = op;
  }

  postfix[j] = '\0'; // Null-terminate the string

  free(stack->items);
  free(stack);
  return true;
}

int main() {
  const char *infix = "a+b*(c-d)/e";
  char postfix[100]; // Assuming a maximum size for the postfix expression

  printf("Infix expression: \t%s\n", infix);
  if (toPostfix(infix, postfix)) {
    printf("Postfix expression: \t%s\n", postfix);
  } else {
    fprintf(stderr, "Error converting infix to postfix\n");
  }

  return 0;
}