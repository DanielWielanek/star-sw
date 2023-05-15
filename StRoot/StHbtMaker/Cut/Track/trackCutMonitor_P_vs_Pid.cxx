#include "StHbtMaker/Cut/Track/trackCutMonitor_P_vs_Pid.h"

#include <cstdio>

#include "StHbtMaker/Infrastructure/StHbtTrack.hh"
#include "StHbtMaker/Infrastructure/StHbtTypes.hh"

#ifdef __ROOT__
ClassImp(trackCutMonitor_P_vs_Pid)
#endif

#define LOG100 4.60517

    trackCutMonitor_P_vs_Pid::trackCutMonitor_P_vs_Pid() {
   char* parttypename;

   switch (pType) {
      case 1:
         parttypename = strdup("Pion P_vs_Pid");
         break;
      case 2:
         parttypename = strdup("Kaon P_vs_Pid");
         break;
      case 3:
         parttypename = strdup("Proton P_vs_Pid");
         break;
      case 4:
         parttypename = strdup("Electron P_vs_Pid");
         break;
   }

   mHisto = new TH2D(parttypename, "momentum (GeV/c)", 20, 0., 2., 100, 0, LOG100);
   mHisto->SetDirectory(0);
}
//------------------------------
trackCutMonitor_P_vs_Pid::trackCutMonitor_P_vs_Pid(const char* TitCutMoni, const char* title, int nbins, double pmin,
                                                   double pmax, int partType) {
   mHisto = new TH2D(TitCutMoni, title, nbins, pmin, pmax, 100, 0, LOG100);
   mHisto->SetDirectory(0);
   pType = partType;
}
//------------------------------
trackCutMonitor_P_vs_Pid::~trackCutMonitor_P_vs_Pid() { delete mHisto; }

//------------------------------
void trackCutMonitor_P_vs_Pid::Fill(const StHbtTrack* track) {
   switch (pType) {
      case 1:
         mHisto->Fill(track->P().mag(), LOG100 - TMath::Log(track->PidProbPion() * 100.0));
         break;
      case 2:
         mHisto->Fill(track->P().mag(), LOG100 - TMath::Log(track->PidProbKaon() * 100.0));
         break;
      case 3:
         mHisto->Fill(track->P().mag(), LOG100 - TMath::Log(track->PidProbProton() * 100.0));
         break;
      case 4:
         mHisto->Fill(track->P().mag(), TMath::Log(track->PidProbElectron() * 100.0));
         break;
   }
}

//------------------------------
void trackCutMonitor_P_vs_Pid::Finish() { cout << " entries in histogram : " << mHisto->Integral() << endl; }

//------------------------------
StHbtString trackCutMonitor_P_vs_Pid::Report() {
   string Stemp;
   char Ctemp[100];
   sprintf(Ctemp, " report some stuff");
   Stemp = Ctemp;
   StHbtString returnThis = Stemp;
   return returnThis;
}
