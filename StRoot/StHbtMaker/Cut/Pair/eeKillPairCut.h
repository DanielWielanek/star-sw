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

#ifndef eeKillPairCut_hh
#define eeKillPairCut_hh

class StHbtPair;
#include "StHbtMaker/Base/StHbtPairCut.h"

class eeKillPairCut : public StHbtPairCut {
  public:
   eeKillPairCut();
   eeKillPairCut(const eeKillPairCut&);

   bool Pass(const StHbtPair*);
   void SetEEPairProbLow(double);
   void SetEEPairProbHigh(double);
   void SetEEPairSigmaProb(double);
   void SetDXY(double);
   void SetDZ(double);
   void SetDecayLength(double, double);
   void SetInvariantMass(double);
   void SetDeltaDipAngle(double);

   eeKillPairCut* Clone();

   string Report();
   string StrReport();
   double GetMinvEE(const StHbtPair* aPair);

  private:
   bool leave(bool);
   double mEEPairProb[2];
   double mDecayLength[2];
   double mEEPairSigmaProb;
   double mDXY;
   double mDZ;
   double mInvM;
   double mDeltaDipAngle;
   long mNPairsPassed;
   long mNPairsFailed;

#ifdef __ROOT__
   ClassDef(eeKillPairCut, 1)
#endif
};

inline void eeKillPairCut::SetEEPairProbLow(double x) { mEEPairProb[0] = x; }
inline void eeKillPairCut::SetEEPairProbHigh(double x) { mEEPairProb[1] = x; }
inline void eeKillPairCut::SetEEPairSigmaProb(double x) { mEEPairSigmaProb = x; }
inline void eeKillPairCut::SetDecayLength(double x, double y) {
   mDecayLength[0] = x;
   mDecayLength[1] = y;
}
inline void eeKillPairCut::SetDXY(double x) { mDXY = x; }
inline void eeKillPairCut::SetDZ(double x) { mDZ = x; }
inline void eeKillPairCut::SetInvariantMass(double x) { mInvM = x; }
inline void eeKillPairCut::SetDeltaDipAngle(double x) { mDeltaDipAngle = x; }

inline eeKillPairCut* eeKillPairCut::Clone() {
   eeKillPairCut* c = new eeKillPairCut(*this);
   return c;
}

inline bool eeKillPairCut::Pass(const StHbtPair* pair) {
   if (pair->track1()->TrackId() == pair->track2()->TrackId()) return leave(false);

   if (pair->getGammaEESol_getMinvEE() > mInvM) return leave(true);

   double esgm1 = 1 - TMath::Erf(fabs(pair->track1()->Track()->NSigmaElectron()) / 1.414213562373095);
   double esgm2 = 1 - TMath::Erf(fabs(pair->track2()->Track()->NSigmaElectron()) / 1.414213562373095);  // sqrt(2.)
   if (esgm1 * esgm2 < mEEPairSigmaProb) {
      return leave(true);
   }
   if (TMath::Abs(pair->track1()->Track()->HelixGlobal().dipAngle() -
                  pair->track2()->Track()->HelixGlobal().dipAngle()) > mDeltaDipAngle)
      return leave(true);

   if (!(pair->getGammaEESol_getNSols())) return leave(true);

   if ((pair->getGammaEESol_getR() < mDecayLength[0]) || ((pair->getGammaEESol_getR() > mDecayLength[1])))
      return leave(true);

   if (pair->getGammaEESol_getDXY() > mDXY) return leave(true);

   if (pair->getGammaEESol_getDZ() > mDZ) return leave(true);
   return leave(false);
}

//__________________
inline bool eeKillPairCut::leave(bool b) {
   b ? mNPairsPassed++ : mNPairsFailed++;
   return b;
}

#endif
