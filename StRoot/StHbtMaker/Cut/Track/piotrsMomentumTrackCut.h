#ifndef PIOTRSMOMENTUMTRACKCUT_H
#define PIOTRSMOMENTUMTRACKCUT_H

#include "StHbtMaker/Base/StHbtTrackCut.h"
#include "StHbtMaker/Infrastructure/StHbtString.hh"

class piotrsMomentumTrackCut : public StHbtTrackCut {
  public:
   piotrsMomentumTrackCut(double min, double max);
   ~piotrsMomentumTrackCut();

   virtual bool Pass(const StHbtTrack*);

   virtual StHbtString Report();
   virtual piotrsMomentumTrackCut* Clone();

  private:
   double mMomentumMin;
   double mMomentumMax;

   ClassDef(piotrsMomentumTrackCut, 0)
};

#endif
