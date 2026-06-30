#include <stdio.h>
#include <stdlib.h>

int* ProductPrices;
int NumOfProducts;
int K;

int compare(const void* a, const void* b) {
  return *(int*)b - *(int*)a;
}

int main() {
  scanf("%d", &NumOfProducts);
  scanf("%d", &K);

  ProductPrices = (int*)malloc(NumOfProducts * sizeof(int));

  for (int i = 0; i < NumOfProducts; i++) {
    scanf("%d", &ProductPrices[i]);
  }

  qsort(ProductPrices, NumOfProducts, sizeof(int), compare);

  long totalPrice = 0;
  int productPositionOnPurchase = 0;
  for (int i = 0; i < NumOfProducts; i++) {
    productPositionOnPurchase++;
    if (productPositionOnPurchase == K)
      productPositionOnPurchase = 0;
    else
      totalPrice += ProductPrices[i];
  }
  printf("%ld", totalPrice);

  free(ProductPrices);
  return 0;
}
