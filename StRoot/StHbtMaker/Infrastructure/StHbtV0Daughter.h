/*
 * StHbtV0Daughter.h
 *
 *  Created on: 2 mar 2017
 *      Author: Daniel Wielanek
 *		E-mail: daniel.wielanek@gmail.com
 *		Warsaw University of Technology, Faculty of Physics
 */
#ifndef STROOT_STWIELANRCF_STHBTV0DAUGHTER_H_
#define STROOT_STWIELANRCF_STHBTV0DAUGHTER_H_
#include "StHbtMaker/Infrastructure/StHbtTypes.hh"
#include "StPhysicalHelixD.hh"
class StHbtV0Daughter {
   /// will be calculated
   double mMergingParNotCalculated;
   double mWeightedAvSep;
   double mFracOfMergedRow;
   double mClosestRowAtDCA;
   double mNominalTpcSep;
   Float_t mQuality;
   ///
   StHbtThreeVector mTpcExitPoint;
   Float_t mBetaTof;
   Float_t mMassTof2;

   Int_t mHits;
   unsigned long mTopo[2];
   void calcMerged(StHbtV0Daughter *dau);
   void calcQuality(StHbtV0Daughter *dau);

  public:
   StHbtV0Daughter(){};
   virtual ~StHbtV0Daughter(){};
   void setNHits(int hits) { mHits = hits; };
   void CalculatePairVariables(StHbtV0Daughter *dau);
   void setTopoMap(unsigned long a, unsigned long b) {
      mTopo[0] = a;
      mTopo[1] = b;
   };
   inline unsigned long trackTopologyMap(unsigned int word) const { return mTopo[word]; }
   int getHits() const { return mHits; };
   void setBetaTof(Float_t betaTof) { mBetaTof = betaTof; };
   Float_t getToFBeta() const { return mBetaTof; };
   Float_t getToFMass2() const { return mMassTof2; };
   void setMassTof2(Float_t mass) { mMassTof2 = mass; };
   void setArray(int sect, float U, float Z, int index) {
      mSect[index] = sect;
      mU[index] = U;
      mZ[index] = Z;
   }
   StHbtThreeVector mNominalPosSample[11];
   int mSect[45];
   float mZ[45];
   float mU[45];
   double quality() { return mQuality; };
   virtual StHbtString Report() { return "zonl"; };
#ifdef __ROOT__
   ClassDef(StHbtV0Daughter, 1)
#endif
};

#endif /* STROOT_STWIELANRCF_STHBTV0DAUGHTER_H_ */
