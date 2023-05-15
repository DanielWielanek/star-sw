#include "StHbtMaker/Cut/Track/TPCandToF_BetavsP_TrackCutMonitor.h"

#include <cstdio>
#include <string>

#include "StHbtMaker/Infrastructure/StHbtTrack.hh"
#include "StLorentzVector.hh"

#ifdef __ROOT__
ClassImp(TPCandToF_BetavsP_TrackCutMonitor)
#endif

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
    TPCandToF_BetavsP_TrackCutMonitor::TPCandToF_BetavsP_TrackCutMonitor(const string& name, int pbins, float plo,
                                                                         float phi, int bbins, float blo, float bhi) {
   string hname("BetavsP");
   mBetavsP = new StHbt2DHisto((hname + name).c_str(), "1/Beta vs Momentum; p [GeV/c]; 1/#beta", pbins, plo, phi, bbins,
                               blo, bhi);
}  // c-tor

TPCandToF_BetavsP_TrackCutMonitor::TPCandToF_BetavsP_TrackCutMonitor(const TPCandToF_BetavsP_TrackCutMonitor& cutMoni) {
   mBetavsP = new StHbt2DHisto(*(cutMoni.mBetavsP));
}  // copy c-tor

TPCandToF_BetavsP_TrackCutMonitor::~TPCandToF_BetavsP_TrackCutMonitor() { delete mBetavsP; }  // d-tor

void TPCandToF_BetavsP_TrackCutMonitor::Fill(const StHbtTrack* track) {
   if (track->ToF_matchFlag()) {
      mBetavsP->Fill(track->P().mag(), 1. / track->ToF_beta());
   }
}  // Fill
