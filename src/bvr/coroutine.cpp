#include<bits/stdc++.h>
using namespace std;

#include "elevator.hpp"
using namespace bvr;

namespace bvr {

  TsT getNext(SignalQ const& signalQ) {
    return get<TS>(signalQ.top());
  }

  TsT getNext(ElevatorT const& el) {
    auto const& state = get<STATE>(el);
    return get<T0>(state) + get<D>(state);
  };

  void procNext(SignalQ &signalQ, ElevatorT& el) {
    // enum ConfigIndexEnum { DE, DS, DU, DR, LAT, LMAX };
    // enum SignalIndexEnum { LVL, WHERE, SIGDIR, TS };
    // enum ElStateIndexEnum { ELDIR, L0, L1, T0, D };

    if (signalQ.empty()) {
      cerr << "ERROR: procNext with empty signalQ." << endl;
      exit(68);
    }

    auto [l, w, sigDir, ts] = signalQ.top();
    auto m = 3*l;
    signalQ.pop();

    // Print output
    cout << "Processing Signal: "
         << "l:" << l << " (" << m << ") "
         << "w:" << w << " "
         << "sigDir:" << (sigDir==UP?"UP":"DN") << " "
         << "ts:" << ts << " "
         << endl
         << "  Signal Q length:" << signalQ.size()
         << "  Empty?:" << signalQ.empty()
         << endl
      ;

    auto &[elDir, m0, m1, t0, d] = get<STATE>(el);

    auto &[de, ds, du, dr, lat, lMax] = get<CONF>(el);

    auto dirGrt = DirLvlGrt(elDir);

    auto toCurQ = (
      (sigDir==CUR || elDir==sigDir)
      && (
        dirGrt(3*m,1+m1)
        ||
        (ts + lat - t0) < d
        )
      )
      ;

    auto &toQ = (
      toCurQ ? get<CURQ>(el)
      : (sigDir==UP || elDir==DN) ? get<UPQ>(el)
      : get<DNQ>(el)
      );

    // Enqueue
    enQ(toQ, m, elDir);

    debugAllQs(cout, el, "  ");
    debugAllQs(cerr, el, "  ");
  }

  void enQ(LvlQ &toQ, LvlT m, DirEnum dir) {
    cerr << "enQ: with dir:" << dir
         << " m:" << m
         << endl
      ;

    auto dirGrt = DirLvlGrt(dir);

    if (!get<Q>(toQ).empty()) {
      // check if adding to preceding path

      auto m0 = get<Q>(toQ).top();
      if (dirGrt(m0, m)) {
        cerr << "  m0:" << m0 << " > m:" << m << endl;
        cerr << "  toQ: ";
        debugRawLvlQ(get<Q>(toQ));

        for (auto l = m+dir*1;
             dirGrt(m0,l);
             l += dir*3) {
          get<Q>(toQ).push(l);
          get<Q>(toQ).push(dir*1+l);
        }
      }

      auto mx = get<QMAX>(toQ);
    
      if (dirGrt(m, mx)) {
        cerr << "  m:" << m << " > "
             << "mx:" << mx
             << endl
          ;
        cerr << "  toQ: ";
        debugRawLvlQ(get<Q>(toQ));

        for (auto l = mx+dir*1;
             dirGrt(m,l);
             l += dir*3) {
          get<Q>(toQ).push(l);
          get<Q>(toQ).push(dir*1+l);
        }
        get<QMAX>(toQ) = m;

      }

      cerr << "  toQ: ";
      debugRawLvlQ(get<Q>(toQ));

    } else {
      get<QMAX>(toQ) = m;
    }

    get<Q>(toQ).push(m);
    get<Q>(toQ).push(m);        // Push again for rest
                                // at level

    cerr << "  toQ:"
         << " QMAX:" << get<QMAX>(toQ)
         << " Q: ";    
    debugRawLvlQ(get<Q>(toQ));
  }

  void procNext(ElevatorT &el) {
    auto &[elDir, m0, m1, t0, d] = get<STATE>(el);

    auto &[de, ds, du, dr, lat, lMax] = get<CONF>(el);

    auto dirGrt = DirLvlGrt(elDir);

    auto &curQ = get<CURQ>(el)
      , &nexQ = (elDir == UP ? get<DNQ>(el)
                : get<UPQ>(el))
      ;

    auto &curRawQ = get<Q>(curQ)
      , &nexRawQ = get<Q>(nexQ)
      ;

    // ------------------------------------------------
    // UPDATE STATE
    // ------------------------------------------------
    // Pop level from Q and update state
    m0 = m1;
    m1 = curRawQ.top();
    cerr << "Debug CURQ: sizeBeforePop:"
         << get<Q>(get<CURQ>(el)).size()
      ;
    curRawQ.pop();
    cerr << " sizeAfterPop:"
         << get<Q>(get<CURQ>(el)).size()
         << endl
      ;

    // Update state timestamp
    t0 = t0 + d;                // Update this based on
                                // now() for a
                                // real-world setting
                                // as such.

    // Update duration of this state
    d = (
      m0 == m1 ? dr                   // rest
      : ((m0%3)==0 || (m1%3)==0) ? de // ease
      : (1+m0 ==m1) ? du              // uniform speed
      : ds                            // skip
      );

    // Print Update
    debugElState(get<STATE>(el), cout);
    // ------------------------------------------------

    if (!curRawQ.empty()) {
      debugAllQs(cout, el, "  ");
      debugAllQs(cerr, el, "  ");
      return;
    };

    // ------------------------------------------------
    // SYNC CUR & NEX 
    // ------------------------------------------------
    cerr << "Syncing @STATE m1:" << m1
         << " elDir:" << elDir
         << " with NEXQ: ";
    if (nexRawQ.empty()) {
      cerr << "Empty.";
    } else {
      cerr << "top:" << nexRawQ.top();
    }
    cerr << endl;
    // debugLvlQ(nexQ);

    if (!nexRawQ.empty()) {
      auto curMx = get<QMAX>(curQ)
        , nexTop = nexRawQ.top();

      if (dirGrt(nexTop,curMx)) {
        enQ(curQ, nexTop, elDir);
        debugAllQs(cout, el, "  ");
        debugAllQs(cerr, el, "  ");
        return;
      }
      else {
        enQ(nexQ, curMx, (elDir==UP?DN:UP));
      }
    }

    while (!nexRawQ.empty() && m1 == nexRawQ.top()) {
      cerr << "Popping out from nexRawQ m1:" << m1
           << endl;
      nexRawQ.pop();
    }

    rotateElQ(el);
    // ------------------------------------------------

    debugAllQs(cout, el, "  ");
    debugAllQs(cerr, el, "  ");

  }

}  // bvr
