#include "StHbtMaker/Cut/Event/AuAu11_centY6EventCut.h"

#include <math.h>

#include <cstdio>

#ifdef __ROOT__
ClassImp(AuAu11_centY6EventCut)
#endif

    AuAu11_centY6EventCut::AuAu11_centY6EventCut() {
   mNEventsPassed = mNEventsFailed = 0;
}
double AuAu11_centY6EventCut::getEtaSym(const StHbtEvent* event) {
   const double correctionSlope = -0.003029;
   const double correctionIntercept = 0.018610;
   int nEtaPositive = 0;
   int nEtaNegative = 0;
   StHbtTrackCollection* tracks = event->TrackCollection();
   for (StHbtTrackIterator it = tracks->begin(); it != tracks->end(); it++) {
      StHbtTrack* track = *it;
      if (track->P().z() > 0) {
         ++nEtaPositive;
      } else {
         ++nEtaNegative;
      }
   }

   double etaSym = ((double)(nEtaPositive - nEtaNegative) / (nEtaPositive + nEtaNegative)) *
                   (correctionSlope * event->PrimVertPos().z() + correctionIntercept) *
                   sqrt(nEtaPositive + nEtaNegative);
   return etaSym;
}

bool AuAu11_centY6EventCut::Pass(const StHbtEvent* event) {
   mtriggerIds = event->triggerIdCollection().nominal().triggerIds();
   unsigned int temp;
   unsigned int jj = 0;
   vector<unsigned int>::iterator i = mtriggerIds.begin();

   for (i = mtriggerIds.begin(); i != mtriggerIds.end(); i++) {
      temp = *i;
      if (temp != 0) cout << "TriggerId(" << jj << ")=" << temp << endl;
      jj++;
   }

   /*
   switch (mTrgSetupName)
       {
       case 1: trg = 15003; break; //minbias - what is it?? :-(
       case 2: trg = 15007; break; //minbis ( High | Mid | Low )
       case 3: trg = 15105; break; //cetral ( High | Mid | Low )
       case 4: trg = 15202; break; //central 50% ( High | Mid | Low )
       case 5: trg = 15210; break; //central 50% ( High | Mid | Low )
       case 6: trg = 15301; break; //strangle searche ( High | Mid | Low )
       case 7: trg = 25007; break; //minbias ( HalfHigh | HalfLow )
       case 8: trg = 25105; break; //central ( HalfHigh | HalfLow )
       case 9: trg = 25203; break; //minbias ( HalfHigh | HalfLow )
       case 10: trg= 25211; break; //minbias ( HalfHigh | HalfLow )
       case 11: trg= 25310; break; //rare trigger ( HalfHigh | HalfLow )
       }
 */
   /*
     if(!(event->triggerIdCollection().nominal().isTrigger(trg))) //m-b early, uncentered z_vertex minbias runs
     {
      cout<<"AuAu200_centY4EventCut:: Wrong Trigger Id!"<<endl;
        return false;
        }
     else
      cout<<"AuAu200_centY4EventCut:: GOOD Trigger Id!"<<endl;
   */
   double VertexXPos = event->PrimVertPos().x();
   double VertexYPos = event->PrimVertPos().y();
   double VertexZPos = event->PrimVertPos().z();
   double VertexRPos = sqrt(VertexXPos * VertexXPos + VertexYPos * VertexYPos);
   double etaSym = getEtaSym(event);

   if (fabs(VertexXPos) < 10e-5 && fabs(VertexYPos) < 10e-5 && fabs(VertexZPos) < 10e-5) return false;

   cout << "AuAu11_centY6EventCut:: VertexZPos: " << mVertZPos[0] << " < " << VertexZPos << " < " << mVertZPos[1]
        << endl;

   if (!(event->triggerIdCollection().nominal().isTrigger(310014))) {
      cout << "AuAu10_cent_Y6EventCut:: Wrong Trigger !" << endl;
      return false;
   }
   // cout<<"AuAu11_centY6EventCut::event->TriggerWord() = "<<event->TriggerWord()<<endl;
   // cout<<"AuAu11_centY6EventCut::event->TriggerActionWord() = "<<event->TriggerActionWord()<<endl;
   bool goodEvent = ((VertexZPos > mVertZPos[0]) && (VertexZPos < mVertZPos[1]) && (VertexRPos < mVertRPos));

   if (goodEvent) {
      int multTPC = event->UncorrectedNumberOfPrimaries();
      int multFTPCeast = event->UncorrectedNumberOfFtpcEastPrimaries();

      cout << "AuAu11_centY6EventCut:: TPC multiplicity: " << mEventMult[0] << " < " << multTPC << " < "
           << mEventMult[1] << endl;
      cout << "AuAu11_centY6EventCut:: FTPC east multiplicity: " << mFtpcEventMult[0] << " <= " << multFTPCeast
           << " =< " << mFtpcEventMult[1] << endl;
      goodEvent = (goodEvent && (multTPC >= mEventMult[0]) && (multTPC <= mEventMult[1]) && (fabs(etaSym) < 5.5));
   }

   goodEvent ? mNEventsPassed++ : mNEventsFailed++;
   cout << "AuAu11_centY6EventCut:: return : " << goodEvent << endl;

   return (goodEvent);
}

//------------------------------
StHbtString AuAu11_centY6EventCut::Report() {
   string Stemp;
   char Ctemp[400];
   sprintf(Ctemp, "\nTpc  Multiplicity:\t %d-%d", mEventMult[0], mEventMult[1]);
   Stemp = Ctemp;
   sprintf(Ctemp, "\nFtpc Multiplicity:\t %d-%d", mFtpcEventMult[0], mFtpcEventMult[1]);
   Stemp += Ctemp;
   sprintf(Ctemp, "\nVertex Z-position:\t %E-%E", mVertZPos[0], mVertZPos[1]);
   Stemp += Ctemp;
   sprintf(Ctemp, "\nNumber of events which passed:\t%ld  Number which failed:\t%ld", mNEventsPassed, mNEventsFailed);
   Stemp += Ctemp;

   StHbtString returnThis = Stemp;
   return returnThis;
}
