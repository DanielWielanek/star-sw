/***************************************************************************
 *
 * $Id: PairNtuple.cxx,v 1.4 2000/01/25 17:34:45 laue Exp $
 *
 * Author: Mike Lisa, Ohio State, lisa@mps.ohio-state.edu
 ***************************************************************************
 *
 * Description: part of STAR HBT Framework: StHbtMaker package
 *   a simple Q-invariant correlation function
 *
 ***************************************************************************
 *
 * $Log: PairNtuple.cxx,v $
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

#include "StHbtMaker/CorrFctn/PairNtuple.h"

#include <cstdio>

#include "StHbtMaker/Base/StHbtThPair.hh"
#include "StHbtMaker/Infrastructure/StHbtPair.hh"
//#include <strstream.h>
#ifdef __ROOT__
ClassImp(PairNtuple)
#endif

    //____________________________
    PairNtuple::PairNtuple(char* title, double aKStarMin = 0.0, double aKStarMax = 0.2, int aKStarBins = 40,
                           double aBinMax = 30000, double aKStarNormMin = 0.3, double aKStarNormMax = 0.4)
    : mKStarMin(aKStarMin),
      mKStarMax(aKStarMax),
      mKStarBins(aKStarBins),
      mBinMax(aBinMax),
      mKStarNormMin(aKStarNormMin),
      mKStarNormMax(aKStarNormMax),
      mNormCount(0) {
   //   mPairNtuple = new TNtuple("pair", title, "e1:e2:px1:px2:py1:py2:pz1:pz2");
   mPairNtuple = new TNtuple(title, title, "e1:e2:px1:px2:py1:py2:pz1:pz2");
   mBinCounts = new TH1D("bincounts", "bincounts", mKStarBins, mKStarMin, mKStarMax);
}

//____________________________
PairNtuple::~PairNtuple() { delete mPairNtuple; }
//_________________________
void PairNtuple::Finish() {}

void PairNtuple::Write() { mPairNtuple->Write(); }

//____________________________
StHbtString PairNtuple::Report() {
   string stemp = "Pair Ntuple writer : nothing to say\n";
   StHbtString returnThis = stemp;
   return returnThis;
}

//____________________________
void PairNtuple::AddRealPair(const StHbtPair* aPair) {}

//____________________________
void PairNtuple::AddMixedPair(const StHbtPair* aPair) {
   if ((aPair->KStar() < mKStarMax) && (aPair->KStar() > mKStarMin)) {
      if (mBinCounts->GetBinContent(mBinCounts->GetXaxis()->FindFixBin(aPair->KStar())) < mBinMax) {
         mPairNtuple->Fill(aPair->track1()->FourMomentum().e(), aPair->track2()->FourMomentum().e(),
                           aPair->track1()->FourMomentum().x(), aPair->track2()->FourMomentum().x(),
                           aPair->track1()->FourMomentum().y(), aPair->track2()->FourMomentum().y(),
                           aPair->track1()->FourMomentum().z(), aPair->track2()->FourMomentum().z());
         mBinCounts->Fill(aPair->KStar());
      }
   } else if ((aPair->KStar() < mKStarNormMax) && (aPair->KStar() > mKStarNormMin)) {
      if (mNormCount < mBinMax) {
         mPairNtuple->Fill(aPair->track1()->FourMomentum().e(), aPair->track2()->FourMomentum().e(),
                           aPair->track1()->FourMomentum().x(), aPair->track2()->FourMomentum().x(),
                           aPair->track1()->FourMomentum().y(), aPair->track2()->FourMomentum().y(),
                           aPair->track1()->FourMomentum().z(), aPair->track2()->FourMomentum().z());
         mNormCount++;
      }
   }
}

void PairNtuple::SetKStarRange(double aKStarMin, double aKStarMax) {
   mKStarMin = aKStarMin;
   mKStarMax = aKStarMax;
   if (mBinCounts) delete mBinCounts;
   mBinCounts = new TH1D("bincounts", "bincounts", mKStarBins, mKStarMin, mKStarMax);
}

void PairNtuple::SetKStarNormRange(double aKStarNormMin, double aKStarNormMax) {
   mKStarNormMin = aKStarNormMin;
   mKStarNormMax = aKStarNormMax;
   mNormCount = 0;
}

void PairNtuple::SetKStarBins(int aKStarBins) {
   mKStarBins = aKStarBins;
   if (mBinCounts) delete mBinCounts;
   mBinCounts = new TH1D("bincounts", "bincounts", mKStarBins, mKStarMin, mKStarMax);
}

void PairNtuple::SetKStarBinMax(double aBinMax) { mBinMax = aBinMax; }
