#ifndef Chi2TrackCutMonitor_h
#define Chi2TrackCutMonitor_h

class StHbtTrack;

#include "StHbtMaker/Base/StHbtCutMonitor.hh"
#include "StHbtMaker/Infrastructure/StHbtHisto.hh"

class Chi2TrackCutMonitor : public StHbtCutMonitor {
  private:
   StHbt2DHisto* mChi2vsP;

  public:
   Chi2TrackCutMonitor(const string& name, int pbins, float plo, float phi, int chi2bins, float chi2lo, float chi2hi);
   Chi2TrackCutMonitor(const Chi2TrackCutMonitor& cutMoni);
   StHbt2DHisto* Histo() const { return mChi2vsP; }
   virtual ~Chi2TrackCutMonitor();

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
   ClassDef(Chi2TrackCutMonitor, 1)
#endif
};

#endif
