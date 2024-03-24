#include <stdio.h>
#include <time.h>

#define CLOCKS_PER_MILLI (CLOCKS_PER_SEC / 1000)

int fib(int n) {
  if (n < 2) return n;
  return fib(n - 1) + fib(n - 2);
}

int main() {
  double start = (double)clock() / CLOCKS_PER_MILLI;
  printf("%d\n", fib(40));
  printf("%f\n", (double)clock() / CLOCKS_PER_MILLI - start);
}
