#ifndef PIOTRSKINKCUTREJECTALL_H
#define PIOTRSKINKCUTREJECTALL_H

#include "StHbtMaker/Base/StHbtKinkCut.h"
#include "StHbtMaker/Infrastructure/StHbtTypes.hh"

class StHbtKink;

class piotrsKinkCutRejectAll : public StHbtKinkCut {
  public:
   piotrsKinkCutRejectAll() { /* no - op */
   }
   ~piotrsKinkCutRejectAll() { /* no - op */
   }

   virtual bool Pass(const StHbtKink*) { return false; }
   virtual StHbtString Report() { return "kill kinks"; }

  private:
   ClassDef(piotrsKinkCutRejectAll, 0)
};

#endif
