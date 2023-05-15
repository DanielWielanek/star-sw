/***************************************************************************
 *
 * $Id: StarStandardEventCut.cxx $
 *
 * Author:  FR, LBL
 *
 ***************************************************************************
 *
 * Description: Event cut
 * - multiplicity: cut on ncharge (Y2 way, Y1 should be added at some point)
 *   pick from {1.,0.8,.7,.6,0.5,0.4,.3,.2,0.1,0.5,0.}
 *   e.g. setFractionOfCentrality(0.1,0.) for top 10%
 *   Default:  setFractionOfCentrality(1.,0.} (all)
 * - Vertex z position. Default: -1000. - 1000. (open)
 * - Y2 Trigger word. Default: all accepted
 * - L3 trigger algorithm. Default: no algorithm
 *
 ***************************************************************************
 *
 * $Log: StarStandardEventCut.cxx $
 *
 **************************************************************************/

#ifndef StarStandardEventCut_hh
#define StarStandardEventCut_hh

#include "StHbtMaker/Base/StHbtEventCut.h"
#ifdef HPUX
#include <fstream.h>
#else
#include <fstream>
#endif
// class ostrstream;

class StarStandardEventCut : public StHbtEventCut {
  public:
   StarStandardEventCut();
   StarStandardEventCut(const StarStandardEventCut&);
   //  ~StarStandardEventCut();

   void SetAllTriggerWords();
   void SetTriggerWord(int aWord);
   void SetY2TriggerWords();
   void SetL3AlgorithmOn(int aAlgorithm);

   void setFractionOfCentrality(double aMostCentralCrossSection, double aLeastCentralCrossSection);
   // (0.1,0.) = 10% most central
   // (1.,0.) = all (default)
   // Available bins: 1.,0.8,0.7,0.6,0.5,0.4,0.3,0.2,0.1,0.5,0.

   void SetEventMult(const int& lo, const int& hi);
   void SetVertZPos(const float& lo, const float& hi);
   int NEventsPassed();
   int NEventsFailed();

   virtual StHbtString Report();
   virtual bool Pass(const StHbtEvent*);

   StarStandardEventCut* Clone();

   //  ostrstream* finalReport() const;

  private:  // here are the quantities I want to cut on...
   unsigned int* mTriggerWords;
   int mNTriggerWords;
   int mL3Algorithm;

   int mEventMult[2];   // range of multiplicity
   float mVertZPos[2];  // range of z-position of vertex

   long mNEventsPassed;
   long mNEventsFailed;

   long mPassTrigger;
   long mPassVertex;
   long mBadField;
   long mPassMult;
   long mTot;

   double mField;

   ofstream* mOutFile;  //!

#ifdef __ROOT__
   ClassDef(StarStandardEventCut, 0)
#endif
};

inline void StarStandardEventCut::SetEventMult(const int& lo, const int& hi) {
   mEventMult[0] = lo;
   mEventMult[1] = hi;
   mField = -1000.0;
}
inline void StarStandardEventCut::SetVertZPos(const float& lo, const float& hi) {
   mVertZPos[0] = lo;
   mVertZPos[1] = hi;
}
inline int StarStandardEventCut::NEventsPassed() { return mNEventsPassed; }
inline int StarStandardEventCut::NEventsFailed() { return mNEventsFailed; }
inline StarStandardEventCut* StarStandardEventCut::Clone() {
   StarStandardEventCut* c = new StarStandardEventCut(*this);
   return c;
}

#endif
