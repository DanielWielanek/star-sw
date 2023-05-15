#include "StHbtMaker/Cut/Track/primaryPicoTrackCutMonitor.h"

#include <cstdio>
#include <string>

#include "StHbtMaker/Infrastructure/StHbtTrack.hh"
#include "StLorentzVector.hh"

#ifdef __ROOT__
ClassImp(primaryPicoTrackCutMonitor)
#endif

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
    primaryPicoTrackCutMonitor::primaryPicoTrackCutMonitor(const char* name, const char* suff,
                                                           int ptype) {  // default constructor
   string s(suff);
   string n(name);
   mDCAxy = new StHbt2IHisto((n + "_DCAvsPt" + s).c_str(), "DCAxy (cm) vs Pt (GeV/c)", 50, 0, 1.5, 30, 0, 3.);
   mYPt = new StHbt2IHisto((n + "_YvsPt" + s).c_str(), "y vs Pt (GeV/c)", 50, -1., 1, 50, 0., 1.5);
   mNSigmaPt = new StHbt2IHisto((n + "_NSigmavsPt" + s).c_str(), "NSigma vs Pt (GeV/c)", 50, 0., 1.5, 50, -3., 3);
   //	mNSigmaPID   = new StHbt2IHisto( (n+"_NSigmavsPID"+s).c_str(),"NSigma vs PID ",50,0.,1.,50,-3.,3);
   mNSigmavsNSigmaEl =
       new StHbt2IHisto((n + "_NSigmavsNSigmaEl" + s).c_str(), "NSigma vs NSigmaEl ", 50, -3., 3., 50, -3., 3);
   mParticleType = ptype;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
primaryPicoTrackCutMonitor::primaryPicoTrackCutMonitor(const primaryPicoTrackCutMonitor& cutMoni) {
   mDCAxy = new StHbt2IHisto(*(cutMoni.mDCAxy));
   mYPt = new StHbt2IHisto(*(cutMoni.mYPt));
   mNSigmaPt = new StHbt2IHisto(*(cutMoni.mNSigmaPt));
   //	mNSigmaPID = new StHbt2IHisto(*(cutMoni.mNSigmaPID));
   mNSigmavsNSigmaEl = new StHbt2IHisto(*(cutMoni.mNSigmavsNSigmaEl));
   mParticleType = cutMoni.mParticleType;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
primaryPicoTrackCutMonitor::~primaryPicoTrackCutMonitor() {
   delete mDCAxy;
   delete mYPt;
   delete mNSigmaPt;
   //	delete mNSigmaPID;
   delete mNSigmavsNSigmaEl;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

void primaryPicoTrackCutMonitor::Write() {
   mDCAxy->Write();
   mYPt->Write();
   mNSigmaPt->Write();
   //	mNSigmaPID->Write();
   mNSigmavsNSigmaEl->Write();
}
