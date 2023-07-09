#include<bits/stdc++.h>
using namespace std;

#include "elevator.hpp"
using namespace bvr;

namespace bvr {

  void debugConfig(const ConfigT & config,
                   ostream& sout) {
    // sout << endl;
    sout << "Debugging CONFIG" << endl
         << "  DE:" << get<DE>(config) << ' '
         << "DS:" << get<DS>(config) << ' '
         << "DU:" << get<DU>(config) << ' '
         << "DR:" << get<DR>(config) << ' '
         << "LAT:" << get<LAT>(config) << ' '
         << "LMAX:" << get<LMAX>(config) << ' '
         << endl;
    // sout << endl;
      ;
  }

  void debugSignalV(const SignalV & signalV,
                    ostream& sout) {
    // sout << endl
    sout << "Debugging SIGNAL VECTOR:" << endl;

    for (auto & signal : signalV) {
      debugSignal(signal, sout);
    }

    SignalQ signalQ(signalV.begin(), signalV.end());
    sout << endl;
    sout << "Debugging Signal Queue:" << endl;
    while (!signalQ.empty()) {
      debugSignal(signalQ.top(), sout);
      signalQ.pop();
    }
    // sout << endl;

  }

  void debugSignal(const SignalT & signal,
                   ostream& sout) {
    sout << "  TS:" << get<TS>(signal) << ' '
         << "WHERE:" << get<WHERE>(signal) << ' '
         << "LVL:" << get<LVL>(signal) << ' ';

    if (get<WHERE>(signal) == FROM)
      sout << "SIGDIR:" << get<SIGDIR>(signal) << ' ';

    sout << endl;
    
  }

  void debugElevator(ElevatorT const & el,
                     ostream& sout) {
    // sout << endl;
    sout << "Debugging Elevator:" << endl;
    debugConfig(get<CONF>(el), sout);
    debugElState(get<STATE>(el), sout);

    sout << "Debugging CURQ:" << endl;
    debugLvlQ(get<CURQ>(el), sout);
    sout << "Debugging CURQ:" << endl;
    debugLvlQ(get<CURQ>(el), sout);
    sout << "Debugging UPQ:" << endl;
    debugLvlQ(get<UPQ>(el), sout);
    sout << "Debugging DNQ:" << endl;
    debugLvlQ(get<DNQ>(el), sout);
    
  }

  void debugElState(ElStateT const & state,
                    ostream& sout) {
    // sout << endl;
    sout << "STATE: "
         << "  L0:" << get<L0>(state) << ' '
         << "L1:" << get<L1>(state) << ' '
         << "T0:" << get<T0>(state) << ' '
         << "D:"  << get<D>(state)  << ' '
         << "DIR:"  << get<ELDIR>(state)  << ' '
         << endl;
  }

  void debugLvlQ(LvlQ const& q, ostream& sout) {
    auto [lvlQ, qMax] = q;

    // sout << endl
    sout << "  qMax:" << qMax << endl
         << "  Q: "
      ;
    debugRawLvlQ(lvlQ, sout);
  }

  void debugRawLvlQ(RawLvlQ rawQ, ostream& sout) {
    if (rawQ.empty()) {
      sout << "Empty";
    }

    while (!rawQ.empty()) {
      sout << rawQ.top() << ' ';
      rawQ.pop();
    }

    sout << endl;
  }

  ostream& debugAllQs(
    ostream& sout,
    ElevatorT const& el,
    string prefix
    ) {
    sout << prefix << "CURQ: QMAX:"
         << get<QMAX>(get<CURQ>(el))
         << " Q: ";
    debugRawLvlQ(get<Q>(get<CURQ>(el)), sout);

    sout << prefix << "UPQ: QMAX:"
         << get<QMAX>(get<UPQ>(el))
         << " Q: ";
    debugRawLvlQ(get<Q>(get<UPQ>(el)), sout);

    sout << prefix << "DNQ: QMAX:"
         << get<QMAX>(get<DNQ>(el))
         << " Q: ";
    debugRawLvlQ(get<Q>(get<DNQ>(el)), sout);

    return sout;
  }


  // void debugLvlQ(LvlQ const& q, ostream& sout) {
  //   LvlV lvlV; LvlT qMax, l; LvlCmp cmp;
  //   tie(lvlV, qMax, cmp) = q;

  //   sout << endl
  //        << "Debugging LvlQ" << endl
  //        << "qMax:" << qMax << endl
  //        << "Q: "
  //     ;

  //   if (lvlV.empty()) {
  //     sout << "Empty";
  //   }

  //   while (!lvlV.empty()) {
  //     l = lvlV.front();

  //     sout << l << ' ';

  //     pop_heap(lvlV.begin(), lvlV.end(), cmp);
  //     lvlV.pop_back();
  //   }

  //   sout << endl << endl;
  // }

}  // bvr
