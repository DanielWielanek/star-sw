#ifndef PIOTRSTRIGGERIDEVENTCUT_H
#define PIOTRSTRIGGERIDEVENTCUT_H

#include <vector>

#include "StHbtMaker/Base/StHbtEventCut.h"

class StHbtEvent;

class piotrsTriggerIdEventCut : public StHbtEventCut {
  public:
   piotrsTriggerIdEventCut();
   virtual ~piotrsTriggerIdEventCut() { /* no-op */
   }

   virtual bool Pass(const StHbtEvent* event);
   virtual StHbtString Report();
   virtual piotrsTriggerIdEventCut* Clone();

   void addTriggerId(unsigned int tId) { fTriggerIds.push_back(tId); }

  private:
   std::vector<unsigned int> fTriggerIds;

   ClassDef(piotrsTriggerIdEventCut, 0)
};

#endif
