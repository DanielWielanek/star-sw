#include "StHbtMaker/Cut/Event/piotrsVertexPositionEventCut.h"

#include <cmath>
#include <iostream>

#include "StHbtMaker/Base/StHbtEventCut.h"
#include "StHbtMaker/Infrastructure/StHbtString.hh"

using namespace std;

ClassImp(piotrsVertexPositionEventCut)

    piotrsVertexPositionEventCut::piotrsVertexPositionEventCut()
    : fZVertexMin(-200.0), fZVertexMax(200.0), fRVertexMax(50) {}

piotrsVertexPositionEventCut::piotrsVertexPositionEventCut(double zWidth, double rMax)
    : fZVertexMin(-zWidth), fZVertexMax(zWidth), fRVertexMax(rMax) {}

bool piotrsVertexPositionEventCut::Pass(const StHbtEvent* event) {
   double vertexXPos = event->PrimVertPos().x();
   double vertexYPos = event->PrimVertPos().y();
   double vertexZPos = event->PrimVertPos().z();
   double vertexRPos = sqrt(vertexXPos * vertexXPos + vertexYPos * vertexYPos);
   if (mVerbose) {
      cout << "Vertex cut: x:" << vertexXPos << " y:" << vertexYPos << " z:" << vertexZPos << endl;
   }
   if (fabs(vertexXPos) < 10e-5 && fabs(vertexYPos) < 10e-5 && fabs(vertexZPos) < 10e-5) {
      return false;
   }
   if (vertexZPos >= fZVertexMin && vertexZPos <= fZVertexMax && vertexRPos <= fRVertexMax) {
      cout << "piotrsVertexPositionEventCut: passed" << endl;
      return true;
   } else {
      cout << "piotrsVertexPositionEventCut: failed" << endl;
      return false;
   }
}

StHbtString piotrsVertexPositionEventCut::Report() {
   StHbtString retVal("piotrsVertexPositionEventCut: ");
   retVal += "fZVertexMin: ";
   retVal += fZVertexMin;
   retVal += " fZVertexMax: ";
   retVal += fZVertexMax;
   retVal += " fRVertexMax: ";
   retVal += fRVertexMax;
   return retVal;
}

piotrsVertexPositionEventCut* piotrsVertexPositionEventCut::Clone() { return 0; }
