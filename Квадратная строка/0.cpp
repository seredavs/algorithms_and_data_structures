#include <stdio.h>

#include <iostream>
using namespace std;

int IsSquareString(string st);

int main() {
  int numberOfStrings;
  string s;

  cin >> numberOfStrings;
  for (int i = 0; i < numberOfStrings; i++) {
    cin >> s;
    if (IsSquareString(s)) {
      printf("YES\n");

    } else {
      printf("NO\n");
    }
  }

  return 0;
}

int IsSquareString(string st) {
  int len = st.size();
  if (len % 2 != 0) {
    return 0;
  }
  int halfLen = len / 2;
  for (int i = 0; i < halfLen; i++) {
    if (st[i] != st[halfLen + i]) {
      return 0;
    }
  }
  return 1;
}
