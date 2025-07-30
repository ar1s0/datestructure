#include <stdio.h>

#define dataType long long

int main() {
  dataType a[3] = {1, 2, 3};
  // 000000E4493FF900
  printf("%p\n", (void *)a);
  // 这里的加一实际是计算过的数据偏移等效于 a + sizeof(dataType)
  printf("%p\n", (void *)(a + 1));
  printf("%p\n", (void *)(a + 2));
  return 0;
}