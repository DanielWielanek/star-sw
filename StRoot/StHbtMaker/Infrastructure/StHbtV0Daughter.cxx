/*
 * StHbtV0Daughter.cxx
 *
 *  Created on: 2 mar 2017
 *      Author: Daniel Wielanek
 *		E-mail: daniel.wielanek@gmail.com
 *		Warsaw University of Technology, Faculty of Physics
 */
#include "StHbtV0Daughter.h"

void StHbtV0Daughter::calcMerged(StHbtV0Daughter* dau) {
   double mMaxDuInner = .8;
   double mMaxDzInner = 3.;
   double mMaxDuOuter = 1.4;
   double mMaxDzOuter = 3.2;
   mMergingParNotCalculated = 0;

   double tDu, tDz;
   int tN = 0;
   mFracOfMergedRow = 0.;
   mWeightedAvSep = 0.;
   double tDist;
   double tDistMax = 200.;
   for (int ti = 0; ti < 45; ti++) {
      if (mSect[ti] == dau->mSect[ti] && mSect[ti] != -1) {
         tDu = fabs(mU[ti] - dau->mU[ti]);
         tDz = fabs(mZ[ti] - dau->mZ[ti]);
         tN++;
         if (ti < 13) {
            mFracOfMergedRow += (tDu < mMaxDuInner && tDz < mMaxDzInner);
            tDist = ::sqrt(tDu * tDu / mMaxDuInner / mMaxDuInner + tDz * tDz / mMaxDzInner / mMaxDzInner);
            // mFracOfMergedRow += (tDu<mMaxDuInner && tDz<mMaxDzInner);
         } else {
            mFracOfMergedRow += (tDu < mMaxDuOuter && tDz < mMaxDzOuter);
            tDist = ::sqrt(tDu * tDu / mMaxDuOuter / mMaxDuOuter + tDz * tDz / mMaxDzOuter / mMaxDzOuter);
            // mFracOfMergedRow += (tDu<mMaxDuOuter && tDz<mMaxDzOuter);
         }
         if (tDist < tDistMax) {
            mClosestRowAtDCA = ti + 1;
            tDistMax = tDist;
         }
         mWeightedAvSep += tDist;
      }
   }
   if (tN > 0) {
      mWeightedAvSep /= tN;
      mFracOfMergedRow /= tN;
   } else {
      mClosestRowAtDCA = -1;
      mFracOfMergedRow = -1.;
      mWeightedAvSep = -1.;
   }
}

void StHbtV0Daughter::calcQuality(StHbtV0Daughter* dau) {
   unsigned long mapMask0 = 0xFFFFFF00;
   unsigned long mapMask1 = 0x1FFFFF;
   unsigned long padRow1To24Track1 = mTopo[0] & mapMask0;
   unsigned long padRow25To45Track1 = mTopo[1] & mapMask1;
   unsigned long padRow1To24Track2 = dau->mTopo[0] & mapMask0;
   unsigned long padRow25To45Track2 = dau->mTopo[1] & mapMask1;
   // AND logic
   unsigned long bothPads1To24 = padRow1To24Track1 & padRow1To24Track2;
   unsigned long bothPads25To45 = padRow25To45Track1 & padRow25To45Track2;
   // XOR logic
   unsigned long onePad1To24 = padRow1To24Track1 ^ padRow1To24Track2;
   unsigned long onePad25To45 = padRow25To45Track1 ^ padRow25To45Track2;
   unsigned long bitI;
   int ibits;
   int Quality = 0;
   double normQual = 0.0;
   int MaxQuality = mHits + dau->mHits;
   for (ibits = 8; ibits <= 31; ibits++) {
      bitI = 0;
      bitI |= 1UL << (ibits);
      if (onePad1To24 & bitI) {
         Quality++;
         continue;
      } else {
         if (bothPads1To24 & bitI) Quality--;
      }
   }
   for (ibits = 0; ibits <= 20; ibits++) {
      bitI = 0;
      bitI |= 1UL << (ibits);
      if (onePad25To45 & bitI) {
         Quality++;
         continue;
      } else {
         if (bothPads25To45 & bitI) Quality--;
      }
   }
   mQuality = (double)Quality / ((double)MaxQuality);
}

void StHbtV0Daughter::CalculatePairVariables(StHbtV0Daughter* dau) { calcQuality(dau); }
