/***************************************************************************
 *
 * $Id: picoEventCutMonitor.h,v 1.2 2003/02/02 23:50:43 magestro Exp $
 *
 * Author: Mercedes Lopez Noriega , Ohio State, pico@pacific.mps.ohio-state.edu
 *
 ***************************************************************************
 *
 * Event Cut Monitor that plots just the tracks that passed
 * picoStarStandardEventCut in the multiplicity plot
 * Plots: EventMultiplicity (just # of tracks that passed the event cut),
 * ZVertexPosition, and 2D plot: EventMultiplicity vs Tracks (# of tracks that
 * passed the cuts vs # of tracks in the event)
 *
 ***************************************************************************
 *
 * $Log: picoEventCutMonitor.h,v $
 * Revision 1.2  2003/02/02 23:50:43  magestro
 * Added dummy Fill() functions to take care of compiler warning related to overloaded virtual functions
 *
 * Revision 1.1  2002/04/09 15:14:34  pico
 * Event Cut Monitor for picoStarStandardEventCut
 *
 *
 **************************************************************************/

#ifndef picoEventCutMonitor_hh
#define picoEventCutMonitor_hh

#include "StHbtMaker/Base/StHbtCutMonitor.hh"
#include "StHbtMaker/Infrastructure/StHbtEvent.hh"
#include "StHbtMaker/Infrastructure/StHbtTypes.hh"

class picoEventCutMonitor : public StHbtCutMonitor {
  public:
   picoEventCutMonitor(bool bPass = true);
   ~picoEventCutMonitor();

   StHbtString Report() { return "picoEventCutMonitor has nothing to report"; }
   void Fill(const StHbtEvent* event) {
      if (mEventMultHisto && mZVertexPosHisto) {
         double VertexZPos = event->PrimVertPos().z();
         int mult = event->UncorrectedNumberOfPrimaries();
         mEventMultHisto->Fill(mult);
         mZVertexPosHisto->Fill(VertexZPos);
      }
   }

   void Finish();

   // These dummy Fill() functions were introduced to remove a compiler
   //   warning related to overloaded base-class Fill() functions being
   //   hidden by a single version of Fill() in this derived class
   void Fill(const StHbtParticleCollection* d) {}
   void Fill(const StHbtEvent* d1, const StHbtParticleCollection* d2) {}
   void Fill(const StHbtPair* d) {}
   void Fill(const StHbtKink* d) {}
   void Fill(const StHbtV0* d) {}
   void Fill(const StHbtTrack* d) {}

   StHbt1IHisto* EventMultHisto() { return mEventMultHisto; }
   StHbt1IHisto* ZVertexPosHisto() { return mZVertexPosHisto; }

  private:
   picoEventCutMonitor(const picoEventCutMonitor&) {}
   picoEventCutMonitor& operator=(const picoEventCutMonitor&) { return *this; }
   StHbt1IHisto* mEventMultHisto;
   StHbt1IHisto* mZVertexPosHisto;

#ifdef __ROOT__
   ClassDef(picoEventCutMonitor, 1)
#endif
};

#endif
