#include <stdio.h>

int NumOfRequests;
int Goblins[1000005][2];
const int PrevGoblin = 0;
const int NextGoblin = 1;

int FirstGoblin = 0;
int ItemsInQueue = 0;
int LastGoblin = 0;
int MiddleGoblin = 0;

void AddFirstGoblin(int goblinIndex) {
  FirstGoblin = LastGoblin = MiddleGoblin = goblinIndex;
  Goblins[goblinIndex][PrevGoblin] = 0;
  Goblins[goblinIndex][NextGoblin] = 0;
  ItemsInQueue = 1;
}

void AddRegularGoblin(int goblinIndex) {
  Goblins[goblinIndex][PrevGoblin] = LastGoblin;
  Goblins[goblinIndex][NextGoblin] = 0;
  Goblins[LastGoblin][NextGoblin] = goblinIndex;
  LastGoblin = goblinIndex;
  ItemsInQueue++;
  if (ItemsInQueue % 2 != 0) {
    MiddleGoblin = Goblins[MiddleGoblin][NextGoblin];
  }
}

void AddPrivilegedGoblin(int goblinIndex) {
  int next = Goblins[MiddleGoblin][NextGoblin];
  Goblins[goblinIndex][PrevGoblin] = MiddleGoblin;
  Goblins[goblinIndex][NextGoblin] = next;
  Goblins[MiddleGoblin][NextGoblin] = goblinIndex;
  if (next != 0) {
    Goblins[next][PrevGoblin] = goblinIndex;
  } else {
    LastGoblin = goblinIndex;
  }
  ItemsInQueue++;
  if (ItemsInQueue % 2 != 0) {
    MiddleGoblin = Goblins[MiddleGoblin][NextGoblin];
  }
}

void ServeCurrentGoblin() {
  if (ItemsInQueue < 1) {
    return;
  }
  printf("%d\n", FirstGoblin);
  int toRemove = FirstGoblin;
  FirstGoblin = Goblins[FirstGoblin][NextGoblin];

  if (FirstGoblin != 0) {
    Goblins[FirstGoblin][PrevGoblin] = 0;
  } else {
    LastGoblin = 0;
  }

  if (ItemsInQueue % 2 == 0) {
    MiddleGoblin = Goblins[MiddleGoblin][NextGoblin];
  }
  if (toRemove == MiddleGoblin) {
    MiddleGoblin = FirstGoblin;
  }

  ItemsInQueue--;
}

int main() {
  if (scanf("%d", &NumOfRequests) != 1) {
    return 0;
  }

  for (int i = 0; i < NumOfRequests; i++) {
    char RequestType;
    scanf(" %c", &RequestType);

    if (RequestType == '+' || RequestType == '*') {
      int id;
      scanf("%d", &id);
      if (ItemsInQueue == 0) {
        AddFirstGoblin(id);
      } else if (RequestType == '+') {
        AddRegularGoblin(id);
      } else {
        AddPrivilegedGoblin(id);
      }
    } else if (RequestType == '-') {
      ServeCurrentGoblin();
    }
  }

  return 0;
}
