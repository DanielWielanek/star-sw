
#include "StHbtMaker/Cut/Track/piotrsChargeTrackCut.h"

#include "StHbtMaker/Base/StHbtTrackCut.h"
#include "StHbtMaker/Infrastructure/StHbtString.hh"

ClassImp(piotrsChargeTrackCut)

    piotrsChargeTrackCut::piotrsChargeTrackCut(int charge)
    : mCharge(charge) {}

piotrsChargeTrackCut::~piotrsChargeTrackCut() {}

bool piotrsChargeTrackCut::Pass(const StHbtTrack* track) { return track->Charge() == mCharge; }

StHbtString piotrsChargeTrackCut::Report() {
   StHbtString retVal("");
   return retVal;
}

piotrsChargeTrackCut* piotrsChargeTrackCut::Clone() { return 0; }
