/*
 * wielanEventCut.cxx
 *
 *  Created on: 26 lis 2022
 *      Author: Daniel Wielanek
 *		E-mail: daniel.wielanek@gmail.com
 *		Warsaw University of Technology, Faculty of Physics
 */
#include "StHbtMaker/Cut/Event/NUncorPrimEventCut.h"

NUncorPrimEventCut::NUncorPrimEventCut() {
   mMin = 0;
   mMax = 1E+5;
}

bool NUncorPrimEventCut::Pass(const StHbtEvent* event) {
   int val = event->UncorrectedNumberOfPrimaries();
   if (val > mMax) return false;
   if (val < mMin) return false;
   return true;
}

StHbtString NUncorPrimEventCut::Report() {
   StHbtString retVal("wielanEventCut");
   return retVal;
}

NUncorPrimEventCut* NUncorPrimEventCut::Clone() { return nullptr; }
