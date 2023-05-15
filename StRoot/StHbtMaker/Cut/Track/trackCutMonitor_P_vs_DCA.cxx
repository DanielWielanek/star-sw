#include "StHbtMaker/Cut/Track/trackCutMonitor_P_vs_DCA.h"

#include <cstdio>

#include "StHbtMaker/Infrastructure/StHbtTrack.hh"
#include "StHbtMaker/Infrastructure/StHbtTypes.hh"

#ifdef __ROOT__
ClassImp(trackCutMonitor_P_vs_DCA)
#endif

    trackCutMonitor_P_vs_DCA::trackCutMonitor_P_vs_DCA() {
   mHisto = new StHbt2IHisto("DCA", "DCA (cm)", 50, 0., 1., 20, 0., 10.);
   mHisto->SetDirectory(0);
}
//------------------------------
trackCutMonitor_P_vs_DCA::trackCutMonitor_P_vs_DCA(const char* TitCutMoni, const char* title, int nbins1, double min1,
                                                   double max1, int nbins2, double min2, double max2) {
   mHisto = new StHbt2IHisto(TitCutMoni, title, nbins1, min1, max1, nbins2, min2, max2);
   mHisto->SetDirectory(0);
}
//------------------------------
trackCutMonitor_P_vs_DCA::~trackCutMonitor_P_vs_DCA() { delete mHisto; }
//------------------------------
void trackCutMonitor_P_vs_DCA::Fill(const StHbtTrack* track) {
   // mHisto->Fill( track->P().mag(),
   // sqrt(track->DCAxyGlobal()*track->DCAxyGlobal()+track->DCAzGlobal()*track->DCAzGlobal()), 1. );
   mHisto->Fill(track->P().mag(), track->DCAxyGlobal());
}
