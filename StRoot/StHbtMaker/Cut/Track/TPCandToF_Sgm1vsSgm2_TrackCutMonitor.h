#ifndef TPCandToF_Sgm1vsSgm2_TrackCutMonitor_hh
#define TPCandToF_Sgm1vsSgm2_TrackCutMonitor_hh

class StHbtTrack;

#include "StHbtMaker/Base/StHbtCutMonitor.hh"
#include "StHbtMaker/Infrastructure/StHbtHisto.hh"

class TPCandToF_Sgm1vsSgm2_TrackCutMonitor : public StHbtCutMonitor {
  private:
   StHbt2DHisto* mSgm1vsSgm2;
   float mToF_p_threshold;
   int mtype1;
   int mtype2;

  public:
   TPCandToF_Sgm1vsSgm2_TrackCutMonitor(const string& name, float tof_p_threshold, int bins, float lo, float hi,
                                        int type1, int type2);
   TPCandToF_Sgm1vsSgm2_TrackCutMonitor(const TPCandToF_Sgm1vsSgm2_TrackCutMonitor& cutMoni);
   virtual ~TPCandToF_Sgm1vsSgm2_TrackCutMonitor();
   StHbt2DHisto* Histo() const { return mSgm1vsSgm2; }

   virtual void Fill(const StHbtTrack* track);
   virtual void AppendOutput(TList* output) { output->Add(Histo()); }
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
   ClassDef(TPCandToF_Sgm1vsSgm2_TrackCutMonitor, 1)
#endif
};

#endif
