#ifndef TPCandToF_SgmToFvsSgmTPCvsP_TrackCutMonitor_hh
#define TPCandToF_SgmToFvsSgmTPCvsP_TrackCutMonitor_hh

class StHbtTrack;

#include "StHbtMaker/Base/StHbtCutMonitor.hh"
#include "StHbtMaker/Infrastructure/StHbtHisto.hh"

class TPCandToF_SgmToFvsSgmTPCvsP_TrackCutMonitor : public StHbtCutMonitor {
  private:
   StHbt3DHisto* mSgmToFvsSgmTPC;
   int mtype;

  public:
   TPCandToF_SgmToFvsSgmTPCvsP_TrackCutMonitor(const string& name, int sbins, float slo, float shi, int pbins,
                                               float plo, float phi, int type);
   TPCandToF_SgmToFvsSgmTPCvsP_TrackCutMonitor(const TPCandToF_SgmToFvsSgmTPCvsP_TrackCutMonitor& cutMoni);
   virtual ~TPCandToF_SgmToFvsSgmTPCvsP_TrackCutMonitor();
   StHbt3DHisto* Histo() const { return mSgmToFvsSgmTPC; }

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
   ClassDef(TPCandToF_SgmToFvsSgmTPCvsP_TrackCutMonitor, 1)
#endif
};

#endif
