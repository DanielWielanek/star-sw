/***************************************************************************
 *
 * $Id: StHbtMultMeanPtAnalysisMB.cxx,v 1.5 2004/04/12 14:05:46 magestro Exp $
 *
 * Author: Randall Wells, Ohio State, rcwells@mps.ohio-state.edu
 ***************************************************************************
 *
 * Description: part of STAR HBT Framework: StHbtMaker package
 *      This is the Class for Analysis objects.  Each of the simultaneous
 *      Analyses running should have one of these instantiated.  They link
 *      into the Manager in an Analysis Collection.
 *
 ***************************************************************************
 *
 * $Log: StHbtMultMeanPtAnalysisMB.cxx,v $
 * Revision 1.5  2004/04/12 14:05:46  magestro
 * Added Vz dimension to event-mixing
 *
 * Revision 1.4  2002/05/28 14:04:07  rcwells
 * Added multiplicity binning to StHbtMultMeanPtAnalysisMB
 *
 * Revision 1.2  2001/07/20 20:03:53  rcwells
 * Added pT weighting and moved event angle cal. to event cut
 *
 * Revision 1.1  2001/07/13 20:03:14  rcwells
 * Adding reaction plane analysis
 *
 *
 **************************************************************************/

#include "StHbtMaker/Infrastructure/StHbtMultMeanPtAnalysisMB.h"

#include "PhysicalConstants.h"
#include "StHbtMaker/Base/StHbtTrackCut.h"
#include "StHbtMaker/Base/StHbtV0Cut.h"
#include "StHbtMaker/CorrFctn/NonId3DCorrFctnMB.h"
#include "StHbtMaker/CorrFctn/NonIdPurityCorrFctnMB.h"
#include "StHbtMaker/Cut/MultMeanPtEventCutMonitor.h"
#include "StHbtMaker/Infrastructure/StHbtParticleCollection.hh"
#include "StHbtMaker/Infrastructure/StHbtPicoEventCollectionVector.hh"
#include "StHbtMaker/Infrastructure/StHbtPicoEventCollectionVectorHideAway.hh"

#ifdef __ROOT__
ClassImp(StHbtMultMeanPtAnalysisMB)
#endif

    extern void FillHbtParticleCollection(StHbtParticleCut* partCut, StHbtEvent* hbtEvent,
                                          StHbtParticleCollection* partCollection);

//____________________________
StHbtMultMeanPtAnalysisMB::StHbtMultMeanPtAnalysisMB(unsigned int nBinsMeanPt, double MPtLo, double MPtHi,
                                                     unsigned int binsMult, double minMult, double maxMult,
                                                     unsigned int binsVert, double minVert, double maxVert) {
   //  mControlSwitch     = 0;
   mEventCut = 0;
   mFirstParticleCut = 0;
   mSecondParticleCut = 0;
   mPairCut = 0;
   //  mCorrFctnCollection= 0;
   //  mCorrFctnCollection = new StHbtCorrFctnCollection; //mem-leaks
   mUnderFlow = 0;
   mOverFlow = 0;
   if (mMixingBuffer) delete mMixingBuffer;

   // For now only for central data !!!
   //   if (maxMult<450) {
   //     cout << "StHbtMultMeanPtAnalysisMB::StHbtMultMeanPtAnalysisMB: Non-central collisions not implemented yet!" <<
   //     endl << "Aborting "<< endl; exit(0);
   //   }
   if (nBinsMeanPt == 0) {
      // Initialize table for central collisions
      mMultTable[0] = 400.0;
      mMultTable[1] = 470.0;
      mMultTable[2] = 500.0;
      mMultTable[3] = 530.0;
      mMultTable[4] = 570.0;
      mMultTable[5] = 1000.0;
      mMeanPtTable[0] = 0.5;
      mMeanPtTable[1] = 0.565;
      mMeanPtTable[2] = 0.575;
      mMeanPtTable[3] = 0.585;
      mMeanPtTable[4] = 0.595;
      mMeanPtTable[5] = 1.0;
      mMultTableSize = 5;
      mMeanPtTableSize = 5;
   } else {
      mMultTableSize = binsMult;
      mMeanPtTableSize = nBinsMeanPt;
   }

   mPicoEventCollectionVectorHideAway =
       new StHbtPicoEventCollectionVectorHideAway(mMultTableSize, 0.5, mMultTableSize + 0.5, mMeanPtTableSize, 0.5,
                                                  mMeanPtTableSize + 0.5, binsVert, minVert, maxVert);
   mBufFill = new TH3I("BufFill", "Mixing Buffer Fill Monitor", mMultTableSize, 0.5, mMultTableSize + 0.5,
                       mMeanPtTableSize, 0.5, mMeanPtTableSize + 0.5, binsVert, minVert, maxVert);

   mNBinsVertex = binsVert;
   mVertexZMin = minVert;
   mVertBinSize = (maxVert - minVert) / (binsVert);
};
//____________________________

