#ifndef PIOTRSTOFPID_H
#define PIOTRSTOFPID_H

#include <vector>

#include "TROOT.h"

class piotrsToFPIDDataHolder;
class StHbtTrack;

class piotrsToFPID {
  public:
   piotrsToFPID();
   ~piotrsToFPID();

   void setTriggerId(int);
   void getSigmas(StHbtTrack *, double *, double *, double *);

  private:
   double getSigma(StHbtTrack *, double, double);

   piotrsToFPIDDataHolder *fCurrentDataPositive;
   piotrsToFPIDDataHolder *fCurrentDataNegative;
   piotrsToFPIDDataHolder *fDummy;
   int fCurrentTriggerId;

   std::vector<piotrsToFPIDDataHolder *> fData;

   ClassDef(piotrsToFPID, 0)
};

#endif
