/***************************************************************************
 * TPCandToF_TrackCut based on franksTrackCut
 * Marcin Zawisza, WUT, zawisza@if.pw.edu.pl
 ***************************************************************************
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

#ifndef TPCandToF_TrackCut_hh
#define TPCandToF_TrackCut_hh

//#ifndef StMaker_H
//#include "StMaker.h"
//#endif

#include <Stsstream.h>

#include "StHbtMaker/Base/StHbtTrackCut.h"
#include "StHbtMaker/Cut/ToFRequiredPredicate.h"

class TPCandToF_TrackCut : public StHbtTrackCut {
  public:
   TPCandToF_TrackCut();
   TPCandToF_TrackCut(TPCandToF_TrackCut&);

   virtual bool Pass(const StHbtTrack*);

   virtual StHbtString Report();

   void SetPidProbElectron(const float& lo, const float& hi);
   void SetPidProbPion(const float& lo, const float& hi);
   void SetPidProbKaon(const float& lo, const float& hi);
   void SetPidProbProton(const float& lo, const float& hi);
   void SetNSigmaElectron(const float& lo, const float& hi, const float& lo2, const float& hi2);
   void SetNSigmaPion(const float& lo, const float& hi, const float& lo2, const float& hi2);
   void SetNSigmaKaon(const float& lo, const float& hi, const float& lo2, const float& hi2);
   void SetNSigmaProton(const float& lo, const float& hi, const float& lo2, const float& hi2);

   void SetOrMode(const bool mode);
   void SetNSigmaAntiElectron(const float& lo, const float& hi);
   void SetNSigmaAntiPion(const float& lo, const float& hi);
   void SetNSigmaAntiKaon(const float& lo, const float& hi);
   void SetNSigmaAntiProton(const float& lo, const float& hi);
   void SetToFRequiredPredicate(ToFRequiredPredicate* pred);
   void SetToF_sigmaElectron(const float& lo, const float& hi);
   void SetToF_sigmaPion(const float& lo, const float& hi);
   void SetToF_sigmaKaon(const float& lo, const float& hi);
   void SetToF_sigmaProton(const float& lo, const float& hi);
   void SetToF_sigmaAntiElectron(const float& lo, const float& hi);
   void SetToF_sigmaAntiPion(const float& lo, const float& hi);
   void SetToF_sigmaAntiKaon(const float& lo, const float& hi);
   void SetToF_sigmaAntiProton(const float& lo, const float& hi);
   void SetToF_MassWindow(const float& lo, const float& hi);
   void SetToF_p_threshold(const float& val);

   void SetNHits(const int& lo, const int& hi);
   void SetNdEdxHits(const int& lo, const int& hi);
   void SetP(const float& lo, const float& hi);
   void SetPt(const float& lo, const float& hi);
   void SetPx(const float& lo, const float& hi);
   void SetPy(const float& lo, const float& hi);
   void SetPz(const float& lo, const float& hi);
   void SetRapidity(const float& lo, const float& hi);
   void SetEta(const float& lo, const float& hi);
   void SetyLocal(const float& lo, const float& hi);  // poniatowska
   void SetDCA(const float& lo, const float& hi);
   void SetDCAGlobal(const float& lo, const float& hi);
   void SetCharge(const int&);
   // void SetMass(const float&);
   /// !!
   void SetdEdx(const float& lo, const float& hi);

   void SetTreshold(const float&);

   TPCandToF_TrackCut* Clone();

   ostrstream* finalReport() const;

   // private:   // here are the quantities I want to cut on...
  protected:
   int mCharge;
   // float mMass;
   float mTreshold;
   float mPidProbElectron[2];
   float mPidProbPion[2];
   float mPidProbKaon[2];
   float mPidProbProton[2];
   float mNSigmaElectron[4];
   float mNSigmaPion[4];
   float mNSigmaKaon[4];
   float mNSigmaProton[4];

   bool mOrMode;
   /*
   float mNSigmaAntiElectron[2];
   float mNSigmaAntiPion[2];
   float mNSigmaAntiKaon[2];
   float mNSigmaAntiProton[2];
   */
   int mNHits[2];
   int mNdEdxHits[2];
   float mP[2];
   float mPt[2];
   float mPx[2];
   float mPy[2];
   float mPz[2];
   float mRapidity[2];
   float mEta[2];
   float myLocal[2];  // poniatowska
   float mDCA[2];
   float mDCAGlobal[2];
   Float_t mToF_sigmaElectron[2];
   Float_t mToF_sigmaPion[2];
   Float_t mToF_sigmaKaon[2];
   Float_t mToF_sigmaProton[2];
   /*
   Float_t mToF_sigmaAntiElectron[2];
   Float_t mToF_sigmaAntiPion[2];
   Float_t mToF_sigmaAntiKaon[2];
   Float_t mToF_sigmaAntiProton[2];
   */
   Float_t mToF_MassWindow[2];

   //!!!
   float mdEdx[2];
   ToFRequiredPredicate* mTofPredicate;

  protected:
   long mNTracksPassed;
   long mNTracksFailed;
   void UpdatePidProbs(StHbtTrack* track);
