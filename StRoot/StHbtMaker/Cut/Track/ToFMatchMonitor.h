#ifndef ToFMatchMonitor_hh
#define ToFMatchMonitor_hh

class StHbtTrack;

#include "StHbtMaker/Base/StHbtCutMonitor.hh"
#include "StHbtMaker/Infrastructure/StHbtHisto.hh"

class ToFMatchMonitor : public StHbtCutMonitor {
  private:
   StHbt1DHisto* mToFMatch0;
   StHbt1DHisto* mToFMatch1;
   StHbt1DHisto* mToFMatch2;
   StHbt1DHisto* mToFMatch3;

  public:
   ToFMatchMonitor(const string& name, int pbins, float plo, float phi);
   ToFMatchMonitor(const ToFMatchMonitor& cutMoni);
   virtual ~ToFMatchMonitor();
   StHbt2DHisto* Histo() const { return 0; }

   virtual void Fill(const StHbtTrack* track);
   virtual void AppendOutput(TList* output) {
      output->Add(mToFMatch0);
      output->Add(mToFMatch1);
      output->Add(mToFMatch2);
      output->Add(mToFMatch3);
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
   ClassDef(ToFMatchMonitor, 1)
#endif
};

#endif
