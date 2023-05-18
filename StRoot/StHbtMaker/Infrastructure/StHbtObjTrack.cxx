/***************************************************************************
 *
 * $Id: StHbtObjTrack.cc,v 1.16 2003/03/18 14:41:48 kisiel Exp $
 *
 * Author: Frank Laue, Ohio State, laue@mps.ohio-state.edu
 ***************************************************************************
 *
 * Description: part of STAR HBT Framework: StHbtMaker package
 * Implementation of methods
 *
 ***************************************************************************
 *
 *
 ****************************************************************************/

#include "StHbtMaker/Infrastructure/StHbtObjTrack.h"
#ifdef __ROOT__
#include "StEvent/StEnumerations.h"
#include "StEventUtilities/StuProbabilityPidAlgorithm.h"
#include "StHbtMaker/Infrastructure/StHbtAihongPid.h"
#include "StHbtMaker/Infrastructure/StHbtTTreeEvent.h"
#include "StHbtMaker/Infrastructure/StHbtTTreeTrack.h"
#endif

#ifdef __ROOT__
ClassImp(StHbtObjTrack)
#endif

    StHbtObjTrack::StHbtObjTrack(const StHbtObjTrack& t) {  // copy constructor
   mCharge = t.mCharge;
   mNHits = t.mNHits;
   mNSigmaElectron = t.mNSigmaElectron;
   mNSigmaPion = t.mNSigmaPion;
   mNSigmaKaon = t.mNSigmaKaon;
   mNSigmaProton = t.mNSigmaProton;
   mPidProbElectron = t.mPidProbElectron;
   mPidProbPion = t.mPidProbPion;
   mPidProbKaon = t.mPidProbKaon;
   mPidProbProton = t.mPidProbProton;
   mP[0] = t.mP[0];
   mP[1] = t.mP[1];
   mP[2] = t.mP[2];
   mHelixGlobalMomentum[0] = t.mHelixGlobalMomentum[0];
   mHelixGlobalMomentum[1] = t.mHelixGlobalMomentum[1];
   mHelixGlobalMomentum[2] = t.mHelixGlobalMomentum[2];
   mHelixGlobalOrigin[0] = t.mHelixGlobalOrigin[0];
   mHelixGlobalOrigin[1] = t.mHelixGlobalOrigin[1];
   mHelixGlobalOrigin[2] = t.mHelixGlobalOrigin[2];
   mHelixGlobalCharge = t.mHelixGlobalCharge;
   mHelixGlobalField = t.mHelixGlobalField;
   mMap[0] = t.mMap[0];
   mMap[1] = t.mMap[1];
   // mDCAxy = t.mDCAxy;
   mDCAxyGlobal = t.mDCAxyGlobal;
   mChiZ = t.mChiZ;
   mChiXY = t.mChiXY;
};
//___________________________________________________
StHbtObjTrack::StHbtObjTrack(const StHbtTrack& t) {  // copy constructor of StHbtTrack
   mCharge = t.Charge();
   // mNHits = t.NHits();
   mNHits = t.NHits() > 255 ? 255 : (unsigned char)t.NHits();
   mNSigmaElectron = t.NSigmaElectron();
   mNSigmaPion = t.NSigmaPion();
   mNSigmaKaon = t.NSigmaKaon();
   mNSigmaProton = t.NSigmaProton();
   mPidProbElectron = (unsigned char)(t.PidProbElectron() * 200.);
   mPidProbPion = (unsigned char)(t.PidProbPion() * 200.);
   mPidProbKaon = (unsigned char)(t.PidProbKaon() * 200.);
   mPidProbProton = (unsigned char)(t.PidProbProton() * 200.);
   mP[0] = t.P()[0];
   mP[1] = t.P()[1];
   mP[2] = t.P()[2];
   mHelixGlobalCharge = t.HelixGlobal().charge(1);
   mHelixGlobalField = -t.HelixGlobal().h() / mHelixGlobalCharge;
   mHelixGlobalMomentum[0] = t.HelixGlobal().momentum(mHelixGlobalField).x();
   mHelixGlobalMomentum[1] = t.HelixGlobal().momentum(mHelixGlobalField).y();
   mHelixGlobalMomentum[2] = t.HelixGlobal().momentum(mHelixGlobalField).z();
   mHelixGlobalOrigin[0] = t.HelixGlobal().x(0);
   mHelixGlobalOrigin[1] = t.HelixGlobal().y(0);
   mHelixGlobalOrigin[2] = t.HelixGlobal().z(0);
   mMap[0] = t.TopologyMap(0);
   mMap[1] = t.TopologyMap(1);
   // mDCAxy = t.DCAxy();
   // mDCAxyGlobal = t.DCAxyGlobal();
   // mDCAxy = t.DCAxy()>3.0 ? mDCAxy=UCHAR_MAX : mDCAxy=t.DCAxy()*40.0;
   // mDCAz = if (t.DCAz()>3.0) mDCAz=UCHAR_MAX; else mDCAz=t.DCAz()*40.0;
   mDCAxyGlobal = t.DCAxyGlobal() > 3.0 ? mDCAxyGlobal = 255 : mDCAxyGlobal = (unsigned char)(t.DCAxyGlobal() * 40.0);
   // mDCAzGlobal = if (t.DCAzGlobal()>3.0) mDCAzGlobal=UCHAR_MAX; else mDCAzGlobal=t.DCAzGlobal()*40.0;
   mChiZ = t.ChiSquaredZ();
   mChiXY = t.ChiSquaredXY();
};
//___________________________________________________
void StHbtObjTrack::CopyTrack(const StHbtTrack& t) {  // copy constructor
   mCharge = t.Charge();
   // mNHits = t.NHits();
   mNHits = t.NHits() > 255 ? 255 : (unsigned char)t.NHits();
   mNSigmaElectron = t.NSigmaElectron();
   mNSigmaPion = t.NSigmaPion();
   mNSigmaKaon = t.NSigmaKaon();
   mNSigmaProton = t.NSigmaProton();
   mPidProbElectron = (unsigned char)(t.PidProbElectron() * 200.);
   mPidProbPion = (unsigned char)(t.PidProbPion() * 200.);
   mPidProbKaon = (unsigned char)(t.PidProbKaon() * 200.);
   mPidProbProton = (unsigned char)(t.PidProbProton() * 200.);
   mP[0] = t.P()[0];
   mP[1] = t.P()[1];
   mP[2] = t.P()[2];
   mHelixGlobalCharge = t.HelixGlobal().charge(1);
   mHelixGlobalField = -t.HelixGlobal().h() / mHelixGlobalCharge;
   mHelixGlobalMomentum[0] = t.HelixGlobal().momentum(mHelixGlobalField).x();
   mHelixGlobalMomentum[1] = t.HelixGlobal().momentum(mHelixGlobalField).y();
   mHelixGlobalMomentum[2] = t.HelixGlobal().momentum(mHelixGlobalField).z();
   mHelixGlobalOrigin[0] = t.HelixGlobal().x(0);
   mHelixGlobalOrigin[1] = t.HelixGlobal().y(0);
   mHelixGlobalOrigin[2] = t.HelixGlobal().z(0);
   mMap[0] = t.TopologyMap(0);
   mMap[1] = t.TopologyMap(1);
   // mDCAxy = t.DCAxy();
   // mDCAxyGlobal = t.DCAxyGlobal();
   // mDCAxy = t.DCAxy()>3.0 ? mDCAxy=UCHAR_MAX : mDCAxy=t.DCAxy()*40.0;
   // mDCAz = if (t.DCAz()>3.0) mDCAz=UCHAR_MAX; else mDCAz=t.DCAz()*40.0;
   mDCAxyGlobal = t.DCAxyGlobal() > 3.0 ? mDCAxyGlobal = 255 : mDCAxyGlobal = (unsigned char)(t.DCAxyGlobal() * 40.0);
   // mDCAzGlobal = if (t.DCAzGlobal()>3.0) mDCAzGlobal=UCHAR_MAX; else mDCAzGlobal=t.DCAzGlobal()*40.0;
};

