#include <cstdio>
#include <set>

using namespace std;

struct MemoryBlock {
  long long size;
  long long location;
  int prev;
  int next;
  int id;
};

MemoryBlock pool[400005];
int req_to_block[100005];
set<pair<long long, int>> free_blocks;
int blocks_count = 0;

void remove_free(int idx) {
  free_blocks.erase({pool[idx].size, idx});
}

void add_free(int idx) {
  free_blocks.insert({pool[idx].size, idx});
}

int main() {
  long long n;
  int m;
  if (scanf("%lld %d", &n, &m) != 2) {
    return 0;
  }

  pool[0].size = n;
  pool[0].location = 1;
  pool[0].prev = -1;
  pool[0].next = -1;
  pool[0].id = -1;
  add_free(0);
  blocks_count = 1;

  for (int i = 1; i <= m; i++) {
    int k;
    scanf("%d", &k);

    if (k > 0) {
      auto it = free_blocks.lower_bound({(long long)k, -1});
      if (it == free_blocks.end()) {
        printf("-1\n");
        req_to_block[i] = -1;
      } else {
        int idx = it->second;
        remove_free(idx);

        if (pool[idx].size == k) {
          pool[idx].id = i;
          req_to_block[i] = idx;
        } else {
          int new_idx = blocks_count++;
          pool[new_idx].size = (long long)k;
          pool[new_idx].location = pool[idx].location;
          pool[new_idx].id = i;
          pool[new_idx].prev = pool[idx].prev;
          pool[new_idx].next = idx;

          if (pool[idx].prev != -1) {
            pool[pool[idx].prev].next = new_idx;
          }
          pool[idx].prev = new_idx;
          pool[idx].location += k;
          pool[idx].size -= k;
          add_free(idx);
          req_to_block[i] = new_idx;
        }
        printf("%lld\n", pool[req_to_block[i]].location);
      }
    } else {
      int t = -k;
      int idx = req_to_block[t];
      if (idx != -1 && pool[idx].id != -1) {
        pool[idx].id = -1;
        int next = pool[idx].next;
        if (next != -1 && pool[next].id == -1) {
          remove_free(next);
          pool[idx].size += pool[next].size;
          pool[idx].next = pool[next].next;
          if (pool[next].next != -1) {
            pool[pool[next].next].prev = idx;
          }
          pool[next].id = -2;
        }
        int prev = pool[idx].prev;
        if (prev != -1 && pool[prev].id == -1) {
          remove_free(prev);
          pool[prev].size += pool[idx].size;
          pool[prev].next = pool[idx].next;
          if (pool[idx].next != -1) {
            pool[pool[idx].next].prev = prev;
          }
          pool[idx].id = -2;
          idx = prev;
        }
        add_free(idx);
      }
    }
  }
  return 0;
}
