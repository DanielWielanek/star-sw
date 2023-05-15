/***************************************************************************
 *
 * $Id:
 *
 * Author: Frank Laue, Ohio State, laue@mps.ohio-state.edu
 ***************************************************************************
 *
 * Description: part of STAR HBT Framework: StHbtMaker package
 *    a simple particle cut that selects on phasespace, #hits, DCA, and PID
 *
 ***************************************************************************
 *
 * $Log:
 **************************************************************************/

#include "StHbtMaker/Cut/Track/primaryPicoTrackCut.h"

#include <cstdio>

#ifdef __ROOT__
ClassImp(primaryPicoTrackCut)
#endif

    //#define STHBTDEBUG

    primaryPicoTrackCut::primaryPicoTrackCut() {
   mNPassed = 0;
   mNFailed = 0;
   mNSigmaElectron[0] = -1e9;
   mNSigmaElectron[1] = +1e9;
   mNSigmaPion[0] = -1e9;
   mNSigmaPion[1] = +1e9;
   mNSigmaKaon[0] = -1e9;
   mNSigmaKaon[1] = +1e9;
   mNSigmaProton[0] = -1e9;
   mNSigmaProton[1] = +1e9;
   mNSigmaAntiElectron[0] = 0.;
   mNSigmaAntiElectron[1] = 0.;
   mEta[0] = -1e9;
   mEta[1] = +1e9;
   mRapidity[0] = -1e9;
   mRapidity[1] = +1e9;
   mP[0] = -1e9;
   mP[1] = +1e9;
   mPt[0] = -1e9;
   mPt[1] = +1e9;
   mDCAxy = +1e9;
   mNHits = 0;
   mNdEdxHits = 0;
}
//------------------------------
primaryPicoTrackCut::primaryPicoTrackCut(primaryPicoTrackCut& c) : StHbtTrackCut(c) {
   mNPassed = 0;
   mNFailed = 0;
   mCharge = c.mCharge;
   mNSigmaElectron[0] = c.mNSigmaElectron[0];
   mNSigmaElectron[1] = c.mNSigmaElectron[1];
   mNSigmaPion[0] = c.mNSigmaPion[0];
   mNSigmaPion[1] = c.mNSigmaPion[1];
   mNSigmaKaon[0] = c.mNSigmaKaon[0];
   mNSigmaKaon[1] = c.mNSigmaKaon[1];
   mNSigmaProton[0] = c.mNSigmaProton[0];
   mNSigmaProton[1] = c.mNSigmaProton[1];
   mNSigmaAntiElectron[0] = c.mNSigmaAntiElectron[0];
   mNSigmaAntiElectron[1] = c.mNSigmaAntiElectron[1];
   mNHits = c.mNHits;
   mNdEdxHits = c.mNdEdxHits;
   mP[0] = c.mP[0];
   mP[1] = c.mP[1];
   mPt[0] = c.mPt[0];
   mPt[1] = c.mPt[1];
   mRapidity[0] = c.mRapidity[0];
   mRapidity[1] = c.mRapidity[1];
   mEta[0] = c.mEta[0];
   mEta[1] = c.mEta[1];
   mDCAxy = c.mDCAxy;
#ifdef STHBTDEBUG
   cout << " primaryPicoTrackCut::primaryPicoTrackCut(primaryPicoTrackCut& c) " << endl;
#endif
}

string primaryPicoTrackCut::Report() {
   string Stemp = "primaryPicoTrackCut:";
   char Ctemp[1000];
   sprintf(Ctemp, "Number of particles which passed: %ld, failed %ld", mNPassed, mNFailed);
   Stemp += Ctemp;
   return Stemp;
}

string primaryPicoTrackCut::StrReport() {
   string Stemp = "primaryPicoTrackCut:";
   char Ctemp[1000];
   sprintf(Ctemp, "\nParticle mass:\t%E", mMass);
   Stemp += Ctemp;
   sprintf(Ctemp, "\nParticle charge:\t%d", mCharge);
   Stemp += Ctemp;
   sprintf(Ctemp, "\nParticle Nsigma from pion:\t%E - %E", mNSigmaPion[0], mNSigmaPion[1]);
   Stemp += Ctemp;
   sprintf(Ctemp, "\nParticle Nsigma from kaon:\t%E - %E", mNSigmaKaon[0], mNSigmaKaon[1]);
   Stemp += Ctemp;
   sprintf(Ctemp, "\nParticle Nsigma from proton:\t%E - %E", mNSigmaProton[0], mNSigmaProton[1]);
   Stemp += Ctemp;
   sprintf(Ctemp, "\nParticle #hits >=\t%d", mNHits);
   Stemp += Ctemp;
   sprintf(Ctemp, "\nParticle dEdx #hits >=\t%d", mNdEdxHits);
   Stemp += Ctemp;
   sprintf(Ctemp, "\nParticle p:\t%E - %E", mP[0], mP[1]);
   Stemp += Ctemp;
   sprintf(Ctemp, "\nParticle pT:\t%E - %E", mPt[0], mPt[1]);
   Stemp += Ctemp;
   sprintf(Ctemp, "\nParticle rapidity:\t%E - %E", mRapidity[0], mRapidity[1]);
   Stemp += Ctemp;
   sprintf(Ctemp, "\nParticle mEta:\t%E - %E", mEta[0], mEta[1]);
   Stemp += Ctemp;
   sprintf(Ctemp, "\nParticle DCA: <\t%E", mDCAxy);
   Stemp += Ctemp;
   return Stemp;
}
