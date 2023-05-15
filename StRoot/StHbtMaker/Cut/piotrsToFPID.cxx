#include "StHbtMaker/Cut/piotrsToFPID.h"

#include <fstream>
#include <vector>

#include "StHbtMaker/Cut/piotrsToFPIDDataHolder.h"
#include "StHbtMaker/Infrastructure/StHbtTrack.hh"

using namespace std;

ClassImp(piotrsToFPID)

    piotrsToFPID::piotrsToFPID() {
   ifstream in("piotrsPidTables.txt");
   while (!in.eof()) {
      piotrsToFPIDDataHolder *tmp = new piotrsToFPIDDataHolder(in);
      // tmp->printData();
      fData.push_back(tmp);
   }
   in.close();
   fDummy = new piotrsToFPIDDataHolder();
}

piotrsToFPID::~piotrsToFPID() {
   for (vector<piotrsToFPIDDataHolder *>::iterator i = fData.begin(); i != fData.end(); ++i) {
      delete *i;
   }
}

void piotrsToFPID::setTriggerId(int trgId) {
   fCurrentTriggerId = trgId;
   fCurrentDataPositive = fDummy;
   fCurrentDataNegative = fDummy;
   for (vector<piotrsToFPIDDataHolder *>::iterator i = fData.begin(); i != fData.end(); ++i) {
      if ((*i)->getTrgId() == trgId) {
         if ((*i)->getSign() > 0) {
            fCurrentDataPositive = *i;
         } else if ((*i)->getSign() < 0) {
            fCurrentDataNegative = *i;
         }
      }
   }
}

void piotrsToFPID::getSigmas(StHbtTrack *track, double *sigmaPion, double *sigmaKaon, double *sigmaProton) {
   if (!track->ToF_matchFlag()) {
      *sigmaPion = -999.;
      *sigmaKaon = -999.;
      *sigmaProton = -999.;
      return;
   }
   piotrsToFPIDDataHolder *toUse;
   if (track->Charge() > 0) {
      toUse = fCurrentDataPositive;
   } else if (track->Charge() < 0) {
      toUse = fCurrentDataNegative;
   } else {
      *sigmaPion = *sigmaKaon = *sigmaProton = -999.0;
      return;
   }
   double mass2, sigma;
   if (toUse->getPionData(track->P().mag(), mass2, sigma)) {
      *sigmaPion = getSigma(track, mass2, sigma);
   } else {
      *sigmaPion = -999.0;
   }
   if (toUse->getKaonData(track->P().mag(), mass2, sigma)) {
      *sigmaKaon = getSigma(track, mass2, sigma);
   } else {
      *sigmaKaon = -999.0;
   }
   if (toUse->getProtonData(track->P().mag(), mass2, sigma)) {
      *sigmaProton = getSigma(track, mass2, sigma);
   } else {
      *sigmaProton = -999.0;
   }
}

double piotrsToFPID::getSigma(StHbtTrack *track, double mass2, double sigma) {
   double beta2 = track->ToF_beta();
   beta2 = beta2 * beta2;
   double p = track->P().mag();
   double m2 = p * p * (1 / beta2 - 1);
   //  cout << "Track m2: " << m2 << " expected m2: " << mass2 << " sigma " << sigma << " retVal: " << ((m2 -
   //  mass2)/sigma) << endl;
   return (m2 - mass2) / sigma;
}
