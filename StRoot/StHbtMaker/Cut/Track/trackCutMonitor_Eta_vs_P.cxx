#include "StHbtMaker/Cut/Track/trackCutMonitor_Eta_vs_P.h"

#include <cstdio>

#include "StHbtMaker/Infrastructure/StHbtTrack.hh"
#include "StHbtMaker/Infrastructure/StHbtTypes.hh"

#ifdef __ROOT__
ClassImp(trackCutMonitor_Eta_vs_P)
#endif

    trackCutMonitor_Eta_vs_P::trackCutMonitor_Eta_vs_P() {
   mHisto = new StHbt2IHisto("Eta_vs_P", "eta vs P (GeV/c)", 50, -2., 2, 50, 0., 2.);
   cout << " this " << this << endl;
   mHisto->SetDirectory(0);
}
//------------------------------
trackCutMonitor_Eta_vs_P::trackCutMonitor_Eta_vs_P(double aMass, const char* TitCutMoni, const char* title, int nbins1,
                                                   double min1, double max1, int nbins2, double min2, double max2)
    : mMass(aMass) {
   mHisto = new StHbt2IHisto(TitCutMoni, title, nbins1, min1, max1, nbins2, min2, max2);
   mHisto->SetDirectory(0);
}
//------------------------------
trackCutMonitor_Eta_vs_P::trackCutMonitor_Eta_vs_P(const char* TitCutMoni, const char* title, int nbins1, double min1,
                                                   double max1, int nbins2, double min2, double max2)
    : mMass(0.139) {
   mHisto = new StHbt2IHisto(TitCutMoni, title, nbins1, min1, max1, nbins2, min2, max2);
   mHisto->SetDirectory(0);
}
//------------------------------
trackCutMonitor_Eta_vs_P::~trackCutMonitor_Eta_vs_P() { delete mHisto; }

//------------------------------
void trackCutMonitor_Eta_vs_P::Fill(const StHbtTrack* track) {
   mHisto->Fill(track->P().pseudoRapidity(), track->P().mag());  // track->P().perp(), 1.);
   // pseudoRapidity
}
