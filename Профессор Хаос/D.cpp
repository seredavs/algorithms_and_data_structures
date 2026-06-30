#include <stdio.h>

int main() {
  unsigned short a, b, c, d;
  unsigned long long k;
  scanf("%hu %hu %hu %hu %llu", &a, &b, &c, &d, &k);

  unsigned long long numOfBakterii = a;
  unsigned long long prev = a;
  int cycleDetected = 0;

  for (unsigned long long i = 1; i <= k; i++) {
    numOfBakterii = numOfBakterii * b;

    if (numOfBakterii <= c) {
      numOfBakterii = 0;
      break;
    }
    numOfBakterii -= c;

    if (numOfBakterii > d) {
      numOfBakterii = d;
    }

    if (numOfBakterii == prev) {
      cycleDetected = 1;
      break;
    }
    prev = numOfBakterii;

    if (numOfBakterii == 0) {
      break;
    }
  }

  if (cycleDetected) {
    printf("%llu", numOfBakterii);
  } else {
    printf("%llu", numOfBakterii);
  }

  return 0;
}
