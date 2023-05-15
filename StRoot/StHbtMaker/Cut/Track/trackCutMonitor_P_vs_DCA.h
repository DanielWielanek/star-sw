#ifndef trackCutMonitor_P_vs_DCA_hh
#define trackCutMonitor_P_vs_DCA_hh

//#include<string>
//#include <typeinfo>
#include "StHbtMaker/Base/StHbtCutMonitor.hh"
#include "StHbtMaker/Infrastructure/StHbtTrack.hh"
#include "StHbtMaker/Infrastructure/StHbtTypes.hh"

class trackCutMonitor_P_vs_DCA : public StHbtCutMonitor {
  private:
   StHbt2IHisto* mHisto;

  public:
   trackCutMonitor_P_vs_DCA();
   trackCutMonitor_P_vs_DCA(const char* TitCutMoni, const char* title, int nbinsX, double minX, double maxX, int nbinsY,
                            double minY, double maxY);
   virtual ~trackCutMonitor_P_vs_DCA();

   virtual void Fill(const StHbtTrack* track);
   StHbt2IHisto* Histo() { return mHisto; }

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
   ClassDef(trackCutMonitor_P_vs_DCA, 1)
#endif
};

#endif
