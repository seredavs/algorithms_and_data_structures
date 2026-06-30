#include <stdio.h>

int main() {
  int numberOfFlowers;
  int startMaxSetPosition;
  int endMaxSetPosition;
  int startCurrentSetPosition;
  int endCurrentSetPosition;
  int repetitionsCount;
  unsigned long previousFlowerType;
  unsigned long currentFlowerType;

  scanf("%d", &numberOfFlowers);

  scanf("%lu", &previousFlowerType);
  startCurrentSetPosition = 1;
  startMaxSetPosition = 1;
  endMaxSetPosition = 1;
  endCurrentSetPosition = 1;
  repetitionsCount = 1;

  for (int i = 2; i <= numberOfFlowers; i++) {
    scanf("%lu", &currentFlowerType);

    if (previousFlowerType == currentFlowerType) {
      repetitionsCount++;

      if (repetitionsCount == 3) {
        endCurrentSetPosition = i - 1;

        int currentLength = endCurrentSetPosition - startCurrentSetPosition + 1;
        int maxLength = endMaxSetPosition - startMaxSetPosition + 1;
        if (currentLength > maxLength) {
          startMaxSetPosition = startCurrentSetPosition;
          endMaxSetPosition = endCurrentSetPosition;
        }

        startCurrentSetPosition = i - 1;
        repetitionsCount = 2;
      }
    } else {
      repetitionsCount = 1;
    }

    if (i == numberOfFlowers) {
      int currentLength = i - startCurrentSetPosition + 1;
      int maxLength = endMaxSetPosition - startMaxSetPosition + 1;
      if (currentLength > maxLength) {
        startMaxSetPosition = startCurrentSetPosition;
        endMaxSetPosition = i;
      }
    }

    previousFlowerType = currentFlowerType;
  }

  printf("%d %d\n", startMaxSetPosition, endMaxSetPosition);

  return 0;
}
