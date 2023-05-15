/***************************************************************************
 *
 * $Id: mercedesEventCutMonitor.cxx,v 1.3 2003/01/22 16:05:11 mercedes Exp $
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
 * $Log: mercedesEventCutMonitor.cxx,v $
 * Revision 1.3  2003/01/22 16:05:11  mercedes
 * Minor changes
 *
 * Revision 1.2  2003/01/17 16:47:31  mercedes
 * Updated to get reference multiplicity
 *
 * Revision 1.1  2002/04/09 15:14:46  mercedes
 * Event Cut Monitor for mercedesStarStandardEventCut
 *
 *
 **************************************************************************/

#include "StHbtMaker/Cut/mercedesEventCutMonitor.h"

#include <cstdio>

#include "StHbtMaker/Infrastructure/StHbtEvent.hh"
#include "StHbtMaker/Infrastructure/StHbtTypes.hh"

#ifdef __ROOT__
ClassImp(mercedesEventCutMonitor)
#endif

    mercedesEventCutMonitor::mercedesEventCutMonitor()
    : mercedesEventCutMonitor(nullptr) {
}

mercedesEventCutMonitor::mercedesEventCutMonitor(TString *name) {
   TString prefix = "EventMultHisto";
   if (name == nullptr) name = new TString("mercedesEv");
   mEventMultHisto = new StHbt1DHisto((prefix + (*name)).Data(), "Event Multiplicity", 1000, 0., 1000.);
   mEventMultHisto->SetDirectory(0);
   prefix = "ZVertexPos";
   mZVertexPosHisto = new StHbt1DHisto((prefix + (*name)).Data(), "zVertex Position", 1000, -300.0, 300.0);
   mZVertexPosHisto->SetDirectory(0);
   prefix = "EventMultvsTracks";
   mEventMultvsTracks = new StHbt2DHisto((prefix + (*name)).Data(), "Event Multiplicity vs Total Tracks", 1000, 0.,
                                         1000., 1000, 0., 10000.0);
   mEventMultvsTracks->SetDirectory(0);
   prefix = "EtaAsymvsZVertex";
   mEtaAsymvsZVertex =
       new StHbt2DHisto((prefix + (*name)).Data(), "EtaAsym vs Z Vertex", 200, -100, 100., 200, -10., 10);
   mEtaAsymvsZVertex->SetDirectory(0);
   prefix = "RefMultvsTofMult";
   mRefMultvsTofMult =
       new StHbt2DHisto((prefix + (*name)).Data(), "RefMult vs TfMult", 1000, 0., 1000., 5000, 0., 5000.0);
   mRefMultvsTofMult->SetDirectory(0);
   prefix = "RefMultvsTofMatch";
   mRefMultvsTofMatch =
       new StHbt2DHisto((prefix + (*name)).Data(), "RefMult vs TofMatch", 1000, 0., 1000., 1000, 0., 1000.0);
   mRefMultvsTofMatch->SetDirectory(0);
   prefix = "VzminusVzVpd";
   mVzminusVzVpd = new StHbt1DHisto((prefix + (*name)).Data(), "zVertex Position zVertexVpd diff,", 1000, -70.0, 70.0);
   mVzminusVzVpd->SetDirectory(0);
}
//------------------------------
mercedesEventCutMonitor::~mercedesEventCutMonitor() {
   delete mEventMultHisto;
   delete mZVertexPosHisto;
   delete mEventMultvsTracks;
   delete mEtaAsymvsZVertex;
   delete mRefMultvsTofMult;
   delete mRefMultvsTofMatch;
   delete mVzminusVzVpd;
}

//------------------------------
void mercedesEventCutMonitor::Fill(const StHbtEvent *event) {
   double VertexZPos = event->PrimVertPos().z();
   int mult = event->UncorrectedNumberOfPrimaries();
   int tofMult = event->TofMultiplicity();
   double etaAsym = event->EtaAsymmetry();
   double VertexZPosVpd = event->PrimVertPosVpd();
   mEventMultHisto->Fill(mult, 1.);
   mZVertexPosHisto->Fill(VertexZPos, 1.);
   mEventMultvsTracks->Fill(mult, event->NumberOfTracks(), 1.);
   mEtaAsymvsZVertex->Fill(VertexZPos, etaAsym);
   mRefMultvsTofMult->Fill(mult, tofMult);
   mVzminusVzVpd->Fill(VertexZPos - VertexZPosVpd);

   StHbtTrackCollection *tracks = event->TrackCollection();
   int tofMatch = 0;
   for (StHbtTrackIterator it = tracks->begin(); it != tracks->end(); it++) {
      StHbtTrack *track = *it;
      if (fabs(track->P().pseudoRapidity()) < 0.5 && track->ToF_matchFlag() > 0) {
         ++tofMatch;
      }
   }
   mRefMultvsTofMatch->Fill(mult, tofMatch);
}

//------------------------------
void mercedesEventCutMonitor::Finish() {
   cout << " entries in Multiplicity  histogram : " << mEventMultHisto->Integral() << endl;
   cout << " entries in Vertex Pos.  histogram : " << mZVertexPosHisto->Integral() << endl;
}

//------------------------------
StHbtString mercedesEventCutMonitor::Report() {
   string Stemp;
   char Ctemp[100];
   sprintf(Ctemp, " mercedesEventCutMonitor");
   Stemp = Ctemp;
   StHbtString returnThis = Stemp;
   return returnThis;
}

void mercedesEventCutMonitor::AppendOutput(TList *output) const {
   output->Add(mEventMultHisto);
   output->Add(mZVertexPosHisto);
   output->Add(mEventMultvsTracks);
   output->Add(mEtaAsymvsZVertex);
   output->Add(mVzminusVzVpd);
   output->Add(mRefMultvsTofMult);
   output->Add(mRefMultvsTofMatch);
}
