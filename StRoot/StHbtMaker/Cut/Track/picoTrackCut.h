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

#ifndef picoTrackCut_hh
#define picoTrackCut_hh

//#ifndef StMaker_H
//#include "StMaker.h"
//#endif

//#include <Stsstream.h>
#include "StHbtMaker/Base/StHbtTrackCut.h"

class picoTrackCut : public StHbtTrackCut {
  public:
   picoTrackCut();
   picoTrackCut(picoTrackCut&);

   bool Pass(const StHbtTrack*);

   StHbtString Report();

   void SetPidProbElectron(const float& lo, const float& hi);
   void SetPidProbPion(const float& lo, const float& hi);
   void SetPidProbKaon(const float& lo, const float& hi);
   void SetPidProbProton(const float& lo, const float& hi);
   void SetNSigmaElectron(const float& lo, const float& hi);
   void SetNSigmaPion(const float& lo, const float& hi);
   void SetNSigmaKaon(const float& lo, const float& hi);
   void SetNSigmaProton(const float& lo, const float& hi);
   void SetNSigmaAntiElectron(const float& lo, const float& hi);
   void SetNSigmaAntiPion(const float& lo, const float& hi);
   void SetNSigmaAntiKaon(const float& lo, const float& hi);
   void SetNSigmaAntiProton(const float& lo, const float& hi);

   void SetNHits(const int& lo, const int& hi);
   void SetNdEdxHits(const int& lo, const int& hi);
   void SetP(const float& lo, const float& hi);
   void SetPt(const float& lo, const float& hi);
   void SetPx(const float& lo, const float& hi);
   void SetPy(const float& lo, const float& hi);
   void SetPz(const float& lo, const float& hi);
   void SetRapidity(const float& lo, const float& hi);
   void SetEta(const float& lo, const float& hi);
   void SetDCA(const float& lo, const float& hi);
   void SetDCAGlobal(const float& lo, const float& hi);
   void SetCharge(const int&);

   void SetdEdx(const float& lo, const float& hi);

   picoTrackCut* Clone();

   //  ostrstream* finalReport() const;

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
   float mNSigmaAntiPion[2];
   float mNSigmaAntiKaon[2];
   float mNSigmaAntiProton[2];
   int mNHits[2];
   int mNdEdxHits[2];
   float mP[2];
   float mPt[2];
   float mPx[2];
   float mPy[2];
   float mPz[2];
   float mRapidity[2];
   float mEta[2];
   float mDCA[2];
   float mDCAGlobal[2];

   float mdEdx[2];

  protected:
   long mNTracksPassed;
   long mNTracksFailed;

#ifdef __ROOT__
   ClassDef(picoTrackCut, 1)
#endif
};

inline void picoTrackCut::SetPidProbElectron(const float& lo, const float& hi) {
   mPidProbElectron[0] = lo;
   mPidProbElectron[1] = hi;
}
inline void picoTrackCut::SetPidProbPion(const float& lo, const float& hi) {
   mPidProbPion[0] = lo;
   mPidProbPion[1] = hi;
}
inline void picoTrackCut::SetPidProbKaon(const float& lo, const float& hi) {
   mPidProbKaon[0] = lo;
   mPidProbKaon[1] = hi;
}
inline void picoTrackCut::SetPidProbProton(const float& lo, const float& hi) {
   mPidProbProton[0] = lo;
   mPidProbProton[1] = hi;
}
inline void picoTrackCut::SetNSigmaElectron(const float& lo, const float& hi) {
   mNSigmaElectron[0] = lo;
   mNSigmaElectron[1] = hi;
}
inline void picoTrackCut::SetNSigmaPion(const float& lo, const float& hi) {
   mNSigmaPion[0] = lo;
   mNSigmaPion[1] = hi;
}
inline void picoTrackCut::SetNSigmaKaon(const float& lo, const float& hi) {
   mNSigmaKaon[0] = lo;
   mNSigmaKaon[1] = hi;
}
inline void picoTrackCut::SetNSigmaProton(const float& lo, const float& hi) {
   mNSigmaProton[0] = lo;
   mNSigmaProton[1] = hi;
}
inline void picoTrackCut::SetNSigmaAntiElectron(const float& lo, const float& hi) {
   mNSigmaAntiElectron[0] = lo;
   mNSigmaAntiElectron[1] = hi;
}
inline void picoTrackCut::SetNSigmaAntiPion(const float& lo, const float& hi) {
   mNSigmaAntiPion[0] = lo;
   mNSigmaAntiPion[1] = hi;
}
inline void picoTrackCut::SetNSigmaAntiKaon(const float& lo, const float& hi) {
   mNSigmaAntiKaon[0] = lo;
   mNSigmaAntiKaon[1] = hi;
}
inline void picoTrackCut::SetNSigmaAntiProton(const float& lo, const float& hi) {
   mNSigmaAntiProton[0] = lo;
   mNSigmaAntiProton[1] = hi;
}

