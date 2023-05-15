
#include "StHbtMaker/Cut/Track/Chi2TrackCut.h"

#include "StHbtMaker/Base/StHbtTrackCut.h"
#include "StHbtMaker/Infrastructure/StHbtString.hh"

ClassImp(Chi2TrackCut)

    Chi2TrackCut::Chi2TrackCut(double chi2Max)
    : mChi2Max(chi2Max) {}

Chi2TrackCut::~Chi2TrackCut() {}

bool Chi2TrackCut::Pass(const StHbtTrack* track) { return track->ChiSquared() <= mChi2Max; }

StHbtString Chi2TrackCut::Report() {
   StHbtString retVal("Chi2TrackCut report \n");
   return retVal;
}

Chi2TrackCut* Chi2TrackCut::Clone() { return 0; }
