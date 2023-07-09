#include<bits/stdc++.h>
using namespace std;

#include "elevator.hpp"
using namespace bvr;

// ----------------------------------------------------
// Main
// ----------------------------------------------------

int main() {
  auto [config, signalV] = readInput();

  debugConfig(config);
  debugSignalV(signalV);

  SignalQ signalQ(signalV.begin(), signalV.end());

  auto el = createFtElevator(config);
  debugElevator(el);

  int i=0, N=2000;
  while (i<N && (!signalQ.empty() || !empty(el))) {
    cerr << "MAIN: @i:" << i
         << " signalQ.size:" << signalQ.size()
         << " el->CURQ.size:"
         << get<Q>(get<CURQ>(el)).size()
         << " el->UPQ.size:"
         << get<Q>(get<UPQ>(el)).size()
         << " el->DNQ.size:"
         << get<Q>(get<DNQ>(el)).size()
         << endl

         << "  getNext(signalQ):" << getNext(signalQ)
         << " getNext(el):" << getNext(el)
         << endl

         << "  STATE: "
      ;
    debugElState(get<STATE>(el));
    if (empty(el) || (
          !signalQ.empty()
          &&
          getNext(signalQ) < getNext(el)
          )) {

      procNext(signalQ, el);
    } else {
      procNext(el);
    }
    ++i;
  }

}
