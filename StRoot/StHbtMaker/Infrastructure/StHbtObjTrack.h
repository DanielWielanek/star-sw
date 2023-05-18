/***************************************************************************
 *
 * $Id: StHbtObjTrack.hh,v 1.23 2003/09/02 17:58:32 perev Exp $
 *
 * Author: Mike Lisa, Ohio State, lisa@mps.ohio-state.edu
 ***************************************************************************
 *
 * Description: part of STAR HBT Framework: StHbtMaker package
 *    Intermediate format for particle.  This is built from the
 *    input particle format (e.g. StTrack of StEvent) and presented to
 *    the Analyses for ParticleCuts.
 *
 ***************************************************************************
 *
 *
 **************************************************************************/

#ifndef StHbtObjTrack_hh
#define StHbtObjTrack_hh

#include "StHbtMaker/Infrastructure/StHbtTrack.hh"
#include "StHbtMaker/Infrastructure/StHbtTypes.hh"
#include "StPhysicalHelixD.hh"
#include "Stiostream.h"

class StEvent;
class StTrack;
class StHbtTTreeTrack;
class StHbtTTreeEvent;
class StMuDst;
class StMuTrack;

class StHbtObjTrack : public TObject {
  public:
   StHbtObjTrack();
   StHbtObjTrack(const StHbtObjTrack&);  // copy constructor
   StHbtObjTrack(const StHbtTrack&);     // copy constructor from non-TObject track
   void CopyTrack(const StHbtTrack&);
   void CopyToTrack(StHbtTrack&);

   short TrackType() const;
   short Charge() const;
   short NHits() const;
   short NHitsPossible() const;
   short NHitsDedx() const;
   const float* NSigma() const;  // Fab private
   float NSigmaElectron() const;
   float NSigmaPion() const;
   float NSigmaKaon() const;
   float NSigmaProton() const;
   float PidProbElectron() const;
   float PidProbPion() const;
   float PidProbKaon() const;
   float PidProbProton() const;
   float dEdx() const;
   float DCAz() const;
   float DCAxy() const;
   float DCAzGlobal() const;
   float DCAxyGlobal() const;
   float ChiSquaredZ() const;
   float ChiSquaredXY() const;
   const double* P() const;
   float Pt() const;
   const double* PGlobal() const;
   float PtGlobal() const;
   const StPhysicalHelixD& Helix() const;
   const StPhysicalHelixD& HelixGlobal() const;
   unsigned int TopologyMap(const unsigned int word) const;
   short TrackId() const;

   void SetTrackType(const short&);
   void SetCharge(const short&);
   void SetNHits(const short&);
   void SetNHitsPossible(const short&);
   void SetNHitsDedx(const short&);
   void SetNSigmaElectron(const float&);
   void SetNSigmaPion(const float&);
   void SetNSigmaKaon(const float&);
   void SetNSigmaProton(const float&);
   void SetPidProbElectron(const float&);
   void SetPidProbPion(const float&);
   void SetPidProbKaon(const float&);
   void SetPidProbProton(const float&);
   void SetdEdx(const float&);
   void SetDCAxy(const float&);
   void SetDCAz(const float&);
   void SetDCAxyGlobal(const float&);
   void SetDCAzGlobal(const float&);
   void SetChiSquaredXY(const float&);
   void SetChiSquaredZ(const float&);
   void SetP(const StHbtThreeVector&);
   void SetPt(const float&);
   void SetPGlobal(const StHbtThreeVector&);
   void SetPtGlobal(const float&);
   void SetHelix(const StPhysicalHelixD&);
   void SetHelixGlobal(const StPhysicalHelixD&);
   void SetTopologyMap(const int word, const unsigned int map);
   void SetTrackId(const short&);

  private:
   char mCharge;
   // unsigned short mNHits;
   unsigned char mNHits;
   float mNSigmaElectron;
   float mNSigmaPion;
   float mNSigmaKaon;
   float mNSigmaProton;
   // float mPidProbElectron; // new
   // float mPidProbPion; // new
   // float mPidProbKaon; // new
   // float mPidProbProton; // new
   unsigned char mPidProbElectron;
   unsigned char mPidProbPion;
   unsigned char mPidProbKaon;
   unsigned char mPidProbProton;
   unsigned int mMap[2];

