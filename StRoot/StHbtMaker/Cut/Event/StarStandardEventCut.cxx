/***************************************************************************
 *
 * $Id: StarStandardEventCut.cxx $
 *
 * Author:  FR, LBL
 *
 ***************************************************************************
 *
 * Description: Event cut
 * - multiplicity: cut on ncharge (Y2 way, Y1 should be added at some point)
 *   pick from {1.,0.8,.7,.6,0.5,0.4,.3,.2,0.1,0.5,0.}
 *   e.g. setFractionOfCentrality(0.1,0.) for top 10%
 *   Default:  setFractionOfCentrality(1.,0.} (all)
 * - Vertex z position. Default: -1000. - 1000. (open)
 * - Y2 Trigger word. Default: all accepted
 * - L3 trigger algorithm. Default: no algorithm
 *
 ***************************************************************************
 *
 * $Log: StarStandardEventCut.cxx $
 *
 **************************************************************************/

#include "StHbtMaker/Cut/Event/StarStandardEventCut.h"

#include <Stsstream.h>

#include <cstdio>

#ifdef __ROOT__
ClassImp(StarStandardEventCut)
#endif

    StarStandardEventCut::StarStandardEventCut() {
   mNEventsPassed = mNEventsFailed = 0;
   setFractionOfCentrality(0.1, 0.);
   mVertZPos[0] = -1000.;
   mVertZPos[1] = 1000.;
   mNTriggerWords = 0;
   mTriggerWords = 0;
   mL3Algorithm = -1;
   mField = 0.;
}

StarStandardEventCut::StarStandardEventCut(const StarStandardEventCut& c) : StHbtEventCut(c) {
   mEventMult[0] = c.mEventMult[0];
   mEventMult[1] = c.mEventMult[1];
   mVertZPos[0] = c.mVertZPos[0];
   mVertZPos[1] = c.mVertZPos[1];
   mNEventsPassed = 0;
   mNEventsFailed = 0;
   mPassTrigger = 0;
   mPassVertex = 0;
   mBadField = 0;
   mPassMult = 0;
   mTot = 0;
   mField = 0.;

   mNTriggerWords = c.mNTriggerWords;
   mTriggerWords = new unsigned int[mNTriggerWords];
   for (int ti = 0; ti < mNTriggerWords; ti++) {
      mTriggerWords[ti] = c.mTriggerWords[ti];
   }
   mL3Algorithm = c.mL3Algorithm;
}

//
void StarStandardEventCut::SetAllTriggerWords() {
   mNTriggerWords = 0;
   if (mTriggerWords) delete[] mTriggerWords;
}
void StarStandardEventCut::SetTriggerWord(int aWord) {
   int mNTriggerWords = 1;
   if (mTriggerWords) delete[] mTriggerWords;
   mTriggerWords = new unsigned int[mNTriggerWords];
   mTriggerWords[0] = aWord;
}
void StarStandardEventCut::SetY2TriggerWords() {
   int mNTriggerWords = 3;
   if (mTriggerWords) delete[] mTriggerWords;
   mTriggerWords = new unsigned int[mNTriggerWords];
   mTriggerWords[0] = 4096;  // minBias 0x1000
   mTriggerWords[1] = 4352;  // central 0x1100
   mTriggerWords[2] = 8192;  // p-p minBias 0x2000
}
void StarStandardEventCut::SetL3AlgorithmOn(int aAlgorithm) { mL3Algorithm = aAlgorithm; }

