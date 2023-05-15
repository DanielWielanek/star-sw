#ifndef trackCutMonitor_P_vs_Pid_hh
#define trackCutMonitor_P_vs_Pid_hh

#include <TProfile.h>

#include "StHbtMaker/Base/StHbtCutMonitor.hh"
#include "StHbtMaker/Infrastructure/StHbtTrack.hh"
#include "StHbtMaker/Infrastructure/StHbtTypes.hh"

class trackCutMonitor_P_vs_Pid : public StHbtCutMonitor {
  private:
   TH2D* mHisto;
   int pType;

   // pType: particle type:
   // 1 - pion;
   // 2 - kaon;
   // 3 - proton
   // 4 - electron

  public:
   trackCutMonitor_P_vs_Pid();
   trackCutMonitor_P_vs_Pid(const char* TitCutMoni, const char* title, int nbins, double pmin, double pmax, int pType);
   virtual ~trackCutMonitor_P_vs_Pid();

   virtual StHbtString Report();
   virtual void Fill(const StHbtTrack* track);
   virtual void Finish();
   TH2D* Histo() { return mHisto; }

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
   ClassDef(trackCutMonitor_P_vs_Pid, 1)
#endif
};

#endif
