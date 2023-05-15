#ifndef TPCandToF_SgmToFvsSgmTPC_TrackCutMonitor_hh
#define TPCandToF_SgmToFvsSgmTPC_TrackCutMonitor_hh

class StHbtTrack;

#include "StHbtMaker/Base/StHbtCutMonitor.hh"
#include "StHbtMaker/Infrastructure/StHbtHisto.hh"

class TPCandToF_SgmToFvsSgmTPC_TrackCutMonitor : public StHbtCutMonitor {
  private:
   StHbt2DHisto* mSgmToFvsSgmTPC;
   float mToF_p_threshold;
   int mtype;

  public:
   TPCandToF_SgmToFvsSgmTPC_TrackCutMonitor(const string& name, float tof_p_threshold, int bins, float lo, float hi,
                                            int type);
   TPCandToF_SgmToFvsSgmTPC_TrackCutMonitor(const TPCandToF_SgmToFvsSgmTPC_TrackCutMonitor& cutMoni);
   virtual ~TPCandToF_SgmToFvsSgmTPC_TrackCutMonitor();
   const StHbt2DHisto* Histo() const { return mSgmToFvsSgmTPC; }

   virtual void Fill(const StHbtTrack* track);

   // These dummy Fill() functions were introduced to remove a compiler
   //   warning related to overloaded base-class Fill() functions being
   //   hidden by a single version of Fill() in this derived class
   void Fill(const StHbtParticleCollection* d) {}
   void Fill(const StHbtEvent* d1, const StHbtParticleCollection* d2) {}
   void Fill(const StHbtPair* d) {}
   void Fill(const StHbtKink* d) {}
   void Fill(const StHbtV0* d) {}
   void Fill(const StHbtEvent* d) {}

#ifdef __ROOT__
   ClassDef(TPCandToF_SgmToFvsSgmTPC_TrackCutMonitor, 1)
#endif
};

#endif
