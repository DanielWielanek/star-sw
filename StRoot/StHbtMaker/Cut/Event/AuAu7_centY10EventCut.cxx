#include "StHbtMaker/Cut/Event/AuAu7_centY10EventCut.h"

#include <math.h>

#include <cstdio>

#ifdef __ROOT__
ClassImp(AuAu7_centY10EventCut)
#endif

    AuAu7_centY10EventCut::AuAu7_centY10EventCut() {
   mNEventsPassed = mNEventsFailed = 0;
}

double AuAu7_centY10EventCut::getEtaSym(const StHbtEvent* event) {
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

bool AuAu7_centY10EventCut::Pass(const StHbtEvent* event) {
   mtriggerIds = event->triggerIdCollection().nominal().triggerIds();
   unsigned int temp;
   unsigned int jj = 0;
   vector<unsigned int>::iterator i = mtriggerIds.begin();

   for (i = mtriggerIds.begin(); i != mtriggerIds.end(); i++) {
      temp = *i;
      if (temp != 0) cout << "TriggerId(" << jj << ")=" << temp << endl;
      jj++;
   }

   double VertexXPos = event->PrimVertPos().x();
   double VertexYPos = event->PrimVertPos().y();
   double VertexZPos = event->PrimVertPos().z();
   double VertexRPos = sqrt(VertexXPos * VertexXPos + VertexYPos * VertexYPos);

   if (fabs(VertexXPos) < 10e-5 && fabs(VertexYPos) < 10e-5 && fabs(VertexZPos) < 10e-5) return false;

   cout << "AuAu7_centY10EventCut:: VertexZPos: " << mVertZPos[0] << " < " << VertexZPos << " < " << mVertZPos[1]
        << endl;

   // if (fabs(VertexZPos)>=30) return false;
   /*
   if (!(event->triggerIdCollection().nominal().isTrigger(15007) ||
    //event->triggerIdCollection().nominal().isTrigger(15105) ||
    event->triggerIdCollection().nominal().isTrigger(15003) ||
    //event->triggerIdCollection().nominal().isTrigger(25105) ||
    event->triggerIdCollection().nominal().isTrigger(25007) )) {
       cout<<"AuAu39_cent_Y10EventCut:: Wrong Trigger !"<<endl;
       return false;
    }
    if (event->triggerIdCollection().nominal().isTrigger(15003)) {
    if (VertexZPos<=-10 || VertexZPos>=50) return false;
    }
    else {
    if (fabs(VertexZPos)>=30) return false;
    }
    */
   if (!(event->triggerIdCollection().nominal().isTrigger(290001) ||
         event->triggerIdCollection().nominal().isTrigger(290004))) {
      cout << "AuAu7xx_cent_Y10EventCut:: Wrong Trigger !" << endl;
      return false;
   }

   cout << "AuAu7_centY10EventCut::event->TriggerWord() = " << event->TriggerWord() << endl;
   cout << "AuAu7_centY10EventCut::event->TriggerActionWord() = " << event->TriggerActionWord() << endl;
   bool goodEvent = ((VertexZPos > mVertZPos[0]) && (VertexZPos < mVertZPos[1]) && (VertexRPos < mVertRPos));

   if (goodEvent) {
      int multTPC = event->UncorrectedNumberOfPrimaries();
      int multFTPCeast = event->UncorrectedNumberOfFtpcEastPrimaries();
      double etaSym = getEtaSym(event);

      cout << "AuAu7_centY10EventCut:: TPC multiplicity: " << mEventMult[0] << " < " << multTPC << " < "
           << mEventMult[1] << endl;
      cout << "AuAu7_centY10EventCut:: FTPC east multiplicity: " << mFtpcEventMult[0] << " <= " << multFTPCeast
           << " =< " << mFtpcEventMult[1] << endl;
      goodEvent = (goodEvent && (multTPC >= mEventMult[0]) && (multTPC <= mEventMult[1]) && (fabs(etaSym) < 5.5));
   }

   goodEvent ? mNEventsPassed++ : mNEventsFailed++;
   cout << "AuAu7_centY10EventCut:: return : " << goodEvent << endl;

   return (goodEvent);
}

//------------------------------
StHbtString AuAu7_centY10EventCut::Report() {
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
