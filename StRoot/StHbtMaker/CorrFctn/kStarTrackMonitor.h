#ifndef kStarTrackMonitor_h
#define kStarTrackMonitor_h

#include "StHbtMaker/Base/StHbtCorrFctn.hh"
#include "StHbtMaker/Cut/primaryPicoTrackCutMonitor.h"

class kStarTrackMonitor : public StHbtCorrFctn {
  public:
   void AddTrackCutMonitor(double kStarMin, double kStarMax, primaryPicoTrackCutMonitor* t1,
                           primaryPicoTrackCutMonitor* t2);
   virtual StHbtString Report() { return StHbtString(); }
   void AddRealPair(const StHbtPair* p) {
      double kStar = TMath::Abs(p->KStar());
      for (size_t i = 0; i < mMonitors_track1.size(); i++) {
         if (mkStarBins[i].first <= kStar && kStar < mkStarBins[i].second) {
            mMonitors_track1[i]->Fill(p->track1()->Track());
            mMonitors_track2[i]->Fill(p->track2()->Track());
         }
      }
   }
   virtual void AddMixedPair(const StHbtPair*) {}

   virtual void Finish() {}
   virtual void Write();

  private:
   typedef std::vector<primaryPicoTrackCutMonitor*> mContainer_t;
   typedef mContainer_t::iterator mIterator_t;
   std::vector<std::pair<double, double> > mkStarBins;
   mContainer_t mMonitors_track1;
   mContainer_t mMonitors_track2;
   mIterator_t mIt;

#ifdef __ROOT__
   ClassDef(kStarTrackMonitor, 1)
#endif
};  // kStarTrackMonitor

#endif  // kStarTrackMonitor_h
