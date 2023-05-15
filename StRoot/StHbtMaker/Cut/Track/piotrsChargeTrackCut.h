#ifndef PIOTRSCHARGETRACKCUT_H
#define PIOTRSCHARGETRACKCUT_H

#include "StHbtMaker/Base/StHbtTrackCut.h"
#include "StHbtMaker/Infrastructure/StHbtString.hh"

class piotrsChargeTrackCut : public StHbtTrackCut {
  public:
   piotrsChargeTrackCut(int charge);
   ~piotrsChargeTrackCut();

   virtual bool Pass(const StHbtTrack*);

   virtual StHbtString Report();
   virtual piotrsChargeTrackCut* Clone();

  private:
   int mCharge;

   ClassDef(piotrsChargeTrackCut, 0)
};

#endif