void StHbtObjTrack::CopyToTrack(StHbtTrack& t) {
   t.SetTrackType(TrackType());
   t.SetCharge(Charge());
   t.SetNHits(NHits());
   t.SetNHitsPossible(NHitsPossible());
   t.SetNHitsDedx(NHitsDedx());
   t.SetNSigmaElectron(NSigmaElectron());
   t.SetNSigmaPion(NSigmaPion());
   t.SetNSigmaKaon(NSigmaKaon());
   t.SetNSigmaProton(NSigmaProton());
   t.SetPidProbElectron(PidProbElectron());
   t.SetPidProbPion(PidProbPion());
   t.SetPidProbKaon(PidProbKaon());
   t.SetPidProbProton(PidProbProton());
   t.SetdEdx(dEdx());
   t.SetDCAxy(DCAxy());
   t.SetDCAz(DCAz());
   t.SetDCAxyGlobal(DCAxyGlobal());
   t.SetDCAzGlobal(DCAzGlobal());
   t.SetChiSquaredXY(ChiSquaredXY());
   t.SetChiSquaredZ(ChiSquaredZ());

   StHbtThreeVector mPV(mP[0], mP[1], mP[2]);
   //   t.P()[0] = mP[0];
   //   t.P()[1] = mP[1];
   //   t.P()[2] = mP[2];
   t.SetP(mPV);
   t.SetPt(Pt());
   //   t.PGlobal()[0] = mP[0];
   //   t.PGlobal()[1] = mP[1];
   //   t.PGlobal()[2] = mP[2];
   t.SetPGlobal(mPV);
   t.SetPtGlobal(PtGlobal());
   //   StHbtThreeVector mPHM(mHelixMomentum[0], mHelixMomentum[1], mHelixMomentum[2]);
   //   StHbtThreeVector mPHO(mHelixOrigin[0], mHelixOrigin[1], mHelixOrigin[2]);
   //   StPhysicalHelixD tPH(mPHM, mPHO, mHelixField, mHelixCharge);
   //   t.SetHelix(tPH);

   StHbtThreeVector mPHGM(mHelixGlobalMomentum[0], mHelixGlobalMomentum[1], mHelixGlobalMomentum[2]);
   StHbtThreeVector mPHGO(mHelixGlobalOrigin[0], mHelixGlobalOrigin[1], mHelixGlobalOrigin[2]);
   StPhysicalHelixD tPHG(mPHGM, mPHGO, mHelixGlobalField, mHelixGlobalCharge);
   t.SetHelixGlobal(tPHG);

   //   t.HelixGlobalCharge = HelixGlobal().charge(1);
   //   t.HelixGlobalField = -t.HelixGlobal().h()/mHelixGlobalCharge;
   //   t.HelixGlobalMomentum[0] = HelixGlobal().momentum(mHelixGlobalField).x();
   //   t.HelixGlobalMomentum[1] = HelixGlobal().momentum(mHelixGlobalField).y();
   //   t.HelixGlobalMomentum[2] = HelixGlobal().momentum(mHelixGlobalField).z();
   //   t.HelixGlobalOrigin[0] = HelixGlobal().x(0);
   //   t.HelixGlobalOrigin[1] = HelixGlobal().y(0);
   //   t.HelixGlobalOrigin[2] = HelixGlobal().z(0);
   //   t.Map[0] = TopologyMap(0);
   //   t.Map[1] = TopologyMap(1);
   t.SetTopologyMap(0, mMap[0]);
   t.SetTopologyMap(1, mMap[1]);
   t.SetTrackId(TrackId());
}