#ifdef __ROOT__
   ClassDef(TPCandToF_TrackCut, 1)
#endif
};

inline void TPCandToF_TrackCut::SetPidProbElectron(const float& lo, const float& hi) {
   mPidProbElectron[0] = lo;
   mPidProbElectron[1] = hi;
}
inline void TPCandToF_TrackCut::SetPidProbPion(const float& lo, const float& hi) {
   mPidProbPion[0] = lo;
   mPidProbPion[1] = hi;
}
inline void TPCandToF_TrackCut::SetPidProbKaon(const float& lo, const float& hi) {
   mPidProbKaon[0] = lo;
   mPidProbKaon[1] = hi;
}
inline void TPCandToF_TrackCut::SetPidProbProton(const float& lo, const float& hi) {
   mPidProbProton[0] = lo;
   mPidProbProton[1] = hi;
}
inline void TPCandToF_TrackCut::SetNSigmaElectron(const float& lo, const float& hi, const float& lo2,
                                                  const float& hi2) {
   mNSigmaElectron[0] = lo;
   mNSigmaElectron[1] = hi;
   mNSigmaElectron[2] = lo2;
   mNSigmaElectron[3] = hi2;
}
inline void TPCandToF_TrackCut::SetNSigmaPion(const float& lo, const float& hi, const float& lo2, const float& hi2) {
   mNSigmaPion[0] = lo;
   mNSigmaPion[1] = hi;
   mNSigmaPion[2] = lo2;
   mNSigmaPion[3] = hi2;
}
inline void TPCandToF_TrackCut::SetNSigmaKaon(const float& lo, const float& hi, const float& lo2, const float& hi2) {
   mNSigmaKaon[0] = lo;
   mNSigmaKaon[1] = hi;
   mNSigmaKaon[2] = lo2;
   mNSigmaKaon[3] = hi2;
}
inline void TPCandToF_TrackCut::SetNSigmaProton(const float& lo, const float& hi, const float& lo2, const float& hi2) {
   mNSigmaProton[0] = lo;
   mNSigmaProton[1] = hi;
   mNSigmaProton[2] = lo2;
   mNSigmaProton[3] = hi2;
}
inline void TPCandToF_TrackCut::SetOrMode(const bool mode) { mOrMode = mode; }
/*inline void TPCandToF_TrackCut::SetNSigmaAntiElectron(const float& lo, const float& hi){mNSigmaAntiElectron[0]=lo;
mNSigmaAntiElectron[1]=hi;} inline void TPCandToF_TrackCut::SetNSigmaAntiPion(const float& lo, const float&
hi){mNSigmaAntiPion[0]=lo; mNSigmaAntiPion[1]=hi;} inline void TPCandToF_TrackCut::SetNSigmaAntiKaon(const float& lo,
const float& hi){mNSigmaAntiKaon[0]=lo; mNSigmaAntiKaon[1]=hi;} inline void
TPCandToF_TrackCut::SetNSigmaAntiProton(const float& lo, const float& hi){mNSigmaAntiProton[0]=lo;
mNSigmaAntiProton[1]=hi;}
*/
inline void TPCandToF_TrackCut::SetNHits(const int& lo, const int& hi) {
   mNHits[0] = lo;
   mNHits[1] = hi;
}
inline void TPCandToF_TrackCut::SetNdEdxHits(const int& lo, const int& hi) {
   mNdEdxHits[0] = lo;
   mNdEdxHits[1] = hi;
}
inline void TPCandToF_TrackCut::SetP(const float& lo, const float& hi) {
   mP[0] = lo;
   mP[1] = hi;
}
inline void TPCandToF_TrackCut::SetPt(const float& lo, const float& hi) {
   mPt[0] = lo;
   mPt[1] = hi;
}
inline void TPCandToF_TrackCut::SetPx(const float& lo, const float& hi) {
   mPx[0] = lo;
   mPx[1] = hi;
}
inline void TPCandToF_TrackCut::SetPy(const float& lo, const float& hi) {
   mPy[0] = lo;
   mPy[1] = hi;
}
inline void TPCandToF_TrackCut::SetPz(const float& lo, const float& hi) {
   mPz[0] = lo;
   mPz[1] = hi;
}
inline void TPCandToF_TrackCut::SetRapidity(const float& lo, const float& hi) {
   mRapidity[0] = lo;
   mRapidity[1] = hi;
}
inline void TPCandToF_TrackCut::SetEta(const float& lo, const float& hi) {
   mEta[0] = lo;
   mEta[1] = hi;
}
inline void TPCandToF_TrackCut::SetyLocal(const float& lo, const float& hi) {
   myLocal[0] = lo;
   myLocal[1] = hi;
}  // poniatowska
inline void TPCandToF_TrackCut::SetDCA(const float& lo, const float& hi) {
   mDCA[0] = lo;
   mDCA[1] = hi;
}
inline void TPCandToF_TrackCut::SetDCAGlobal(const float& lo, const float& hi) {
   mDCAGlobal[0] = lo;
   mDCAGlobal[1] = hi;
}
inline void TPCandToF_TrackCut::SetCharge(const int& ch) { mCharge = ch; }
// inline void TPCandToF_TrackCut::SetMass(const float& m){mMass = m;}
inline void TPCandToF_TrackCut::SetTreshold(const float& t) { mTreshold = t; }

