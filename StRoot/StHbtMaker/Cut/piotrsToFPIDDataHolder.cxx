#include "StHbtMaker/Cut/piotrsToFPIDDataHolder.h"

#include <math.h>
#include <stdlib.h>

#include <iostream>
#include <istream>

using namespace std;

piotrsToFPIDDataHolder::piotrsToFPIDDataHolder(istream& in) {
   in >> trgId;
   if (trgId < 0) {
      sign = -1;
      trgId = abs(trgId);
   } else {
      sign = +1;
   }
   readData(in, pionBoundaryLower, pionBoundaryHigher, pionStepSize, &pionMassTable, &pionSigmaTable);
   readData(in, kaonBoundaryLower, kaonBoundaryHigher, kaonStepSize, &kaonMassTable, &kaonSigmaTable);
   readData(in, protonBoundaryLower, protonBoundaryHigher, protonStepSize, &protonMassTable, &protonSigmaTable);
}

void piotrsToFPIDDataHolder::readData(istream& in, double& bl, double& bh, double& step, double** mass,
                                      double** sigma) {
   int nsteps;
   in >> bl >> bh >> step >> nsteps;
   *mass = new double[nsteps];
   *sigma = new double[nsteps];
   for (int i = 0; i < nsteps; ++i) {
      in >> (*mass)[i] >> (*sigma)[i];
   }
}

piotrsToFPIDDataHolder::piotrsToFPIDDataHolder() {
   pionBoundaryLower = 2.0;
   pionBoundaryHigher = 1.0;
   kaonBoundaryLower = 2.0;
   kaonBoundaryHigher = 1.0;
   protonBoundaryLower = 2.0;
   protonBoundaryHigher = 1.0;
}

piotrsToFPIDDataHolder::~piotrsToFPIDDataHolder() {
   delete[] pionMassTable;
   delete[] pionSigmaTable;
   delete[] kaonMassTable;
   delete[] kaonSigmaTable;
   delete[] protonMassTable;
   delete[] protonSigmaTable;
}

bool piotrsToFPIDDataHolder::getPionData(double p, double& mass2, double& sigma) {
   if (p >= pionBoundaryLower && p < pionBoundaryHigher) {
      int index = (int)floor((p - pionBoundaryLower) / pionStepSize);
      mass2 = pionMassTable[index];
      sigma = pionSigmaTable[index];
      //    cout << "Pion data: " << p << " " << mass2 << " " << sigma << endl;
      return true;
   } else {
      return false;
   }
}

bool piotrsToFPIDDataHolder::getKaonData(double p, double& mass2, double& sigma) {
   if (p >= kaonBoundaryLower && p < kaonBoundaryHigher) {
      int index = (int)floor((p - kaonBoundaryLower) / kaonStepSize);
      mass2 = kaonMassTable[index];
      sigma = kaonSigmaTable[index];
      //    cout << "Kaon data: " << p << " " << mass2 << " " << sigma << endl;
      return true;
   } else {
      return false;
   }
}

bool piotrsToFPIDDataHolder::getProtonData(double p, double& mass2, double& sigma) {
   if (p >= protonBoundaryLower && p < protonBoundaryHigher) {
      int index = (int)floor((p - protonBoundaryLower) / protonStepSize);
      mass2 = protonMassTable[index];
      sigma = protonSigmaTable[index];
      //    cout << "Proton data: " << p << " " << mass2 << " " << sigma << endl;
      return true;
   } else {
      return false;
   }
}

int piotrsToFPIDDataHolder::getTrgId() const { return trgId; }

int piotrsToFPIDDataHolder::getSign() const { return sign; }

void piotrsToFPIDDataHolder::printData() const {
   cout << (sign * trgId) << endl;
   cout << pionBoundaryLower << " " << pionBoundaryHigher << " " << pionStepSize << " "
        << (int)((pionBoundaryHigher - pionBoundaryLower) / pionStepSize) << endl;
   for (int i = 0; i < (int)((pionBoundaryHigher - pionBoundaryLower) / pionStepSize); ++i) {
      cout << pionMassTable[i] << " " << pionSigmaTable[i] << endl;
   }
   cout << kaonBoundaryLower << " " << kaonBoundaryHigher << " " << kaonStepSize << " "
        << (int)((kaonBoundaryHigher - kaonBoundaryLower) / kaonStepSize) << endl;
   for (int i = 0; i < (int)((kaonBoundaryHigher - kaonBoundaryLower) / kaonStepSize); ++i) {
      cout << kaonMassTable[i] << " " << kaonSigmaTable[i] << endl;
   }
   cout << protonBoundaryLower << " " << protonBoundaryHigher << " " << protonStepSize << " "
        << (int)((protonBoundaryHigher - protonBoundaryLower) / protonStepSize) << endl;
   for (int i = 0; i < (int)((protonBoundaryHigher - protonBoundaryLower) / protonStepSize); ++i) {
      cout << protonMassTable[i] << " " << protonSigmaTable[i] << endl;
   }
}
