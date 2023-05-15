#include "StHbtMaker/Cut/Event/piotrsTriggerIdEventCut.h"

#include <stdio.h>
#include <stdlib.h>

#include <cmath>
#include <iostream>
#include <vector>

#include "StHbtMaker/Base/StHbtEventCut.h"
#include "StHbtMaker/Infrastructure/StHbtString.hh"

using namespace std;

ClassImp(piotrsTriggerIdEventCut)

    piotrsTriggerIdEventCut::piotrsTriggerIdEventCut() {
   cout << "!!!!!piotrsTriggerIdEventCut!!!!!" << endl;
}

bool piotrsTriggerIdEventCut::Pass(const StHbtEvent* event) {
   if (fTriggerIds.size() == 0) {
      cerr << "fTriggerIds size == 0 " << endl;
      return true;
   }
   //  if (mVerbose) {
   cout << "Checking triggers... ";
   vector<unsigned int> mtriggerIds = event->triggerIdCollection().nominal().triggerIds();
   for (vector<unsigned int>::iterator i = mtriggerIds.begin(); i != mtriggerIds.end(); ++i) {
      cout << *i << " ";
   }
   cout << endl;
   //  }
   for (vector<unsigned int>::iterator checking = fTriggerIds.begin(); checking != fTriggerIds.end(); ++checking) {
      if (event->triggerIdCollection().nominal().isTrigger(*checking)) {
         return true;
      }
   }
   return false;
}

StHbtString piotrsTriggerIdEventCut::Report() {
   StHbtString retVal("piotrsTriggerIdEventCut triggerIds:");
   char buf[20];
   for (vector<unsigned int>::iterator i = fTriggerIds.begin(); i != fTriggerIds.end(); ++i) {
      retVal += " ";
      sprintf(buf, "%d", *i);
      retVal += buf;
   }
   return retVal;
}

piotrsTriggerIdEventCut* piotrsTriggerIdEventCut::Clone() { return 0; }
