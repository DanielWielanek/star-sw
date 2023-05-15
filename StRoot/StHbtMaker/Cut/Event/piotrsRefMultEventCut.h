#ifndef PIOTRSREFMULTEVENTCUT_H
#define PIOTRSREFMULTEVENTCUT_H

#include <set>

#include "StHbtMaker/Base/StHbtEventCut.h"
#include "StRefMultCorr/StRefMultCorr.h"

class StHbtEvent;

class piotrsRefMultEventCut : public StHbtEventCut {
  public:
   piotrsRefMultEventCut(int binCount, ...);
   virtual ~piotrsRefMultEventCut() { /* no-op */
   }

   virtual bool Pass(const StHbtEvent* event);
   virtual StHbtString Report();
   virtual piotrsRefMultEventCut* Clone();

  private:
   bool isRefMultOk();
   void initRunNumber(int);

   std::set<int> fRefMultBins;
   StRefMultCorr stRefMultCorr;
   int fRunNumber;
   ClassDef(piotrsRefMultEventCut, 0)
};

#endif
