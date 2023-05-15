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

#ifndef AuAu200_centY4EventCut_hh
#define AuAu200_centY4EventCut_hh

#include "StHbtMaker/Base/StHbtEventCut.h"
#ifdef HPUX
#include <fstream.h>
#else
#include <fstream>
#endif
#include <vector>

class AuAu200_centY4EventCut : public StHbtEventCut {
  public:
   AuAu200_centY4EventCut();
   AuAu200_centY4EventCut(AuAu200_centY4EventCut&);
   //  ~AuAu200Y4EventCut();

   void SetEventMult(const int& lo, const int& hi);
   void SetVertZPos(const float& lo, const float& hi);
   void SetCentralityBin(const int& cenbin);
   // void SetTrgSetupName(const unsigned short& trgstp);
   bool CheckId(int runnr);

   int NEventsPassed();
   int NEventsFailed();

   virtual StHbtString Report();
   virtual bool Pass(const StHbtEvent*);

   AuAu200_centY4EventCut* Clone();

  private:                 // here are the quantities I want to cut on...
   int mEventMult[2];      // range of multiplicity
   int mFtpcEventMult[2];  // range of Ftpc multiplicity
   float mVertZPos[2];     // range of z-position of vertex
   int mCentralityBin;     // ftpc centrality bin
   // unsigned short mTrgSetupName;      // trigger setup name 1=mb 2=mb 3=central

   long mNEventsPassed;
   long mNEventsFailed;

   ofstream* mOutFile;  //!
   vector<unsigned int> mtriggerIds;
#ifdef __ROOT__
   ClassDef(AuAu200_centY4EventCut, 0)
#endif
};

inline void AuAu200_centY4EventCut::SetEventMult(const int& lo, const int& hi) {
   mEventMult[0] = lo;
   mEventMult[1] = hi;
}
inline void AuAu200_centY4EventCut::SetVertZPos(const float& lo, const float& hi) {
   mVertZPos[0] = lo;
   mVertZPos[1] = hi;
}
inline void AuAu200_centY4EventCut::SetCentralityBin(const int& cenbin) {
   mCentralityBin = cenbin;
   switch (mCentralityBin) {
      case 0:
         mEventMult[0] = 1;
         mEventMult[1] = 1000;
         break;
      case 1:
         mEventMult[0] = 14;
         mEventMult[1] = 96;
         break;
      case 2:
         mEventMult[0] = 96;
         mEventMult[1] = 222;
         break;
      case 3:
         mEventMult[0] = 222;
         mEventMult[1] = 319;
         break;
      case 4:
         mEventMult[0] = 319;
         mEventMult[1] = 441;
         break;
      case 5:
         mEventMult[0] = 441;
         mEventMult[1] = 520;
         break;
      case 6:
         mEventMult[0] = 520;
         mEventMult[1] = 1000;
         break;
      case 7:
         mEventMult[0] = 14;
         mEventMult[1] = 222;
         break;
      case 8:
         mEventMult[0] = 222;
         mEventMult[1] = 441;
         break;
      case 9:
         mEventMult[0] = 441;
         mEventMult[1] = 1000;
         break;
      default:
         mEventMult[0] = 0;
         mEventMult[1] = 1000;
         break;
   }
}

// inline void AuAu200_centY4EventCut::SetTrgSetupName(const unsigned short& trgstp){ mTrgSetupName=trgstp;}

inline int AuAu200_centY4EventCut::NEventsPassed() { return mNEventsPassed; }
inline int AuAu200_centY4EventCut::NEventsFailed() { return mNEventsFailed; }
inline AuAu200_centY4EventCut* AuAu200_centY4EventCut::Clone() {
   AuAu200_centY4EventCut* c = new AuAu200_centY4EventCut(*this);
   return c;
}
inline AuAu200_centY4EventCut::AuAu200_centY4EventCut(AuAu200_centY4EventCut& c) : StHbtEventCut(c) {
   mEventMult[0] = c.mEventMult[0];
   mEventMult[1] = c.mEventMult[1];
   mVertZPos[0] = c.mVertZPos[0];
   mVertZPos[1] = c.mVertZPos[1];
   mFtpcEventMult[0] = c.mFtpcEventMult[0];
   mFtpcEventMult[1] = c.mFtpcEventMult[1];
   mCentralityBin = 0;
   mNEventsPassed = 0;
   mNEventsFailed = 0;
}

#endif
