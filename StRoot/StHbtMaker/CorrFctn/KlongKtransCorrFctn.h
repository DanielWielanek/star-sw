// Hanna Gos, Warsaw University of Technology, SUBATECH

#ifndef KlongKtransCorrFctn_hh
#define KlongKtransCorrFctn_hh

#include "StHbtMaker/Base/StHbtCorrFctn.hh"

class KlongKtransCorrFctn : public StHbtCorrFctn {
  public:
   KlongKtransCorrFctn(char* title, const int& nbins, const float& QinvLo, const float& QinvHi);
   virtual ~KlongKtransCorrFctn();

   virtual StHbtString Report();
   virtual void AddRealPair(const StHbtPair*);
   virtual void AddMixedPair(const StHbtPair*);

   virtual void Finish();
   virtual void Write();

   StHbt2DHisto* Num();
   StHbt2DHisto* Den();

   StHbt1DHisto* Mon();

  private:
   StHbt2DHisto* mNum;
   StHbt2DHisto* mDen;

   StHbt1DHisto* mMon;

#ifdef __ROOT__
   ClassDef(KlongKtransCorrFctn, 1)
#endif
};

inline StHbt2DHisto* KlongKtransCorrFctn::Num() { return mNum; }
inline StHbt2DHisto* KlongKtransCorrFctn::Den() { return mDen; }
inline StHbt1DHisto* KlongKtransCorrFctn::Mon() { return mMon; }

#endif
