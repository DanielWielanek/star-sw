#include "StHbtMaker/Cut/Track/Chi2TrackCutMonitor.h"

#include <cstdio>
#include <string>

#include "StHbtMaker/Infrastructure/StHbtTrack.hh"
#include "StLorentzVector.hh"

#ifdef __ROOT__
ClassImp(Chi2TrackCutMonitor)
#endif

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Chi2TrackCutMonitor::Chi2TrackCutMonitor(const string& name, int pbins, float plo, float phi, int chi2bins,
                                             float chi2lo, float chi2hi) {
   string hname("Chi2vsP");
   mChi2vsP = new StHbt2DHisto((hname + name).c_str(), "Chi2 vs Momentum; p [GeV/c]; Chi^{2}]", pbins, plo, phi,
                               chi2bins, chi2lo, chi2hi);
   hname = "MassSquaredvsP";
}  // c-tor

Chi2TrackCutMonitor::Chi2TrackCutMonitor(const Chi2TrackCutMonitor& cutMoni) {
   mChi2vsP = new StHbt2DHisto(*(cutMoni.mChi2vsP));
}  // copy c-tor

Chi2TrackCutMonitor::~Chi2TrackCutMonitor() { delete mChi2vsP; }  // d-tor

void Chi2TrackCutMonitor::Fill(const StHbtTrack* track) {
   double p = track->P().mag();
   double chi2 = track->ChiSquared();
   mChi2vsP->Fill(p, chi2);
}  // Fill
