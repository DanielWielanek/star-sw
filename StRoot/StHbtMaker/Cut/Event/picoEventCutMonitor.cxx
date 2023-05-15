/***************************************************************************
 *
 * $Id: picoEventCutMonitor.cxx,v 1.3 2003/01/22 16:05:11 pico Exp $
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
 * $Log: picoEventCutMonitor.cxx,v $
 * Revision 1.3  2003/01/22 16:05:11  pico
 * Minor changes
 *
 * Revision 1.2  2003/01/17 16:47:31  pico
 * Updated to get reference multiplicity
 *
 * Revision 1.1  2002/04/09 15:14:46  pico
 * Event Cut Monitor for picoStarStandardEventCut
 *
 *
 **************************************************************************/

#include "StHbtMaker/Cut/Event/picoEventCutMonitor.h"

#include <cstdio>

#include "StHbtMaker/Infrastructure/StHbtEvent.hh"
#include "StHbtMaker/Infrastructure/StHbtTypes.hh"

#ifdef __ROOT__
ClassImp(picoEventCutMonitor)
#endif

    picoEventCutMonitor::picoEventCutMonitor(bool bPass) {
   if (bPass == true) {
      mEventMultHisto = new StHbt1IHisto("EventMultHisto", "Event Multiplicity", 1000, 0., 1000.);
      mEventMultHisto->SetDirectory(0);
      mZVertexPosHisto = new StHbt1IHisto("ZVertexPos", "zVertex Position", 60, -30.0, 30.0);
      mZVertexPosHisto->SetDirectory(0);
   } else {
      mEventMultHisto = NULL;
      mZVertexPosHisto = NULL;
   }
}
//------------------------------
picoEventCutMonitor::~picoEventCutMonitor() {
   delete mEventMultHisto;
   delete mZVertexPosHisto;
}

//------------------------------
void picoEventCutMonitor::Finish() {
   if (mEventMultHisto) cout << " entries in Multiplicity  histogram : " << mEventMultHisto->Integral() << endl;
   if (mZVertexPosHisto) cout << " entries in Vertex Pos.  histogram : " << mZVertexPosHisto->Integral() << endl;
}