   double mP[3];
   double mHelixGlobalMomentum[3];
   double mHelixGlobalOrigin[3];
   double mHelixGlobalCharge;
   double mHelixGlobalField;
   float mChiXY;
   float mChiZ;
   // float mDCAxy;
   // float mDCAxyGlobal;
   // char mDCAxy;
   // char mDCAz;
   char mDCAxyGlobal;
   // char mDCAzGlobal;

#ifdef __ROOT__
   ClassDef(StHbtObjTrack, 2)
#endif
};

inline const float* StHbtObjTrack::NSigma() const { return &mNSigmaElectron; }  // Fab private
inline float StHbtObjTrack::PidProbElectron() const { return (double)mPidProbElectron / 200.; }
inline float StHbtObjTrack::PidProbPion() const { return (double)mPidProbPion / 200.; }
inline float StHbtObjTrack::PidProbKaon() const { return (double)mPidProbKaon / 200.; }
inline float StHbtObjTrack::PidProbProton() const { return (double)mPidProbProton / 200.; }
inline const double* StHbtObjTrack::PGlobal() const { return mP; }
inline float StHbtObjTrack::PtGlobal() const { return sqrt(mP[0] * mP[0] + mP[1] * mP[1]); }

inline void StHbtObjTrack::SetTopologyMap(const int word, const unsigned int map) { mMap[word] = map; }

inline float StHbtObjTrack::ChiSquaredZ() const { return mChiZ; }

inline float StHbtObjTrack::ChiSquaredXY() const { return mChiXY; }

inline void StHbtObjTrack::SetChiSquaredXY(const float& z) { mChiXY = z; }

inline void StHbtObjTrack::SetChiSquaredZ(const float& z) { mChiZ = z; }

inline void StHbtObjTrack::SetTrackId(const short& id) {}

inline short StHbtObjTrack::TrackType() const { return 0; }
inline short StHbtObjTrack::Charge() const { return mCharge; }
inline short StHbtObjTrack::NHits() const { return mNHits; }
inline short StHbtObjTrack::NHitsPossible() const { return 45; }
inline short StHbtObjTrack::NHitsDedx() const { return 45; }
inline float StHbtObjTrack::NSigmaElectron() const { return mNSigmaElectron; }
inline float StHbtObjTrack::NSigmaPion() const { return mNSigmaPion; }
inline float StHbtObjTrack::NSigmaKaon() const { return mNSigmaKaon; }
inline float StHbtObjTrack::NSigmaProton() const { return mNSigmaProton; }
inline float StHbtObjTrack::dEdx() const { return 0; }

// inline float StHbtObjTrack::DCAxy() const {return mDCAxy;}
inline float StHbtObjTrack::DCAz() const { return 0; }
// inline float StHbtObjTrack::DCAxyGlobal() const {return mDCAxyGlobal;}
inline float StHbtObjTrack::DCAzGlobal() const { return 0; }
inline float StHbtObjTrack::DCAxy() const { return 0; }
// inline float StHbtObjTrack::DCAz() const {return mDCAz/40.0;}
inline float StHbtObjTrack::DCAxyGlobal() const { return (double)mDCAxyGlobal / 40.0; }
// inline float StHbtObjTrack::DCAzGlobal() const {return mDCAzGlobal/40.0;}
inline const double* StHbtObjTrack::P() const { return mP; }
inline float StHbtObjTrack::Pt() const { return sqrt(mP[0] * mP[0] + mP[1] * mP[1]); }
inline const StPhysicalHelixD& StHbtObjTrack::Helix() const {
   StThreeVector<double> mom(mHelixGlobalMomentum[0], mHelixGlobalMomentum[1], mHelixGlobalMomentum[2]);
   StThreeVector<double> origin(mHelixGlobalOrigin[0], mHelixGlobalOrigin[1], mHelixGlobalOrigin[2]);
   StPhysicalHelixD* tH = (new StPhysicalHelixD(mom, origin, mHelixGlobalCharge, mHelixGlobalField));
   return *tH;
}
inline const StPhysicalHelixD& StHbtObjTrack::HelixGlobal() const {
   StThreeVector<double> mom(mHelixGlobalMomentum[0], mHelixGlobalMomentum[1], mHelixGlobalMomentum[2]);
   StThreeVector<double> origin(mHelixGlobalOrigin[0], mHelixGlobalOrigin[1], mHelixGlobalOrigin[2]);
   StPhysicalHelix* tH = (new StPhysicalHelixD(mom, origin, mHelixGlobalCharge, mHelixGlobalField));
   return *tH;
}
inline unsigned int StHbtObjTrack::TopologyMap(const unsigned int word) const { return mMap[word]; }
inline short StHbtObjTrack::TrackId() const { return 0; }

#endif
