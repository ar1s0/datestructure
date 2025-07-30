#include <stdio.h>

void fun(int *b, int *c) {
  *b = 5; // 修改指针b指向的值
  *c = 6; // 修改指针c指向的值
}

int main() {
  int a = 2;
  int b, *c;
  c = &a;
  fun(&b, c); // 调用函数修改b和c
  printf("a = %d, b = %d, *c = %d\n", a, b, *c);
  *c = 3; // 修改指针c指向的值
  printf("a = %d, b = %d, *c = %d\n", a, b, *c);
  a = 4; // 修改变量a的值
  printf("a = %d, b = %d, *c = %d\n", a, b, *c);
  b = 7; // 修改变量b的值
  printf("a = %d, b = %d, *c = %d\n", a, b, *c);
  printf("Address of a: %p\n", (void *)&a);
  printf("Address of b: %p\n", (void *)&b);
  printf("Address of c: %p\n", (void *)&c);
  return 0;
}