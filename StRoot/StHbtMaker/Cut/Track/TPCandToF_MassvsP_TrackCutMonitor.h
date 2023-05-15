#ifndef TPCandToF_MassvsP_TrackCutMonitor_hh
#define TPCandToF_MassvsP_TrackCutMonitor_hh

class StHbtTrack;

#include "StHbtMaker/Base/StHbtCutMonitor.hh"
#include "StHbtMaker/Infrastructure/StHbtHisto.hh"

class TPCandToF_MassvsP_TrackCutMonitor : public StHbtCutMonitor {
  private:
   StHbt2DHisto* mMassvsP;
   StHbt2DHisto* mMassSquaredvsP;

  public:
   TPCandToF_MassvsP_TrackCutMonitor(const string& name, int pbins, float plo, float phi, int bbins, float blo,
                                     float bhi);
   TPCandToF_MassvsP_TrackCutMonitor(const TPCandToF_MassvsP_TrackCutMonitor& cutMoni);
   StHbt2DHisto* Histo() const { return mMassvsP; }
   virtual ~TPCandToF_MassvsP_TrackCutMonitor();

   virtual void Fill(const StHbtTrack* track);
   virtual void AppendOutput(TList* output) {
      output->Add(Histo());
      output->Add(mMassSquaredvsP);
   }
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
   ClassDef(TPCandToF_MassvsP_TrackCutMonitor, 1)
#endif
};

#endif
