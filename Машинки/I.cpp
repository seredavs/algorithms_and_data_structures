#include <cstdio>
#include <queue>
#include <vector>

using namespace std;

unsigned long NumOfCars, MaxCarsInGame, NumOfGameSteps;
unsigned long CarOnGameStep[500005];
unsigned long NextOccurrence[500005];
unsigned long LastSeen[100005];
int IsCarInGame[100005];
unsigned long OperationsCount = 0;
unsigned long CurrentCarsCount = 0;

int main() {
  if (scanf("%lu %lu %lu", &NumOfCars, &MaxCarsInGame, &NumOfGameSteps) != 3) {
    return 0;
  }

  for (unsigned long i = 0; i < NumOfGameSteps; i++) {
    scanf("%lu", &CarOnGameStep[i]);
  }

  for (unsigned long i = 1; i <= NumOfCars; i++) {
    LastSeen[i] = 1000001;
  }

  for (int i = (int)NumOfGameSteps - 1; i >= 0; i--) {
    NextOccurrence[i] = LastSeen[CarOnGameStep[i]];
    LastSeen[CarOnGameStep[i]] = (unsigned long)i;
  }

  priority_queue<pair<unsigned long, unsigned long>> pq;

  for (unsigned long i = 0; i < NumOfGameSteps; i++) {
    unsigned long car = CarOnGameStep[i];

    if (!IsCarInGame[car]) {
      if (CurrentCarsCount == MaxCarsInGame) {
        while (!pq.empty()) {
          pair<unsigned long, unsigned long> top = pq.top();
          pq.pop();
          if (IsCarInGame[top.second]) {
            IsCarInGame[top.second] = 0;
            CurrentCarsCount--;
            break;
          }
        }
      }
      IsCarInGame[car] = 1;
      CurrentCarsCount++;
      OperationsCount++;
    }
    pq.push(make_pair(NextOccurrence[i], car));
  }

  printf("%lu\n", OperationsCount);

  return 0;
}
