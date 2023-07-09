#include<bits/stdc++.h>
using namespace std;

#include "elevator.hpp"
using namespace bvr;

namespace bvr {

  ElevatorT createFtElevator(ConfigT& conf) {
    ElevatorT el;

    get<CONF>(el) = conf;

    ElStateT state;
    get<ELDIR>(state) = UP;
    get<L0>(state) = 0;
    get<L1>(state) = 0;
    get<T0>(state) = 0;
    get<D>(state) = 0;
    
    get<STATE>(el) = state;

    get<CURQ>(el) = createFtUpQ(conf);
    get<Q>(get<CURQ>(el)).push(0);
    get<Q>(get<CURQ>(el)).push(0);

    get<UPQ>(el)  = createFtUpQ(conf);
    get<DNQ>(el)  = createFtDnQ(conf);


    // get<CURQ>(el) = createFtUpQ(conf);
    // get<UPQ>(el)  = createFtUpQ(conf);
    // get<DNQ>(el)  = createFtDnQ(conf);

    return el;
  }

  LvlQ createFtUpQ(ConfigT& conf) {
    return make_tuple(
      RawLvlQ(DirLvlGrt(UP)), 0
      );
  }

  LvlQ createFtDnQ(ConfigT& conf) {
    return make_tuple(
      RawLvlQ(DirLvlGrt(DN)), 3*(get<LMAX>(conf)-1)
      );
  }

  bool empty(ElevatorT const& el) {
    return get<Q>(get<CURQ>(el)).empty();
  }

  void rotateElQ(ElevatorT& el) {
    // This assumes that CURQ is empty
    if (!get<Q>(get<CURQ>(el)).empty()) {
      cerr << "Attempting rotate with non-empty CURQ:"
           << endl;
      debugLvlQ(get<CURQ>(el));
      cerr << "At State:" << endl;
      debugElState(get<STATE>(el));
      return;
    }
    cerr << "Rotating." << endl;

    auto elDir = get<ELDIR>(get<STATE>(el));
    auto conf  = get<CONF>(el);

    auto a = (elDir == UP)
      , b = get<Q>(get<DNQ>(el)).empty()
      , c = get<Q>(get<UPQ>(el)).empty()
      ;

    if ((a || c) && !b) {
      // Either going up and DNQ ----------------------
      // OR going down and no UPQ and DNQ -------------
      get<CURQ>(el) = get<DNQ>(el);
      get<DNQ>(el)  = createFtDnQ(conf);
      get<ELDIR>(get<STATE>(el)) = DN;
    }

    if ((!a || b) && !c) {
      // Either going down and UPQ --------------------
      // OR going up and no DNQ and UPQ ---------------
      get<CURQ>(el) = get<UPQ>(el);
      get<UPQ>(el)  = createFtUpQ(conf);
      get<ELDIR>(get<STATE>(el)) = UP;
    }

    // Else everything is empty
  }


  // LvlQ createFtUpQ(ConfigT const& conf) {
  //   return make_tuple(
  //     LvlV(), 0, std::greater<LvlT>{}
  //     );
  // }

  // LvlQ createFtDnQ(ConfigT const& conf) {
  //   return make_tuple(
  //     LvlV(), get<LMAX>(conf)-1, std::less<LvlT>{}
  //     );
  // }

  // LvlT topQ(LvlQ const& q) {
  //   return get<Q>(q).front();
  // }

  // void pushQ(LvlQ &q, LvlT l) {
  //   get<Q>(q).push_back(l);
  //   push_heap(
  //     get<Q>(q).begin(), get<Q>(q).end(),
  //     get<CMP>(q)
  //     );
    
  // }

  // LvlT popQ(LvlQ& q) {
  //   LvlT l = topQ(q);
  //   pop_heap(
  //     get<Q>(q).begin(), get<Q>(q).end(),
  //     get<CMP>(q)
  //     );
  //   get<Q>(q).pop_back();
  //   return l;
  // }

  // LvlT maxQ(LvlQ const& q) {
  //   return get<QMAX>(q);
  // };


}  // bvr