void StarStandardEventCut::setFractionOfCentrality(double aMostCentralCrossSection, double aLeastCentralCrossSection) {
   double tCrossSectionSample[] = {1., 0.8, 0.7, 0.6, 0.5, 0.4, 0.3, 0.2, 0.1, 0.05, 0.};
   int ti = 0;
   while (aLeastCentralCrossSection < tCrossSectionSample[ti]) {
      ti++;
   }
   if (aLeastCentralCrossSection != tCrossSectionSample[ti]) {
      cerr << "Warning : rounding up fraction of cross section from " << aLeastCentralCrossSection << " to "
           << tCrossSectionSample[ti] << endl;
   }
   mEventMult[0] = ti;
   ti = 0;
   while (aMostCentralCrossSection < tCrossSectionSample[ti]) {
      ti++;
   }
   if (aMostCentralCrossSection != tCrossSectionSample[ti]) {
      cerr << "Warning : rounding up fraction of cross section from " << aMostCentralCrossSection << " to "
           << tCrossSectionSample[ti] << endl;
   }
   mEventMult[1] = ti;
}
//------------------------------
bool StarStandardEventCut::Pass(const StHbtEvent* event) {
   mTot++;

   bool tGood = (mNTriggerWords == 0);
   int ti = 0;
   while (!tGood && ti < mNTriggerWords) {
      tGood = (event->TriggerWord() == mTriggerWords[ti]);
      ti++;
   }
   if (mL3Algorithm > 0 && tGood) tGood = (event->L3TriggerAlgorithm(mL3Algorithm) != 0);

   mPassTrigger += (tGood ? 1 : 0);
   bool goodEvent = tGood;

   double VertexZPos = event->PrimVertPos().z();
   tGood = (VertexZPos > mVertZPos[0] && VertexZPos < mVertZPos[1]);
   mPassVertex += (tGood ? 1 : 0);
   goodEvent *= tGood;

   // AK FIX
   // If the multiplicity is set to some values, do not change it
   if (mField == -1000.0) mField = event->MagneticField();
   // END AK FIX

   if (mField != event->MagneticField()) {
      if (mField == 0.) {
         cout << mField << " " << event->MagneticField() << " ";
         mField = event->MagneticField();
         int tFieldTime2 = (int)floor(fabs(mField) / 4.97958 * 2. + 0.5);
         // cout << fabs(mField/4.97958) << " " << (fabs(mField/4.97958) == 1.)
         //   << " " << tFieldTime2 << endl;
         if (tFieldTime2 == 2) {
            int centFullFieldY2[] = {2, 14, 30, 56, 94, 146, 217, 312, 431, 510, 1000};
            cout << "Set the centrality selection for full field Y2" << endl;
            mEventMult[0] = centFullFieldY2[mEventMult[0]];
            mEventMult[1] = centFullFieldY2[mEventMult[1]];
         } else {
            // Done with P02gk, need update for P02gc
            int centHalfFieldY2[] = {2, 14, 32, 59, 98, 149, 216, 302, 409, 474, 1000};
            cout << "Set the centrality selection for 1/2 field Y2" << endl;
            mEventMult[0] = centHalfFieldY2[mEventMult[0]];
            mEventMult[1] = centHalfFieldY2[mEventMult[1]];
         }
      } else {
         mBadField++;
         // cerr << " ---------------------------------------" << endl
         //   << "Field has changed! " <<  endl
         //   << "Former field: " << mField << " | New field: "
         //   << event->MagneticField()<< endl;
      }
   }

   int mult = 0;
   //   StHbtTrack* track;
   //   for (StHbtTrackIterator pIter=event->TrackCollection()->begin();pIter!=event->TrackCollection()->end();pIter++){
   //     track = *pIter;
   //     if ((track->NHits()>=10)&&(track->DCAxy()<3.0)&&(fabs(track->P().pseudoRapidity())<0.5)){
   //       mult++;
   //     }
   //   }
   mult = event->UncorrectedNumberOfPrimaries();

   tGood = (mult > mEventMult[0] && mult < mEventMult[1]);
   mPassMult += (tGood ? 1 : 0);
   goodEvent *= tGood;

   goodEvent ? mNEventsPassed++ : mNEventsFailed++;
   cout << "StarStandardEventCut:: return mult min max: " << goodEvent << " " << mult << " " << mEventMult[0] << " "
        << mEventMult[1] << endl;

   return (goodEvent);
}

//------------------------------
StHbtString StarStandardEventCut::Report() {
   string Stemp;
   char Ctemp[100];
   sprintf(Ctemp, "\nMultiplicity:\t %d-%d", mEventMult[0], mEventMult[1]);
   Stemp = Ctemp;
   sprintf(Ctemp, "\nVertex Z-position:\t %E-%E", mVertZPos[0], mVertZPos[1]);
   Stemp += Ctemp;
   sprintf(Ctemp, "\nNumber of events which passed:\t%ld  Number which failed:\t%ld", mNEventsPassed, mNEventsFailed);
   Stemp += Ctemp;
   StHbtString returnThis = Stemp;
   return returnThis;
}

// ostrstream* StarStandardEventCut::finalReport() const{
//   ostrstream* tFinalReport = new ostrstream;
//   (*tFinalReport) << "_____ Event Cut _____ " << endl
// 		  << mEventMult[0] << " < mult < " << mEventMult[1] << endl
// 		  << mVertZPos[0] << " < Vertex Z < " << mVertZPos[1] << endl
// 		  << " >>> N events passed : " << mNEventsPassed << endl
// 		  << " >>> N events failed : " << mNEventsFailed << endl
// 		  << " >>> tot: " << mTot
// 		  << " t: " << mPassTrigger
// 		  << " v: " << mPassVertex
// 		  << " m: " << mPassMult
// 		  << " bf: " << mBadField << endl
// 		  << ends;
//   return tFinalReport;

// }