StHbtMultMeanPtAnalysisMB::StHbtMultMeanPtAnalysisMB(const StHbtMultMeanPtAnalysisMB& a) : StHbtAnalysis() {
   // StHbtMultMeanPtAnalysisMB();
   mEventCut = 0;
   mFirstParticleCut = 0;
   mSecondParticleCut = 0;
   mPairCut = 0;
   //  mCorrFctnCollection= 0;
   //  mCorrFctnCollection = new StHbtCorrFctnCollection;
   mUnderFlow = 0;
   mOverFlow = 0;
   if (mMixingBuffer) delete mMixingBuffer;
   mPicoEventCollectionVectorHideAway =
       new StHbtPicoEventCollectionVectorHideAway(10, 0, 1000, 10, 0.0, 2.0, 10, -200, 200);
   mMeanPtTableSize = a.mMeanPtTableSize;
   mMultTableSize = a.mMultTableSize;
   mNBinsVertex = a.mNBinsVertex;
   mVertexZMin = a.mVertexZMin;
   mVertBinSize = a.mVertBinSize;

   // find the right event cut
   mEventCut = a.mEventCut->Clone();
   // find the right first particle cut
   mFirstParticleCut = a.mFirstParticleCut->Clone();
   // find the right second particle cut
   if (a.mFirstParticleCut == a.mSecondParticleCut)
      SetSecondParticleCut(mFirstParticleCut);  // identical particle hbt
   else
      mSecondParticleCut = a.mSecondParticleCut->Clone();

   mPairCut = a.mPairCut->Clone();

   if (mEventCut) {
      SetEventCut(mEventCut);  // this will set the myAnalysis pointer inside the cut
      cout << " StHbtMultMeanPtAnalysisMB::StHbtMultMeanPtAnalysisMB(const StHbtMultMeanPtAnalysisMB& a) - event cut "
              "set "
           << endl;
   }
   if (mFirstParticleCut) {
      SetFirstParticleCut(mFirstParticleCut);  // this will set the myAnalysis pointer inside the cut
      cout << " StHbtMultMeanPtAnalysisMB::StHbtMultMeanPtAnalysisMB(const StHbtMultMeanPtAnalysisMB& a) - first "
              "particle cut set "
           << endl;
   }
   if (mSecondParticleCut) {
      SetSecondParticleCut(mSecondParticleCut);  // this will set the myAnalysis pointer inside the cut
      cout << " StHbtMultMeanPtAnalysisMB::StHbtMultMeanPtAnalysisMB(const StHbtMultMeanPtAnalysisMB& a) - second "
              "particle cut set "
           << endl;
   }
   if (mPairCut) {
      SetPairCut(mPairCut);  // this will set the myAnalysis pointer inside the cut
      cout
          << " StHbtMultMeanPtAnalysisMB::StHbtMultMeanPtAnalysisMB(const StHbtMultMeanPtAnalysisMB& a) - pair cut set "
          << endl;
   }

   StHbtCorrFctnIterator iter;
   for (iter = a.mCorrFctnCollection->begin(); iter != a.mCorrFctnCollection->end(); iter++) {
      cout << " StHbtMultMeanPtAnalysisMB::StHbtMultMeanPtAnalysisMB(const StHbtMultMeanPtAnalysisMB& a) - looking for "
              "correlation functions "
           << endl;
      StHbtCorrFctn* fctn = (*iter)->Clone();
      if (fctn)
         AddCorrFctn(fctn);
      else
         cout << " StHbtMultMeanPtAnalysisMB::StHbtMultMeanPtAnalysisMB(const StHbtMultMeanPtAnalysisMB& a) - "
                 "correlation function not found "
              << endl;
   }

   mNumEventsToMix = a.mNumEventsToMix;

   cout
       << " StHbtMultMeanPtAnalysisMB::StHbtMultMeanPtAnalysisMB(const StHbtMultMeanPtAnalysisMB& a) - analysis copied "
       << endl;

   mBufFill = new TH3I(*a.mBufFill);
}
//____________________________
StHbtMultMeanPtAnalysisMB::~StHbtMultMeanPtAnalysisMB() {
   // now delete every PicoEvent in the EventMixingBuffer and then the Buffer itself
   delete mPicoEventCollectionVectorHideAway;
   delete mBufFill;
}

