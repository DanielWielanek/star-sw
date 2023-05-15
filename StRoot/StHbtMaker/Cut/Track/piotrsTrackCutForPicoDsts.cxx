#include "StHbtMaker/Cut/Track/piotrsTrackCutForPicoDsts.h"

#include "StHbtMaker/Infrastructure/StHbtTrack.hh"

ClassImp(piotrsTrackCutForPicoDsts)

    bool piotrsTrackCutForPicoDsts::Pass(const StHbtTrack* track) {
   bool goodTrack = ((track->TrackType() == 1) &&  // primary
                     (track->DCAxy() >= 0) && (track->DCAxy() <= 3.0) && (track->NHits() >= 15) &&
                     (track->NHits() <= 100) && (track->P().mag() >= 0.1) && (track->P().mag() <= 3.0) &&
                     (track->P().pseudoRapidity() >= -1) && (track->P().pseudoRapidity() <= +1) &&
                     //		        ((fabs(track->NSigmaElectron()) <= 3.0) ||
                     //			(fabs(track->NSigmaPion())   <= 3.0) ||
                     //(fabs(track->NSigmaKaon())   <= 3.0)
                     (fabs(track->NSigmaProton()) <= 3.0)
                     //((fabs(track->NSigmaProton()) * fabs(track->NSigmaProton()) + fabs(track->ToF_sigmaProton()) *
                     //fabs(track->ToF_sigmaProton()) <=9.0)) || (fabs(track->ToF_sigmaProton()) <=3.0)	)
   );

   return goodTrack;
}
