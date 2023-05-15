/***************************************************************************
 *
 * Author: Maciek Jedynak, Warsaw University of Technoogy, jedynak@if.pw.edu.pl
 ***************************************************************************
 *
 * Description: part of STAR HBT Framework: StHbtMaker package
 * Cuts e+e- pairs, on the basis of distance of closest approach,
 * decay length, invariant mass, difference in Theta angle of particles,
 * and particles PID.
 ***************************************************************************
 *
 *
 **************************************************************************/
// NOTE: decay length is calculated with respect to  (0,0) not primary vertex !

#include "StHbtMaker/Cut/Pair/eeKillPairCut.h"

#include <cstdio>
#include <string>

#include "StHbtMaker/Infrastructure/StHbtTypes.hh"

#ifdef __ROOT__
ClassImp(eeKillPairCut)
#endif

    eeKillPairCut::eeKillPairCut() {
   mNPairsPassed = mNPairsFailed = 0;
   mEEPairProb[0] = 0.0001;
   mEEPairProb[1] = 1.;
   mDecayLength[0] = 3.;
   mDecayLength[1] = 30.;
   mDXY = 3.;
   mDZ = 2.;
   mInvM = 0.08;
   mDeltaDipAngle = 0.08;
}

eeKillPairCut::eeKillPairCut(const eeKillPairCut& c) : StHbtPairCut(c) {
#ifdef STHBTDEBUG
   cout << " eeKillPairCut::eeKillPairCut(const eeKillPairCut& c) " << endl;
#endif
   mNPairsPassed = mNPairsFailed = 0;
   mEEPairProb[0] = c.mEEPairProb[0];
   mEEPairProb[1] = c.mEEPairProb[1];
   mDecayLength[0] = c.mDecayLength[0];
   mDecayLength[1] = c.mDecayLength[1];
   mDXY = c.mDXY;
   mDZ = c.mDZ;
   mInvM = c.mInvM;
   mDeltaDipAngle = c.mDeltaDipAngle;
}

string eeKillPairCut::Report() {
   string Stemp = "eeKillPairCut\n";
   char Ctemp[100];
   sprintf(Ctemp, "Number of pairs which passed: %ld, failed: %ld\n", mNPairsPassed, mNPairsFailed);
   Stemp += Ctemp;
   return Stemp;
}

string eeKillPairCut::StrReport() {
   string Stemp = "eeKillPairCut\n";
   char Ctemp[100];
   sprintf(Ctemp, "ElectronPairProb[0]: %E\n", mEEPairProb[0]);
   Stemp += Ctemp;
   sprintf(Ctemp, "ElectronPairProb[1]: %E\n", mEEPairProb[1]);
   Stemp += Ctemp;
   sprintf(Ctemp, "Delta Theta: %E\n", mDeltaDipAngle);
   Stemp += Ctemp;
   sprintf(Ctemp, "DXY: %E\n", mDXY);
   Stemp += Ctemp;
   sprintf(Ctemp, "DZ: %E\n", mDZ);
   Stemp += Ctemp;
   sprintf(Ctemp, "DecayLength: %E -- %E\n", mDecayLength[0], mDecayLength[1]);
   Stemp += Ctemp;
   sprintf(Ctemp, "InvariantMass: %E", mInvM);
   Stemp += Ctemp;
   return Stemp;
}
