#include "StHbtMaker/Cut/piotrsRefMultBoundariesRetriever.h"

#include <cstdarg>
#include <set>

using namespace std;

ClassImp(piotrsRefMultBoundariesRetriever)

    piotrsRefMultBoundariesRetriever::piotrsRefMultBoundariesRetriever(int binCount, ...)
    : fRefMultMin(0), fRefMultMax(2000) {
   va_list bins;
   va_start(bins, binCount);
   while (binCount > 0) {
      fRefMultBins.insert(va_arg(bins, int));
      --binCount;
   }
   va_end(bins);
}

void piotrsRefMultBoundariesRetriever::retrieveBoundaries(int runNumber) {
   stRefMultCorr.init(runNumber);
   fRefMultMin = 20000;
   fRefMultMax = -1;
   for (int testValue = 0; testValue < 20000; ++testValue) {
      stRefMultCorr.initEvent(testValue, 0.0);
      if (isRefMultOk()) {
         fRefMultMin = testValue < fRefMultMin ? testValue : fRefMultMin;
         fRefMultMax = testValue > fRefMultMax ? testValue : fRefMultMax;
      }
   }
}

bool piotrsRefMultBoundariesRetriever::isRefMultOk() {
   int actualBin = stRefMultCorr.getCentralityBin9();
   return fRefMultBins.count(actualBin) > 0 ? true : false;
}
