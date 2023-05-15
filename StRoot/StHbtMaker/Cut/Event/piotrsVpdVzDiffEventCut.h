#ifndef PIOTRSVPDVZDIFFEVENTCUT_H
#define PIOTRSVPDVZDIFFEVENTCUT_H

#include "StHbtMaker/Base/StHbtEventCut.h"

class StHbtEvent;

class piotrsVpdVzDiffEventCut : public StHbtEventCut {
  public:
   piotrsVpdVzDiffEventCut(double maxDiff) : fMaxDiff(maxDiff) {}
   virtual ~piotrsVpdVzDiffEventCut() { /* no-op */
   }

   virtual bool Pass(const StHbtEvent* event);
   virtual StHbtString Report();
   virtual piotrsVpdVzDiffEventCut* Clone();

  private:
   double fMaxDiff;

   ClassDef(piotrsVpdVzDiffEventCut, 0)
};

#endif
