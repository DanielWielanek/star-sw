//-----------------------------------------------------
// Event cut for 62GeV AuAu 2004 Run
// Based on Zibi's dAuEventCut class
// SP 08/2004
//-----------------------------------------------------
#ifndef AuAu62GevEventCut_hh
#define AuAu62GevEventCut_hh

#include "StHbtMaker/Base/StHbtEventCut.h"
#ifdef HPUX
#include <fstream.h>
#else
#include <fstream>
#endif
#include <vector>

class AuAu62GevEventCut : public StHbtEventCut {
  public:
   AuAu62GevEventCut();
   AuAu62GevEventCut(AuAu62GevEventCut&);
   //  ~AuAu62GevEventCut();

   void SetEventMult(const int& lo, const int& hi);
   void SetVertZPos(const float& lo, const float& hi);
   void SetCentralityBin(const int& cenbin);
   bool CheckId(int runnr);

   int NEventsPassed();
   int NEventsFailed();

   virtual StHbtString Report();
   virtual bool Pass(const StHbtEvent*);

   AuAu62GevEventCut* Clone();

  private:                 // here are the quantities I want to cut on...
   int mEventMult[2];      // range of multiplicity
   int mFtpcEventMult[2];  // range of Ftpc multiplicity
   float mVertZPos[2];     // range of z-position of vertex
   int mCentralityBin;     // ftpc centrality bin

   long mNEventsPassed;
   long mNEventsFailed;

   ofstream* mOutFile;  //!

   vector<unsigned int> mtriggerIds;

#ifdef __ROOT__
   ClassDef(AuAu62GevEventCut, 0)
#endif
};

inline void AuAu62GevEventCut::SetEventMult(const int& lo, const int& hi) {
   mEventMult[0] = lo;
   mEventMult[1] = hi;
}
inline void AuAu62GevEventCut::SetVertZPos(const float& lo, const float& hi) {
   mVertZPos[0] = lo;
   mVertZPos[1] = hi;
}
inline void AuAu62GevEventCut::SetCentralityBin(const int& cenbin) {
   mCentralityBin = cenbin;
   switch (mCentralityBin) {
         // Min Bias
      case 0:
         mEventMult[0] = 1;
         mEventMult[1] = 1000;
         break;
         // 50-80%
      case 1:
         mEventMult[0] = 9;
         mEventMult[1] = 65;
         break;
         // 30-50%
      case 2:
         mEventMult[0] = 65;
         mEventMult[1] = 154;
         break;
         // 20-30%
      case 3:
         mEventMult[0] = 154;
         mEventMult[1] = 222;
         break;
         // 10-20%
      case 4:
         mEventMult[0] = 222;
         mEventMult[1] = 313;
         break;
         // 5-10%
      case 5:
         mEventMult[0] = 313;
         mEventMult[1] = 373;
         break;
         // 0-5%
      case 6:
         mEventMult[0] = 373;
         mEventMult[1] = 1000;
         break;
         // Extended set: Large centrality bins 10/18/04 SP
      case 7:
         // 80-30%
         mEventMult[0] = 9;
         mEventMult[1] = 154;
         break;
      case 8:
         // 30-10
         mEventMult[0] = 154;
         mEventMult[1] = 313;
         break;
      case 9:
         // 10-0
         mEventMult[0] = 313;
         mEventMult[1] = 1000;
         break;
         //    default: ;
   }
}

inline int AuAu62GevEventCut::NEventsPassed() { return mNEventsPassed; }
inline int AuAu62GevEventCut::NEventsFailed() { return mNEventsFailed; }
inline AuAu62GevEventCut* AuAu62GevEventCut::Clone() {
   AuAu62GevEventCut* c = new AuAu62GevEventCut(*this);
   return c;
}
inline AuAu62GevEventCut::AuAu62GevEventCut(AuAu62GevEventCut& c) : StHbtEventCut(c) {
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
