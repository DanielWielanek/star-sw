#include "StHbtMaker/Cut/Event/piotrsTofMultEventCut.h"

#include <iostream>

#include "StHbtMaker/Base/StHbtEventCut.h"
#include "StHbtMaker/Infrastructure/StHbtString.hh"
using namespace std;

ClassImp(piotrsTofMultEventCut)

    piotrsTofMultEventCut::piotrsTofMultEventCut(int lo, int hi)
    : mTofMultLo(lo), mTofMultHi(hi) {}

bool piotrsTofMultEventCut::Pass(const StHbtEvent* event) {
   if (event->TofMultiplicity() >= mTofMultLo && event->TofMultiplicity() <= mTofMultHi) {
      return true;
   } else {
      return false;
   }
}

StHbtString piotrsTofMultEventCut::Report() {
   StHbtString retVal("piotrsTofMultEventCut");
   return retVal;
}

piotrsTofMultEventCut* piotrsTofMultEventCut::Clone() { return 0; }
