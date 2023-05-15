#include "StHbtMaker/Cut/Track/TPCandToF_SgmToFvsSgmTPCvsP_TrackCutMonitor.h"

#include <cstdio>
#include <string>

#include "StHbtMaker/Infrastructure/StHbtTrack.hh"
#include "StLorentzVector.hh"

#ifdef __ROOT__
ClassImp(TPCandToF_SgmToFvsSgmTPCvsP_TrackCutMonitor)
#endif

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
    TPCandToF_SgmToFvsSgmTPCvsP_TrackCutMonitor::TPCandToF_SgmToFvsSgmTPCvsP_TrackCutMonitor(
        const string& name, int sbins, float slo, float shi, int pbins, float plo, float phi, int type) {
   mtype = type;
   string hname("SgmToFvsSgmTPCvsP");
   mSgmToFvsSgmTPC = new StHbt3DHisto((hname + name).c_str(), "Sigma ToF vs sigma dEdx vs P", sbins, slo, shi, sbins,
                                      slo, shi, pbins, plo, phi);
}  // c-tor

TPCandToF_SgmToFvsSgmTPCvsP_TrackCutMonitor::TPCandToF_SgmToFvsSgmTPCvsP_TrackCutMonitor(
    const TPCandToF_SgmToFvsSgmTPCvsP_TrackCutMonitor& cutMoni) {
   mSgmToFvsSgmTPC = new StHbt3DHisto(*(cutMoni.mSgmToFvsSgmTPC));
}  // copy c-tor

TPCandToF_SgmToFvsSgmTPCvsP_TrackCutMonitor::~TPCandToF_SgmToFvsSgmTPCvsP_TrackCutMonitor() {
   delete mSgmToFvsSgmTPC;
}  // d-tor

void TPCandToF_SgmToFvsSgmTPCvsP_TrackCutMonitor::Fill(const StHbtTrack* track) {
   float sgm1 = 0;
   float sgm2 = 0;
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
   mSgmToFvsSgmTPC->Fill(sgm1, sgm2, track->P().mag());
}  // Fill
