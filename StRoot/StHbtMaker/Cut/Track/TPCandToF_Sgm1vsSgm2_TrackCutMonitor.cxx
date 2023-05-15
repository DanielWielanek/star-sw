#include "StHbtMaker/Cut/Track/TPCandToF_Sgm1vsSgm2_TrackCutMonitor.h"

#include <cstdio>
#include <string>

#include "StHbtMaker/Infrastructure/StHbtTrack.hh"
#include "StLorentzVector.hh"

#ifdef __ROOT__
ClassImp(TPCandToF_Sgm1vsSgm2_TrackCutMonitor)
#endif

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
    TPCandToF_Sgm1vsSgm2_TrackCutMonitor::TPCandToF_Sgm1vsSgm2_TrackCutMonitor(const string& name,
                                                                               float tof_p_threshold, int bins,
                                                                               float lo, float hi, int type1,
                                                                               int type2) {
   mToF_p_threshold = tof_p_threshold;
   mtype1 = type1;
   mtype2 = type2;
   string hname("Sgm1csSgm2");
   mSgm1vsSgm2 =
       new StHbt2DHisto((hname + name).c_str(), "Sigma other particle vs sigma particle", bins, lo, hi, bins, lo, hi);
}  // c-tor

TPCandToF_Sgm1vsSgm2_TrackCutMonitor::TPCandToF_Sgm1vsSgm2_TrackCutMonitor(
    const TPCandToF_Sgm1vsSgm2_TrackCutMonitor& cutMoni) {
   mSgm1vsSgm2 = new StHbt2DHisto(*(cutMoni.mSgm1vsSgm2));
   mtype1 = cutMoni.mtype1;
   mtype2 = cutMoni.mtype2;
}  // copy c-tor

TPCandToF_Sgm1vsSgm2_TrackCutMonitor::~TPCandToF_Sgm1vsSgm2_TrackCutMonitor() { delete mSgm1vsSgm2; }  // d-tor

void TPCandToF_Sgm1vsSgm2_TrackCutMonitor::Fill(const StHbtTrack* track) {
   float sgm1 = 0;
   float sgm2 = 0;
   if (track->P().mag() >= mToF_p_threshold) {
      switch (mtype1) {
         case 0:
            sgm1 = track->ToF_sigmaElectron();
            break;
         case 1:
            sgm1 = track->ToF_sigmaPion();
            break;
         case 2:
            sgm1 = track->ToF_sigmaKaon();
            break;
         case 3:
            sgm1 = track->ToF_sigmaProton();
            break;
      }
      switch (mtype2) {
         case 0:
            sgm2 = track->ToF_sigmaElectron();
            break;
         case 1:
            sgm2 = track->ToF_sigmaPion();
            break;
         case 2:
            sgm2 = track->ToF_sigmaKaon();
            break;
         case 3:
            sgm2 = track->ToF_sigmaProton();
            break;
      }
   } else {
      switch (mtype1) {
         case 0:
            sgm1 = track->NSigmaElectron();
            break;
         case 1:
            sgm1 = track->NSigmaPion();
            break;
         case 2:
            sgm1 = track->NSigmaKaon();
            break;
         case 3:
            sgm1 = track->NSigmaProton();
            break;
      }
      switch (mtype2) {
         case 0:
            sgm2 = track->NSigmaElectron();
            break;
         case 1:
            sgm2 = track->NSigmaPion();
            break;
         case 2:
            sgm2 = track->NSigmaKaon();
            break;
         case 3:
            sgm2 = track->NSigmaProton();
            break;
      }
   }

   mSgm1vsSgm2->Fill(sgm1, sgm2);
}  // Fill
