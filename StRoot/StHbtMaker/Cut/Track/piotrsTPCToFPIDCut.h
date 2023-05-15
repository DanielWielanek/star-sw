#ifndef PIOTRSTPCTOFPIDCUT_H
#define PIOTRSTPCTOFPIDCUT_H

#include "StHbtMaker/Base/StHbtTrackCut.h"
#include "StHbtMaker/Cut/ToFRequiredPredicate.h"
#include "StHbtMaker/Cut/piotrsToFPID.h"
#include "StHbtMaker/Infrastructure/StHbtString.hh"

class piotrsTPCToFPIDCut : public StHbtTrackCut {
  public:
   piotrsTPCToFPIDCut(ToFRequiredPredicate*, piotrsToFPID* tpid);
   ~piotrsTPCToFPIDCut();

   virtual bool Pass(const StHbtTrack*);

   virtual StHbtString Report();
   virtual piotrsTPCToFPIDCut* Clone();

   void SetNSigmaElectron(const float& lo, const float& hi);
   void SetNSigmaPion(const float& lo, const float& hi);
   void SetNSigmaKaon(const float& lo, const float& hi);
   void SetNSigmaProton(const float& lo, const float& hi);

   void SetOrMode(const bool);

  private:
   float mNSigmaElectron[2];
   float mNSigmaPion[2];
   float mNSigmaKaon[2];
   float mNSigmaProton[2];

   bool mOrMode;

   ToFRequiredPredicate* mTofPredicate;
   piotrsToFPID* mToFPID;

   ClassDef(piotrsTPCToFPIDCut, 0)
};

#endif
