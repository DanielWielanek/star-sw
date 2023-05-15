#ifndef TOFREQUIREDPREDICATE_H
#define TOFREQUIREDPREDICATE_H
#include "TROOT.h"
class StHbtTrack;

class ToFRequiredPredicate {
  public:
   virtual bool isToFRequired(StHbtTrack*) = 0;

   virtual ~ToFRequiredPredicate() = 0;

  private:
   ClassDef(ToFRequiredPredicate, 0)
};

#endif
