#ifndef PIOTRSTOFMULTEVENTCUT_H
#define PIOTRSTOFMULTEVENTCUT_H

#include "StHbtMaker/Base/StHbtEventCut.h"

class StHbtEvent;

class piotrsTofMultEventCut : public StHbtEventCut {
  public:
   piotrsTofMultEventCut(int lo, int hi = 1000000);
   virtual ~piotrsTofMultEventCut() { /*no-op*/
   }

   virtual bool Pass(const StHbtEvent* event);
   virtual StHbtString Report();
   virtual piotrsTofMultEventCut* Clone();

  private:
   int mTofMultLo;
   int mTofMultHi;

   ClassDef(piotrsTofMultEventCut, 0)
};

#endif
