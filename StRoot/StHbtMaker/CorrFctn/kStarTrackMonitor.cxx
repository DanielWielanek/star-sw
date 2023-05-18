#include "StHbtMaker/CorrFctn/kStarTrackMonitor.h"

#ifdef __ROOT__
ClassImp(kStarTrackMonitor)
#endif

    void kStarTrackMonitor::AddTrackCutMonitor(double kStarMin, double kStarMax, primaryPicoTrackCutMonitor* t1,
                                               primaryPicoTrackCutMonitor* t2) {
   mkStarBins.push_back(make_pair(kStarMin, kStarMax));
   mMonitors_track1.push_back(t1);
   mMonitors_track2.push_back(t2);
}

void kStarTrackMonitor::Write() {
   for (size_t i = 0; i < mMonitors_track1.size(); i++) {
      mMonitors_track1[i]->Write();
      mMonitors_track2[i]->Write();
   }
}
