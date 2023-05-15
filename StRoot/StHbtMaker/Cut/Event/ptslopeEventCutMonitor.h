/***************************************************************************
 *
 * $Id: ptslopeEventCutMonitor.h,v 1.2 2003/02/02 23:50:43 magestro Exp $
 *
 * Author: Mercedes Lopez Noriega , Ohio State, mercedes@pacific.mps.ohio-state.edu
 *
 ***************************************************************************
 *
 * Event Cut Monitor that plots just the tracks that passed
 * mercedesStarStandardEventCut in the multiplicity plot
 * Plots: EventMultiplicity (just # of tracks that passed the event cut),
 * ZVertexPosition, and 2D plot: EventMultiplicity vs Tracks (# of tracks that
 * passed the cuts vs # of tracks in the event)
 *
 ***************************************************************************
 *
 * $Log: ptslopeEventCutMonitor.h,v $
 * Revision 1.2  2003/02/02 23:50:43  magestro
 * Added dummy Fill() functions to take care of compiler warning related to overloaded virtual functions
 *
 * Revision 1.1  2002/04/09 15:14:34  mercedes
 * Event Cut Monitor for mercedesStarStandardEventCut
 *
 *
 **************************************************************************/

#ifndef ptslopeEventCutMonitor_hh
#define ptslopeEventCutMonitor_hh

#include "StHbtMaker/Base/StHbtCutMonitor.hh"
#include "StHbtMaker/Infrastructure/StHbtEvent.hh"
#include "StHbtMaker/Infrastructure/StHbtTypes.hh"
#include "TF1.h"

class ptslopeEventCutMonitor : public StHbtCutMonitor {
  private:
   StHbt1IHisto* mMtSlope1;
   StHbt1IHisto* mMtSlope2;
   StHbt1IHisto* mMeanPt1;
   StHbt1IHisto* mMeanPt2;

   StHbt2IHisto* mMtvsPt1;
   StHbt2IHisto* mMtvsPt2;
   StHbt2IHisto* mMt1vsMt2;
   StHbt2IHisto* mPt1vsPt2;

   StHbt2IHisto* mMultvsMt1;
   StHbt2IHisto* mMultvsMt2;
   StHbt2IHisto* mMultvsPt1;
   StHbt2IHisto* mMultvsPt2;

   StHbt1IHisto* mMtDist1;
   StHbt1IHisto* mMtDist2;
   TF1* mMtFun;

   StHbt1IHisto* mOverallMeanPt;

   int pid1, pid2;
   double mass1, mass2;

   double probpi1, probk1, probp1, probe1;
   double probpi2, probk2, probp2, probe2;
   double ptmin1, ptmax1;
   double ptmin2, ptmax2;
   double mtmin1, mtmax1;
   double mtmin2, mtmax2;

  public:
   ptslopeEventCutMonitor();
   ptslopeEventCutMonitor(int pid1, int pid2, char* suff);
   virtual ~ptslopeEventCutMonitor();

   virtual StHbtString Report();
   virtual void Fill(const StHbtEvent* event);
   virtual void Finish();

   // These dummy Fill() functions were introduced to remove a compiler
   //   warning related to overloaded base-class Fill() functions being
   //   hidden by a single version of Fill() in this derived class
   void Fill(const StHbtParticleCollection* d) { ; }
   void Fill(const StHbtEvent* d1, const StHbtParticleCollection* d2) { ; }
   void Fill(const StHbtPair* d) { ; }
   void Fill(const StHbtKink* d) { ; }
   void Fill(const StHbtV0* d) { ; }
   void Fill(const StHbtTrack* d) { ; }

   void Write();

#ifdef __ROOT__
   ClassDef(ptslopeEventCutMonitor, 1)
#endif
};

#endif
