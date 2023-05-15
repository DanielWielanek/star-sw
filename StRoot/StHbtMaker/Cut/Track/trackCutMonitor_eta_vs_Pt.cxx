#include "StHbtMaker/Cut/Track/trackCutMonitor_eta_vs_Pt.h"

#include <cstdio>

#include "StHbtMaker/Infrastructure/StHbtTrack.hh"
#include "StHbtMaker/Infrastructure/StHbtTypes.hh"

#ifdef __ROOT__
ClassImp(trackCutMonitor_eta_vs_Pt)
#endif

    trackCutMonitor_eta_vs_Pt::trackCutMonitor_eta_vs_Pt() {
   mHisto = new StHbt2IHisto("Eta_vs_Pt", "eta vs Pt (GeV/c)", 50, -2., 2, 50, 0., 2.);
   cout << " this " << this << endl;
   mHisto->SetDirectory(0);
}
//------------------------------
trackCutMonitor_eta_vs_Pt::trackCutMonitor_eta_vs_Pt(double aMass, const char* TitCutMoni, const char* title,
                                                     int nbins1, double min1, double max1, int nbins2, double min2,
                                                     double max2)
    : mMass(aMass) {
   mHisto = new StHbt2IHisto(TitCutMoni, title, nbins1, min1, max1, nbins2, min2, max2);
   mHisto->SetDirectory(0);
}
//------------------------------
trackCutMonitor_eta_vs_Pt::trackCutMonitor_eta_vs_Pt(const char* TitCutMoni, const char* title, int nbins1, double min1,
                                                     double max1, int nbins2, double min2, double max2)
    : mMass(0.139) {
   mHisto = new StHbt2IHisto(TitCutMoni, title, nbins1, min1, max1, nbins2, min2, max2);
   mHisto->SetDirectory(0);
}
//------------------------------
trackCutMonitor_eta_vs_Pt::~trackCutMonitor_eta_vs_Pt() { delete mHisto; }

//------------------------------
void trackCutMonitor_eta_vs_Pt::Fill(const StHbtTrack* track) {
   StHbtLorentzVector L;
   L.setVect(track->P());
   L.setE(track->P().massHypothesis(mMass));
   mHisto->Fill(L.pseudoRapidity(), L.vect().perp(), 1.);
}
