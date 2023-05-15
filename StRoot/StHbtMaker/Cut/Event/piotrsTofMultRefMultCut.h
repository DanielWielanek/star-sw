#ifndef PIOTRSTOFMULTREFMULTCUT_H
#define PIOTRSTOFMULTREFMULTCUT_H

#include "StHbtMaker/Base/StHbtEventCut.h"

class StHbtEvent;

class piotrsTofMultRefMultCut : public StHbtEventCut {
  public:
   piotrsTofMultRefMultCut() { /*no-op*/
   }
   virtual ~piotrsTofMultRefMultCut() { /*no-op*/
   }

   virtual bool Pass(const StHbtEvent* event);
   virtual StHbtString Report();
   virtual piotrsTofMultRefMultCut* Clone();

   void SetParametersUpper(double p0, double p1, double p2) {
      mp0upper = p0;
      mp1upper = p1;
      mp2upper = p2;
   }

   void SetParametersLower(double p0, double p1, double p2) {
      mp0lower = p0;
      mp1lower = p1;
      mp2lower = p2;
   }

  private:
   double mp0upper;
   double mp1upper;
   double mp2upper;

   double mp0lower;
   double mp1lower;
   double mp2lower;

   ClassDef(piotrsTofMultRefMultCut, 0)
};

#endif
