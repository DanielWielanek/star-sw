/***************************************************************************
 *
 * $Id: StHbtObjEvent.cc,v 1.21 2003/09/02 17:58:32 perev Exp $
 *
 * Author: Mike Lisa, Ohio State, lisa@mps.ohio-state.edu
 ***************************************************************************
 *
 * Description: part of STAR HBT Framework: StHbtMaker package
 *   HbtEvent is the "transient microDST"  Objects of this class are
 *   generated from the input data by a Reader, and then presented to
 *   the Cuts of the various active Analyses.
 *
 ***************************************************************************
 *
 *
 **************************************************************************/

#include "StHbtMaker/Infrastructure/StHbtObjEvent.h"

#include "PhysicalConstants.h"
#include "StHbtMaker/Base/StHbtKinkCut.h"
#include "StHbtMaker/Base/StHbtTrackCut.h"
#include "StHbtMaker/Base/StHbtV0Cut.h"
#include "StHbtMaker/Base/StHbtXiCut.h"
#include "StHbtMaker/Infrastructure/StHbtEvent.hh"
#include "StHbtMaker/Infrastructure/StHbtKink.hh"
#include "StHbtMaker/Infrastructure/StHbtObjTrack.h"
#include "StHbtMaker/Infrastructure/StHbtTrack.hh"
#include "StHbtMaker/Infrastructure/StHbtV0.hh"
#include "StHbtMaker/Infrastructure/StHbtXi.hh"
#include "SystemOfUnits.h"

