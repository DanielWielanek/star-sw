#ifndef trackCutMonitor_Eta_vs_P_hh
#define trackCutMonitor_Eta_vs_P_hh

#include "StHbtMaker/Base/StHbtCutMonitor.hh"
#include "StHbtMaker/Infrastructure/StHbtTrack.hh"
#include "StHbtMaker/Infrastructure/StHbtTypes.hh"

class trackCutMonitor_Eta_vs_P : public StHbtCutMonitor {
  private:
   StHbt2IHisto* mHisto;
   double mMass;
   StHbtThreeVector mP;

  public:
   trackCutMonitor_Eta_vs_P();
   trackCutMonitor_Eta_vs_P(double aMass, const char* TitCutMoni, const char* title, int nbins1, double min1,
                            double max1, int nbins2, double min2, double max2);
   trackCutMonitor_Eta_vs_P(const char* TitCutMoni, const char* title, int nbins1, double min1, double max1, int nbins2,
                            double min2, double max2);
   virtual ~trackCutMonitor_Eta_vs_P();

   void Fill(const StHbtTrack* track);
   StHbt2IHisto* Histo() { return mHisto; }
   void AppendOutput(TList* output) const { output->Add(mHisto); }
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
   ClassDef(trackCutMonitor_Eta_vs_P, 1)
#endif
};

#endif
