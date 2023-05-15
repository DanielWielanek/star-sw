#include "StHbtMaker/Cut/Track/TPCandToF_yLocalvsP_TrackCutMonitor.h"

#include <cstdio>
#include <string>

#include "StHbtMaker/Infrastructure/StHbtTrack.hh"
#include "StLorentzVector.hh"
#include "StMuDSTMaker/COMMON/StMuBTofPidTraits.h"

#ifdef __ROOT__
ClassImp(TPCandToF_yLocalvsP_TrackCutMonitor)
#endif

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
    TPCandToF_yLocalvsP_TrackCutMonitor::TPCandToF_yLocalvsP_TrackCutMonitor(const string& name, int pbins, float plo,
                                                                             float phi, int bbins, float blo,
                                                                             float bhi) {
   string hname("yLocalvsP");
   myLocalvsP = new StHbt2DHisto((hname + name).c_str(), "yLocal vs Momentum; p [GeV/c]; yLocal [cm]", pbins, plo, phi,
                                 bbins, blo, bhi);
}  // c-tor

TPCandToF_yLocalvsP_TrackCutMonitor::TPCandToF_yLocalvsP_TrackCutMonitor(
    const TPCandToF_yLocalvsP_TrackCutMonitor& cutMoni) {
   myLocalvsP = new StHbt2DHisto(*(cutMoni.myLocalvsP));
}  // copy c-tor

TPCandToF_yLocalvsP_TrackCutMonitor::~TPCandToF_yLocalvsP_TrackCutMonitor() { delete myLocalvsP; }  // d-tor

void TPCandToF_yLocalvsP_TrackCutMonitor::Fill(const StHbtTrack* track) {
   // Int_t index2global = dynamic_cast<StMuTrack *>(mEvent->Track(pr))->index2Global();

   //	if (index2global >= 0)
   //	{ btof = new StMuBTofPidTraits((((StMuTrack *)(mEvent->Track_g(index2global)))->btofPidTraits())); }
   //	else{ btof = NULL; }

   if (track->ToF_matchFlag()) {
      myLocalvsP->Fill(track->P().mag(), track->ToF_yLocal());
   }
}  // Fill
