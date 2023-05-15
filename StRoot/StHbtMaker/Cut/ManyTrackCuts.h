/*
 * ManyTrackCuts.h
 *
 *  Created on: 15 maj 2023
 *      Author: Daniel Wielanek
 *		E-mail: daniel.wielanek@gmail.com
 *		Warsaw University of Technology, Faculty of Physics
 */
#ifndef STHBTMAKER_CUT_MANYTRACKCUTS_H_
#define STHBTMAKER_CUT_MANYTRACKCUTS_H_

#include "StHbtMaker/Base/StHbtTrackCut.h"

class ManyTrackCuts : public StHbtTrackCut {
   std::vector<StHbtTrackCut *> mTrackCuts;
   long mNTracksPassed;
   long mNTracksFailed;

  public:
   ManyTrackCuts();
   ManyTrackCuts(const ManyTrackCuts &other);
   virtual StHbtString Report();
   virtual bool Pass(const StHbtTrack *event);
   virtual StHbtTrackCut *Clone();
   void AddCut(StHbtTrackCut *cut);
   virtual ~ManyTrackCuts();
#ifdef __ROOT__
   ClassDef(ManyTrackCuts, 1)
#endif
};

#endif /* STHBTMAKER_CUT_MANYTRACKCUTS_H_ */
