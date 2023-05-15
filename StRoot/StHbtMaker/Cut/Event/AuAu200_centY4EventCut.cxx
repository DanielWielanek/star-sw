#include "StHbtMaker/Cut/Event/AuAu200_centY4EventCut.h"

#include <cstdio>

#ifdef __ROOT__
ClassImp(AuAu200_centY4EventCut)
#endif

    AuAu200_centY4EventCut::AuAu200_centY4EventCut() {
   mNEventsPassed = mNEventsFailed = 0;
}

bool AuAu200_centY4EventCut::Pass(const StHbtEvent* event) {
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

   if (fabs(VertexXPos) < 10e-5 && fabs(VertexYPos) < 10e-5 && fabs(VertexZPos) < 10e-5) return false;

   cout << "AuAu200_centY4EventCut:: VertexZPos: " << mVertZPos[0] << " < " << VertexZPos << " < " << mVertZPos[1]
        << endl;

   // if (fabs(VertexZPos)>=30) return false;

   if (!(event->triggerIdCollection().nominal().isTrigger(15007) ||
         // event->triggerIdCollection().nominal().isTrigger(15105) ||
         event->triggerIdCollection().nominal().isTrigger(15003) ||
         // event->triggerIdCollection().nominal().isTrigger(25105) ||
         event->triggerIdCollection().nominal().isTrigger(25007))) {
      cout << "AuAu200_cent_Y4EventCut:: Wrong Trigger !" << endl;
      return false;
   }
   if (event->triggerIdCollection().nominal().isTrigger(15003)) {
      if (VertexZPos <= -10 || VertexZPos >= 50) return false;
   } else {
      if (fabs(VertexZPos) >= 30) return false;
   }

   cout << "AuAu200_centY4EventCut::event->TriggerWord() = " << event->TriggerWord() << endl;
   cout << "AuAu200_centY4EventCut::event->TriggerActionWord() = " << event->TriggerActionWord() << endl;
   bool goodEvent = ((VertexZPos > mVertZPos[0]) && (VertexZPos < mVertZPos[1]));

   if (goodEvent) {
      int multTPC = event->UncorrectedNumberOfPrimaries();
      int multFTPCeast = event->UncorrectedNumberOfFtpcEastPrimaries();

      cout << "AuAu200_centY4EventCut:: TPC multiplicity: " << mEventMult[0] << " < " << multTPC << " < "
           << mEventMult[1] << endl;
      cout << "AuAu200_centY4EventCut:: FTPC east multiplicity: " << mFtpcEventMult[0] << " <= " << multFTPCeast
           << " =< " << mFtpcEventMult[1] << endl;
      goodEvent = (goodEvent && (multTPC >= mEventMult[0]) && (multTPC <= mEventMult[1]));
   }

   goodEvent ? mNEventsPassed++ : mNEventsFailed++;
   cout << "AuAu200_centY4EventCut:: return : " << goodEvent << endl;

   return (goodEvent);
}

//------------------------------
StHbtString AuAu200_centY4EventCut::Report() {
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
