#ifndef primaryPicoTrackCutMonitor_hh
#define primaryPicoTrackCutMonitor_hh

class StHbtTrack;

#include "StHbtMaker/Base/StHbtCutMonitor.hh"
#include "StHbtMaker/Infrastructure/StHbtHisto.hh"

class primaryPicoTrackCutMonitor : public StHbtCutMonitor {
  private:
   StHbt2IHisto* mDCAxy;
   StHbt2IHisto* mYPt;
   StHbt2IHisto* mNSigmaPt;
   //		StHbt2IHisto* mNSigmaPID;
   StHbt2IHisto* mNSigmavsNSigmaEl;
   int mParticleType;

  public:
   primaryPicoTrackCutMonitor(const char* name, const char* suff, int ptype);  // default constructor
   primaryPicoTrackCutMonitor(const primaryPicoTrackCutMonitor& cutMoni);
   ~primaryPicoTrackCutMonitor();

   void Fill(const StHbtTrack* track);
   void Write();

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
   ClassDef(primaryPicoTrackCutMonitor, 1)
#endif
};

inline void primaryPicoTrackCutMonitor::Fill(const StHbtTrack* track) {
   double mass = 0;
   double nsgm = 0;
   //	double pid=0;
   switch (mParticleType) {
      case 0:
         nsgm = track->NSigmaElectron();
         //		pid=track->PidProbElectron();
         mass = 0.511e-3;
         break;
      case 1:
         nsgm = track->NSigmaPion();
         //		pid=track->PidProbPion();
         mass = 0.13956995;
         break;
      case 2:
         nsgm = track->NSigmaKaon();
         //		pid=track->PidProbKaon();
         mass = 0.493677;
         break;
      case 3:
         nsgm = track->NSigmaProton();
         //		pid=track->PidProbProton();
         mass = 0.93827231;
         break;
      default:
         cerr << "primaryPicoTrackCutMonitor - unknown particle type: " << mParticleType << endl;
         assert(false);
   }
   StHbtLorentzVector L;
   L.setVect(track->P());
   L.setE(track->P().massHypothesis(mass));
   double pt = L.vect().perp();
   double y = L.rapidity();
   mDCAxy->Fill(pt, track->DCAxyGlobal());
   mYPt->Fill(y, pt);
   mNSigmaPt->Fill(pt, nsgm);
   //	mNSigmaPID->Fill( pid, nsgm);
   mNSigmavsNSigmaEl->Fill(track->NSigmaElectron(), nsgm);
}
#endif
