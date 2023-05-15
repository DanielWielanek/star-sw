/*
 * Zbigniew Chajecki, chajecki@mps.ohio-state.edu
 * Event cut for AuAu200 Y4 data
 * created: 08/23/2004
 * trigger selection implemented:
 *     see the following web page for more details:
 *     http://www.star.bnl.gov/protected/common/common2004/trigger2004/triggers2004.html
 * no centrality selection yet
 *
 */

#ifndef picoEventCut_hh
#define picoEventCut_hh

#include "StHbtMaker/Base/StHbtEventCut.h"
#ifdef HPUX
#include <fstream.h>
#else
#include <fstream>
#endif
#include <vector>

class picoEventCut : public StHbtEventCut {
  public:
   picoEventCut() : mNEventsPassed(0) {}
   picoEventCut(picoEventCut&) : mNEventsPassed(0) {}

   int NEventsPassed() const { return mNEventsPassed; }
   int NEventsFailed() { return 0; }
   virtual StHbtString Report() {
      StHbtString Stemp;
      char Ctemp[100];
      sprintf(Ctemp, "%ld events passed picoEventCut", mNEventsPassed);
      return Stemp;
   }
   virtual bool Pass(const StHbtEvent*) {
      ++mNEventsPassed;
      return true;
   }
   picoEventCut* Clone() {
      picoEventCut* c = new picoEventCut(*this);
      return c;
   }

  private:
   long mNEventsPassed;

#ifdef __ROOT__
   ClassDef(picoEventCut, 0)
#endif
};

#endif
