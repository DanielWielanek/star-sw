/***************************************************************************
 *
 * $Id: fabricesPairCut.cxx,v 1.1 2001/12/14 23:11:27 fretiere Exp $
 *
 * Author: Adam Kisiel, Warsaw University of Technology, kisiel@if.pw.edu.pl
 ***************************************************************************
 *
 * Description: part of STAR HBT Framework: StHbtMaker package
 *   Cuts on probability of a pair being e+e-, pi+pi- or K+K-
 *   using dEdx NSigma PID information
 *
 ***************************************************************************
 *
 *
 **************************************************************************/

#include "StHbtMaker/Cut/adamsPairCut.h"

#include <Stsstream.h>

#include <cstdio>
#include <string>

#ifdef __ROOT__
ClassImp(adamsPairCut)
#endif

    //__________________
    adamsPairCut::adamsPairCut()
    : HitMergingPairCut() {
   mNPairsPassed = mNPairsFailed = 0;
   mElSigma = 0.0;
   mPiSigma = 0.0;
   mKSigma = 0.0;
   mPSigma = 0.0;
   mElPIDMax = 1.0;
   mPiPIDMax = 1.0;
   mKPIDMax = 1.0;
   mPPIDMax = 1.0;
   mPIDPThreshold = 0.0;
   mDipMin = 0.0;
   mDipElPIDMax = 1.0;
   for (int iter = 0; iter < 10; iter++) {
      mPIDLower[iter] = 0.0;
      mPIDUpper[iter] = 1.0;
   }
}
//__________________
// adamsPairCut::~adamsPairCut(){
//  /* no-op */
//}
//________`__________
bool adamsPairCut::Pass(const StHbtPair* pair) {
   bool isElPair, isPiPair, isKPair, isPPair;
   double tDeltaTheta = TMath::Abs(pair->track1()->FourMomentum().theta() - pair->track2()->FourMomentum().theta());
   double tDipElPID = pair->track1()->Track()->PidProbElectron() * pair->track2()->Track()->PidProbElectron();
   double tPidValues[10];
   bool isAll = 1;

   if (pair->track1()->Track()->P().mag() < mPIDPThreshold) {
      bool is1El = (TMath::Abs(pair->track1()->Track()->NSigmaElectron()) < mElSigma);
      bool is1Pi = (TMath::Abs(pair->track1()->Track()->NSigmaPion()) < mPiSigma);
      bool is1K = (TMath::Abs(pair->track1()->Track()->NSigmaKaon()) < mKSigma);
      bool is1P = (TMath::Abs(pair->track1()->Track()->NSigmaProton()) < mPSigma);
      if (pair->track2()->Track()->P().mag() < mPIDPThreshold) {
         isElPair = is1El && (TMath::Abs(pair->track2()->Track()->NSigmaElectron()) < mElSigma);
         isPiPair = is1Pi && (TMath::Abs(pair->track2()->Track()->NSigmaPion()) < mPiSigma);
         isKPair = is1K && (TMath::Abs(pair->track2()->Track()->NSigmaKaon()) < mKSigma);
         isPPair = is1P && (TMath::Abs(pair->track2()->Track()->NSigmaProton()) < mPSigma);
      } else {
         isElPair = is1El && (pair->track2()->Track()->PidProbElectron() <= mElPIDMax);
         isPiPair = is1Pi && (pair->track2()->Track()->PidProbPion() <= mPiPIDMax);
         isKPair = is1K && (pair->track2()->Track()->PidProbKaon() <= mKPIDMax);
         isPPair = is1P && (pair->track2()->Track()->PidProbProton() <= mPPIDMax);
      }
   } else {
      if (pair->track2()->Track()->P().mag() < mPIDPThreshold) {
         bool is2El = (TMath::Abs(pair->track2()->Track()->NSigmaElectron()) < mElSigma);
         bool is2Pi = (TMath::Abs(pair->track2()->Track()->NSigmaPion()) < mPiSigma);
         bool is2K = (TMath::Abs(pair->track2()->Track()->NSigmaKaon()) < mKSigma);
         bool is2P = (TMath::Abs(pair->track2()->Track()->NSigmaProton()) < mPSigma);
         isElPair = is2El && (pair->track1()->Track()->PidProbElectron() <= mElPIDMax);
         isPiPair = is2Pi && (pair->track1()->Track()->PidProbPion() <= mPiPIDMax);
         isKPair = is2K && (pair->track1()->Track()->PidProbKaon() <= mKPIDMax);
         isPPair = is2P && (pair->track1()->Track()->PidProbProton() <= mPPIDMax);
      } else {
         tPidValues[0] = pair->track1()->Track()->PidProbElectron() * pair->track2()->Track()->PidProbElectron();
         tPidValues[1] = pair->track1()->Track()->PidProbElectron() * pair->track2()->Track()->PidProbPion();
         tPidValues[2] = pair->track1()->Track()->PidProbPion() * pair->track2()->Track()->PidProbPion();
         tPidValues[3] = pair->track1()->Track()->PidProbElectron() * pair->track2()->Track()->PidProbKaon();
         tPidValues[4] = pair->track1()->Track()->PidProbPion() * pair->track2()->Track()->PidProbKaon();
         tPidValues[5] = pair->track1()->Track()->PidProbKaon() * pair->track2()->Track()->PidProbKaon();
         tPidValues[6] = pair->track1()->Track()->PidProbElectron() * pair->track2()->Track()->PidProbProton();
         tPidValues[7] = pair->track1()->Track()->PidProbPion() * pair->track2()->Track()->PidProbProton();
         tPidValues[8] = pair->track1()->Track()->PidProbKaon() * pair->track2()->Track()->PidProbProton();
         tPidValues[9] = pair->track1()->Track()->PidProbProton() * pair->track2()->Track()->PidProbProton();

         isElPair = (tPidValues[0]) > mElPIDMax;
         isPiPair = (tPidValues[2]) > mPiPIDMax;
         isKPair = (tPidValues[5]) > mKPIDMax;
         isPPair = (tPidValues[9]) > mPPIDMax;

         for (int iter = 0; iter < 10; iter++)
            if ((tPidValues[iter] < mPIDLower[iter]) || (tPidValues[iter] > mPIDUpper[iter])) isAll = 0;
      }
   }
   bool temp = (pair->track1()->TrackId() != pair->track2()->TrackId() && (!isElPair) && (!isPiPair) && (!isKPair) &&
                (!isPPair) && (isAll) && (pair->getFracOfMergedRow() < mMaxFracPair) &&
                ((tDeltaTheta > mDipMin) || (tDipElPID < mDipElPIDMax)));
   temp ? mNPairsPassed++ : mNPairsFailed++;
   return temp;
}
//__________________
StHbtString adamsPairCut::Report() {
   string Stemp = "Adams Pair Cut - cut on e+e- pi+pi+ K+K- using NSigma\n";
   char Ctemp[100];
   sprintf(Ctemp, "Number of pairs which passed:\t%ld  Number which failed:\t%ld\n", mNPairsPassed, mNPairsFailed);
   Stemp += Ctemp;
   StHbtString returnThis = Stemp;
   return returnThis;
}
//__________________
std::ostringstream* adamsPairCut::finalReport() const {
   std::ostringstream* tFinalReport = new std::ostringstream;
   (*tFinalReport) << "_____ Adams pair Cut _____ " << endl
                   << " N pairs passed : " << mNPairsPassed << endl
                   << " N pairs failed : " << mNPairsFailed << endl
                   << ends;
   return tFinalReport;
}
//__________________
void adamsPairCut::setLowerPidValues(double* aPidLower) {
   for (int iter = 0; iter < 10; iter++) mPIDLower[iter] = aPidLower[iter];
}
//__________________
void adamsPairCut::setUpperPidValues(double* aPidUpper) {
   for (int iter = 0; iter < 10; iter++) mPIDUpper[iter] = aPidUpper[iter];
}