inline void picoTrackCut::SetNHits(const int& lo, const int& hi) {
   mNHits[0] = lo;
   mNHits[1] = hi;
}
inline void picoTrackCut::SetNdEdxHits(const int& lo, const int& hi) {
   mNdEdxHits[0] = lo;
   mNdEdxHits[1] = hi;
}
inline void picoTrackCut::SetP(const float& lo, const float& hi) {
   mP[0] = lo;
   mP[1] = hi;
}
inline void picoTrackCut::SetPt(const float& lo, const float& hi) {
   mPt[0] = lo;
   mPt[1] = hi;
}
inline void picoTrackCut::SetPx(const float& lo, const float& hi) {
   mPx[0] = lo;
   mPx[1] = hi;
}
inline void picoTrackCut::SetPy(const float& lo, const float& hi) {
   mPy[0] = lo;
   mPy[1] = hi;
}
inline void picoTrackCut::SetPz(const float& lo, const float& hi) {
   mPz[0] = lo;
   mPz[1] = hi;
}
inline void picoTrackCut::SetRapidity(const float& lo, const float& hi) {
   mRapidity[0] = lo;
   mRapidity[1] = hi;
}
inline void picoTrackCut::SetEta(const float& lo, const float& hi) {
   mEta[0] = lo;
   mEta[1] = hi;
}
inline void picoTrackCut::SetDCA(const float& lo, const float& hi) {
   mDCA[0] = lo;
   mDCA[1] = hi;
}
inline void picoTrackCut::SetDCAGlobal(const float& lo, const float& hi) {
   mDCAGlobal[0] = lo;
   mDCAGlobal[1] = hi;
}
inline void picoTrackCut::SetCharge(const int& ch) { mCharge = ch; }
inline picoTrackCut* picoTrackCut::Clone() {
   picoTrackCut* c = new picoTrackCut(*this);
   return c;
}

inline void picoTrackCut::SetdEdx(const float& lo, const float& hi) {
   mdEdx[0] = lo;
   mdEdx[1] = hi;
}

inline bool picoTrackCut::Pass(const StHbtTrack* track) {
#ifdef STHBTDEBUG
   cout << track->NSigmaElectron() << " " << track->NSigmaPion() << " " << track->NSigmaKaon() << " "
        << track->NSigmaProton() << " " << track->DCAxy() << " " << track->DCAxyGlobal() << " " << track->NHits() << " "
        << track->NHitsDedx() << " " << track->P().mag() << " " << track->Pt() << " " << TRapidity << " "
        << track->Charge() << " ";
#endif

   bool goodPID =
       ((track->NSigmaElectron() >= mNSigmaElectron[0]) && (track->NSigmaElectron() <= mNSigmaElectron[1]) &&
            ((track->NSigmaPion() >= mNSigmaPion[0]) && (track->NSigmaPion() <= mNSigmaPion[1])) ||
        ((track->NSigmaKaon() >= mNSigmaKaon[0]) && (track->NSigmaKaon() <= mNSigmaKaon[1])) ||
        ((track->NSigmaProton() >= mNSigmaProton[0]) && (track->NSigmaProton() <= mNSigmaProton[1])) ||
        !((track->NSigmaElectron() > mNSigmaAntiElectron[0]) && (track->NSigmaElectron() < mNSigmaAntiElectron[1])) &&
            !((track->NSigmaPion() > mNSigmaAntiPion[0]) && (track->NSigmaPion() < mNSigmaAntiPion[1])) &&
            !((track->NSigmaKaon() > mNSigmaAntiKaon[0]) && (track->NSigmaKaon() < mNSigmaAntiKaon[1])) &&
            !((track->NSigmaProton() > mNSigmaAntiProton[0]) && (track->NSigmaProton() < mNSigmaAntiProton[1])) &&
            (track->Charge() == mCharge || mCharge == 0));
   if (!goodPID) {
      mNTracksFailed++;
      return false;
   }

#ifdef STHBTDEBUG
   cout << mNSigmaElectron[0] << " << " << track->NSigmaElectron() << " << " << mNSigmaElectron[1] << " ";
   cout << (track->NSigmaElectron() >= mNSigmaElectron[0]) << (track->NSigmaElectron() <= mNSigmaElectron[1]) << endl;
#endif

   bool goodTrack =
       ((track->DCAxy() >= mDCA[0]) && (track->DCAxy() <= mDCA[1]) && (track->dEdx() >= mdEdx[0]) &&
        (track->dEdx() <= mdEdx[1]) && (track->DCAxyGlobal() >= mDCAGlobal[0]) &&
        (track->DCAxyGlobal() <= mDCAGlobal[1]) && (track->NHits() >= mNHits[0]) && (track->NHits() <= mNHits[1]) &&
        (track->NHitsDedx() >= mNdEdxHits[0]) && (track->NHitsDedx() <= mNdEdxHits[1]) && (track->P().mag() >= mP[0]) &&
        (track->P().mag() <= mP[1]) && (track->Pt() >= mPt[0]) && (track->Pt() <= mPt[1]) &&
        (track->P().x() >= mPx[0]) && (track->P().x() <= mPx[1]) && (track->P().y() >= mPy[0]) &&
        (track->P().y() <= mPy[1]) && (track->P().z() >= mPz[0]) && (track->P().z() <= mPz[1]) &&
        (track->P().pseudoRapidity() >= mEta[0]) && (track->P().pseudoRapidity() <= mEta[1]));
   if (!goodTrack) {
      mNTracksFailed++;
      return false;
   }
   float TEnergy = ::sqrt(track->P().mag2() + mMass * mMass);
   float TRapidity = 0.5 * ::log((TEnergy + track->P().z()) / (TEnergy - track->P().z()));
   goodTrack = (TRapidity >= mRapidity[0]) && (TRapidity <= mRapidity[1]);

   (goodTrack) ? mNTracksPassed++ : mNTracksFailed++;

   return goodTrack;
}  // Pass

#endif
