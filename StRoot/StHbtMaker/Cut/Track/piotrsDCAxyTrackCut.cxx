
#include "StHbtMaker/Cut/Track/piotrsDCAxyTrackCut.h"

#include "StHbtMaker/Base/StHbtTrackCut.h"
#include "StHbtMaker/Infrastructure/StHbtString.hh"

ClassImp(piotrsDCAxyTrackCut)

    piotrsDCAxyTrackCut::piotrsDCAxyTrackCut(double min, double max)
    : mDCAmin(min), mDCAmax(max) {}

piotrsDCAxyTrackCut::~piotrsDCAxyTrackCut() {}

bool piotrsDCAxyTrackCut::Pass(const StHbtTrack* track) { return track->DCAxy() >= mDCAmin && track->DCAxy() <= mDCAmax; }

StHbtString piotrsDCAxyTrackCut::Report() {
   StHbtString retVal("");
   return retVal;
}

piotrsDCAxyTrackCut* piotrsDCAxyTrackCut::Clone() { return 0; }
