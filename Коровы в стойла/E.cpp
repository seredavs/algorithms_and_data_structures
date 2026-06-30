#include <stdio.h>

int n, k;
int stalls[100000];

int can_fit(int min_dist) {
  int count = 1;
  int current_sum = 0;
  for (int i = 0; i < n - 1; i++) {
    current_sum += stalls[i + 1] - stalls[i];
    if (current_sum >= min_dist) {
      count++;
      current_sum = 0;
    }
  }
  return count >= k;
}

int main() {
  scanf("%d %d", &n, &k);
  for (int i = 0; i < n; i++) {
    scanf("%d", &stalls[i]);
  }
  int low = 0;
  int high = stalls[n - 1] - stalls[0];
  int ans = 0;
  while (low <= high) {
    int mid = (low + high) / 2;
    if (can_fit(mid)) {
      ans = mid;
      low = mid + 1;
    } else {
      high = mid - 1;
    }
  }
  printf("%d\n", ans);
  return 0;
}
