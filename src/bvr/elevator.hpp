#pragma once

#include<bits/stdc++.h>
// #include <boost/variant.hpp>

namespace bvr {

  // --------------------------------------------------
  // Types
  // --------------------------------------------------

  // Signal -------------------------------------------
  enum WhereEnum { FROM, TO };
  enum DirEnum { UP=1, DN=-1, CUR=0 };
  enum SignalIndexEnum { LVL, WHERE, SIGDIR, TS };
  typedef std::uint64_t TsT;
  typedef std::uint16_t LvlT;
  typedef std::vector<LvlT> LvlV;
  typedef std::tuple<LvlT,WhereEnum,DirEnum,TsT>
  SignalT;
  typedef std::vector<SignalT> SignalV;

  template<typename T>
  using BinCmp =  std::function<bool(T,T)>;
  typedef BinCmp<LvlT> LvlCmp;

  template <typename T>
  struct DirComparator : public BinCmp<T>
  {
    DirEnum dir;
    DirComparator(DirEnum dir=UP) : dir(dir) {}
    bool operator()(const T& o1, const T& o2)
      {
        return (dir==UP ? o2 < o1 : o1 < o2);
      }
  };
  typedef DirComparator<LvlT> DirLvlGrt;
  
  // Signal Queue -------------------------------------
  typedef std::priority_queue<
    SignalT,SignalV,std::greater<SignalT>
    > SignalQ;

  // Config -------------------------------------------
  enum ConfigIndexEnum { DE, DS, DU, DR, LAT, LMAX };
  typedef std::tuple<TsT,TsT,TsT,TsT,TsT,LvlT> ConfigT;

  // Elevator State -----------------------------------
  enum ElStateIndexEnum { ELDIR, L0, L1, T0, D };
  typedef std::tuple<
    DirEnum, LvlT, LvlT, TsT, TsT
    > ElStateT;

  // Elevator Queue -----------------------------------
  enum QueIndexEnum { Q, QMAX };
  typedef std::priority_queue<
    LvlT, LvlV, DirLvlGrt
    > RawLvlQ;
  typedef std::tuple<RawLvlQ, LvlT> LvlQ;
  // enum QueIndexEnum { Q, QMAX, CMP };
  // typedef std::tuple<LvlV, LvlT, LvlCmp> LvlQ;
  // typedef boost::variant<DnQ,UpQ> UniQ;
  // typedef std::shared_ptr<UpQ> UpQueP;
  // typedef std::shared_ptr<DnQ> DnQueP;
  // typedef std::shared_ptr<UniQ> UniQueP;
  // typedef std::weak_ptr<UniQ> UniQuePw;

  // Elevator
  enum ElevatorIndexEnum {
    CONF, STATE, CURQ, UPQ, DNQ
  };
  typedef std::tuple<
    ConfigT,
    ElStateT,
    LvlQ, LvlQ, LvlQ
    > ElevatorT;
  // Note: to get NexQ use: STATE to infer cur dir and
  // choose the opposite: -1*ELDIR.

  // --------------------------------------------------
  // Signal
  // --------------------------------------------------
  bool operator <(SignalT const&,  SignalT const&);

  // --------------------------------------------------
  // Elevator
  // --------------------------------------------------
  ElevatorT createFtElevator(ConfigT&);
  void enQ(LvlQ &, LvlT, DirEnum);
  void rotateElQ(ElevatorT&);
  bool empty(ElevatorT const&);
  LvlQ createFtUpQ(ConfigT&);
  LvlQ createFtDnQ(ConfigT&);
  // LvlQ createFtUpQ(ConfigT const&);
  // LvlQ createFtDnQ(ConfigT const&);
  // LvlT topQ(LvlQ const&);
  // void pushQ(LvlQ&, LvlT);
  // LvlT popQ(LvlQ&);
  // LvlT maxQ(LvlQ const&);

  // --------------------------------------------------
  // Input
  // --------------------------------------------------
  typedef std::pair<ConfigT,SignalV> InputT;
  InputT readInput(std::istream& = std::cin);
  ConfigT readConfig(std:: istream& sin = std::cin);
  SignalV readSignalV(const ConfigT& config,
                      std::istream& sin = std::cin);

  // --------------------------------------------------
  // Debug
  // --------------------------------------------------
  void debugConfig(const ConfigT &,
                   std::ostream& sout = std::cerr);
  void debugSignalV(const SignalV &,
                    std::ostream& sout = std::cerr);
  void debugSignal(const SignalT &,
                   std::ostream& sout = std::cerr);
  void debugElevator(ElevatorT const &,
                     std::ostream& sout = std::cerr);
  void debugElState(ElStateT const &,
                    std::ostream& sout = std::cerr);
  void debugLvlQ(LvlQ const &,
                 std::ostream& sout = std::cerr);
  void debugRawLvlQ(RawLvlQ,
                    std::ostream& sout = std::cerr);
  std::ostream& debugAllQs(
    std::ostream& sout,
    ElevatorT const& el,
    std::string prefix = ""
    );
  // void debugUniQ(UniQ const & );

  // --------------------------------------------------
  // CoRoutine
  // --------------------------------------------------
  TsT  getNext  (SignalQ   const&);
  TsT  getNext  (ElevatorT const&);
  void procNext (SignalQ   &, ElevatorT&);
  void procNext (ElevatorT &);

}  // bvr
