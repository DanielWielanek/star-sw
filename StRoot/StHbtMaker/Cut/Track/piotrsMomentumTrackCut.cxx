
#include "StHbtMaker/Cut/Track/piotrsMomentumTrackCut.h"

#include "StHbtMaker/Base/StHbtTrackCut.h"
#include "StHbtMaker/Infrastructure/StHbtString.hh"

ClassImp(piotrsMomentumTrackCut)

    piotrsMomentumTrackCut::piotrsMomentumTrackCut(double min, double max)
    : mMomentumMin(min), mMomentumMax(max) {}

piotrsMomentumTrackCut::~piotrsMomentumTrackCut() {}

bool piotrsMomentumTrackCut::Pass(const StHbtTrack* track) {
   return track->P().mag() >= mMomentumMin && track->P().mag() <= mMomentumMax;
}

StHbtString piotrsMomentumTrackCut::Report() {
   StHbtString retVal("piotrsMomentumTrackCut report \n");
   return retVal;
}

piotrsMomentumTrackCut* piotrsMomentumTrackCut::Clone() { return 0; }
