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

#ifndef PairNtuple_hh
#define PairNtuple_hh

#include <TNtuple.h>

#include "StHbtMaker/Base/StHbtCorrFctn.hh"
class StHbtThPair;
#include "StHbtMaker/Infrastructure/StHbtTypes.hh"

class PairNtuple : public StHbtCorrFctn {
  public:
   PairNtuple(char* title, double aKStarMin, double aKStarMax, int aKStarBins, double aBinMax, double aKStarNormMin,
              double aKStarNormMax);
   virtual ~PairNtuple();

   virtual StHbtString Report();
   virtual void AddRealPair(const StHbtPair*);
   virtual void AddMixedPair(const StHbtPair*);

   virtual void Finish();
   virtual void Write();
   virtual void SetKStarRange(double, double);
   virtual void SetKStarNormRange(double, double);
   virtual void SetKStarBins(int);
   virtual void SetKStarBinMax(double);

  protected:
   TNtuple* mPairNtuple;
   TH1D* mBinCounts;

   StHbtThPair* mThPair;  //!
   double mKStarMin;
   double mKStarMax;
   int mKStarBins;
   double mBinMax;
   double mKStarNormMin;
   double mKStarNormMax;
   double mNormCount;

#ifdef __ROOT__
   ClassDef(PairNtuple, 1)
#endif
};

#endif