#ifdef __ROOT__
ClassImp(StHbtObjEvent)
#endif

    //___________________
    // end Gael addition 24 Sept 02
    //___________________
    StHbtObjEvent::StHbtObjEvent() {
   mPrimVertPos[0] = -999.0;
   mPrimVertPos[1] = -999.0;
   mPrimVertPos[2] = -999.0;
   mTrackCollection = new TClonesArray(TClass::GetClass("StHbtObjTrack"), 2000);
   mMagneticField = 0.0;
}
//___________________
StHbtObjEvent::StHbtObjEvent(const StHbtEvent& ev, StHbtTrackCut* tCut) {  // copy constructor with track and v0 cuts
   // cout << "StHbtObjEvent::StHbtObjEvent(const StHbtEvent& ev, StHbtTrackCut* tCut, StHbtV0Cut* vCut, StHbtV0Cut*
   // kCut)" << endl;
   mEventNumber = ev.EventNumber();
   mRunNumber = ev.RunNumber();
   mCtbMultiplicity = ev.CtbMult();
   mZdcAdc[0] = ev.ZdcAdcEast();
   mZdcAdc[1] = ev.ZdcAdcWest();
   mTpcNhits = ev.NumberOfTpcHits();
   mNumberOfTracks = ev.NumberOfTracks();
   mNumberOfGoodTracks = ev.NumberOfGoodTracks();
   mUncorrectedNumberOfPositivePrimaries = ev.UncorrectedNumberOfPositivePrimaries();
   mUncorrectedNumberOfNegativePrimaries = ev.UncorrectedNumberOfNegativePrimaries();
   mUncorrectedNumberOfPrimaries = ev.UncorrectedNumberOfPrimaries();
   mReactionPlane[0] = ev.ReactionPlane(0);
   mReactionPlane[1] = ev.ReactionPlaneSubEventDifference(0);
   mReactionPlanePtWgt[0] = ev.ReactionPlane(1);
   mReactionPlanePtWgt[1] = ev.ReactionPlaneSubEventDifference(1);
   mPrimVertPos[0] = ev.PrimVertPos()[0];
   mPrimVertPos[1] = ev.PrimVertPos()[1];
   mPrimVertPos[2] = ev.PrimVertPos()[2];
   mMagneticField = ev.MagneticField();
   mTriggerWord = ev.TriggerWord();
   mTriggerActionWord = ev.TriggerActionWord();
   for (int i = 0; i < 4; i++) mL3TriggerAlgorithm[i] = ev.L3TriggerAlgorithm(i);

   // create collections
   mTrackCollection = new TClonesArray(TClass::GetClass("StHbtObjTrack"), 2000);

   // copy track collection
   int itrack = 0;
   for (StHbtTrackIterator tIter = ev.TrackCollection()->begin(); tIter != ev.TrackCollection()->end(); tIter++) {
      if (!tCut || tCut->Pass(*tIter)) {
         //       StHbtTrack* trackCopy = new StHbtTrack(**tIter);
         //       mTrackCollection->push_back(trackCopy);
         new ((*mTrackCollection)[itrack++]) StHbtObjTrack(**tIter);
      }
   }
}
void StHbtObjEvent::CopyEvent(const StHbtEvent& ev, StHbtTrackCut* trc) {
   // cout << "StHbtObjEvent::StHbtObjEvent(const StHbtEvent& ev, StHbtTrackCut* tCut, StHbtV0Cut* vCut, StHbtV0Cut*
   // kCut)" << endl;
   mEventNumber = ev.EventNumber();
   mRunNumber = ev.RunNumber();
   mCtbMultiplicity = ev.CtbMult();
   mZdcAdc[0] = ev.ZdcAdcEast();
   mZdcAdc[1] = ev.ZdcAdcWest();
   mTpcNhits = ev.NumberOfTpcHits();
   mNumberOfTracks = ev.NumberOfTracks();
   mNumberOfGoodTracks = ev.NumberOfGoodTracks();
   mUncorrectedNumberOfPositivePrimaries = ev.UncorrectedNumberOfPositivePrimaries();
   mUncorrectedNumberOfNegativePrimaries = ev.UncorrectedNumberOfNegativePrimaries();
   mUncorrectedNumberOfPrimaries = ev.UncorrectedNumberOfPrimaries();
   mReactionPlane[0] = ev.ReactionPlane(0);
   mReactionPlane[1] = ev.ReactionPlaneSubEventDifference(0);
   mReactionPlanePtWgt[0] = ev.ReactionPlane(1);
   mReactionPlanePtWgt[1] = ev.ReactionPlaneSubEventDifference(1);
   mPrimVertPos[0] = ev.PrimVertPos()[0];
   mPrimVertPos[1] = ev.PrimVertPos()[1];
   mPrimVertPos[2] = ev.PrimVertPos()[2];
   mMagneticField = ev.MagneticField();
   mTriggerWord = ev.TriggerWord();
   mTriggerActionWord = ev.TriggerActionWord();
   for (int i = 0; i < 4; i++) mL3TriggerAlgorithm[i] = ev.L3TriggerAlgorithm(i);

   // create collections
   //   for (StHbtTrackIterator iter=mTrackCollection->begin();iter!=mTrackCollection->end();iter++){
   //     delete *iter;
   //   }
   mTrackCollection->Clear();
   int itrack = 0;
   // copy track collection
   for (StHbtTrackIterator tIter = ev.TrackCollection()->begin(); tIter != ev.TrackCollection()->end(); tIter++) {
      //    if ( !tCut || tCut->Pass(*tIter) ) {
      //       StHbtTrack* trackCopy = new StHbtTrack(**tIter);
      //       mTrackCollection->push_back(trackCopy);
      if ((!trc) || (trc->Pass(*tIter))) new ((*mTrackCollection)[itrack++]) StHbtObjTrack(**tIter);
      //    }
   }
   cout << "Returning event with  " << mTrackCollection->GetEntries() << " " << itrack << " tracks " << endl;
}