//____________________________
StHbtString StHbtMultMeanPtAnalysisMB::Report() {
   cout << "StHbtMultMeanPtAnalysisMB - constructing Report..." << endl;
   char Ctemp[200] = "";
   StHbtString temp = "-----------\nHbt StHbtMultMeanPtAnalysisMB Report:\n";
   //   sprintf(Ctemp,"Events are mixed in %d bins in the range %E cm to %E
   //   cm.\n",mReactionPlaneBins,mReactionPlane[0],mReactionPlane[1]);
   //  temp += Ctemp;
   sprintf(Ctemp, "Events underflowing: %d\n", mUnderFlow);
   temp += Ctemp;
   sprintf(Ctemp, "Events overflowing: %d\n", mOverFlow);
   temp += Ctemp;
   sprintf(Ctemp, "Now adding StHbtAnalysis(base) Report\n");
   temp += Ctemp;
   temp += StHbtAnalysis::Report();
   StHbtString returnThis = temp;
   return returnThis;
}
//_________________________
void StHbtMultMeanPtAnalysisMB::ProcessEvent(const StHbtEvent* hbtEvent) {
   // get right mixing buffer
   mVertexZ = hbtEvent->PrimVertPos().z();

   double meanpt = 0.0;
   int mult = 0;
   StHbtTrack* track;
   for (StHbtTrackIterator pIter = hbtEvent->TrackCollection()->begin(); pIter != hbtEvent->TrackCollection()->end();
        pIter++) {
      track = *pIter;
      if ((track->NHits() >= 10) && (track->DCAxy() < 3.0) && (fabs(track->P().pseudoRapidity()) < 0.5)) {
         meanpt += track->Pt();
         mult++;
      }
   }
   meanpt /= mult;

   int multiplicity = hbtEvent->UncorrectedNumberOfPrimaries();
   cout << "Event has z-vertex " << mVertexZ << " multiplicity " << multiplicity << " mean pt " << meanpt << endl;

   int ptbin, multbin;
   ptbin = 0;
   multbin = 0;

   if ((multiplicity < mMultTable[0]) || (meanpt < mMeanPtTable[0])) {
      cout << "Underflow" << endl;
      mUnderFlow++;
      mMixingBuffer = 0;
   } else if ((multiplicity > mMultTable[mMultTableSize]) || (meanpt > mMeanPtTable[mMeanPtTableSize])) {
      //    cerr << "Mixing buffer overflow: " << multiplicity << "\t" << meanpt << endl;
      cout << "Overflow" << endl;
      mOverFlow++;
      mMixingBuffer = 0;
   } else {
      while ((multiplicity > mMultTable[multbin]) && (multbin < mMultTableSize + 1)) {
         multbin++;
      }
      while ((meanpt > mMeanPtTable[ptbin]) && (ptbin < mMeanPtTableSize + 1)) {
         ptbin++;
      }

      mMixingBuffer = mPicoEventCollectionVectorHideAway->PicoEventCollection((double)multbin, (double)ptbin, mVertexZ);
      mBufFill->Fill(multbin, ptbin, mVertexZ);
   }

   if (!mMixingBuffer) {
      cout << "!mMixingBuffer" << endl;
      return;
   }

   mNBin = (ptbin - 1) * mMultTableSize * mNBinsVertex + (multbin - 1) * mNBinsVertex +
           (mVertexZ - mVertexZMin) / mVertBinSize;
   mMixingBinNumber = mNBin;

   cout << "Bin number is " << mNBin << " " << ptbin << " " << multbin << " "
        << (int)(mVertexZ - mVertexZMin) / mVertBinSize << endl;

   // call ProcessEvent() from StHbtAnalysis-bas
   //  StHbtAnalysis::ProcessEvent(hbtEvent);
   // Add event to processed events
   mPicoEvent = 0;  // we will get a new pico event, if not prevent corr. fctn to access old pico event
   mEventUsed = 0;
   AddEventProcessed();
   // startup for EbyE
   EventBegin(hbtEvent);
   // event cut and event cut monitor
   bool tmpPassEvent = mEventCut->Pass(hbtEvent);
   mEventCut->FillCutMonitor(hbtEvent, tmpPassEvent);
   if (tmpPassEvent) {
      cout << "StHbtMultMeanPtAnalysisMB::ProcessEvent() - Event has passed cut - build picoEvent from "
           << hbtEvent->TrackCollection()->size() << " tracks in TrackCollection" << endl;
      // OK, analysis likes the event-- build a pico event from it, using tracks the analysis likes...
      mPicoEvent = new StHbtPicoEvent;  // this is what we will make pairs from and put in Mixing Buffer
      // no memory leak. we will delete picoevents when they come out of the mixing buffer
      FillHbtParticleCollection(mFirstParticleCut, (StHbtEvent*)hbtEvent, mPicoEvent->FirstParticleCollection());
      if (!(AnalyzeIdenticalParticles()))
         FillHbtParticleCollection(mSecondParticleCut, (StHbtEvent*)hbtEvent, mPicoEvent->SecondParticleCollection());
      cout << "StHbtMultMeanPtAnalysisMB::ProcessEvent - #particles in First, Second Collections: "
           << mPicoEvent->FirstParticleCollection()->size() << " " << mPicoEvent->SecondParticleCollection()->size()
           << endl;

      if ((mPicoEvent->FirstParticleCollection()->size() > mMinSizePartCollection) &&
          (mPicoEvent->SecondParticleCollection()->size() > mMinSizePartCollection)) {
         mEventUsed = 1;
      }

      // mal - implement a switch which allows only using events with ParticleCollections containing a minimum
      // number of entries (jun2002)
      if ((mPicoEvent->FirstParticleCollection()->size() >= mMinSizePartCollection) &&
          (AnalyzeIdenticalParticles() || (mPicoEvent->SecondParticleCollection()->size() >= mMinSizePartCollection))) {
         cout << "Got Pico Event " << mPicoEvent << endl;
         cout << "Sending it to Pico Monitor " << mPicoMonitor << endl;
         if (mPicoMonitor) mPicoMonitor->Fill(mPicoEvent);

         //------------------------------------------------------------------------------
         //   Temporary comment:
         //      This whole section rewritten so that all pairs are built using the
         //      same code... easier to read and manage, and MakePairs() can be called by
         //      derived classes.  Also, the requirement of a full mixing buffer before
         //      mixing is removed.
         //                          Dan Magestro, 11/2002

         //------ Make real pairs. If identical, make pairs for one collection ------//

         if (AnalyzeIdenticalParticles()) {
            MakePairs("real", mPicoEvent->FirstParticleCollection(), 0, mNBin);
         } else {
            MakePairs("real", mPicoEvent->FirstParticleCollection(), mPicoEvent->SecondParticleCollection(), mNBin);
         }
         cout << "StHbtMultMeanPtAnalysisMB::ProcessEvent() - reals done ";

         //---- Make pairs for mixed events, looping over events in mixingBuffer ----//

         StHbtPicoEvent* storedEvent;
         StHbtPicoEventIterator mPicoEventIter;

         for (mPicoEventIter = MixingBuffer()->begin(); mPicoEventIter != MixingBuffer()->end(); mPicoEventIter++) {
            storedEvent = *mPicoEventIter;

            if (AnalyzeIdenticalParticles()) {
               MakePairs("mixed", mPicoEvent->FirstParticleCollection(), storedEvent->FirstParticleCollection(), mNBin);
            } else {
               MakePairs("mixed", mPicoEvent->FirstParticleCollection(), storedEvent->SecondParticleCollection(),
                         mNBin);

               MakePairs("mixed", storedEvent->FirstParticleCollection(), mPicoEvent->SecondParticleCollection(),
                         mNBin);
            }
         }
         cout << " - mixed done   " << endl;

         //--------- If mixing buffer is full, delete oldest event ---------//

         if (MixingBufferFull()) {
            delete MixingBuffer()->back();
            MixingBuffer()->pop_back();
         }

         //-------- Add current event (mPicoEvent) to mixing buffer --------//

         MixingBuffer()->push_front(mPicoEvent);

         // Temporary comment: End of rewritten section... Dan Magestro, 11/2002
         //------------------------------------------------------------------------------

      }  // if ParticleCollections are big enough (mal jun2002)
      else {
         delete mPicoEvent;
      }
   }                    // if currentEvent is accepted by currentAnalysis
   EventEnd(hbtEvent);  // cleanup for EbyE
                        // cout << "StHbtMultMeanPtAnalysisMB::ProcessEvent() - return to caller ... " << endl;
}

