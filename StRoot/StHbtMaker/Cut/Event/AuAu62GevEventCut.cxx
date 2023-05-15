//-----------------------------------------------------
// Event cut for 62GeV AuAu 2004 Run
// Based on Zibi's dAuEventCut class
//
// Cut values are based on algorithm from
// www.star.bnl.gov/protected/common/common2004/trigger2004/62gev/62gevFaq.html
//
// SP 08/2004
//-----------------------------------------------------
#include "StHbtMaker/Cut/Event/AuAu62GevEventCut.h"

#include <cstdio>

#ifdef __ROOT__
ClassImp(AuAu62GevEventCut)
#endif

    AuAu62GevEventCut::AuAu62GevEventCut() {
   mNEventsPassed = mNEventsFailed = 0;
}

// int AuAu62GevEventCut::CheckId(int runnr);

//------------------------------
bool AuAu62GevEventCut::Pass(const StHbtEvent* event) {
   // remnants of dAu analysis.
   // Bad run table for 62 GeV data does not exist (yet?)
   //
   if (!CheckId(event->RunNumber())) {
      cout << "AuAu62GevEventCut:: BAD RUN (RunNumber=" << event->RunNumber() << ")" << endl;
      return false;
   }

   mtriggerIds = event->triggerIdCollection().nominal().triggerIds();

   unsigned int temp;
   unsigned int jj = 0;

   vector<unsigned int>::iterator i = mtriggerIds.begin();

   for (i = mtriggerIds.begin(); i != mtriggerIds.end(); i++) {
      temp = *i;
      if (temp != 0) cout << "TriggerId(" << jj << ")=" << temp << endl;
      jj++;
   }
   cout << "CtbMult " << event->CtbMult() << endl;
   cout << "Trigger Word=" << event->TriggerWord() << endl;
   cout << "Trigger Action Word=" << event->TriggerActionWord() << endl;

   double VertexXPos = event->PrimVertPos().x();
   double VertexYPos = event->PrimVertPos().y();
   double VertexZPos = event->PrimVertPos().z();

   if (fabs(VertexXPos) < 10e-5 && fabs(VertexYPos) < 10e-5 && fabs(VertexZPos) < 10e-5) {
      cout << "AuAu62GevEventCut:: BAD VERTEX" << endl;
      return false;
   }

   int multTPC = 0;
   // int multFTPCeast=0;
   // int ftpcInRun=0;

   cout << "AuAu62GevEventCut:: VertexZPos: " << mVertZPos[0] << " < " << VertexZPos << " < " << mVertZPos[1] << endl;

   if (fabs(VertexZPos) >= 30) return false;

   // cout<<"TrigIsd "<<event->triggerIdCollection().nominal().triggerIds()<<endl;

   if (!((event->triggerIdCollection().nominal().isTrigger(35004) ||
          event->triggerIdCollection().nominal().isTrigger(35007)) ||
         ((event->triggerIdCollection().nominal().isTrigger(35001) ||
           event->triggerIdCollection().nominal().isTrigger(35009)) &&
          event->CtbMult() > 15))) {
      cout << "AuAu62GevEventCut:: Wrong Trigger !" << endl;

      return false;
   }
   bool goodEvent = ((VertexZPos > mVertZPos[0]) && (VertexZPos < mVertZPos[1]));

   if (goodEvent) {
      //
      // Filtered multiplicity at this point: NFit Points>10, DCA<3cm, |y| <0.5
      //
      multTPC = event->UncorrectedNumberOfPrimaries();
      //  multFTPCeast = event->GetFtpcEastMultiplicity();
      // ftpcInRun = event->GetFtpcInRun();

      cout << "AuAu62GevEventCut:: Uncorrected primaries in TPC multiplicity: " << mEventMult[0] << " < " << multTPC
           << " < " << mEventMult[1] << endl;
      // cout << "AuAu62GevEventCut:: FTPC east multiplicity: " << mFtpcEventMult[0] << " <= " << multFTPCeast << " =< "
      // << mFtpcEventMult[1]<<endl;

      goodEvent = (goodEvent && (multTPC >= mEventMult[0]) && (multTPC <= mEventMult[1]));
      //		           && (multFTPCeast >= mFtpcEventMult[0]) && (multFTPCeast <= mFtpcEventMult[1]) );
   }

   goodEvent ? mNEventsPassed++ : mNEventsFailed++;
   cout << "AuAu62GevEventCut:: return : " << goodEvent << endl;

   return (goodEvent);
}

//------------------------------
StHbtString AuAu62GevEventCut::Report() {
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

bool AuAu62GevEventCut::CheckId(int runnr) {
   int nBadRuns = 1;
   int badList[1] = {1};

   for (int i = 0; i < nBadRuns; i++) {
      if (runnr == badList[i]) return false;
   }
   return true;
}
