#ifndef PIOTRSDCAXYTRACKCUT_H
#define PIOTRSDCAXYTRACKCUT_H

#include "StHbtMaker/Base/StHbtTrackCut.h"
#include "StHbtMaker/Infrastructure/StHbtString.hh"

class piotrsDCAxyTrackCut : public StHbtTrackCut {
  public:
   piotrsDCAxyTrackCut(double min, double max);
   ~piotrsDCAxyTrackCut();

   virtual bool Pass(const StHbtTrack*);

   virtual StHbtString Report();
   virtual piotrsDCAxyTrackCut* Clone();

  private:
   double mDCAmin;
   double mDCAmax;

   ClassDef(piotrsDCAxyTrackCut, 0)
};

#endif
