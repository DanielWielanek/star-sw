#ifndef NonIdTrue3DCorrFctn_hh
#define NonIdTrue3DCorrFctn_hh

#include "StHbtMaker/Base/StHbtCorrFctn.hh"
#include "StHbtMaker/Infrastructure/StHbtCoulomb.h"
#include "StHbtMaker/Infrastructure/StHbtHisto.hh"

class NonIdTrue3DCorrFctn : public StHbtCorrFctn {
  public:
   NonIdTrue3DCorrFctn(char* title, const int& nbins, const float& QLo, const float& QHi, int nmixbin);
   virtual ~NonIdTrue3DCorrFctn();

   virtual StHbtString Report();
   virtual void AddRealPair(const StHbtPair*);
   virtual void AddMixedPair(const StHbtPair*);

   virtual void Finish();
   virtual void Write();

   virtual void EventBegin(const StHbtEvent*);
   virtual void EventEnd(const StHbtEvent*);

   virtual void makeHistos(char* title, const int& nbins, const float& QinvLo, const float& QinvHi, int nmixbins);

  private:
   StHbt3IHisto** mNums;
   StHbt3IHisto** mDens;

   StHbt3IHisto* mNumSum;
   StHbt3IHisto* mDenSum;

   int NBins;

#ifdef __ROOT__
   ClassDef(NonIdTrue3DCorrFctn, 1)
#endif
};

#endif
