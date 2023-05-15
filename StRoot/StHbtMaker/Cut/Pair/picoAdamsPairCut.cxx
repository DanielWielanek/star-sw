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

#include "StHbtMaker/Cut/Pair/picoAdamsPairCut.h"

#include <Stsstream.h>

#include <cstdio>
#include <string>

#ifdef __ROOT__
ClassImp(picoAdamsPairCut)
#endif

    //__________________
    picoAdamsPairCut::picoAdamsPairCut()
    : HitMergingPairCut() {
   mElSigma = 0.0;
   mPiSigma = 0.0;
   mKSigma = 0.0;
   mPSigma = 0.0;
}

string picoAdamsPairCut::Report() {
   string Stemp = "picoAdamsPairCut\n";
   char Ctemp[100];
   sprintf(Ctemp, "Number of pairs which passed: %ld, failed: %ld\n", mNPairsPassed, mNPairsFailed);
   Stemp += Ctemp;
   return Stemp;
}

string picoAdamsPairCut::StrReport() {
   string Stemp = "picoAdamsPairCut\n";
   char Ctemp[100];
   sprintf(Ctemp, "electron nsigma: %E\n", mElSigma);
   Stemp += Ctemp;
   sprintf(Ctemp, "pion nsigma: %E\n", mPiSigma);
   Stemp += Ctemp;
   sprintf(Ctemp, "kaon nsigma: %E\n", mKSigma);
   Stemp += Ctemp;
   sprintf(Ctemp, "proton nsigma: %E\n", mPSigma);
   Stemp += Ctemp;
   sprintf(Ctemp, "max merge fraction: %E", mMaxFracPair);
   Stemp += Ctemp;
   return Stemp;
}
