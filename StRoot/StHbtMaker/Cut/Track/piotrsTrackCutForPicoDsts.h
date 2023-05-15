#ifndef PIOTRSTRACKCUTFORPICODSTS_H
#define PIOTRSTRACKCUTFORPICODSTS_H

#include "StHbtMaker/Base/StHbtTrackCut.h"
#include "StHbtMaker/Infrastructure/StHbtTypes.hh"

class StHbtTrack;

class piotrsTrackCutForPicoDsts : public StHbtTrackCut {
  public:
   piotrsTrackCutForPicoDsts() { /* no - op */
   }
   ~piotrsTrackCutForPicoDsts() { /* no - op */
   }

   bool Pass(const StHbtTrack*);
   virtual StHbtString Report() { return "Track Cut"; }

  private:
   ClassDef(piotrsTrackCutForPicoDsts, 0)
};

#endif
