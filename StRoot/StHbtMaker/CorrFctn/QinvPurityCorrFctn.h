#ifndef QinvPurityCorrFctn_hh
#define QinvPurityCorrFctn_hh

#include <TProfile.h>

#include "StHbtMaker/Base/StHbtCorrFctn.hh"
#include "TList.h"

class QinvPurityCorrFctn : public StHbtCorrFctn {
  public:
   QinvPurityCorrFctn(char* title, const int& nbins, const float& QinvLo, const float& QinvHi, int pType);
   virtual ~QinvPurityCorrFctn();

   virtual StHbtString Report();
   virtual void AddRealPair(const StHbtPair*);
   virtual void AddMixedPair(const StHbtPair*);

   virtual void Finish();
   virtual void Write();
   virtual void AppendOutput(TList*);

   StHbt1DHisto* Num();
   StHbt1DHisto* Den();
   StHbt1DHisto* Rat();
   TProfile* PairPurity();

  private:
   StHbt1DHisto* mNum;
   StHbt1DHisto* mDen;
   StHbt1DHisto* mRat;

   int mpType;
   TProfile* mPairPurity;

#ifdef __ROOT__
   ClassDef(QinvPurityCorrFctn, 1)
#endif
};

inline StHbt1DHisto* QinvPurityCorrFctn::Num() { return mNum; }
inline StHbt1DHisto* QinvPurityCorrFctn::Den() { return mDen; }
inline StHbt1DHisto* QinvPurityCorrFctn::Rat() { return mRat; }
inline TProfile* QinvPurityCorrFctn::PairPurity() { return mPairPurity; }
inline void QinvPurityCorrFctn::AppendOutput(TList* output) {
   output->Add(Num());
   output->Add(Den());
   output->Add(Rat());
   output->Add(PairPurity());
}
#endif
