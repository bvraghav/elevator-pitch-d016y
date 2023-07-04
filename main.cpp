#include<bits/stdc++.h>
using namespace std;

// ----------------------------------------------------
// Types
// ----------------------------------------------------
typedef vector<int> Vi;
typedef pair<int,Vi> Input;
typedef vector<Input> Inputs;

Inputs read_input();
// ----------------------------------------------------

// ----------------------------------------------------
// Solution
// ----------------------------------------------------

class Solution {
public:
  int solve(Vi const& nums, int t) const {
    for (auto n : nums)
      t += n;

    return t;
  }
};


// ----------------------------------------------------
// Main
// ----------------------------------------------------

int main() {
  Solution sol;
  for(auto &[t, nums] : read_input()) {
    cout << sol.solve(nums, t) << endl;
  }
}

Inputs read_input() {
  Inputs inputs;
  Vi nums;
  int T, t, N, n;

  cin >> T;

  inputs.reserve(T);
  while(T--) {
    cin >> t >> N;
    nums.clear();
    nums.reserve(N);
    while (N--) {
      cin >> n;
      nums.push_back(n);
    }
    inputs.push_back(make_pair(t, nums));
  }

  return inputs;
}

