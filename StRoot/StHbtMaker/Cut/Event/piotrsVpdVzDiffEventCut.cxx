#include "StHbtMaker/Cut/Event/piotrsVpdVzDiffEventCut.h"

#include <math.h>

#include "StHbtMaker/Base/StHbtEventCut.h"
#include "StHbtMaker/Infrastructure/StHbtString.hh"

ClassImp(piotrsVpdVzDiffEventCut)

    bool piotrsVpdVzDiffEventCut::Pass(const StHbtEvent* event) {
   if (fabs(event->PrimVertPosVpd() - event->PrimVertPos().z()) < fMaxDiff) {
      cout << "piotrsVpdVzDiffEventCut passed" << endl;
      return true;
   } else {
      cout << "piotrsVpdVzDiffEventCut failed" << endl;
      return false;
   }
}

StHbtString piotrsVpdVzDiffEventCut::Report() {
   StHbtString retVal("piotrsVpdVzDiffEventCut");
   return retVal;
}

piotrsVpdVzDiffEventCut* piotrsVpdVzDiffEventCut::Clone() { return 0; }