inline TPCandToF_TrackCut* TPCandToF_TrackCut::Clone() {
   TPCandToF_TrackCut* c = new TPCandToF_TrackCut(*this);
   return c;
}

inline void TPCandToF_TrackCut::SetdEdx(const float& lo, const float& hi) {
   mdEdx[0] = lo;
   mdEdx[1] = hi;
}

inline void TPCandToF_TrackCut::SetToF_sigmaElectron(const float& lo, const float& hi) {
   mToF_sigmaElectron[0] = lo;
   mToF_sigmaElectron[1] = hi;
}
inline void TPCandToF_TrackCut::SetToFRequiredPredicate(ToFRequiredPredicate* pred) { mTofPredicate = pred; }
inline void TPCandToF_TrackCut::SetToF_sigmaPion(const float& lo, const float& hi) {
   mToF_sigmaPion[0] = lo;
   mToF_sigmaPion[1] = hi;
}
inline void TPCandToF_TrackCut::SetToF_sigmaKaon(const float& lo, const float& hi) {
   mToF_sigmaKaon[0] = lo;
   mToF_sigmaKaon[1] = hi;
}
inline void TPCandToF_TrackCut::SetToF_sigmaProton(const float& lo, const float& hi) {
   mToF_sigmaProton[0] = lo;
   mToF_sigmaProton[1] = hi;
}
/*
inline void TPCandToF_TrackCut::SetToF_sigmaAntiElectron(const float& lo, const float& hi){mToF_sigmaAntiElectron[0]=lo;
mToF_sigmaAntiElectron[1]=hi;} inline void TPCandToF_TrackCut::SetToF_sigmaAntiPion(const float& lo, const float&
hi){mToF_sigmaAntiPion[0]=lo; mToF_sigmaAntiPion[1]=hi;} inline void TPCandToF_TrackCut::SetToF_sigmaAntiKaon(const
float& lo, const float& hi){mToF_sigmaAntiKaon[0]=lo; mToF_sigmaAntiKaon[1]=hi;} inline void
TPCandToF_TrackCut::SetToF_sigmaAntiProton(const float& lo, const float& hi){mToF_sigmaAntiProton[0]=lo;
mToF_sigmaAntiProton[1]=hi;}
*/
inline void TPCandToF_TrackCut::SetToF_MassWindow(const float& lo, const float& hi) {
   mToF_MassWindow[0] = lo;
   mToF_MassWindow[1] = hi;
}

inline void TPCandToF_TrackCut::SetToF_p_threshold(const float& val) {}

