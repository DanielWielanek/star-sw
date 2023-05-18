/***************************************************************************
 *
 * $Id: PairNtuple2.cxx,v 1.4 2000/01/25 17:34:45 laue Exp $
 *
 * Author: Mike Lisa, Ohio State, lisa@mps.ohio-state.edu
 ***************************************************************************
 *
 * Description: part of STAR HBT Framework: StHbtMaker package
 *   a simple Q-invariant correlation function
 *
 ***************************************************************************
 *
 * $Log: PairNtuple2.cxx,v $
 * Revision 1.4  2000/01/25 17:34:45  laue
 * I. In order to run the stand alone version of the StHbtMaker the following
 * changes have been done:
 * a) all ClassDefs and ClassImps have been put into #ifdef __ROOT__ statements
 * b) unnecessary includes of StMaker.h have been removed
 * c) the subdirectory StHbtMaker/doc/Make has been created including everything
 * needed for the stand alone version
 *
 * II. To reduce the amount of compiler warning
 * a) some variables have been type casted
 * b) some destructors have been declared as virtual
 *
 * Revision 1.3  1999/07/29 02:47:09  lisa
 * 1) add OpeningAngle correlation function 2) add StHbtMcEventReader 3) make histos in CorrFctns do errors correctly
 *
 * Revision 1.2  1999/07/06 22:33:20  lisa
 * Adjusted all to work in pro and new - dev itself is broken
 *
 * Revision 1.1.1.1  1999/06/29 16:02:57  lisa
 * Installation of StHbtMaker
 *
 **************************************************************************/

#include "StHbtMaker/CorrFctn/PairNtuple2.h"

#include <cstdio>

#include "StHbtMaker/Base/StHbtThPair.hh"
#include "StHbtMaker/Infrastructure/StHbtPair.hh"
//#include <strstream.h>
#ifdef __ROOT__
ClassImp(PairNtuple2)
#endif

    //____________________________
    PairNtuple2::PairNtuple2(char* title, double aKStarMin = 0.0, double aKStarMax = 0.2, int aKStarBins = 40,
                             double aBinMax = 10000)
    : mKStarMin(aKStarMin), mKStarMax(aKStarMax), mKStarBins(aKStarBins), mBinMax(aBinMax) {
   mPairNtuple2 = new TNtuple(title, title, "px1:py1:pz1:e1:px2:py2:pz2:e2");
   mBinCounts = new TH1D("bincounts", "bincounts", mKStarBins, mKStarMin, mKStarMax);
}

//____________________________
PairNtuple2::~PairNtuple2() { delete mPairNtuple2; }
//_________________________
void PairNtuple2::Finish() {}

void PairNtuple2::Write() { mPairNtuple2->Write(); }

//____________________________
StHbtString PairNtuple2::Report() {
   string stemp = "Pair Ntuple writer : nothing to say\n";
   StHbtString returnThis = stemp;
   return returnThis;
}

//____________________________
void PairNtuple2::AddRealPair(const StHbtPair* aPair) {}

//____________________________
void PairNtuple2::AddMixedPair(const StHbtPair* aPair) {
   if ((aPair->KStar() < mKStarMax) && (aPair->KStar() > mKStarMin)) {
      if (mBinCounts->GetBinContent(mBinCounts->GetXaxis()->FindFixBin(aPair->KStar())) < mBinMax) {
         mPairNtuple2->Fill(aPair->track1()->FourMomentum().x(), aPair->track1()->FourMomentum().y(),
                            aPair->track1()->FourMomentum().z(), aPair->track1()->FourMomentum().e(),
                            aPair->track2()->FourMomentum().x(), aPair->track2()->FourMomentum().y(),
                            aPair->track2()->FourMomentum().z(), aPair->track2()->FourMomentum().e());
         mBinCounts->Fill(aPair->KStar());
      }
   }
}

void PairNtuple2::SetKStarRange(double aKStarMin, double aKStarMax) {
   mKStarMin = aKStarMin;
   mKStarMax = aKStarMax;
   delete mBinCounts;
   mBinCounts = new TH1D("bincounts", "bincounts", mKStarBins, mKStarMin, mKStarMax);
}

void PairNtuple2::SetKStarBins(int aKStarBins) {
   mKStarBins = aKStarBins;
   delete mBinCounts;
   mBinCounts = new TH1D("bincounts", "bincounts", mKStarBins, mKStarMin, mKStarMax);
}

void PairNtuple2::SetKStarBinMax(double aBinMax) { mBinMax = aBinMax; }
