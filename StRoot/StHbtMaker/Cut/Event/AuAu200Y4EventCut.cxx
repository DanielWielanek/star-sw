#include "StHbtMaker/Cut/Event/AuAu200Y4EventCut.h"

#include <cstdio>

#ifdef __ROOT__
ClassImp(AuAu200Y4EventCut)
#endif

    AuAu200Y4EventCut::AuAu200Y4EventCut() {
   mNEventsPassed = mNEventsFailed = 0;
}

bool AuAu200Y4EventCut::Pass(const StHbtEvent* event) {
   cout << "AuAu200Y4EventCut:: mTriggerSetupName  = " << mTrgSetupName << endl;
   int trg;

   switch (mTrgSetupName) {
      case 1:
         trg = 15003;
         break;
      case 2:
         trg = 15007;
         break;
      case 3:
         trg = 15105;
         break;
      case 4:
         trg = 25105;
         break;  // central
      case 5:
         trg = 25007;
         break;  // half-low
   }

   if (!(event->triggerIdCollection().nominal().isTrigger(trg)))  // m-b early, uncentered z_vertex minbias runs
   {
      cout << "AuAu200Y4EventCut:: Wrong Trigger Id!" << endl;
      return false;
   } else
      cout << "AuAu200Y4EventCut:: GOOD Trigger Id!" << endl;

   double VertexXPos = event->PrimVertPos().x();
   double VertexYPos = event->PrimVertPos().y();
   double VertexZPos = event->PrimVertPos().z();

   if (fabs(VertexXPos) < 10e-3 && fabs(VertexYPos) < 10e-3 && fabs(VertexZPos) < 10e-3) return false;

   cout << "AuAu200Y4EventCut:: VertexZPos: " << mVertZPos[0] << " < " << VertexZPos << " < " << mVertZPos[1] << endl;

   //  if (fabs(VertexZPos)>=30) return false;
   cout << "AuAu200Y4EventCut::event->TriggerWord() = " << event->TriggerWord() << endl;
   cout << "AuAu200Y4EventCut::event->TriggerActionWord() = " << event->TriggerActionWord() << endl;
   bool goodEvent = ((VertexZPos > mVertZPos[0]) && (VertexZPos < mVertZPos[1]));

   if (goodEvent) {
      int multTPC = event->UncorrectedNumberOfPrimaries();
      int multFTPCeast = event->UncorrectedNumberOfFtpcEastPrimaries();

      cout << "AuAu200Y4EventCut:: TPC multiplicity: " << mEventMult[0] << " < " << multTPC << " < " << mEventMult[1]
           << endl;
      cout << "AuAu200Y4EventCut:: FTPC east multiplicity: " << mFtpcEventMult[0] << " <= " << multFTPCeast << " =< "
           << mFtpcEventMult[1] << endl;
      goodEvent = (goodEvent && (multTPC >= mEventMult[0]) && (multTPC <= mEventMult[1]));
   }

   goodEvent ? mNEventsPassed++ : mNEventsFailed++;
   cout << "AuAu200Y4EventCut:: return : " << goodEvent << endl;

   return (goodEvent);
}

//------------------------------
StHbtString AuAu200Y4EventCut::Report() {
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
