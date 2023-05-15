#ifndef PIOTRSV0CUTREJECTALL_H
#define PIOTRSV0CUTREJECTALL_H

#include "StHbtMaker/Base/StHbtV0Cut.h"
#include "StHbtMaker/Infrastructure/StHbtTypes.hh"

class StHbtV0;

class piotrsV0CutRejectAll : public StHbtV0Cut {
  public:
   piotrsV0CutRejectAll() { /* no - op */
   }
   ~piotrsV0CutRejectAll() { /* no - op */
   }

   virtual bool Pass(const StHbtV0*) { return false; }
   virtual StHbtString Report() { return "kill kinks"; }

  private:
   ClassDef(piotrsV0CutRejectAll, 0)
};

#endif
