#ifndef PIOTRSTRIGGERIDCUTMONITOR_H
#define PIOTRSTRIGGERIDCUTMONITOR_H

#include "StHbtMaker/Base/StHbtCutMonitor.hh"
#include "TH1D.h"
#include "TList.h"
class StHbtEvent;

class piotrsTriggerIdCutMonitor : public StHbtCutMonitor {
  public:
   piotrsTriggerIdCutMonitor();
   ~piotrsTriggerIdCutMonitor();

   void Fill(const StHbtEvent*);

   virtual void AppendOutput(TList* output) { output->Add(fHisto); }

  private:
   TH1D* fHisto;

   ClassDef(piotrsTriggerIdCutMonitor, 0)
};

#endif
