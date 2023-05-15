#include "StHbtMaker/Cut/Track/TPC_Sgm1vsSgm2vsP_TrackCutMonitor.h"

#include <cstdio>
#include <string>

#include "StHbtMaker/Infrastructure/StHbtTrack.hh"
#include "StLorentzVector.hh"

#ifdef __ROOT__
ClassImp(TPC_Sgm1vsSgm2vsP_TrackCutMonitor)
#endif

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
    TPC_Sgm1vsSgm2vsP_TrackCutMonitor::TPC_Sgm1vsSgm2vsP_TrackCutMonitor(const string& name, int sbins, float slo,
                                                                         float shi, int pbins, float plo, float phi,
                                                                         int type1, int type2) {
   mtype1 = type1;
   mtype2 = type2;
   string hname("TPCSgm1vsSgm2");
   mSgm1vsSgm2 = new StHbt3DHisto((hname + name).c_str(), "Sigma other particle vs sigma particle vs momentum (TPC)",
                                  sbins, slo, shi, sbins, slo, shi, pbins, plo, phi);
}  // c-tor

TPC_Sgm1vsSgm2vsP_TrackCutMonitor::TPC_Sgm1vsSgm2vsP_TrackCutMonitor(const TPC_Sgm1vsSgm2vsP_TrackCutMonitor& cutMoni) {
   mSgm1vsSgm2 = new StHbt3DHisto(*(cutMoni.mSgm1vsSgm2));
   mtype1 = cutMoni.mtype1;
   mtype2 = cutMoni.mtype2;
}  // copy c-tor

TPC_Sgm1vsSgm2vsP_TrackCutMonitor::~TPC_Sgm1vsSgm2vsP_TrackCutMonitor() { delete mSgm1vsSgm2; }  // d-tor

void TPC_Sgm1vsSgm2vsP_TrackCutMonitor::Fill(const StHbtTrack* track) {
   float sgm1 = 0;
   float sgm2 = 0;
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
   mSgm1vsSgm2->Fill(sgm1, sgm2, track->P().mag());
}  // Fill
