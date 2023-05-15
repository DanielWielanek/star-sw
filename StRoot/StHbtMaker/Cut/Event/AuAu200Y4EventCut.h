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

#ifndef AuAu200Y4EventCut_hh
#define AuAu200Y4EventCut_hh

#include "StHbtMaker/Base/StHbtEventCut.h"
#ifdef HPUX
#include <fstream.h>
#else
#include <fstream>
#endif

class AuAu200Y4EventCut : public StHbtEventCut {
  public:
   AuAu200Y4EventCut();
   AuAu200Y4EventCut(AuAu200Y4EventCut&);
   //  ~AuAu200Y4EventCut();

   void SetEventMult(const int& lo, const int& hi);
   void SetVertZPos(const float& lo, const float& hi);
   void SetCentralityBin(const int& cenbin);
   void SetTrgSetupName(const unsigned short& trgstp);

   int NEventsPassed();
   int NEventsFailed();

   virtual StHbtString Report();
   virtual bool Pass(const StHbtEvent*);

   AuAu200Y4EventCut* Clone();

  private:                        // here are the quantities I want to cut on...
   int mEventMult[2];             // range of multiplicity
   int mFtpcEventMult[2];         // range of Ftpc multiplicity
   float mVertZPos[2];            // range of z-position of vertex
   int mCentralityBin;            // ftpc centrality bin
   unsigned short mTrgSetupName;  // trigger setup name 1=mb 2=mb 3=central

   long mNEventsPassed;
   long mNEventsFailed;

   ofstream* mOutFile;  //!

#ifdef __ROOT__
   ClassDef(AuAu200Y4EventCut, 0)
#endif
};

inline void AuAu200Y4EventCut::SetEventMult(const int& lo, const int& hi) {
   mEventMult[0] = lo;
   mEventMult[1] = hi;
}
inline void AuAu200Y4EventCut::SetVertZPos(const float& lo, const float& hi) {
   mVertZPos[0] = lo;
   mVertZPos[1] = hi;
}
inline void AuAu200Y4EventCut::SetCentralityBin(const int& cenbin) {
   mCentralityBin = cenbin;
   switch (mCentralityBin) {
      case 0:
         mFtpcEventMult[0] = 0;
         mFtpcEventMult[1] = 10000;
         break;
      case 1:
         mFtpcEventMult[0] = 1;
         mFtpcEventMult[1] = 1;
         break;
      case 2:
         mFtpcEventMult[0] = 2;
         mFtpcEventMult[1] = 2;
         break;
      case 3:
         mFtpcEventMult[0] = 3;
         mFtpcEventMult[1] = 3;
         break;
      default:
         mFtpcEventMult[0] = 0;
         mFtpcEventMult[1] = 10000;
         break;
   }
}

inline void AuAu200Y4EventCut::SetTrgSetupName(const unsigned short& trgstp) { mTrgSetupName = trgstp; }

inline int AuAu200Y4EventCut::NEventsPassed() { return mNEventsPassed; }
inline int AuAu200Y4EventCut::NEventsFailed() { return mNEventsFailed; }
inline AuAu200Y4EventCut* AuAu200Y4EventCut::Clone() {
   AuAu200Y4EventCut* c = new AuAu200Y4EventCut(*this);
   return c;
}
inline AuAu200Y4EventCut::AuAu200Y4EventCut(AuAu200Y4EventCut& c) : StHbtEventCut(c) {
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
