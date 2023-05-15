
#include "StHbtMaker/Cut/Track/piotrsNHitsTrackCut.h"

#include "StHbtMaker/Base/StHbtTrackCut.h"
#include "StHbtMaker/Infrastructure/StHbtString.hh"

ClassImp(piotrsNHitsTrackCut)

    piotrsNHitsTrackCut::piotrsNHitsTrackCut(int min, int max)
    : mNHitsMin(min), mNHitsMax(max) {}

piotrsNHitsTrackCut::~piotrsNHitsTrackCut() {}

bool piotrsNHitsTrackCut::Pass(const StHbtTrack* track) { return track->NHits() >= mNHitsMin && track->NHits() <= mNHitsMax; }

StHbtString piotrsNHitsTrackCut::Report() {
   StHbtString retVal("");
   return retVal;
}

piotrsNHitsTrackCut* piotrsNHitsTrackCut::Clone() { return 0; }
