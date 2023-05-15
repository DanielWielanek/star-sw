/*
 * EventCombinedCut.h
 *
 *  Created on: 15 maj 2023
 *      Author: Daniel Wielanek
 *		E-mail: daniel.wielanek@gmail.com
 *		Warsaw University of Technology, Faculty of Physics
 */
#ifndef STHBTMAKER_CUT_MANYEVENTCUTS_H_
#define STHBTMAKER_CUT_MANYEVENTCUTS_H_

#include "StHbtMaker/Base/StHbtEventCut.h"

class ManyEventCuts : public StHbtEventCut {
   std::vector<StHbtEventCut *> mEventCuts;
   long mNEventsPassed;
   long mNEventsFailed;

  public:
   ManyEventCuts();
   ManyEventCuts(const ManyEventCuts &other);
   virtual StHbtString Report();
   virtual bool Pass(const StHbtEvent *event);
   virtual StHbtEventCut *Clone();
   void AddCut(StHbtEventCut *cut);
   virtual ~ManyEventCuts();
#ifdef __ROOT__
   ClassDef(ManyEventCuts, 1)
#endif
};

#endif /* STHBTMAKER_CUT_MANYEVENTCUTS_H_ */
