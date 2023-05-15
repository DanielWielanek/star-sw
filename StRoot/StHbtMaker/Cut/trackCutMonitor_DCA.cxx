#include "StHbtMaker/Cut/trackCutMonitor_DCA.h"

#include <cstdio>

#include "StHbtMaker/Infrastructure/StHbtTrack.hh"
#include "StHbtMaker/Infrastructure/StHbtTypes.hh"

#ifdef __ROOT__
ClassImp(trackCutMonitor_DCA)
#endif

    trackCutMonitor_DCA::trackCutMonitor_DCA() {
   mHisto = new StHbt2DHisto("DCAxyvsDCAz", "DCAxy vs DCAz (cm)", 100, 0., 10., 100, 0., 10.);
   mHistoGlobal = new StHbt2DHisto("DCAxyvsDCAzGlobal", "Global DCAxy vs DCAz (cm)", 100, 0., 10., 100, 0., 10.);
   mHisto->SetDirectory(0);
}
//------------------------------
trackCutMonitor_DCA::trackCutMonitor_DCA(const char* TitCutMoni, const char* title, int nbins1, double min1,
                                         double max1, int nbins2, double min2, double max2) {
   mHisto = new StHbt2DHisto(TitCutMoni, title, nbins1, min1, max1, nbins2, min2, max2);
   mHistoGlobal =
       new StHbt2DHisto((TString(TitCutMoni) + "Global").Data(), title, nbins1, min1, max1, nbins2, min2, max2);
   mHisto->SetDirectory(0);
   mHistoGlobal->SetDirectory(0);
}
//------------------------------
trackCutMonitor_DCA::~trackCutMonitor_DCA() {
   delete mHisto;
   delete mHistoGlobal;
}
//------------------------------
void trackCutMonitor_DCA::Fill(const StHbtTrack* track) {
   mHisto->Fill(track->DCAz(), track->DCAxy());
   mHistoGlobal->Fill(track->DCAzGlobal(), track->DCAxyGlobal());
}
