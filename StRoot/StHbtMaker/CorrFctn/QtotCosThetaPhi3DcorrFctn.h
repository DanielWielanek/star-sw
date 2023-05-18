/***************************************************************************
 *
 * $Id: QtotCosThetaPhi3DcorrFctn.h,v 0.1 2004/10/12 04:20:3 zch  $
 *
 * Author: Zbigniew Chajecki, chajecki@mps.ohio-state.edu
 ***************************************************************************
 * 2004/10/23 - phi angle fixed [0,2Pi]
 *
 **************************************************************************/

#ifndef QtotCosThetaPhi3DcorrFctn_hh
#define QtotCosThetaPhi3DcorrFctn_hh

#include "StHbtMaker/Base/StHbtCorrFctn.hh"
#include "StHbtMaker/Infrastructure/StHbtCoulomb.h"

class QtotCosThetaPhi3DcorrFctn : public StHbtCorrFctn {
  public:
   QtotCosThetaPhi3DcorrFctn(char* title, const int& nbinsQi, const float& QiLo, const float& QiHi, const int& nbinsCT,
                             const float& CTLo, const float& CTHi, const int& nbinsPh, const float& PhLo,
                             const float& PhHi);
   virtual ~QtotCosThetaPhi3DcorrFctn();

   virtual StHbtString Report();
   virtual void AddRealPair(const StHbtPair*);
   virtual void AddMixedPair(const StHbtPair*);

   virtual void Finish();

   StHbt3DHisto* Numerator();
   StHbt3DHisto* Denominator();

   void WriteOutHistos();

   void SetCoulombCorrection(StHbtCoulomb* Correction);

  private:
   StHbt3DHisto* mNumerator;
   StHbt3DHisto* mDenominator;

   /*   StHbt2DHisto* mSZb; */
   /*   StHbt2DHisto* mSF; */
   /*   StHbt2DHisto* mDZb; */
   /*   StHbt2DHisto* mDF; */

#ifdef __ROOT__
   ClassDef(QtotCosThetaPhi3DcorrFctn, 1)
#endif
};

inline StHbt3DHisto* QtotCosThetaPhi3DcorrFctn::Numerator() { return mNumerator; }
inline StHbt3DHisto* QtotCosThetaPhi3DcorrFctn::Denominator() { return mDenominator; }

#endif
