#ifndef TPC_Sgm1vsSgm2vsP_TrackCutMonitor_hh
#define TPC_Sgm1vsSgm2vsP_TrackCutMonitor_hh

class StHbtTrack;

#include "StHbtMaker/Base/StHbtCutMonitor.hh"
#include "StHbtMaker/Infrastructure/StHbtHisto.hh"

class TPC_Sgm1vsSgm2vsP_TrackCutMonitor : public StHbtCutMonitor {
  private:
   StHbt3DHisto* mSgm1vsSgm2;
   int mtype1;
   int mtype2;

  public:
   TPC_Sgm1vsSgm2vsP_TrackCutMonitor(const string& name, int sbins, float slo, float shi, int pbins, float plo,
                                     float phi, int type1, int type2);
   TPC_Sgm1vsSgm2vsP_TrackCutMonitor(const TPC_Sgm1vsSgm2vsP_TrackCutMonitor& cutMoni);
   virtual ~TPC_Sgm1vsSgm2vsP_TrackCutMonitor();
   StHbt3DHisto* Histo() const { return mSgm1vsSgm2; }

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
   ClassDef(TPC_Sgm1vsSgm2vsP_TrackCutMonitor, 1)
#endif
};

#endif
