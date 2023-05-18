/***************************************************************************
 *
 * $Id: StHbtMultMeanPtAnalysisMB.h,v 1.4 2004/04/12 14:05:46 magestro Exp $
 *
 * Author: Randall Wells, Ohio State, rcwells@mps.ohio-state.edu
 ***************************************************************************
 *
 * Description: part of STAR HBT Framework: StHbtMaker package
 *      This is the Class for Analysis objects.  Each of the simultaneous
 *      Analyses running should have one of these instantiated.  They link
 *      into the Manager in an Analysis Collection.
 *
 ***************************************************************************
 *
 * $Log: StHbtMultMeanPtAnalysisMB.h,v $
 * Revision 1.4  2004/04/12 14:05:46  magestro
 * Added Vz dimension to event-mixing
 *
 * Revision 1.2  2002/05/28 14:04:07  rcwells
 * Added multiplicity binning to StHbtMultMeanPtAnalysisMB
 *
 * Revision 1.1  2001/07/13 20:03:14  rcwells
 * Adding reaction plane analysis
 *
 *
 **************************************************************************/

#ifndef StHbtMultMeanPtAnalysisMB_hh
#define StHbtMultMeanPtAnalysisMB_hh

#include <TH3I.h>

#include "StHbtMaker/Infrastructure/StHbtAnalysis.h"  // base analysis class

class StHbtPicoEventCollectionVectorHideAway;

class StHbtMultMeanPtAnalysisMB : public StHbtAnalysis {
  public:
   StHbtMultMeanPtAnalysisMB(unsigned int nBinMeanPt = 1, double MPtLo = 0.0, double MPtHi = +2.0,
                             unsigned int nBinsMult = 1, double multLo = 0, double multHi = 999999,
                             unsigned int nBinsVert = 1, double vertLo = -1000, double vertHi = 1000);
   StHbtMultMeanPtAnalysisMB(const StHbtMultMeanPtAnalysisMB &);  // copy constructor
   virtual void ProcessEvent(const StHbtEvent *);
   virtual ~StHbtMultMeanPtAnalysisMB();
   virtual StHbtString Report();  //! returns reports of all cuts applied and correlation functions being done
   virtual unsigned int Overflow() { return mOverFlow; }
   virtual unsigned int Underflow() { return mUnderFlow; }
   double MeanPt();
   double VertexZ();
   void BufFillMonitorWrite();
   void BufFillMonitorSetName(const char *);
   void SetMultBinBoundaries(int aNBins, double *aBinBounds);
   void SetMeanPtBinBoundaries(int aNBins, double *aBinBounds);
   void MakePairs(const char *typeIn, StHbtParticleCollection *partCollection1,
                  StHbtParticleCollection *partCollection2, int nbin);

  protected:
   double mVertexZ;
   unsigned int mMult;
   unsigned int mOverFlow;
   unsigned int mUnderFlow;
   unsigned int mMultTable[100];
   double mMeanPtTable[100];
   unsigned int mMultTableSize;
   unsigned int mMeanPtTableSize;
   TH3I *mBufFill;
   int mNBin;
   int mNBinsVertex;
   double mVertexZMin;
   double mVertBinSize;

#ifdef __ROOT__
   ClassDef(StHbtMultMeanPtAnalysisMB, 0)
#endif
};

#endif
