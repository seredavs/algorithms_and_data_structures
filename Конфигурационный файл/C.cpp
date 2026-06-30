#include <cctype>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

struct Snapshot {
  string name;
  string old_value;
  bool is_marker;
};

map<string, string> global_vars;
vector<Snapshot> history;
int block_depth = 0;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  string line;
  while (cin >> line) {
    if (line == "{") {
      block_depth++;
      history.push_back({"", "", true});
    } else if (line == "}") {
      block_depth--;
      while (!history.empty()) {
        Snapshot last = history.back();
        history.pop_back();

        if (last.is_marker) {
          break;
        }
        global_vars[last.name] = last.old_value;
      }
    } else {
      size_t eq_pos = line.find('=');
      string name = line.substr(0, eq_pos);
      string rhs = line.substr(eq_pos + 1);
      string val_to_assign;

      bool rhs_is_var = isalpha(rhs[0]);

      if (rhs_is_var) {
        if (global_vars.count(rhs)) {
          val_to_assign = global_vars[rhs];
        } else {
          val_to_assign = "0";
        }
        cout << val_to_assign << "\n";
      } else {
        val_to_assign = rhs;
      }

      if (block_depth > 0) {
        string current_val = "0";
        if (global_vars.count(name)) {
          current_val = global_vars[name];
        }
        history.push_back({name, current_val, false});
      }

      global_vars[name] = val_to_assign;
    }
  }
  return 0;
}