void StHbtMultMeanPtAnalysisMB::BufFillMonitorWrite() { mBufFill->Write(); }

void StHbtMultMeanPtAnalysisMB::BufFillMonitorSetName(const char* aName) { mBufFill->SetName(aName); }

void StHbtMultMeanPtAnalysisMB::SetMultBinBoundaries(int aNBins, double* aBinBounds) {
   if (aNBins > 99) {
      cout << "Mult table too big!" << endl;
      exit(0);
   }

   mMultTableSize = aNBins;
   for (int iter = 0; iter <= mMultTableSize; iter++) mMultTable[iter] = aBinBounds[iter];
   mMultTable[mMultTableSize] = aBinBounds[mMultTableSize];
}

void StHbtMultMeanPtAnalysisMB::SetMeanPtBinBoundaries(int aNBins, double* aBinBounds) {
   if (aNBins > 99) {
      cout << "MeanPt table too big!" << endl;
      exit(0);
   }

   mMeanPtTableSize = aNBins;
   for (int iter = 0; iter <= mMeanPtTableSize; iter++) mMeanPtTable[iter] = aBinBounds[iter];
   mMeanPtTable[mMeanPtTableSize] = aBinBounds[mMeanPtTableSize];
}

//_________________________
void StHbtMultMeanPtAnalysisMB::MakePairs(const char* typeIn, StHbtParticleCollection* partCollection1,
                                          StHbtParticleCollection* partCollection2, int nbin) {
   // Build pairs, check pair cuts, and call CFs' AddRealPair() or
   // AddMixedPair() methods. If no second particle collection is
   // specfied, make pairs within first particle collection.

   int type = -1;
   if (strcmp(typeIn, "real") == 0) {
      type = 1;
   } else if (strcmp(typeIn, "mixed") == 0) {
      type = 2;
   }

   StHbtPair* ThePair = new StHbtPair;

   StHbtCorrFctnIterator CorrFctnIter;

   StHbtParticleIterator PartIter1, PartIter2;

   StHbtParticleIterator StartOuterLoop = partCollection1->begin();  // always
   StHbtParticleIterator EndOuterLoop = partCollection1->end();      // will be one less if identical
   StHbtParticleIterator StartInnerLoop;
   StHbtParticleIterator EndInnerLoop;

   if (partCollection2) {                         // Two collections:
      StartInnerLoop = partCollection2->begin();  //   Full inner & outer loops
      EndInnerLoop = partCollection2->end();      //
   } else {                                       // One collection:
      EndOuterLoop--;                             //   Outer loop goes to next-to-last particle
      EndInnerLoop = partCollection1->end();      //   Inner loop goes to last particle
   }

   for (PartIter1 = StartOuterLoop; PartIter1 != EndOuterLoop; PartIter1++) {
      if (!partCollection2) {
         StartInnerLoop = PartIter1;
         StartInnerLoop++;
      }
      ThePair->SetTrack1(*PartIter1);

      for (PartIter2 = StartInnerLoop; PartIter2 != EndInnerLoop; PartIter2++) {
         ThePair->SetTrack2(*PartIter2);

         // The following lines have to be uncommented if you want pairCutMonitors
         // they are not in for speed reasons
         // bool tmpPassPair = mPairCut->Pass(ThePair);
         // mPairCut->FillCutMonitor(ThePair, tmpPassPair);
         // if ( tmpPassPair )

         //---- If pair passes cut, loop over CF's and add pair to real/mixed ----//

         if (mPairCut->Pass(ThePair)) {
            for (CorrFctnIter = mCorrFctnCollection->begin(); CorrFctnIter != mCorrFctnCollection->end();
                 CorrFctnIter++) {
               StHbtCorrFctn* CorrFctn = *CorrFctnIter;

               if (type == 1) {
                  NonId3DCorrFctnMB* cf3dmb = dynamic_cast<NonId3DCorrFctnMB*>(CorrFctn);
                  if (cf3dmb) cf3dmb->AddRealPairMB(ThePair, nbin);
                  NonIdPurityCorrFctnMB* cfpmb = dynamic_cast<NonIdPurityCorrFctnMB*>(CorrFctn);
                  if (cfpmb) cfpmb->AddRealPairMB(ThePair, nbin);
                  if ((!cf3dmb) && (!cfpmb)) CorrFctn->AddRealPair(ThePair);
               } else if (type == 2) {
                  NonId3DCorrFctnMB* cf3dmb = dynamic_cast<NonId3DCorrFctnMB*>(CorrFctn);
                  if (cf3dmb) cf3dmb->AddMixedPairMB(ThePair, nbin);
                  NonIdPurityCorrFctnMB* cfpmb = dynamic_cast<NonIdPurityCorrFctnMB*>(CorrFctn);
                  if (cfpmb) cfpmb->AddMixedPairMB(ThePair, nbin);
                  if ((!cf3dmb) && (!cfpmb)) CorrFctn->AddMixedPair(ThePair);
               } else
                  cout << "Problem with pair type, type = " << type << endl;
            }
         }

      }  // loop over second particle
   }     // loop over first particle

   delete ThePair;
}

inline double StHbtMultMeanPtAnalysisMB::VertexZ() { return mVertexZ; }
