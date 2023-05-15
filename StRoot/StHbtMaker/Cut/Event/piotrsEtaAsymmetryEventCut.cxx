#include "StHbtMaker/Cut/Event/piotrsEtaAsymmetryEventCut.h"

#include "StHbtMaker/Base/StHbtEventCut.h"
#include "StHbtMaker/Infrastructure/StHbtEvent.hh"
#include "StHbtMaker/Infrastructure/StHbtString.hh"

ClassImp(piotrsEtaAsymmetryEventCut)

    piotrsEtaAsymmetryEventCut::piotrsEtaAsymmetryEventCut()
    : fEtaAsymmetryMax(1000) {}
piotrsEtaAsymmetryEventCut::piotrsEtaAsymmetryEventCut(double fem) : fEtaAsymmetryMax(fem) {}

bool piotrsEtaAsymmetryEventCut::Pass(const StHbtEvent* event) {
   if (getEtaAsymmetry(event) > fEtaAsymmetryMax) {
      return false;
   } else {
      return true;
   }
}

StHbtString piotrsEtaAsymmetryEventCut::Report() {
   StHbtString retVal("piotrsEtaAsymmetryEventCut EtaAsymmetryMax");
   retVal += fEtaAsymmetryMax;
   return retVal;
}

piotrsEtaAsymmetryEventCut* piotrsEtaAsymmetryEventCut::Clone() { return 0; }

double piotrsEtaAsymmetryEventCut::getEtaAsymmetry(const StHbtEvent* event) {
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
