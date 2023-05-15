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

#include "StHbtMaker/Cut/Track/picoTrackCut.h"

#include <cstdio>

#ifdef __ROOT__
ClassImp(picoTrackCut)
#endif

    //#define STHBTDEBUG

    picoTrackCut::picoTrackCut() {
   mNTracksPassed = mNTracksFailed = 0;
   mPidProbElectron[0] = -1e9;
   mPidProbElectron[1] = +1e9;
   mPidProbPion[0] = -1e9;
   mPidProbPion[1] = +1e9;
   mPidProbKaon[0] = -1e9;
   mPidProbKaon[1] = +1e9;
   mPidProbProton[0] = -1e9;
   mPidProbProton[1] = +1e9;
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
   mNSigmaAntiPion[0] = 0.;
   mNSigmaAntiPion[1] = 0.;
   mNSigmaAntiKaon[0] = 0.;
   mNSigmaAntiKaon[1] = 0.;
   mNSigmaAntiProton[0] = 0.;
   mNSigmaAntiProton[1] = 0.;
   mEta[0] = -1e9;
   mEta[1] = +1e9;
   mRapidity[0] = -1e9;
   mRapidity[1] = +1e9;
   mP[0] = -1e9;
   mP[1] = +1e9;
   mPt[0] = -1e9;
   mPt[1] = +1e9;
   mPx[0] = -1e9;
   mPx[1] = +1e9;
   mPy[0] = -1e9;
   mPy[1] = +1e9;
   mPz[0] = -1e9;
   mPz[1] = +1e9;
   mDCA[0] = -1e9;
   mDCA[1] = +1e9;
   mDCAGlobal[0] = -1e9;
   mDCAGlobal[1] = +1e9;
   mNHits[0] = 0;
   mNHits[1] = 60;
   mNdEdxHits[0] = 0;
   mNdEdxHits[1] = 60;
   mdEdx[0] = -1e9;
   mdEdx[1] = +1e9;
}
//------------------------------
picoTrackCut::picoTrackCut(picoTrackCut& c) : StHbtTrackCut(c) {
   mNTracksPassed = mNTracksFailed = 0;
   mCharge = c.mCharge;
   mPidProbElectron[0] = c.mPidProbElectron[0];
   mPidProbElectron[1] = c.mPidProbElectron[1];
   mPidProbPion[0] = c.mPidProbPion[0];
   mPidProbPion[1] = c.mPidProbPion[1];
   mPidProbKaon[0] = c.mPidProbKaon[0];
   mPidProbKaon[1] = c.mPidProbKaon[1];
   mPidProbProton[0] = c.mPidProbProton[0];
   mPidProbProton[1] = c.mPidProbProton[1];
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
   mNSigmaAntiPion[0] = c.mNSigmaAntiPion[0];
   mNSigmaAntiPion[1] = c.mNSigmaAntiPion[1];
   mNSigmaAntiKaon[0] = c.mNSigmaAntiKaon[0];
   mNSigmaAntiKaon[1] = c.mNSigmaAntiKaon[1];
   mNSigmaAntiProton[0] = c.mNSigmaAntiProton[0];
   mNSigmaAntiProton[1] = c.mNSigmaAntiProton[1];
   mNHits[0] = c.mNHits[0];
   mNHits[1] = c.mNHits[1];
   mNdEdxHits[0] = c.mNdEdxHits[0];
   mNdEdxHits[1] = c.mNdEdxHits[1];
   mP[0] = c.mP[0];
   mP[1] = c.mP[1];
   mPt[0] = c.mPt[0];
   mPt[1] = c.mPt[1];
   mPx[0] = c.mPx[0];
   mPx[1] = c.mPx[1];
   mPy[0] = c.mPy[0];
   mPy[1] = c.mPy[1];
   mPz[0] = c.mPz[0];
   mPz[1] = c.mPz[1];
   mRapidity[0] = c.mRapidity[0];
   mRapidity[1] = c.mRapidity[1];
   mEta[0] = c.mEta[0];
   mEta[1] = c.mEta[1];
   mDCA[0] = c.mDCA[0];
   mDCA[1] = c.mDCA[1];
   mdEdx[0] = c.mdEdx[0];
   mdEdx[1] = c.mdEdx[1];
   mDCAGlobal[0] = c.mDCAGlobal[0];
   mDCAGlobal[1] = c.mDCAGlobal[1];
   mNTracksPassed = 0;
   mNTracksFailed = 0;
#ifdef STHBTDEBUG
   cout << " picoTrackCut::picoTrackCut(picoTrackCut& c) " << endl;
#endif
}

