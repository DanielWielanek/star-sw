#ifndef trackCutMonitor_DCA_hh
#define trackCutMonitor_DCA_hh

//#include<string>
//#include <typeinfo>
#include "StHbtMaker/Base/StHbtCutMonitor.hh"
#include "StHbtMaker/Infrastructure/StHbtTrack.hh"
#include "StHbtMaker/Infrastructure/StHbtTypes.hh"

class trackCutMonitor_DCA : public StHbtCutMonitor {
  private:
   StHbt2DHisto* mHisto;
   StHbt2DHisto* mHistoGlobal;

  public:
   trackCutMonitor_DCA();
   trackCutMonitor_DCA(const char* TitCutMoni, const char* title, int nbins1, double min1, double max1, int nbins2,
                       double min2, double max2);
   virtual ~trackCutMonitor_DCA();

   virtual void Fill(const StHbtTrack* track);
   StHbt2DHisto* Histo() { return mHisto; }
   StHbt2DHisto* HistoGlobal() { return mHistoGlobal; }

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
   ClassDef(trackCutMonitor_DCA, 1)
#endif
};

#endif
