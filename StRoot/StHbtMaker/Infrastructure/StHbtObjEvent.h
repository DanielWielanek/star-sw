/***************************************************************************
 *
 * $Id: StHbtEvent.hh,v 1.20 2003/01/17 16:46:22 mercedes Exp $
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

#ifndef StHbtObjEvent_hh
#define StHbtObjEvent_hh

#include "StHbtMaker/Infrastructure/StHbtEvent.hh"
#include "StHbtMaker/Infrastructure/StHbtKinkCollection.hh"
#include "StHbtMaker/Infrastructure/StHbtTrackCollection.hh"
#include "StHbtMaker/Infrastructure/StHbtTypes.hh"
#include "StHbtMaker/Infrastructure/StHbtV0Collection.hh"
#include "StHbtMaker/Infrastructure/StHbtXiCollection.hh"

class StHbtTrackCut;
class StHbtV0Cut;
class StHbtXiCut;
class StHbtKinkCut;
#ifdef __ROOT__
class StHbtTTreeEvent;
class StMuDst;
#endif

class StHbtObjEvent : public TObject {
  public:
   StHbtObjEvent();
   StHbtObjEvent(const StHbtEvent&, StHbtTrackCut* = 0);  // copy constructor with track and v0 cuts
   ~StHbtObjEvent();

   void CopyEvent(const StHbtEvent&, StHbtTrackCut* = 0);
   void CopyToEvent(StHbtEvent&);

   unsigned short EventNumber() const;
   int RunNumber() const;
   unsigned short CtbMult() const;
   unsigned short ZdcAdcEast() const;
   unsigned short ZdcAdcWest() const;
   int NumberOfTpcHits() const;
   unsigned short NumberOfTracks() const;
   unsigned short NumberOfGoodTracks() const;
   unsigned int UncorrectedNumberOfPositivePrimaries() const;
   unsigned int UncorrectedNumberOfNegativePrimaries() const;
   unsigned int UncorrectedNumberOfPrimaries() const;
   float ReactionPlane(const int& wgt = 0) const;
   float ReactionPlaneError(const int& wgt = 0) const;
   float ReactionPlaneSubEventDifference(const int& wgt = 0) const;
   const float* PrimVertPos() const;
   TClonesArray* TrackCollection() const;
   double MagneticField() const;
   unsigned int TriggerWord() const;
   unsigned int TriggerActionWord() const;
   unsigned int L3TriggerAlgorithm(const unsigned int& l = 0) const;

   void SetEventNumber(const unsigned short&);
   void SetRunNumber(const int&);
   void SetCtbMult(const unsigned short&);
   void SetZdcAdcEast(const unsigned short&);
   void SetZdcAdcWest(const unsigned short&);
   void SetNumberOfTpcHits(const int&);
   void SetNumberOfTracks(const unsigned short&);
   void SetNumberOfGoodTracks(const unsigned short&);
   void SetUncorrectedNumberOfPositivePrimaries(const unsigned int&);
   void SetUncorrectedNumberOfNegativePrimaries(const unsigned int&);
   void SetUncorrectedNumberOfPrimaries(const unsigned int&);
   void SetReactionPlane(const float&, const int& wgt = 0);
   void SetReactionPlaneError(const float&, const int& wgt = 0);
   void SetReactionPlaneSubEventDifference(const float&, const int& wgt = 0);
   void SetPrimVertPos(const StHbtThreeVector&);
   void SetMagneticField(const double&);
   void SetTriggerWord(const unsigned int&);
   void SetTriggerActionWord(const unsigned int&);
   void SetL3TriggerAlgorithm(const unsigned int&, const unsigned int&);

  private:
   unsigned short mEventNumber;  //
   unsigned short mRunNumber;
   unsigned short mCtbMultiplicity;     // Central Trigger Barrel
   unsigned short mZdcAdc[2];           // Zero-degree calorimeter
                                        // values east/west
   int mTpcNhits;                       // number of TPC hits
   unsigned short mNumberOfTracks;      // total number of TPC tracks
   unsigned short mNumberOfGoodTracks;  // number of "good" tracks
   unsigned int mUncorrectedNumberOfPositivePrimaries;
   unsigned int mUncorrectedNumberOfNegativePrimaries;
   unsigned int mUncorrectedNumberOfPrimaries;
   float mReactionPlane[2];       // reaction plane/error  //
   float mReactionPlanePtWgt[2];  // reaction plane/error with pT weight //
   double mMagneticField;         // magnetic field in Z direction
   unsigned int mTriggerWord;
   unsigned int mTriggerActionWord;
   unsigned int mL3TriggerAlgorithm[4];

   float mPrimVertPos[3];
   TClonesArray* mTrackCollection;

   friend class StHbtObjEventReader;

#ifdef __ROOT__
   ClassDef(StHbtObjEvent, 1)
#endif
};

#endif
