#include "StHbtMaker/Cut/Event/piotrsTofMultRefMultCut.h"

#include <iostream>

#include "StHbtMaker/Base/StHbtEventCut.h"
#include "StHbtMaker/Infrastructure/StHbtString.hh"
using namespace std;

ClassImp(piotrsTofMultRefMultCut)

    bool piotrsTofMultRefMultCut::Pass(const StHbtEvent* event) {
   int x = event->UncorrectedNumberOfPrimaries();
   double cutValueUpper = mp0upper + x * (mp1upper + x * mp2upper);
   double cutValueLower = mp0lower + x * (mp1lower + x * mp2lower);

   if (event->TofMultiplicity() > cutValueUpper || event->TofMultiplicity() < cutValueLower) {
      return false;
   } else {
      return true;
   }
}

StHbtString piotrsTofMultRefMultCut::Report() {
   StHbtString retVal("piotrsTofMultRefMultCut");
   return retVal;
}

piotrsTofMultRefMultCut* piotrsTofMultRefMultCut::Clone() { return 0; }