inline bool TPCandToF_TrackCut::Pass(const StHbtTrack* track) {
   double TEnergy = ::sqrt(track->P().mag2() + mMass * mMass);
   double TRapidity = 0.5 * ::log((TEnergy + track->P().z()) / (TEnergy - track->P().z()));
#ifdef STHBTDEBUG
   cout << mNSigmaElectron[0] << " << " << track->NSigmaElectron() << " << " << mNSigmaElectron[1] << " ";
   cout << (track->NSigmaElectron() >= mNSigmaElectron[0]) << (track->NSigmaElectron() <= mNSigmaElectron[1]) << endl;
#endif
   double beta2 = track->ToF_beta();
   beta2 = beta2 * beta2;
   double p = track->P().mag();
   double m2 = p * p * (1. / beta2 - 1);
   int good_counter = 0;
   bool goodVals[8] = {false, false, false, false, false, false, false, false};
   if (((track->NSigmaElectron() >= mNSigmaElectron[0]) && (track->NSigmaElectron() <= mNSigmaElectron[1])) ||
       ((track->NSigmaElectron() >= mNSigmaElectron[2]) && (track->NSigmaElectron() <= mNSigmaElectron[3]))) {
      good_counter++;  // 1
      goodVals[0] = true;
   }

   if ((((track->NSigmaPion() >= mNSigmaPion[0]) && (track->NSigmaPion() <= mNSigmaPion[1])) ||
        ((track->NSigmaPion() >= mNSigmaPion[2]) && (track->NSigmaPion() <= mNSigmaPion[3])))) {
      good_counter++;  // 2
      goodVals[1] = true;
   }
   if ((((track->NSigmaKaon() >= mNSigmaKaon[0]) && (track->NSigmaKaon() <= mNSigmaKaon[1])) ||
        ((track->NSigmaKaon() >= mNSigmaKaon[2]) && (track->NSigmaKaon() <= mNSigmaKaon[3])))) {
      good_counter++;  // 3
      goodVals[2] = true;
   }
   if ((((track->NSigmaProton() >= mNSigmaProton[0]) && (track->NSigmaProton() <= mNSigmaProton[1])) ||
        ((track->NSigmaProton() >= mNSigmaProton[2]) && (track->NSigmaProton() <= mNSigmaProton[3])))) {
      good_counter++;  // 4
      goodVals[3] = true;
   }
   if ((track->Charge() == mCharge || mCharge == 0)) {
      good_counter++;  // 5
      goodVals[4] = true;
   }
   if ((track->DCAxy() >= mDCA[0]) && (track->DCAxy() <= mDCA[1])) {
      good_counter++;  // 6
      goodVals[4] = true;
   }
   if ((track->NHits() >= mNHits[0]) && (track->NHits() <= mNHits[1])) {
      good_counter++;  // 7
      goodVals[5] = true;
   }
   if ((track->P().mag() >= mP[0]) && (track->P().mag() <= mP[1]) && (track->Pt() >= mPt[0]) &&
       (track->Pt() <= mPt[1]) && (track->P().pseudoRapidity() >= mEta[0]) &&  // SS tu podmienialem
       (track->P().pseudoRapidity() <= mEta[1])) {
      good_counter++;  // 8
      goodVals[6] = true;
   }
   bool goodTrack = false;
   if (good_counter >= 8) {
      goodTrack = true;
   }
   /*  std::cout << "******" << std::endl;
     for (int i = 0; i < 7; i++) {
       std::cout << goodVals[i];
     }
     std::cout << std::endl;
     std::cout << "KIN " << track->P().mag() << " " << track->Pt() << " " << track->P().pseudoRapidity() << std::endl;

     std::cout << track->ToF_matchFlag() << std::endl;
     std::cout << track->NSigmaElectron() << " " << track->NSigmaPion() << " " << track->NSigmaKaon() << " " <<
     track->NSigmaProton()
               << std::endl;
     std::cout << track->P().mag() << " " << track->Pt() << " " << track->P().pseudoRapidity() << " " << track->Charge()
               << std::endl;
   */
   bool goodTrackToF = false;
   if ((track->ToF_matchFlag() == 0 && track->P().mag() <= mTreshold) ||
       (track->ToF_matchFlag() != 0 && (m2 >= mToF_MassWindow[0] && m2 <= mToF_MassWindow[1]) &&
        (track->ToF_yLocal() >= myLocal[0] && track->ToF_yLocal() <= myLocal[1])))
      goodTrackToF =
          true; /* SS tu tne || ( (track->ToF_matchFlag()!=0) && ( (m2 >= mToF_MassWindow[0]) && (m2 <=
                mToF_MassWindow[1]) ) && / ((track->ToF_yLocal()>=myLocal[0]))&&(track->ToF_yLocal()<=myLocal[1]) ) )
                goodTrackToF = true;*/
                /*  std::cout << "tof" << std::endl;
                  std::cout << (int)track->ToF_matchFlag() << std::endl;
                  std::cout << m2 << " " << track->ToF_yLocal() <<" "<<track->ToF_beta()<< std::endl;
                */ (goodTrack && goodTrackToF) ? mNTracksPassed++ : mNTracksFailed++;
   return (goodTrackToF && goodTrack);
}

inline void TPCandToF_TrackCut::UpdatePidProbs(StHbtTrack* track) {
   float pidProbElectron = track->PidProbElectron() * track->ToF_probElectron();
   float pidProbPion = track->PidProbPion() * track->ToF_probPion();
   float pidProbKaon = track->PidProbKaon() * track->ToF_probKaon();
   float pidProbProton = track->PidProbProton() * track->ToF_probProton();
   float sum = pidProbElectron + pidProbPion + pidProbKaon + pidProbProton;
   pidProbElectron /= sum;
   pidProbPion /= sum;
   pidProbKaon /= sum;
   pidProbProton /= sum;
   track->SetPidProbElectron(pidProbElectron);
   track->SetPidProbPion(pidProbPion);
   track->SetPidProbKaon(pidProbKaon);
   track->SetPidProbProton(pidProbProton);
}
#endif
