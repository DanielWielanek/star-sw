#ifndef TPCandToF_BetavsP_TrackCutMonitor_hh
#define TPCandToF_BetavsP_TrackCutMonitor_hh

class StHbtTrack;

#include "StHbtMaker/Base/StHbtCutMonitor.hh"
#include "StHbtMaker/Infrastructure/StHbtHisto.hh"

class TPCandToF_BetavsP_TrackCutMonitor : public StHbtCutMonitor {
  private:
   StHbt2DHisto* mBetavsP;

  public:
   TPCandToF_BetavsP_TrackCutMonitor(const string& name, int pbins, float plo, float phi, int bbins, float blo,
                                     float bhi);
   TPCandToF_BetavsP_TrackCutMonitor(const TPCandToF_BetavsP_TrackCutMonitor& cutMoni);
   const StHbt2DHisto* Histo() const { return mBetavsP; }
   virtual ~TPCandToF_BetavsP_TrackCutMonitor();

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

   virtual void AppendOutput(TList* output) { output->Add(mBetavsP); };
#ifdef __ROOT__
   ClassDef(TPCandToF_BetavsP_TrackCutMonitor, 1)
#endif
};

#endif
