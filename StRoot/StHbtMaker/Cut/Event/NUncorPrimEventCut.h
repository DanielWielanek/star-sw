/*
 * wielanEventCut.h
 *
 *  Created on: 26 lis 2022
 *      Author: Daniel Wielanek
 *		E-mail: daniel.wielanek@gmail.com
 *		Warsaw University of Technology, Faculty of Physics
 */
#ifndef STROOT_STHBTMAKER_CUT_WIELANEVENTCUT_H_
#define STROOT_STHBTMAKER_CUT_WIELANEVENTCUT_H_

#include "StHbtMaker/Base/StHbtEventCut.h"

class StHbtEvent;

class NUncorPrimEventCut : public StHbtEventCut {
   int mMin, mMax;

  public:
   NUncorPrimEventCut();
   virtual ~NUncorPrimEventCut() { /* no-op */
   }
   void SetMulti(int lo, int hi) {
      mMin = lo;
      mMax = hi;
   }
   virtual bool Pass(const StHbtEvent* event);
   virtual StHbtString Report();
   virtual NUncorPrimEventCut* Clone();

   ClassDef(NUncorPrimEventCut, 0)
};

#endif /* STROOT_STHBTMAKER_CUT_WIELANEVENTCUT_H_ */
