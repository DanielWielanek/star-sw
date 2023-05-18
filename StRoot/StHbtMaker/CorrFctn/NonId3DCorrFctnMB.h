/***************************************************************************
 *
 * $Id: NonId3DCorrFctnMB.h,v 1.2 2000/01/25 17:34:45 laue Exp $
 *
 * Author: Mike Lisa, Ohio State, lisa@mps.ohio-state.edu
 ***************************************************************************
 *
 * Description: part of STAR HBT Framework: StHbtMaker package
 *   a simple Q-invariant correlation function
 *
 ***************************************************************************
 *
 * $Log: NonId3DCorrFctnMB.h,v $
 * Revision 1.2  2000/01/25 17:34:45  laue
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
 * Revision 1.1  1999/09/23 23:28:02  lisa
 * add helensV0Cut  AND  rename mikes and franks ParticleCuts to TrackCuts  AND  update documentation
 *
 * Revision 1.2  1999/07/06 22:33:20  lisa
 * Adjusted all to work in pro and new - dev itself is broken
 *
 * Revision 1.1.1.1  1999/06/29 16:02:57  lisa
 * Installation of StHbtMaker
 *
 **************************************************************************/

#ifndef NonId3DCorrFctnMB_hh
#define NonId3DCorrFctnMB_hh

#include "StHbtMaker/Base/StHbtCorrFctn.hh"

class NonId3DCorrFctnMB : public StHbtCorrFctn {
  public:
   NonId3DCorrFctnMB(char* title, const int& nbins, const float& QinvLo, const float& QinvHi, int nmixbins);
   NonId3DCorrFctnMB(char* title, const int& nbins, const float& QinvLo, const float& QinvHi, const int mqSideSel,
                     int nmixbins);
   NonId3DCorrFctnMB(char* title, const int& nbins, const float& QinvLo, const float& QinvHi, const float KCompCut,
                     int nmixbins);
   virtual ~NonId3DCorrFctnMB();

   virtual void makeHistos(char* title, const int& nbins, const float& QinvLo, const float& QinvHi, int nmixbins);

   virtual StHbtString Report();
   virtual void AddRealPair(const StHbtPair*);
   virtual void AddMixedPair(const StHbtPair*);
   void AddMixedPairMB(const StHbtPair*, int nbins);
   void AddRealPairMB(const StHbtPair*, int nbins);

   virtual void Finish();
   virtual void Write();

  private:
   StHbt1IHisto** mNumOutP;
   StHbt1IHisto** mDenOutP;
   StHbt1IHisto** mNumOutN;
   StHbt1IHisto** mDenOutN;

   StHbt1IHisto* mNumOutPSum;
   StHbt1IHisto* mDenOutPSum;
   StHbt1IHisto* mNumOutNSum;
   StHbt1IHisto* mDenOutNSum;

   StHbt1IHisto** mNumSideP;
   StHbt1IHisto** mDenSideP;
   StHbt1IHisto** mNumSideN;
   StHbt1IHisto** mDenSideN;

   StHbt1IHisto* mNumSidePSum;
   StHbt1IHisto* mDenSidePSum;
   StHbt1IHisto* mNumSideNSum;
   StHbt1IHisto* mDenSideNSum;

   StHbt1IHisto** mNumLongP;
   StHbt1IHisto** mDenLongP;
   StHbt1IHisto** mNumLongN;
   StHbt1IHisto** mDenLongN;

   StHbt1IHisto* mNumLongPSum;
   StHbt1IHisto* mDenLongPSum;
   StHbt1IHisto* mNumLongNSum;
   StHbt1IHisto* mDenLongNSum;

   StHbt2IHisto* mHOutKSame;
   StHbt2IHisto* mHOutKDiff;
   StHbt2IHisto* mHSideKSame;
   StHbt2IHisto* mHSideKDiff;
   StHbt2IHisto* mHLongKSame;
   StHbt2IHisto* mHLongKDiff;

   StHbt2IHisto* mHKStarRap1OutNum;
   StHbt2IHisto* mHKStarRap2OutNum;

   StHbt2IHisto* mHKStarRap1OutDen;
   StHbt2IHisto* mHKStarRap2OutDen;

   StHbt2IHisto* mHKStarPhi1OutNum;
   StHbt2IHisto* mHKStarPhi2OutNum;

   StHbt2IHisto* mHKStarPhi1OutDen;
   StHbt2IHisto* mHKStarPhi2OutDen;

   StHbt2IHisto* mHPt1KStarOutNum;
   StHbt2IHisto* mHPt1KStarOutDen;
   StHbt2IHisto* mHPt2KStarOutNum;
   StHbt2IHisto* mHPt2KStarOutDen;

   StHbt2IHisto* mHPt1KStarSideNum;
   StHbt2IHisto* mHPt1KStarSideDen;
   StHbt2IHisto* mHPt2KStarSideNum;
   StHbt2IHisto* mHPt2KStarSideDen;

   int mqSideSel;
   float mKCompCut;
   int NBins;

#ifdef __ROOT__
   ClassDef(NonId3DCorrFctnMB, 1)
#endif
};

#endif