//------------------------------
StHbtString picoTrackCut::Report() {
   string Stemp;
   char Ctemp[100];
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
   sprintf(Ctemp, "\nParticle PidProb from electron:\t%E - %E", mPidProbElectron[0], mPidProbElectron[1]);
   Stemp += Ctemp;
   sprintf(Ctemp, "\nParticle PidProb from pion:\t%E - %E", mPidProbPion[0], mPidProbPion[1]);
   Stemp += Ctemp;
   sprintf(Ctemp, "\nParticle PidProb from kaon:\t%E - %E", mPidProbKaon[0], mPidProbKaon[1]);
   Stemp += Ctemp;
   sprintf(Ctemp, "\nParticle PidProb from proton:\t%E - %E", mPidProbProton[0], mPidProbProton[1]);
   Stemp += Ctemp;
   sprintf(Ctemp, "\nParticle PidProb from electron:\t%E - %E", mPidProbElectron[0], mPidProbElectron[1]);
   Stemp += Ctemp;
   sprintf(Ctemp, "\nParticle #hits:\t%d - %d", mNHits[0], mNHits[1]);
   Stemp += Ctemp;
   sprintf(Ctemp, "\nParticle dEdx #hits:\t%d - %d", mNdEdxHits[0], mNdEdxHits[1]);
   Stemp += Ctemp;
   sprintf(Ctemp, "\nParticle p:\t%E - %E", mP[0], mP[1]);
   Stemp += Ctemp;
   sprintf(Ctemp, "\nParticle pT:\t%E - %E", mPt[0], mPt[1]);
   Stemp += Ctemp;
   sprintf(Ctemp, "\nParticle rapidity:\t%E - %E", mRapidity[0], mRapidity[1]);
   Stemp += Ctemp;
   sprintf(Ctemp, "\nParticle mEta:\t%E - %E", mEta[0], mEta[1]);
   Stemp += Ctemp;
   sprintf(Ctemp, "\nParticle DCA:\t%E - %E", mDCA[0], mDCA[1]);
   Stemp += Ctemp;
   sprintf(Ctemp, "\nParticle DCAGlobal:\t%E - %E", mDCAGlobal[0], mDCAGlobal[1]);
   Stemp += Ctemp;
   sprintf(Ctemp, "\nParticle dEdx:\t%E - %E", mdEdx[0], mdEdx[1]);
   Stemp += Ctemp;
   sprintf(Ctemp, "\nNumber of tracks which passed:\t%ld  Number which failed:\t%ld", mNTracksPassed, mNTracksFailed);
   Stemp += Ctemp;
   StHbtString returnThis = Stemp;
   return returnThis;
}

// ostrstream* picoTrackCut::finalReport() const{
// ostrstream* tFinalReport = new ostrstream;
//  (*tFinalReport) <<  "_____ Track Cut _____ " << endl
//		  << "Charge = " << mCharge << endl
//		  << mNSigmaPion[0] << " < Sigma pion < "
//		  << mNSigmaPion[1] << endl
//		  << mNSigmaKaon[0] << " < Sigma Kaon < "
//		  << mNSigmaKaon[1] << endl
//		  << mNSigmaProton[0] << " < Sigma proton < "
//		  << mNSigmaProton[1] << endl
//		  << mNHits[0] << " < NHits < " << mNHits[1] << endl
//		  << mNdEdxHits[0] << " < NHits < " << mNdEdxHits[1] << endl
//		  << mPt[0] << " < pT < " << mPt[1] << endl
//		  << mP[0] << " < p < " << mP[1] << endl
//		  << mRapidity[0] << " < Y < " << mRapidity[1] << endl
//		  << mDCA[0] << " < dca < " << mDCA[1] << endl
//		  << mdEdx[0] << " < dEdx < " << mdEdx[1] << endl
//		  << " >>> N Tracks passed " << mNTracksPassed << endl
//		  << " >>> N Tracks failed " << mNTracksFailed << endl
//		  << ends;
// return tFinalReport;
//}
