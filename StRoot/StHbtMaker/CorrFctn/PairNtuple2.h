/***************************************************************************
 *
 *
 * Author: Adam Kisiel, Warsaw Univeristy of Technology, kisiel@if.pw.edu.pl
 ***************************************************************************
 *
 * Description: A correlation function that stores pairs that passes all the
 *   cuts in the format suitable for the CorrFit fitting program
 *
 ***************************************************************************
 *
 *
 **************************************************************************/

#ifndef PairNtuple2_hh
#define PairNtuple2_hh

#include <TNtuple.h>

#include "StHbtMaker/Base/StHbtCorrFctn.hh"
class StHbtThPair;
#include "StHbtMaker/Infrastructure/StHbtTypes.hh"

class PairNtuple2 : public StHbtCorrFctn {
  public:
   PairNtuple2(char* title, double aKStarMin, double aKStarMax, int aKStarBins, double aBinMax);

   virtual ~PairNtuple2();

   virtual StHbtString Report();
   virtual void AddRealPair(const StHbtPair*);
   virtual void AddMixedPair(const StHbtPair*);

   virtual void Finish();
   virtual void Write();
   virtual void SetKStarRange(double, double);
   virtual void SetKStarBins(int);
   virtual void SetKStarBinMax(double);

  protected:
   TNtuple* mPairNtuple2;
   TH1D* mBinCounts;

   StHbtThPair* mThPair;  //!
   double mKStarMin;
   double mKStarMax;
   int mKStarBins;
   double mBinMax;

#ifdef __ROOT__
   ClassDef(PairNtuple2, 1)
#endif
};

#endif
