
#include "StHbtMaker/Cut/Track/piotrsTPCToFPIDCut.h"

#include <iostream>

#include "StHbtMaker/Base/StHbtTrackCut.h"
#include "StHbtMaker/Infrastructure/StHbtString.hh"

using namespace std;

ClassImp(piotrsTPCToFPIDCut)

    piotrsTPCToFPIDCut::piotrsTPCToFPIDCut(ToFRequiredPredicate* trup, piotrsToFPID* tpid)
    : mTofPredicate(trup), mToFPID(tpid) {
   mOrMode = false;
}

piotrsTPCToFPIDCut::~piotrsTPCToFPIDCut() {
   delete mTofPredicate;
   delete mToFPID;
}

bool piotrsTPCToFPIDCut::Pass(const StHbtTrack* track) {
   //  cout << mNSigmaElectron[0] << " "
   //       << mNSigmaElectron[1] << " "
   //       << mNSigmaPion[0] << " "
   //       << mNSigmaPion[1] << " "
   //       << mNSigmaKaon[0] << " "
   //       << mNSigmaKaon[1] << " "
   //       << mNSigmaProton[0] << " "
   //       << mNSigmaProton[1] << endl;
   //  cout << track->NSigmaElectron() << " "
   //       << track->NSigmaPion() << " "
   //       << track->NSigmaKaon() << " "
   //       << track->NSigmaProton() << endl;
   bool goodPID;
   bool goodPIDand;
   bool goodPIDor;
   if (!mTofPredicate->isToFRequired(track) && (track->ToF_matchFlag() == 0)) {
      goodPIDand =
          ((fabs(track->NSigmaElectron()) >= mNSigmaElectron[0]) &&
           (fabs(track->NSigmaElectron()) <= mNSigmaElectron[1]) && (fabs(track->NSigmaPion()) >= mNSigmaPion[0]) &&
           (fabs(track->NSigmaPion()) <= mNSigmaPion[1]) && (fabs(track->NSigmaKaon()) >= mNSigmaKaon[0]) &&
           (fabs(track->NSigmaKaon()) <= mNSigmaKaon[1]) && (fabs(track->NSigmaProton()) >= mNSigmaProton[0]) &&
           (fabs(track->NSigmaProton()) <= mNSigmaProton[1]));
      goodPIDor =
          (((fabs(track->NSigmaElectron()) >= mNSigmaElectron[0]) &&
            (fabs(track->NSigmaElectron()) <= mNSigmaElectron[1])) ||
           ((fabs(track->NSigmaPion()) >= mNSigmaPion[0]) && (fabs(track->NSigmaPion()) <= mNSigmaPion[1])) ||
           ((fabs(track->NSigmaKaon()) >= mNSigmaKaon[0]) && (fabs(track->NSigmaKaon()) <= mNSigmaKaon[1])) ||
           ((fabs(track->NSigmaProton()) >= mNSigmaProton[0]) && (fabs(track->NSigmaProton()) <= mNSigmaProton[1])));
      goodPID = mOrMode ? goodPIDor : goodPIDand;
      //	  cout << "TPC only " << goodPID << endl;
   } else if (mTofPredicate->isToFRequired(track) && (track->ToF_matchFlag() == 0)) {
      // cout << "High momentum no tof" << endl;
      goodPID = false;
   } else {
      double tofSigmaPion, tofSigmaKaon, tofSigmaProton;
      mToFPID->getSigmas(track, &tofSigmaPion, &tofSigmaKaon, &tofSigmaProton);

      float sigmaElectronSquared = track->NSigmaElectron() * track->NSigmaElectron();
      float sigmaPionSquared = track->NSigmaPion() * track->NSigmaPion() + tofSigmaPion * tofSigmaPion;
      float sigmaKaonSquared = track->NSigmaKaon() * track->NSigmaKaon() + tofSigmaKaon * tofSigmaKaon;
      float sigmaProtonSquared = track->NSigmaProton() * track->NSigmaProton() + tofSigmaProton * tofSigmaProton;
      goodPIDand = ((sigmaElectronSquared >= mNSigmaElectron[0] * mNSigmaElectron[0]) &&
                    (sigmaElectronSquared <= mNSigmaElectron[1] * mNSigmaElectron[1]) &&
                    (sigmaPionSquared >= mNSigmaPion[0] * mNSigmaPion[0]) &&
                    (sigmaPionSquared <= mNSigmaPion[1] * mNSigmaPion[1]) &&
                    (sigmaKaonSquared >= mNSigmaKaon[0] * mNSigmaKaon[0]) &&
                    (sigmaKaonSquared <= mNSigmaKaon[1] * mNSigmaKaon[1]) &&
                    (sigmaProtonSquared >= mNSigmaProton[0] * mNSigmaProton[0]) &&
                    (sigmaProtonSquared <= mNSigmaProton[1] * mNSigmaProton[1]));
      goodPIDor = (((sigmaElectronSquared >= mNSigmaElectron[0] * mNSigmaElectron[0]) &&
                    (sigmaElectronSquared <= mNSigmaElectron[1] * mNSigmaElectron[1])) ||
                   ((sigmaPionSquared >= mNSigmaPion[0] * mNSigmaPion[0]) &&
                    (sigmaPionSquared <= mNSigmaPion[1] * mNSigmaPion[1])) ||
                   ((sigmaKaonSquared >= mNSigmaKaon[0] * mNSigmaKaon[0]) &&
                    (sigmaKaonSquared <= mNSigmaKaon[1] * mNSigmaKaon[1])) ||
                   ((sigmaProtonSquared >= mNSigmaProton[0] * mNSigmaProton[0]) &&
                    (sigmaProtonSquared <= mNSigmaProton[1] * mNSigmaProton[1])));
      goodPID = mOrMode ? goodPIDor : goodPIDand;
      if (goodPID) {
         //	    cout << "TOF: "
         //		 << tofSigmaPion << " "
         //		 << tofSigmaKaon << " "
         //		 << tofSigmaProton << endl;
         //	    cout << "Sq " << sigmaElectronSquared << " " << sigmaPionSquared << " " << sigmaKaonSquared << " " <<
         //sigmaProtonSquared << endl;
      }
   }

   //	cout << "goodPID: " << goodPID << endl;
   return goodPID;
}

StHbtString piotrsTPCToFPIDCut::Report() {
   StHbtString retVal("piotrsTPCToFPIDCut report \n");
   return retVal;
}

piotrsTPCToFPIDCut* piotrsTPCToFPIDCut::Clone() { return 0; }

void piotrsTPCToFPIDCut::SetNSigmaElectron(const float& lo, const float& hi) {
   mNSigmaElectron[0] = lo;
   mNSigmaElectron[1] = hi;
}
void piotrsTPCToFPIDCut::SetNSigmaPion(const float& lo, const float& hi) {
   mNSigmaPion[0] = lo;
   mNSigmaPion[1] = hi;
}
void piotrsTPCToFPIDCut::SetNSigmaKaon(const float& lo, const float& hi) {
   mNSigmaKaon[0] = lo;
   mNSigmaKaon[1] = hi;
}
void piotrsTPCToFPIDCut::SetNSigmaProton(const float& lo, const float& hi) {
   mNSigmaProton[0] = lo;
   mNSigmaProton[1] = hi;
}
void piotrsTPCToFPIDCut::SetOrMode(const bool mode) { mOrMode = mode; }
