#ifndef PIOTRSNHITSTRACKCUT_H
#define PIOTRSNHITSTRACKCUT_H

#include "StHbtMaker/Base/StHbtTrackCut.h"
#include "StHbtMaker/Infrastructure/StHbtString.hh"

class piotrsNHitsTrackCut : public StHbtTrackCut {
  public:
   piotrsNHitsTrackCut(int min, int max);
   ~piotrsNHitsTrackCut();

   virtual bool Pass(const StHbtTrack*);

   virtual StHbtString Report();
   virtual piotrsNHitsTrackCut* Clone();

  private:
   int mNHitsMin;
   int mNHitsMax;

   ClassDef(piotrsNHitsTrackCut, 0)
};

#endif
