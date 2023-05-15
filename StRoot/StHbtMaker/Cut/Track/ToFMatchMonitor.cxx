#include "StHbtMaker/Cut/Track/ToFMatchMonitor.h"

#include <cstdio>
#include <string>

#include "StHbtMaker/Infrastructure/StHbtTrack.hh"
#include "StLorentzVector.hh"

#ifdef __ROOT__
ClassImp(ToFMatchMonitor)
#endif

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ToFMatchMonitor::ToFMatchMonitor(const string& name, int pbins, float plo, float phi) {
   string hname("ToFMatch0");
   mToFMatch0 = new StHbt1DHisto((hname + name).c_str(), "Momentum distribution ToF match = 0", pbins, plo, phi);
   hname = "ToFMatch1";
   mToFMatch1 = new StHbt1DHisto((hname + name).c_str(), "Momentum distribution ToF match = 1", pbins, plo, phi);
   hname = "ToFMatch2";
   mToFMatch2 = new StHbt1DHisto((hname + name).c_str(), "Momentum distribution ToF match = 2", pbins, plo, phi);
   hname = "ToFMatch3";
   mToFMatch3 = new StHbt1DHisto((hname + name).c_str(), "Momentum distribution ToF match = 3", pbins, plo, phi);

}  // c-tor

ToFMatchMonitor::ToFMatchMonitor(const ToFMatchMonitor& cutMoni) {
   mToFMatch0 = new StHbt1DHisto(*(cutMoni.mToFMatch0));
   mToFMatch1 = new StHbt1DHisto(*(cutMoni.mToFMatch1));
   mToFMatch2 = new StHbt1DHisto(*(cutMoni.mToFMatch2));
   mToFMatch3 = new StHbt1DHisto(*(cutMoni.mToFMatch3));
}  // copy c-tor

ToFMatchMonitor::~ToFMatchMonitor() {
   delete mToFMatch0;
   delete mToFMatch1;
   delete mToFMatch2;
   delete mToFMatch3;
}  // d-tor

void ToFMatchMonitor::Fill(const StHbtTrack* track) {
   switch (track->ToF_matchFlag()) {
      case 0:
         mToFMatch0->Fill(track->P().mag());
         break;
      case 1:
         mToFMatch1->Fill(track->P().mag());
         break;
      case 2:
         mToFMatch2->Fill(track->P().mag());
         break;
      case 3:
         mToFMatch3->Fill(track->P().mag());
         break;
      default:
         break;
   }
}  // Fill
