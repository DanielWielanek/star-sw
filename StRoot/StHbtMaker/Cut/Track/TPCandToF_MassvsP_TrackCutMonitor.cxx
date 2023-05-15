#include "StHbtMaker/Cut/Track/TPCandToF_MassvsP_TrackCutMonitor.h"

#include <cstdio>
#include <string>

#include "StHbtMaker/Infrastructure/StHbtTrack.hh"
#include "StLorentzVector.hh"

#ifdef __ROOT__
ClassImp(TPCandToF_MassvsP_TrackCutMonitor)
#endif

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
    TPCandToF_MassvsP_TrackCutMonitor::TPCandToF_MassvsP_TrackCutMonitor(const string& name, int pbins, float plo,
                                                                         float phi, int bbins, float blo, float bhi) {
   string hname("MassvsP");
   mMassvsP = new StHbt2DHisto((hname + name).c_str(), "Mass vs Momentum; p [GeV/c]; m [GeV/c^{2}]", pbins, plo, phi,
                               bbins, blo, bhi);
   hname = "MassSquaredvsP";
   mMassSquaredvsP = new StHbt2DHisto((hname + name).c_str(), "Mass^2 vs Momentum; p [GeV/c]; m^2 [GeV^{2}/c^{4}]",
                                      pbins, plo, phi, bbins, blo, bhi);
}  // c-tor

TPCandToF_MassvsP_TrackCutMonitor::TPCandToF_MassvsP_TrackCutMonitor(const TPCandToF_MassvsP_TrackCutMonitor& cutMoni) {
   mMassvsP = new StHbt2DHisto(*(cutMoni.mMassvsP));
   mMassSquaredvsP = new StHbt2DHisto(*(cutMoni.mMassSquaredvsP));
}  // copy c-tor

TPCandToF_MassvsP_TrackCutMonitor::~TPCandToF_MassvsP_TrackCutMonitor() { delete mMassvsP; }  // d-tor

void TPCandToF_MassvsP_TrackCutMonitor::Fill(const StHbtTrack* track) {
   if (track->ToF_matchFlag()) {
      double beta2 = track->ToF_beta();
      beta2 = beta2 * beta2;
      double p = track->P().mag();
      double m2 = p * p * (1 / beta2 - 1);
      if (m2 > 0.0) {
         mMassvsP->Fill(p, sqrt(m2));
      }
      mMassSquaredvsP->Fill(p, m2);
   }
}  // Fill