void StHbtObjEvent::CopyToEvent(StHbtEvent& ev) {
   ev.SetEventNumber(EventNumber());
   ev.SetRunNumber(RunNumber());
   ev.SetCtbMult(CtbMult());
   ev.SetZdcAdcEast(mZdcAdc[0]);
   ev.SetZdcAdcWest(mZdcAdc[1]);
   ev.SetNumberOfTpcHits(NumberOfTpcHits());
   ev.SetNumberOfTracks(NumberOfTracks());
   ev.SetNumberOfGoodTracks(NumberOfGoodTracks());
   ev.SetUncorrectedNumberOfPositivePrimaries(UncorrectedNumberOfPositivePrimaries());
   ev.SetUncorrectedNumberOfNegativePrimaries(UncorrectedNumberOfNegativePrimaries());
   ev.SetUncorrectedNumberOfPrimaries(UncorrectedNumberOfPrimaries());
   ev.SetReactionPlane(mReactionPlane[0], 0);
   ev.SetReactionPlane(mReactionPlanePtWgt[0], 1);
   ev.SetReactionPlaneError(mReactionPlane[1], 0);
   ev.SetReactionPlaneError(mReactionPlanePtWgt[1], 1);
   StHbtThreeVector mPVP(mPrimVertPos[0], mPrimVertPos[1], mPrimVertPos[2]);
   //   mPrimVertPos[0] = ev.PrimVertPos()[0];
   //   mPrimVertPos[1] = ev.PrimVertPos()[1];
   //   mPrimVertPos[2] = ev.PrimVertPos()[2];
   ev.SetPrimVertPos(mPrimVertPos);
   ev.SetMagneticField(mMagneticField);
   ev.SetTriggerWord(TriggerWord());
   ev.SetTriggerActionWord(TriggerActionWord());
   ev.SetL3TriggerAlgorithm(0, mL3TriggerAlgorithm[0]);
   ev.SetL3TriggerAlgorithm(1, mL3TriggerAlgorithm[1]);
   ev.SetL3TriggerAlgorithm(2, mL3TriggerAlgorithm[2]);
   ev.SetL3TriggerAlgorithm(3, mL3TriggerAlgorithm[3]);
   //  for ( int i=0; i<4; i++) mL3TriggerAlgorithm[i] = ev.L3TriggerAlgorithm(i);

   // create collections
   ev.TrackCollection()->clear();
   int itrack = 0;
   // copy track collection
   for (itrack = 0; itrack < mTrackCollection->GetEntries(); itrack++) {
      StHbtObjTrack* tri = (StHbtObjTrack*)mTrackCollection->At(itrack);
      StHbtTrack* trc = new StHbtTrack();
      tri->CopyToTrack(*trc);

      const StThreeVectorD p((double)tri->P()[0], (double)tri->P()[1], (double)tri->P()[2]);
      const StThreeVectorD origin((double)mPrimVertPos[0], (double)mPrimVertPos[1], (double)mPrimVertPos[2]);

      StPhysicalHelixD helix(p, origin, (double)mMagneticField * kilogauss, (double)(tri->Charge()));

      trc->SetHelix(helix);
      trc->SetTrackId(itrack + 1);

      ev.TrackCollection()->push_back(trc);
   }
   //  for ( StHbtTrackIterator tIter=ev.TrackCollection()->begin(); tIter!=ev.TrackCollection()->end(); tIter++) {
   //    if ( !tCut || tCut->Pass(*tIter) ) {
   //       StHbtTrack* trackCopy = new StHbtTrack(**tIter);
   //       mTrackCollection->push_back(trackCopy);
   //    if ((!trc) || (trc->Pass(*tIter)))
   //      new((*mTrackCollection)[itrack++]) StHbtObjTrack(**tIter);
   //    }
   //  }
   cout << "Returning event with  " << ev.TrackCollection()->size() << " " << itrack << " tracks " << endl;
}

//___________________
StHbtObjEvent::~StHbtObjEvent() {
#ifdef STHBTDEBUG
   cout << " StHbtObjEvent::~StHbtObjEvent() " << endl;
#endif
   //   for (StHbtTrackIterator iter=mTrackCollection->begin();iter!=mTrackCollection->end();iter++){
   //     delete *iter;
   //   }
   mTrackCollection->Clear();
   delete mTrackCollection;
}

