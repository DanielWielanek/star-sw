#include "StHbtMaker/Cut/Event/piotrsTriggerIdCutMonitor.h"

#include <iostream>
#include <vector>

#include "StHbtMaker/Infrastructure/StHbtEvent.hh"
#include "TH1D.h"

using namespace std;

piotrsTriggerIdCutMonitor::piotrsTriggerIdCutMonitor() {
   fHisto = new TH1D("TriggerId", "Trigger ID counter", 1000000, -0.5, 999999.5);
}

piotrsTriggerIdCutMonitor::~piotrsTriggerIdCutMonitor() { delete fHisto; }

void piotrsTriggerIdCutMonitor::Fill(const StHbtEvent *event) {
   vector<unsigned int> mtriggerIds = event->triggerIdCollection().nominal().triggerIds();
   for (vector<unsigned int>::iterator i = mtriggerIds.begin(); i != mtriggerIds.end(); ++i) {
      fHisto->Fill(*i);
   }
}
