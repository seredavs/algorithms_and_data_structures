#include <stdio.h>
#include <string.h>

char Strings[100][102];
int StringsCount = 0;
int AvailableStingsWithBeginningChar[10];
int CurrentAvailableMaxBeginningCharValue;
short StringIsAvailable[100];

int CharToInt(char c) {
  return c - '0';
}

char IntToChar(int i) {
  return i + '0';
}

int IsBetter(int a, int b) {
  char strA[202], strB[202];
  strcpy(strA, Strings[a]);
  strcpy(strB, Strings[b]);
  strcat(strA, Strings[b]);
  strcat(strB, Strings[a]);
  return strcmp(strA, strB) > 0;
}

int GetPreferredString(int firstStringIndex, int secondStringIndex) {
  if (IsBetter(firstStringIndex, secondStringIndex))
    return firstStringIndex;
  return secondStringIndex;
}

void CountAvailableStingsWithBeginningChar() {
  for (int i = 0; i < StringsCount; i++) {
    AvailableStingsWithBeginningChar[CharToInt(Strings[i][0])]++;
  }
  for (int i = 0; i < 10; i++) {
    if (AvailableStingsWithBeginningChar[i] > 0) {
      CurrentAvailableMaxBeginningCharValue = i;
    }
  }
}

void GenerateMaxSubString(int charValue) {
  while (AvailableStingsWithBeginningChar[charValue] > 0) {
    int optimalStringIndex = -1;
    int CheckedStringsCount = 0;
    char firstChar = IntToChar(charValue);
    for (int i = 0; i < StringsCount; i++) {
      if (StringIsAvailable[i] && Strings[i][0] == firstChar) {
        if (optimalStringIndex == -1) {
          optimalStringIndex = i;
        } else {
          optimalStringIndex = GetPreferredString(i, optimalStringIndex);
        }
        CheckedStringsCount++;
        if (CheckedStringsCount == AvailableStingsWithBeginningChar[charValue])
          break;
      }
    }
    printf("%s", Strings[optimalStringIndex]);
    StringIsAvailable[optimalStringIndex] = 0;
    AvailableStingsWithBeginningChar[charValue]--;
  }
}

void GenerateMaxString() {
  for (int i = CurrentAvailableMaxBeginningCharValue; i >= 0; i--) {
    if (AvailableStingsWithBeginningChar[i] > 0) {
      GenerateMaxSubString(i);
    }
  }
}

int main() {
  while (1) {
    char buff[102];
    if (scanf("%s", buff) == EOF)
      break;
    strcpy(Strings[StringsCount], buff);
    StringIsAvailable[StringsCount] = 1;
    StringsCount++;
  }
  CountAvailableStingsWithBeginningChar();
  GenerateMaxString();
  printf("\n");
  return 0;
}