void StHbtObjEvent::SetEventNumber(const unsigned short& event) { mEventNumber = event; }
void StHbtObjEvent::SetRunNumber(const int& runNum) { mRunNumber = runNum; }
void StHbtObjEvent::SetCtbMult(const unsigned short& mult) { mCtbMultiplicity = mult; }
void StHbtObjEvent::SetZdcAdcEast(const unsigned short& adc) { mZdcAdc[0] = adc; }
void StHbtObjEvent::SetZdcAdcWest(const unsigned short& adc) { mZdcAdc[1] = adc; }
void StHbtObjEvent::SetNumberOfTpcHits(const int& nhits) { mTpcNhits = nhits; }
void StHbtObjEvent::SetNumberOfTracks(const unsigned short& tracks) { mNumberOfTracks = tracks; }
void StHbtObjEvent::SetNumberOfGoodTracks(const unsigned short& tracks) { mNumberOfGoodTracks = tracks; }
void StHbtObjEvent::SetUncorrectedNumberOfPositivePrimaries(const unsigned int& tracks) {
   mUncorrectedNumberOfPositivePrimaries = tracks;
}
void StHbtObjEvent::SetUncorrectedNumberOfNegativePrimaries(const unsigned int& tracks) {
   mUncorrectedNumberOfNegativePrimaries = tracks;
}
void StHbtObjEvent::SetUncorrectedNumberOfPrimaries(const unsigned int& tracks) {
   mUncorrectedNumberOfPrimaries = tracks;
}
void StHbtObjEvent::SetReactionPlane(const float& rp, const int& wgt) {
   (wgt) ? mReactionPlanePtWgt[0] = rp : mReactionPlane[0] = rp;
}
void StHbtObjEvent::SetReactionPlaneError(const float& rp, const int& wgt) {
   SetReactionPlaneSubEventDifference(rp, wgt);
}
void StHbtObjEvent::SetReactionPlaneSubEventDifference(const float& rp, const int& wgt) {
   (wgt) ? mReactionPlanePtWgt[1] = rp : mReactionPlane[1] = rp;
}
void StHbtObjEvent::SetPrimVertPos(const StHbtThreeVector& vp) {
   mPrimVertPos[0] = vp[0];
   mPrimVertPos[1] = vp[1];
   mPrimVertPos[2] = vp[2];
}
void StHbtObjEvent::SetMagneticField(const double& magF) { mMagneticField = magF; }
void StHbtObjEvent::SetTriggerWord(const unsigned int& t) { mTriggerWord = t; }
void StHbtObjEvent::SetTriggerActionWord(const unsigned int& t) { mTriggerActionWord = t; }
void StHbtObjEvent::SetL3TriggerAlgorithm(const unsigned int& i, const unsigned int& t) { mL3TriggerAlgorithm[i] = t; }

unsigned short StHbtObjEvent::EventNumber() const { return mEventNumber; }
int StHbtObjEvent::RunNumber() const { return mRunNumber; }
unsigned short StHbtObjEvent::CtbMult() const { return mCtbMultiplicity; }
unsigned short StHbtObjEvent::ZdcAdcEast() const { return mZdcAdc[0]; }
unsigned short StHbtObjEvent::ZdcAdcWest() const { return mZdcAdc[1]; }
int StHbtObjEvent::NumberOfTpcHits() const { return mTpcNhits; }
unsigned short StHbtObjEvent::NumberOfTracks() const { return mNumberOfTracks; }
unsigned short StHbtObjEvent::NumberOfGoodTracks() const { return mNumberOfGoodTracks; }
unsigned int StHbtObjEvent::UncorrectedNumberOfPositivePrimaries() const {
   return mUncorrectedNumberOfPositivePrimaries;
}
unsigned int StHbtObjEvent::UncorrectedNumberOfNegativePrimaries() const {
   return mUncorrectedNumberOfNegativePrimaries;
}
unsigned int StHbtObjEvent::UncorrectedNumberOfPrimaries() const { return mUncorrectedNumberOfPrimaries; }
float StHbtObjEvent::ReactionPlane(const int& wgt) const { return (wgt) ? mReactionPlanePtWgt[0] : mReactionPlane[0]; }
float StHbtObjEvent::ReactionPlaneError(const int& wgt) const { return ReactionPlaneSubEventDifference(wgt); }
float StHbtObjEvent::ReactionPlaneSubEventDifference(const int& wgt) const {
   return (wgt) ? mReactionPlanePtWgt[0] : mReactionPlane[0];
}
TClonesArray* StHbtObjEvent::TrackCollection() const { return mTrackCollection; }
const float* StHbtObjEvent::PrimVertPos() const { return mPrimVertPos; }
double StHbtObjEvent::MagneticField() const { return mMagneticField; }
unsigned int StHbtObjEvent::TriggerWord() const { return mTriggerWord; }
unsigned int StHbtObjEvent::TriggerActionWord() const { return mTriggerActionWord; }
unsigned int StHbtObjEvent::L3TriggerAlgorithm(const unsigned int& i) const { return mL3TriggerAlgorithm[i]; }
