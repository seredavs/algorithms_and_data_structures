#include <stdio.h>
#include <string.h>

char String[100005];
long long Weight[26];
int CharacterCounters[26];
int StringLen;
int ReservedPosition = -1;
int NumOfMultiOccurCharacters = 0;

void CountNumberOfCharacters() {
  for (int i = 0; i < 100005; i++) {
    if (String[i] == '\0') {
      StringLen = i;
      break;
    }
    CharacterCounters[String[i] - 'a']++;
  }
}

void SwapChars(int firstPosition, int secondPosition) {
  char temp = String[firstPosition];
  String[firstPosition] = String[secondPosition];
  String[secondPosition] = temp;
}

int GetSymbolWithMaximumWeight() {
  long long maxWeight = -1;
  int maxWeightIndex = -1;
  for (int i = 0; i < 26; i++) {
    if (CharacterCounters[i] > 1 && Weight[i] > maxWeight) {
      maxWeight = Weight[i];
      maxWeightIndex = i;
    }
  }
  return maxWeightIndex;
}

void ProcessSymbolWithMaximumWeight() {
  int maxWeightIndex = GetSymbolWithMaximumWeight();
  if (maxWeightIndex == -1) {
    return;
  }
  ReservedPosition++;
  int foundChars = 0;
  for (int i = ReservedPosition; i < StringLen - ReservedPosition; i++) {
    if (String[i] == maxWeightIndex + 'a') {
      if (foundChars == 0) {
        foundChars++;
        SwapChars(i, ReservedPosition);
      } else {
        SwapChars(i, StringLen - ReservedPosition - 1);
        break;
      }
    }
  }
  CharacterCounters[maxWeightIndex] = 0;
}

void CountNumOfMultiOccurCharacters() {
  for (int i = 0; i < 26; i++) {
    if (CharacterCounters[i] > 1) {
      NumOfMultiOccurCharacters++;
    }
  }
}

void GetOptimalString() {
  CountNumOfMultiOccurCharacters();
  for (int i = 0; i < NumOfMultiOccurCharacters; i++) {
    ProcessSymbolWithMaximumWeight();
  }
}

int main() {
  scanf("%s", String);
  for (int i = 0; i < 26; i++) {
    scanf("%lld", &Weight[i]);
    CharacterCounters[i] = 0;
  }
  CountNumberOfCharacters();
  GetOptimalString();
  printf("%s\n", String);
  return 0;
}
