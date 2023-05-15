#include "StHbtMaker/Cut/Track/TPCandToF_SgmToFvsSgmTPC_TrackCutMonitor.h"

#include <cstdio>
#include <string>

#include "StHbtMaker/Infrastructure/StHbtTrack.hh"
#include "StLorentzVector.hh"

#ifdef __ROOT__
ClassImp(TPCandToF_SgmToFvsSgmTPC_TrackCutMonitor)
#endif

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
    TPCandToF_SgmToFvsSgmTPC_TrackCutMonitor::TPCandToF_SgmToFvsSgmTPC_TrackCutMonitor(const string& name,
                                                                                       float tof_p_threshold, int bins,
                                                                                       float lo, float hi, int type) {
   mToF_p_threshold = tof_p_threshold;
   mtype = type;
   string hname("SgmToFvsSgmTPC");
   mSgmToFvsSgmTPC = new StHbt2DHisto((hname + name).c_str(), "Sigma ToF vs sigma dEdx", bins, lo, hi, bins, lo, hi);
}  // c-tor

TPCandToF_SgmToFvsSgmTPC_TrackCutMonitor::TPCandToF_SgmToFvsSgmTPC_TrackCutMonitor(
    const TPCandToF_SgmToFvsSgmTPC_TrackCutMonitor& cutMoni) {
   mSgmToFvsSgmTPC = new StHbt2DHisto(*(cutMoni.mSgmToFvsSgmTPC));
}  // copy c-tor

TPCandToF_SgmToFvsSgmTPC_TrackCutMonitor::~TPCandToF_SgmToFvsSgmTPC_TrackCutMonitor() {
   delete mSgmToFvsSgmTPC;
}  // d-tor

void TPCandToF_SgmToFvsSgmTPC_TrackCutMonitor::Fill(const StHbtTrack* track) {
   float sgm1 = 0;
   float sgm2 = 0;
   if (track->P().mag() >= mToF_p_threshold) {
      switch (mtype) {
         case 0:
            sgm1 = track->NSigmaElectron();
            sgm2 = track->ToF_sigmaElectron();
            break;
         case 1:
            sgm1 = track->NSigmaPion();
            sgm2 = track->ToF_sigmaPion();
            break;
         case 2:
            sgm1 = track->NSigmaKaon();
            sgm2 = track->ToF_sigmaKaon();
            break;
         case 3:
            sgm1 = track->NSigmaProton();
            sgm2 = track->ToF_sigmaProton();
            break;
      }
      mSgmToFvsSgmTPC->Fill(sgm1, sgm2);
   }
}  // Fill
