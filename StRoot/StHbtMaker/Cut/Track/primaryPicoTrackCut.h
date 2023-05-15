/***************************************************************************
 *
 * $Id:
 *
 * Author: Frank Laue, Ohio State, laue@mps.ohio-state.edu
 ***************************************************************************
 *
 * Description: part of STAR HBT Framework: StHbtMaker package
 *    a simple particle cut that selects on phasespace, #hits, DCA, and PID
 *
 ***************************************************************************
 *
 * $Log:
 *
 **************************************************************************/

#ifndef primaryPicoTrackCut_hh
#define primaryPicoTrackCut_hh

//#ifndef StMaker_H
//#include "StMaker.h"
//#endif

#include <Stsstream.h>
#include <TObjString.h>

#include "StHbtMaker/Base/StHbtTrackCut.h"

class primaryPicoTrackCut : public StHbtTrackCut {
  public:
   primaryPicoTrackCut();
   primaryPicoTrackCut(primaryPicoTrackCut&);

   bool Pass(const StHbtTrack*);
   string Report();
   string StrReport();

   void SetNSigmaElectron(const float& lo, const float& hi);
   void SetNSigmaPion(const float& lo, const float& hi);
   void SetNSigmaKaon(const float& lo, const float& hi);
   void SetNSigmaProton(const float& lo, const float& hi);
   void SetNSigmaAntiElectron(const float& lo, const float& hi);

   void SetNHits(const int& lo);
   void SetNdEdxHits(const int& lo);
   void SetP(const float& lo, const float& hi);
   void SetPt(const float& lo, const float& hi);
   void SetRapidity(const float& lo, const float& hi);
   void SetEta(const float& lo, const float& hi);
   void SetDCAxy(const float& hi);
   void SetCharge(const int&);

   primaryPicoTrackCut* Clone();

   // private:   // here are the quantities I want to cut on...
  protected:
   int mCharge;
   float mPidProbElectron[2];
   float mPidProbPion[2];
   float mPidProbKaon[2];
   float mPidProbProton[2];
   float mNSigmaElectron[2];
   float mNSigmaPion[2];
   float mNSigmaKaon[2];
   float mNSigmaProton[2];
   float mNSigmaAntiElectron[2];
   int mNHits;
   int mNdEdxHits;
   float mP[2];
   float mPt[2];
   float mRapidity[2];
   float mEta[2];
   float mDCAxy;

   long mNPassed;
   long mNFailed;

#ifdef __ROOT__
   ClassDef(primaryPicoTrackCut, 1)
#endif
};

inline void primaryPicoTrackCut::SetNSigmaElectron(const float& lo, const float& hi) {
   mNSigmaElectron[0] = lo;
   mNSigmaElectron[1] = hi;
}
inline void primaryPicoTrackCut::SetNSigmaPion(const float& lo, const float& hi) {
   mNSigmaPion[0] = lo;
   mNSigmaPion[1] = hi;
}
inline void primaryPicoTrackCut::SetNSigmaKaon(const float& lo, const float& hi) {
   mNSigmaKaon[0] = lo;
   mNSigmaKaon[1] = hi;
}
inline void primaryPicoTrackCut::SetNSigmaProton(const float& lo, const float& hi) {
   mNSigmaProton[0] = lo;
   mNSigmaProton[1] = hi;
}
inline void primaryPicoTrackCut::SetNSigmaAntiElectron(const float& lo, const float& hi) {
   mNSigmaAntiElectron[0] = lo;
   mNSigmaAntiElectron[1] = hi;
}

inline void primaryPicoTrackCut::SetNHits(const int& lo) { mNHits = lo; }
inline void primaryPicoTrackCut::SetNdEdxHits(const int& lo) { mNdEdxHits = lo; }
inline void primaryPicoTrackCut::SetP(const float& lo, const float& hi) {
   mP[0] = lo;
   mP[1] = hi;
}
inline void primaryPicoTrackCut::SetPt(const float& lo, const float& hi) {
   mPt[0] = lo;
   mPt[1] = hi;
}
inline void primaryPicoTrackCut::SetRapidity(const float& lo, const float& hi) {
   mRapidity[0] = lo;
   mRapidity[1] = hi;
}
inline void primaryPicoTrackCut::SetEta(const float& lo, const float& hi) {
   mEta[0] = lo;
   mEta[1] = hi;
}
inline void primaryPicoTrackCut::SetDCAxy(const float& hi) { mDCAxy = hi; }
inline void primaryPicoTrackCut::SetCharge(const int& ch) { mCharge = ch; }
inline primaryPicoTrackCut* primaryPicoTrackCut::Clone() {
   primaryPicoTrackCut* c = new primaryPicoTrackCut(*this);
   return c;
}

inline bool primaryPicoTrackCut::Pass(const StHbtTrack* track) {
#ifdef STHBTDEBUG
   cout << track->NSigmaElectron() << " " << track->NSigmaPion() << " " << track->NSigmaKaon() << " "
        << track->NSigmaProton() << " " << track->DCAxy() << " " << track->NHits() << " " << track->NHitsDedx() << " "
        << track->P().mag() << " " << track->Pt() << " " << TRapidity << " " << track->Charge() << " ";
#endif

   bool goodPID =
       ((track->NSigmaElectron() >= mNSigmaElectron[0]) && (track->NSigmaElectron() <= mNSigmaElectron[1]) &&
        (track->NSigmaPion() >= mNSigmaPion[0]) && (track->NSigmaPion() <= mNSigmaPion[1]) &&
        (track->NSigmaKaon() >= mNSigmaKaon[0]) && (track->NSigmaKaon() <= mNSigmaKaon[1]) &&
        (track->NSigmaProton() >= mNSigmaProton[0]) && (track->NSigmaProton() <= mNSigmaProton[1]) &&
        !((track->NSigmaElectron() > mNSigmaAntiElectron[0]) && (track->NSigmaElectron() < mNSigmaAntiElectron[1])) &&
        (track->Charge() == mCharge || mCharge == 0));
   if (!goodPID) {
      ++mNFailed;
      return false;
   }

   float TEnergy = ::sqrt(track->P().mag2() + mMass * mMass);
   float TRapidity = 0.5 * ::log((TEnergy + track->P().z()) / (TEnergy - track->P().z()));

   bool goodTrack =
       ((track->DCAxyGlobal() <= mDCAxy) && (track->NHits() >= mNHits) && (track->NHitsDedx() >= mNdEdxHits) &&
        (track->P().mag() >= mP[0]) && (track->P().mag() <= mP[1]) && (track->Pt() >= mPt[0]) &&
        (track->Pt() <= mPt[1]) && (track->P().pseudoRapidity() >= mEta[0]) &&
        (track->P().pseudoRapidity() <= mEta[1]) && (TRapidity >= mRapidity[0]) && (TRapidity <= mRapidity[1]));

#ifdef STHBTDEBUG
   cout << " goodPID=" << goodPID << " ";
   cout << " goodTrack=" << goodTrack << " ";
   cout << endl;
#endif
   goodTrack ? ++mNPassed : ++mNFailed;

   return goodTrack;
}  // Pass
#endif
