/*
 * Zbigniew Chajecki, chajecki@mps.ohio-state.edu
 * Event cut for AuAu7 Y10 data
 * created: 08/23/2004
 * trigger selection implemented:
 *
 */

#ifndef AuAu7_cent6Y10EventCut_hh
#define AuAu7_cent6Y10EventCut_hh

#include "StHbtMaker/Base/StHbtEventCut.h"
#ifdef HPUX
#include <fstream.h>
#else
#include <fstream>
#endif
#include <vector>

class AuAu7_cent6Y10EventCut : public StHbtEventCut {
  public:
   AuAu7_cent6Y10EventCut();
   AuAu7_cent6Y10EventCut(AuAu7_cent6Y10EventCut&);
   //  ~AuAu7Y10EventCut();

   void SetEventMult(const int& lo, const int& hi);
   void SetVertZPos(const float& lo, const float& hi);
   void SetVertRPos(const float& hi);
   void SetCentralityBin(const int& cenbin);
   // void SetTrgSetupName(const unsigned short& trgstp);
   bool CheckId(int runnr);

   int NEventsPassed();
   int NEventsFailed();

   int getEventMultLo() const { return mEventMult[0]; }
   int getEventMultHi() const { return mEventMult[1]; }

   virtual StHbtString Report();
   virtual bool Pass(const StHbtEvent*);
   double getEtaSym(const StHbtEvent*);

   AuAu7_cent6Y10EventCut* Clone();

  private:                 // here are the quantities I want to cut on...
   int mEventMult[2];      // range of multiplicity
   int mFtpcEventMult[2];  // range of Ftpc multiplicity
   float mVertZPos[2];     // range of z-position of vertex
   float mVertRPos;        // max of r position of vertex
   int mCentralityBin;     // ftpc centrality bin
   // unsigned short mTrgSetupName;      // trigger setup name 1=mb 2=mb 3=central

   long mNEventsPassed;
   long mNEventsFailed;

   ofstream* mOutFile;  //!
   vector<unsigned int> mtriggerIds;
#ifdef __ROOT__
   ClassDef(AuAu7_cent6Y10EventCut, 0)
#endif
};

inline void AuAu7_cent6Y10EventCut::SetEventMult(const int& lo, const int& hi) {
   mEventMult[0] = lo;
   mEventMult[1] = hi;
}
inline void AuAu7_cent6Y10EventCut::SetVertZPos(const float& lo, const float& hi) {
   mVertZPos[0] = lo;
   mVertZPos[1] = hi;
}
inline void AuAu7_cent6Y10EventCut::SetVertRPos(const float& hi) { mVertRPos = hi; }
inline void AuAu7_cent6Y10EventCut::SetCentralityBin(const int& cenbin) {
   mCentralityBin = cenbin;
   switch (mCentralityBin) {
      case 0:  // 0-80
         mEventMult[0] = 1;
         mEventMult[1] = 1000;
         break;
      case 1:  // 0-5
         mEventMult[0] = 186;
         mEventMult[1] = 1000;
         break;
      case 2:  // 5-10
         mEventMult[0] = 155;
         mEventMult[1] = 185;
         break;
      case 3:  // 10-30
         mEventMult[0] = 73;
         mEventMult[1] = 154;
         break;
      case 4:  // 30-50
         mEventMult[0] = 29;
         mEventMult[1] = 72;
         break;
      case 5:  // 50-80
         mEventMult[0] = 5;
         mEventMult[1] = 28;
         break;
      default:
         mEventMult[0] = 0;
         mEventMult[1] = 1000;
         break;
   }
}

// inline void AuAu7_cent6Y10EventCut::SetTrgSetupName(const unsigned short& trgstp){ mTrgSetupName=trgstp;}

inline int AuAu7_cent6Y10EventCut::NEventsPassed() { return mNEventsPassed; }
inline int AuAu7_cent6Y10EventCut::NEventsFailed() { return mNEventsFailed; }
inline AuAu7_cent6Y10EventCut* AuAu7_cent6Y10EventCut::Clone() {
   AuAu7_cent6Y10EventCut* c = new AuAu7_cent6Y10EventCut(*this);
   return c;
}
inline AuAu7_cent6Y10EventCut::AuAu7_cent6Y10EventCut(AuAu7_cent6Y10EventCut& c) : StHbtEventCut(c) {
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
