/***************************************************************************
 *
 * $Id: adamsPairCut.h,v 1.1 2001/12/14 23:11:27 fretiere Exp $
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

#ifndef adamsPairCut_hh
#define adamsPairCut_hh

// do I need these lines ?
//#ifndef StMaker_H
//#include "StMaker.h"
//#endif

#include <sstream>

#include "StHbtMaker/Cut/HitMergingPairCut.h"
// class ostrstream;

class adamsPairCut : public HitMergingPairCut {
  public:
   adamsPairCut();
   adamsPairCut(const adamsPairCut&);
   //~adamsPairCut();

   virtual bool Pass(const StHbtPair*);
   virtual StHbtString Report();
   adamsPairCut* Clone();
   void setElSigma(double aElSigma);
   void setPiSigma(double aPiSigma);
   void setKSigma(double aKSigma);
   void setPSigma(double aPSigma);
   void setElPairPIDMax(double aElPIDMax);
   void setPiPairPIDMax(double aPiPIDMax);
   void setKPairPIDMax(double aKPIDMax);
   void setPPairPIDMax(double aPPIDMax);
   void SetPIDPThreshold(const float&);
   void setAbsDipAngleDifferenceMin(double aDipMin);
   std::ostringstream* finalReport() const;
   void setDipElPIDMax(double aDipElPIDMax);

   // The convention to set PID boundaries:
   //  0 - ee
   //  1 - e pi   2 - pi pi
   //  3 - e k    4 - pi k   5 - k k
   //  6 - e p    7 - pi p   8 - k p   9 - p p
   void setLowerPidValues(double* aPidLower);
   void setUpperPidValues(double* aPidUpper);

  private:
   double mElSigma;
   double mPiSigma;
   double mKSigma;
   double mPSigma;

   double mElPIDMax;
   double mPiPIDMax;
   double mKPIDMax;
   double mPPIDMax;

   double mDipMin;
   double mDipElPIDMax;

   double mPIDLower[10];
   double mPIDUpper[10];

   float mPIDPThreshold;
#ifdef __ROOT__
   ClassDef(adamsPairCut, 1)
#endif
};

inline adamsPairCut::adamsPairCut(const adamsPairCut& c) : HitMergingPairCut(c) {
   mNPairsPassed = 0;
   mNPairsFailed = 0;
}
inline adamsPairCut* adamsPairCut::Clone() {
   adamsPairCut* c = new adamsPairCut(*this);
   return c;
}

inline void adamsPairCut::setElSigma(double aElSigma) { mElSigma = aElSigma; }
inline void adamsPairCut::setPiSigma(double aPiSigma) { mPiSigma = aPiSigma; }
inline void adamsPairCut::setKSigma(double aKSigma) { mKSigma = aKSigma; }
inline void adamsPairCut::setPSigma(double aPSigma) { mPSigma = aPSigma; }
inline void adamsPairCut::setElPairPIDMax(double aElPIDMax) { mElPIDMax = aElPIDMax; }
inline void adamsPairCut::setPiPairPIDMax(double aPiPIDMax) { mPiPIDMax = aPiPIDMax; }
inline void adamsPairCut::setKPairPIDMax(double aKPIDMax) { mKPIDMax = aKPIDMax; }
inline void adamsPairCut::setPPairPIDMax(double aPPIDMax) { mPPIDMax = aPPIDMax; }
inline void adamsPairCut::setAbsDipAngleDifferenceMin(double aDipMin) { mDipMin = aDipMin; }
inline void adamsPairCut::setDipElPIDMax(double aDipElPIDMax) { mDipElPIDMax = aDipElPIDMax; }
inline void adamsPairCut::SetPIDPThreshold(const float& pidpt) { mPIDPThreshold = pidpt; }

#endif
