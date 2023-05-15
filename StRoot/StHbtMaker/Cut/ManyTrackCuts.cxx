/*
 * ManyTrackCuts.cxx
 *
 *  Created on: 15 maj 2023
 *      Author: Daniel Wielanek
 *		E-mail: daniel.wielanek@gmail.com
 *		Warsaw University of Technology, Faculty of Physics
 */
#include "ManyTrackCuts.h"

ManyTrackCuts::ManyTrackCuts() { mNTracksPassed = mNTracksFailed = 0; }

ManyTrackCuts::ManyTrackCuts(const ManyTrackCuts& other) : StHbtTrackCut(other) {
   for (unsigned int i = 0; mTrackCuts.size(); i++) {
      mTrackCuts.push_back(other.mTrackCuts[i]);
   }
   mNTracksPassed = mNTracksFailed = 0;
}

StHbtString ManyTrackCuts::Report() {
   string Stemp = "EventCombinedCut Report\n";
   char Ctemp[100];
   sprintf(Ctemp, "Number of events which passed:\t%li  Number which failed:\t%li\n", mNTracksPassed, mNTracksFailed);
   Stemp += Ctemp;
   sprintf(Ctemp, "Here are the reports from the\t%i EventCuts in the collection\n", mTrackCuts.size());
   Stemp += Ctemp;

   for (unsigned int iter = 0; iter < mTrackCuts.size(); iter++) {
      Stemp += mTrackCuts[iter]->Report();
   }
   StHbtString returnThis = Stemp;
   return returnThis;
}

bool ManyTrackCuts::Pass(const StHbtTrack* track) {
   for (unsigned int i = 0; mTrackCuts.size(); i++) {
      if (mTrackCuts[i]->Pass(track) == false) {
         mNTracksFailed++;
         return false;
      }
   }
   mNTracksPassed++;
   return true;
}

StHbtTrackCut* ManyTrackCuts::Clone() { return new ManyTrackCuts(*this); }

void ManyTrackCuts::AddCut(StHbtTrackCut* cut) { mTrackCuts.push_back(cut); }

ManyTrackCuts::~ManyTrackCuts() {
   // TODO Auto-generated destructor stub
}
