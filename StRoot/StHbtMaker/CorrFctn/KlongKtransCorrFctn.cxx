// Hanna Gos, Warsaw University of Technology, SUBATECH

#include "StHbtMaker/CorrFctn/KlongKtransCorrFctn.h"

#include <cstdio>

#ifdef __ROOT__
ClassImp(KlongKtransCorrFctn)
#endif

    //____________________________
    KlongKtransCorrFctn::KlongKtransCorrFctn(char* title, const int& nbins, const float& QinvLo, const float& QinvHi) {
   // set up numerator
   char TitNum[100] = "Num";
   strcat(TitNum, title);
   mNum = new StHbt2DHisto(TitNum, title, nbins, QinvLo, QinvHi, nbins, QinvLo, QinvHi);
   // set up denominator
   char TitDen[100] = "Den";
   strcat(TitDen, title);
   mDen = new StHbt2DHisto(TitDen, title, nbins, QinvLo, QinvHi, nbins, QinvLo, QinvHi);
   char TitMon[100] = "Mon";
   strcat(TitMon, title);
   mMon = new StHbt1DHisto(TitMon, title, 200, 0.0, 2.0);

   // to enable error bar calculation...
   mNum->Sumw2();
   mDen->Sumw2();
   mMon->Sumw2();
}

//____________________________
KlongKtransCorrFctn::~KlongKtransCorrFctn() {
   delete mNum;
   delete mDen;
   delete mMon;
}
//_________________________
void KlongKtransCorrFctn::Finish() {}

void KlongKtransCorrFctn::Write() {
   mNum->Write();
   mDen->Write();
   mMon->Write();
}

//____________________________
StHbtString KlongKtransCorrFctn::Report() {
   string stemp = "KlongKtrans Correlation Function Report:\n";
   char ctemp[100];
   sprintf(ctemp, "Number of entries in numerator:\t%E\n", mNum->GetEntries());
   stemp += ctemp;
   sprintf(ctemp, "Number of entries in denominator:\t%E\n", mDen->GetEntries());
   stemp += ctemp;
   StHbtString returnThis = stemp;
   return returnThis;
}
//____________________________
void KlongKtransCorrFctn::AddRealPair(const StHbtPair* pair) {
   double tKStarLong = fabs(pair->KStarLong());
   double tKStarTrans = sqrt(pair->KStarOut() * pair->KStarOut() + pair->KStarSide() * pair->KStarSide());
   double tkT = pair->kT();

   mNum->Fill(tKStarTrans, tKStarLong);
   mMon->Fill(tkT);
}
//____________________________
void KlongKtransCorrFctn::AddMixedPair(const StHbtPair* pair) {
   double tKStarLong = fabs(pair->KStarLong());
   double tKStarTrans = sqrt(pair->KStarOut() * pair->KStarOut() + pair->KStarSide() * pair->KStarSide());

   mDen->Fill(tKStarTrans, tKStarLong);
}
