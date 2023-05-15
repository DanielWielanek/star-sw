/***************************************************************************
 *
 * $Id: picoAdamsPairCut.h,v 1.1 2001/12/14 23:11:27 fretiere Exp $
 *
 * Author: KAdam Kisiel, Warsaw University of Technoogy, kisiel@if.pw.edu.pl
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

#ifndef picoAdamsPairCut_hh
#define picoAdamsPairCut_hh

// do I need these lines ?
//#ifndef StMaker_H
//#include "StMaker.h"
//#endif

#include "StHbtMaker/Cut/HitMergingPairCut.h"
class ostrstream;

class picoAdamsPairCut : public HitMergingPairCut {
  public:
   picoAdamsPairCut();

   bool Pass(const StHbtPair*);
   string Report();
   string StrReport();
   picoAdamsPairCut* Clone();
   void setElSigma(double aElSigma);
   void setPiSigma(double aPiSigma);
   void setKSigma(double aKSigma);
   void setPSigma(double aPSigma);

  private:
   picoAdamsPairCut(const picoAdamsPairCut&);
   double mElSigma;
   double mPiSigma;
   double mKSigma;
   double mPSigma;

#ifdef __ROOT__
   ClassDef(picoAdamsPairCut, 1)
#endif
};

inline picoAdamsPairCut* picoAdamsPairCut::Clone() {
   picoAdamsPairCut* c = new picoAdamsPairCut(*this);
   return c;
}

inline void picoAdamsPairCut::setElSigma(double aElSigma) { mElSigma = aElSigma; }
inline void picoAdamsPairCut::setPiSigma(double aPiSigma) { mPiSigma = aPiSigma; }
inline void picoAdamsPairCut::setKSigma(double aKSigma) { mKSigma = aKSigma; }
inline void picoAdamsPairCut::setPSigma(double aPSigma) { mPSigma = aPSigma; }

inline bool picoAdamsPairCut::Pass(const StHbtPair* pair) {
   bool temp = (pair->track1()->TrackId() != pair->track2()->TrackId());
   if (!temp) {
      ++mNPairsFailed;
      return false;
   }
   bool is1El = (TMath::Abs(pair->track1()->Track()->NSigmaElectron()) < mElSigma);
   bool is1Pi = (TMath::Abs(pair->track1()->Track()->NSigmaPion()) < mPiSigma);
   bool is1K = (TMath::Abs(pair->track1()->Track()->NSigmaKaon()) < mKSigma);
   bool is1P = (TMath::Abs(pair->track1()->Track()->NSigmaProton()) < mPSigma);
   bool isElPair = is1El && (TMath::Abs(pair->track2()->Track()->NSigmaElectron()) < mElSigma);
   bool isPiPair = is1Pi && (TMath::Abs(pair->track2()->Track()->NSigmaPion()) < mPiSigma);
   bool isKPair = is1K && (TMath::Abs(pair->track2()->Track()->NSigmaKaon()) < mKSigma);
   bool isPPair = is1P && (TMath::Abs(pair->track2()->Track()->NSigmaProton()) < mPSigma);
   temp = (!isElPair) && (!isPiPair) && (!isKPair) && (!isPPair);
   if (!temp) {
      ++mNPairsFailed;
      return false;
   }
   temp = pair->getFracOfMergedRow() < mMaxFracPair;
   temp ? ++mNPairsPassed : ++mNPairsFailed;
   return temp;
}

#endif
