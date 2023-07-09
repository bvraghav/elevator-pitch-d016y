#include<bits/stdc++.h>
using namespace std;

#include "elevator.hpp"
using namespace bvr;

namespace bvr {

  InputT readInput(istream& sin) {
    auto config = readConfig(sin);
    auto signalV = readSignalV(config, sin);
    return make_pair(config, signalV);
  }

  ConfigT readConfig(istream& sin) {
    ConfigT conf;

    sin >> get<DE>(conf)
        >> get<DS>(conf)
        >> get<DU>(conf)
        >> get<DR>(conf)
        >> get<LAT>(conf)
        >> get<LMAX>(conf)
      ;

    return conf;
  }


  SignalV readSignalV(const ConfigT& config,
                      istream& sin)
  {

    SignalV signalV;
    TsT ts;
    WhereEnum where;
    LvlT tgt, lMax = get<LMAX>(config);
    DirEnum sigDir;
    int T;
    string aux;


    sin >> T;

    signalV.reserve(T);
    while(T--) {
      sigDir = CUR;                  // set current dir by default

      sin >> ts;

      sin >> aux;                 // read word
      // to upper case
      transform(
        aux.begin(), aux.end(),
        aux.begin(),
        [](unsigned char c) { return toupper(c); }
        );
      if (aux == "FROM") { where = FROM; }
      else if (aux == "TO") { where = TO; }
      else {
        // error
        cerr << "Unknown value for WHERE: "
             << aux << endl;
        cerr << "Expected FROM/TO" << endl;
        exit(65);
      }

      sin >> tgt;
      if (lMax <= tgt) {
        // error
        cerr << "tgt:" << tgt
             << " violates upper bound lMax:" << lMax
             << " (exclusive)" << endl;
        exit(66);
      }

      if (where == FROM) {
        sin >> aux;
        // to upper case
        transform(
          aux.begin(), aux.end(),
          aux.begin(),
          [](unsigned char c) { return toupper(c); }
          );
        if (aux == "UP") { sigDir = UP; }
        else if (aux == "DN") { sigDir = DN; }
        else {
          // error
          cerr << "Unknown value for DIR:"
               << aux << endl;
          cerr << "Expected UP/DN" << endl;
          exit(67);
        }
      }

      signalV.push_back(
        make_tuple(tgt,where,sigDir,ts)
        );
    }

    return signalV;
  
  }

}  // bvr
