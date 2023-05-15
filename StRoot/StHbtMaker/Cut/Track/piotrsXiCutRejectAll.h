#ifndef PIOTRSXICUTREJECTALL_H
#define PIOTRSXICUTREJECTALL_H

#include "StHbtMaker/Base/StHbtXiCut.h"
#include "StHbtMaker/Infrastructure/StHbtTypes.hh"

class StHbtXi;

class piotrsXiCutRejectAll : public StHbtXiCut {
  public:
   piotrsXiCutRejectAll() { /* no - op */
   }
   ~piotrsXiCutRejectAll() { /* no - op */
   }

   virtual bool Pass(const StHbtXi*) { return false; }
   virtual StHbtString Report() { return "kill kinks"; }

  private:
   ClassDef(piotrsXiCutRejectAll, 0)
};

#endif
