#ifndef PIOTRSETATRACKCUT_H
#define PIOTRSETATRACKCUT_H

#include "StHbtMaker/Base/StHbtTrackCut.h"
#include "StHbtMaker/Infrastructure/StHbtString.hh"

class piotrsEtaTrackCut : public StHbtTrackCut {
  public:
   piotrsEtaTrackCut(double min, double max);
   ~piotrsEtaTrackCut();

   virtual bool Pass(const StHbtTrack*);

   virtual StHbtString Report();
   virtual piotrsEtaTrackCut* Clone();

  private:
   double mEtaMin;
   double mEtaMax;

   ClassDef(piotrsEtaTrackCut, 0)
};

#endif
