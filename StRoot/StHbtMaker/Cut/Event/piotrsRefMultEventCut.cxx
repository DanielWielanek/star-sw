#include "StHbtMaker/Cut/Event/piotrsRefMultEventCut.h"

#include <cstdarg>
#include <iostream>

#include "StHbtMaker/Base/StHbtEventCut.h"
#include "StHbtMaker/Infrastructure/StHbtString.hh"

using namespace std;

ClassImp(piotrsRefMultEventCut)

    piotrsRefMultEventCut::piotrsRefMultEventCut(int binCount, ...)
    : fRunNumber(-1) {
   va_list bins;
   va_start(bins, binCount);
   while (binCount > 0) {
      fRefMultBins.insert(va_arg(bins, int));
      --binCount;
   }
   va_end(bins);
   for (set<int>::iterator i = fRefMultBins.begin(); i != fRefMultBins.end(); ++i) {
      cout << "  " << *i;
   }
   cout << endl;
}

bool piotrsRefMultEventCut::Pass(const StHbtEvent* event) {
   initRunNumber(event->RunNumber());
   cout << "RefMult: " << event->UncorrectedNumberOfPrimaries() << endl;
   stRefMultCorr.initEvent(event->UncorrectedNumberOfPrimaries(), event->PrimVertPos().z());
   return isRefMultOk();
}

StHbtString piotrsRefMultEventCut::Report() {
   StHbtString retVal("piotrsRefMultEventCut: ");
   return retVal;
}

piotrsRefMultEventCut* piotrsRefMultEventCut::Clone() { return 0; }

bool piotrsRefMultEventCut::isRefMultOk() {
   int actualBin = stRefMultCorr.getCentralityBin9();
   cout << "!!!!!! Multiplicity bin: " << actualBin << " " << fRefMultBins.count(actualBin);
   for (set<int>::iterator i = fRefMultBins.begin(); i != fRefMultBins.end(); ++i) {
      cout << "  " << *i;
   }
   cout << endl;
   return fRefMultBins.count(actualBin) > 0 ? true : false;
}

void piotrsRefMultEventCut::initRunNumber(int runNumber) {
   if (runNumber != fRunNumber) {
      fRunNumber = runNumber;
      stRefMultCorr.init(fRunNumber);
   }
}
