#ifndef PIOTRSREFMULTBOUNDARIESRETRIEVER_H
#define PIOTRSREFMULTBOUNDARIESRETRIEVER_H

#include <set>

#include "StRefMultCorr/StRefMultCorr.h"
#include "TROOT.h"

class piotrsRefMultBoundariesRetriever {
  public:
   piotrsRefMultBoundariesRetriever(int, ...);
   ~piotrsRefMultBoundariesRetriever() { /* no-op */
   }

   void retrieveBoundaries(int);

   int getRefMultMin() { return fRefMultMin; }
   int getRefMultMax() { return fRefMultMax; }

  private:
   bool isRefMultOk();

   int fRefMultMin;
   int fRefMultMax;

   std::set<int> fRefMultBins;
   StRefMultCorr stRefMultCorr;
   ClassDef(piotrsRefMultBoundariesRetriever, 0)
};

#endif
