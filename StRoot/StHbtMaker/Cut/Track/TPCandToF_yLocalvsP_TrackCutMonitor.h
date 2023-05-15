#ifndef TPCandToF_yLocalvsP_TrackCutMonitor_hh
#define TPCandToF_yLocalvsP_TrackCutMonitor_hh

class StHbtTrack;

#include "StHbtMaker/Base/StHbtCutMonitor.hh"
#include "StHbtMaker/Infrastructure/StHbtHisto.hh"
#include "StMuDSTMaker/COMMON/StMuBTofPidTraits.h"

class TPCandToF_yLocalvsP_TrackCutMonitor : public StHbtCutMonitor {
  private:
   StHbt2DHisto* myLocalvsP;

  public:
   TPCandToF_yLocalvsP_TrackCutMonitor(const string& name, int pbins, float plo, float phi, int bbins, float blo,
                                       float bhi);
   TPCandToF_yLocalvsP_TrackCutMonitor(const TPCandToF_yLocalvsP_TrackCutMonitor& cutMoni);
   const StHbt2DHisto* Histo() const { return myLocalvsP; }
   virtual ~TPCandToF_yLocalvsP_TrackCutMonitor();

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

   virtual void AppendOutput(TList* output) { output->Add(myLocalvsP); };
#ifdef __ROOT__
   ClassDef(TPCandToF_yLocalvsP_TrackCutMonitor, 1)
#endif
};

#endif
