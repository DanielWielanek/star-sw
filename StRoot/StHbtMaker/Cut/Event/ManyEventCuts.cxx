/*
 * EventCombinedCut.cxx
 *
 *  Created on: 15 maj 2023
 *      Author: Daniel Wielanek
 *		E-mail: daniel.wielanek@gmail.com
 *		Warsaw University of Technology, Faculty of Physics
 */
#include "StHbtMaker/Cut/Event/ManyEventCuts.h"

ManyEventCuts::ManyEventCuts() { mNEventsPassed = mNEventsFailed = 0; }

ManyEventCuts::ManyEventCuts(const ManyEventCuts& other) : StHbtEventCut(other) {
   for (unsigned int i = 0; mEventCuts.size(); i++) {
      mEventCuts.push_back(other.mEventCuts[i]);
   }
   mNEventsPassed = mNEventsFailed = 0;
}

StHbtString ManyEventCuts::Report() {
   string Stemp = "EventCombinedCut Report\n";
   char Ctemp[100];
   sprintf(Ctemp, "Number of events which passed:\t%li  Number which failed:\t%li\n", mNEventsPassed, mNEventsFailed);
   Stemp += Ctemp;
   sprintf(Ctemp, "Here are the reports from the\t%i EventCuts in the collection\n", mEventCuts.size());
   Stemp += Ctemp;

   for (unsigned int iter = 0; iter < mEventCuts.size(); iter++) {
      Stemp += mEventCuts[iter]->Report();
   }
   StHbtString returnThis = Stemp;
   return returnThis;
}

bool ManyEventCuts::Pass(const StHbtEvent* event) {
   for (unsigned int i = 0; mEventCuts.size(); i++) {
      if (mEventCuts[i]->Pass(event) == false) {
         mNEventsFailed++;
         return false;
      }
   }
   mNEventsPassed++;
   return true;
}

StHbtEventCut* ManyEventCuts::Clone() { return new ManyEventCuts(*this); }

void ManyEventCuts::AddCut(StHbtEventCut* cut) { mEventCuts.push_back(cut); }

ManyEventCuts::~ManyEventCuts() {
   // TODO Auto-generated destructor stub
}
