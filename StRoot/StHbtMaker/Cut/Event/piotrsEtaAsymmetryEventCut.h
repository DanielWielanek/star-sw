#ifndef PIOTRSETAASYMMETRYEVENTCUT_H
#define PIOTRSETAASYMMETRYEVENTCUT_H

#include "StHbtMaker/Base/StHbtEventCut.h"
#include "StHbtMaker/Infrastructure/StHbtString.hh"

class StHbtEvent;

class piotrsEtaAsymmetryEventCut : public StHbtEventCut {
  public:
   piotrsEtaAsymmetryEventCut();
   piotrsEtaAsymmetryEventCut(double);
   ~piotrsEtaAsymmetryEventCut() { /* no-op */
   }

   virtual bool Pass(const StHbtEvent* event);
   virtual StHbtString Report();
   virtual piotrsEtaAsymmetryEventCut* Clone();

   void setEtaAsymmetryMax(double number) { fEtaAsymmetryMax = number; }

  private:
   double getEtaAsymmetry(const StHbtEvent* event);

   double fEtaAsymmetryMax;
   ClassDef(piotrsEtaAsymmetryEventCut, 0)
};

#endif
