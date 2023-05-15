#ifndef CHI2TRACKCUT_H
#define CHI2TRACKCUT_H

#include "StHbtMaker/Base/StHbtTrackCut.h"
#include "StHbtMaker/Infrastructure/StHbtString.hh"

class Chi2TrackCut : public StHbtTrackCut {
  public:
   Chi2TrackCut(double);
   ~Chi2TrackCut();

   virtual bool Pass(const StHbtTrack*);

   virtual StHbtString Report();
   virtual Chi2TrackCut* Clone();

  private:
   double mChi2Max;

   ClassDef(Chi2TrackCut, 0)
};

#endif
