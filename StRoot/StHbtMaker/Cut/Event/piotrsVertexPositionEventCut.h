#ifndef PIOTRSVERTEXPOSITIONEVENTCUT_H
#define PIOTRSVERTEXPOSITIONEVENTCUT_H

#include "StHbtMaker/Base/StHbtEventCut.h"

class StHbtEvent;

class piotrsVertexPositionEventCut : public StHbtEventCut {
  public:
   piotrsVertexPositionEventCut();
   piotrsVertexPositionEventCut(double, double);
   virtual ~piotrsVertexPositionEventCut() { /* no-op */
   }

   virtual bool Pass(const StHbtEvent* event);
   virtual StHbtString Report();
   virtual piotrsVertexPositionEventCut* Clone();

   void setZVertexMin(double number) { fZVertexMin = number; }
   void setZVertexMax(double number) { fZVertexMax = number; }
   void setRVertexMax(double number) { fRVertexMax = number; }

  private:
   double fZVertexMin;
   double fZVertexMax;
   double fRVertexMax;

   ClassDef(piotrsVertexPositionEventCut, 0)
};

#endif
