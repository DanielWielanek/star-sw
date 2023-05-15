
#include "StHbtMaker/Cut/Track/piotrsEtaTrackCut.h"

#include "StHbtMaker/Base/StHbtTrackCut.h"
#include "StHbtMaker/Infrastructure/StHbtString.hh"

ClassImp(piotrsEtaTrackCut)

    piotrsEtaTrackCut::piotrsEtaTrackCut(double min, double max)
    : mEtaMin(min), mEtaMax(max) {}

piotrsEtaTrackCut::~piotrsEtaTrackCut() {}

bool piotrsEtaTrackCut::Pass(const StHbtTrack* track) {
   return track->P().pseudoRapidity() >= mEtaMin && track->P().pseudoRapidity() <= mEtaMax;
}

StHbtString piotrsEtaTrackCut::Report() {
   StHbtString retVal("piotrsEtaTrackCut");
   return retVal;
}

piotrsEtaTrackCut* piotrsEtaTrackCut::Clone() { return 0; }