//___________________________________________________
// void StHbtObjTrack::SetTrackType(const short& t){}
// void StHbtObjTrack::SetCharge(const short& ch){mCharge=ch;}
// void StHbtObjTrack::SetNHits(const short& nh){mNHits=nh;}
// void StHbtObjTrack::SetNHitsPossible(const short& nh){}
// void StHbtObjTrack::SetNHitsDedx(const short& nh){}
// void StHbtObjTrack::SetNSigmaElectron(const float& x){mNSigmaElectron = x;}
// void StHbtObjTrack::SetNSigmaPion(const float& x){mNSigmaPion = x;}
// void StHbtObjTrack::SetNSigmaKaon(const float& x){mNSigmaKaon = x;}
// void StHbtObjTrack::SetNSigmaProton(const float& x){mNSigmaProton = x;}
// void StHbtObjTrack::SetPidProbElectron(const float& x){mPidProbElectron = x;}
// void StHbtObjTrack::SetPidProbPion(const float& x){mPidProbPion = x;}
// void StHbtObjTrack::SetPidProbKaon(const float& x){mPidProbKaon = x;}
// void StHbtObjTrack::SetPidProbProton(const float& x){mPidProbProton = x;}
//
// void StHbtObjTrack::SetdEdx(const float& x){}
//
// void StHbtObjTrack::SetDCAxy(const float& x){ mDCAxy=x; }
// void StHbtObjTrack::SetDCAz(const float& x){}
////void StHbtObjTrack::SetDCAxyGlobal(const float& x){ mDCAxyGlobal=x; }
// void StHbtObjTrack::SetDCAzGlobal(const float& x){}
// void StHbtObjTrack::SetDCAxy(const float& x){ if (x>3.0) mDCAxy=UCHAR_MAX; else mDCAxy=x*40.0; }
////void StHbtObjTrack::SetDCAz(const float& x){ if (x>3.0) mDCAz=UCHAR_MAX; else mDCAz=x*40.0; }
// void StHbtObjTrack::SetDCAxyGlobal(const float& x){ if (x>3.0) mDCAxy=UCHAR_MAX; else mDCAxyGlobal=x*40.0; }
////void StHbtObjTrack::SetDCAzGlobal(const float& x){ if (x>3.0) mDCAzGlobal=UCHAR_MAX; else mDCAzGlobal=x*40.0; }
// void StHbtObjTrack::SetChiSquaredXY(const float& x){}
// void StHbtObjTrack::SetChiSquaredZ(const float& x){}
// void StHbtObjTrack::SetP(const StHbtThreeVector& p)
//{
//  mP[0] = p.x();
//  mP[1] = p.y();
//  mP[2] = p.z();
//}
// void StHbtObjTrack::SetPt(const float& pt){}
// void StHbtObjTrack::SetPGlobal(const StHbtThreeVector& p)
//{
//}
// void StHbtObjTrack::SetPtGlobal(const float& pt){}
// void StHbtObjTrack::SetHelix(const StPhysicalHelixD& h)
//{
//}
// void StHbtObjTrack::SetHelixGlobal(const StPhysicalHelixD& h){
//  mHelixGlobalCharge = h.charge(1);
//  mHelixGlobalField = -h.h()/mHelixGlobalCharge;
//  mHelixGlobalMomentum[0] = h.momentum(mHelixGlobalField).x();
//  mHelixGlobalMomentum[1] = h.momentum(mHelixGlobalField).y();
//  mHelixGlobalMomentum[2] = h.momentum(mHelixGlobalField).z();
//  mHelixGlobalOrigin[0] = h.x(0);
//  mHelixGlobalOrigin[1] = h.y(0);
//  mHelixGlobalOrigin[2] = h.z(0);
//
//}

StHbtObjTrack::StHbtObjTrack() {
   mCharge = 0;
   mNHits = 5;
   mNSigmaElectron = 0;
   mNSigmaPion = 0;
   mNSigmaKaon = 0;
   mNSigmaProton = 0;
   mPidProbElectron = 0;
   mPidProbPion = 0;
   mPidProbKaon = 0;
   mPidProbProton = 0;
   mP[0] = 0.0;
   mP[1] = 0.0;
   mP[2] = 0.0;
   mHelixGlobalMomentum[0] = 0.0;
   mHelixGlobalMomentum[1] = 0.0;
   mHelixGlobalMomentum[2] = 0.0;
   mHelixGlobalOrigin[0] = 0.0;
   mHelixGlobalOrigin[1] = 0.0;
   mHelixGlobalOrigin[2] = 0.0;
   mHelixGlobalCharge = 0.0;
   mHelixGlobalField = 0.0;
   mMap[0] = 0;
   mMap[1] = 0;
   // mDCAxy=0;
   // mDCAz=0;
   mDCAxyGlobal = 0;
   // mDCAzGlobal=0;
   mChiXY = mChiZ = 0;
};
