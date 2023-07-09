#include<bits/stdc++.h>
using namespace std;

#include "elevator.hpp"
using namespace bvr;

namespace bvr {
  bool operator <(SignalT const&a,  SignalT const&b) {
    return get<TS>(a) < get<TS>(b);
  }
}
