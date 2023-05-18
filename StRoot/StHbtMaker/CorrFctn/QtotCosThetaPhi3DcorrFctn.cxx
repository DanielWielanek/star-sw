#include "StHbtMaker/CorrFctn/QtotCosThetaPhi3DcorrFctn.h"

#include <cstdio>

#ifdef __ROOT__
ClassImp(QtotCosThetaPhi3DcorrFctn)
#endif

    //____________________________
    QtotCosThetaPhi3DcorrFctn::QtotCosThetaPhi3DcorrFctn(char* title, const int& nbinsQi, const float& QiLo,
                                                         const float& QiHi, const int& nbinsCT, const float& CTLo,
                                                         const float& CTHi, const int& nbinsPh, const float& PhLo,
                                                         const float& PhHi) {
   // set some stuff...
   // set up numerator
   char TitNum[100] = "Ang3DNum";
   strcat(TitNum, title);
   mNumerator = new StHbt3DHisto(TitNum, title, nbinsQi, QiLo, QiHi, nbinsCT, CTLo, CTHi, nbinsPh, PhLo, PhHi);
   mNumerator->GetXaxis()->SetTitle("k*");
   mNumerator->GetYaxis()->SetTitle("cosTheta");
   mNumerator->GetZaxis()->SetTitle("Phi");
   // set up denominator
   char TitDen[100] = "Ang3DDen";
   strcat(TitDen, title);
   mDenominator = new StHbt3DHisto(TitDen, title, nbinsQi, QiLo, QiHi, nbinsCT, CTLo, CTHi, nbinsPh, PhLo, PhHi);
   mDenominator->GetXaxis()->SetTitle("k*");
   mDenominator->GetYaxis()->SetTitle("cosTheta");
   mDenominator->GetZaxis()->SetTitle("Phi");
   // to enable error bar calculation...
   mNumerator->Sumw2();
   mDenominator->Sumw2();

   //   char TitSf[100] = "CheckSumF";
   //   strcat(TitSf,title);
   //   mSF= new StHbt2DHisto(TitSf,title,5*nbinsQi,-5.,5,5*nbinsQi,-5.,5);
   //   mSF->GetXaxis()->SetTitle("init");
   //   mSF->GetYaxis()->SetTitle("Fab");

   //   char TitSzb[100] = "CheckSumZB";
   //   strcat(TitSzb,title);
   //   mSZb= new StHbt2DHisto(TitSzb,title,5*nbinsQi,-5.,5,5*nbinsQi,-5.,5);
   //   mSZb->GetXaxis()->SetTitle("init");
   //   mSZb->GetYaxis()->SetTitle("ZB");

   //   char TitDf[100] = "CheckDiffFab";
   //   strcat(TitDf,title);
   //   mDF= new StHbt2DHisto(TitDf,title,5*nbinsQi,-5.,5,5*nbinsQi,-5.,5);
   //   mDF->GetXaxis()->SetTitle("init");
   //   mDF->GetYaxis()->SetTitle("Fab");

   //   char TitDzb[100] = "CheckDiffZB";
   //   strcat(TitDzb,title);
   //   mDZb= new StHbt2DHisto(TitDzb,title,5*nbinsQi,-5.,5,5*nbinsQi,-5.,5);
   //   mDZb->GetXaxis()->SetTitle("init");
   //   mDZb->GetYaxis()->SetTitle("ZB");
}

//____________________________
QtotCosThetaPhi3DcorrFctn::~QtotCosThetaPhi3DcorrFctn() {
   delete mNumerator;
   delete mDenominator;
}

//_________________________
void QtotCosThetaPhi3DcorrFctn::WriteOutHistos() {
   mNumerator->Write();
   mDenominator->Write();
   //   mSF->Write();
   //   mSZb->Write();
   //   mDF->Write();
   //   mDZb->Write();
}

//_________________________
void QtotCosThetaPhi3DcorrFctn::Finish() {}

//____________________________
StHbtString QtotCosThetaPhi3DcorrFctn::Report() {
   string stemp = "LCMS Frame Bertsch-Pratt 3D Correlation Function Report:\n";
   char ctemp[100];
   sprintf(ctemp, "Number of entries in numerator:\t%E\n", mNumerator->GetEntries());
   stemp += ctemp;
   sprintf(ctemp, "Number of entries in denominator:\t%E\n", mDenominator->GetEntries());
   stemp += ctemp;

   //
   StHbtString returnThis = stemp;
   return returnThis;
}
//____________________________
void QtotCosThetaPhi3DcorrFctn::AddRealPair(const StHbtPair* pair) {
   /* z for some reason doesn't work
   double qOut   = pair->qOutPf()/2.;
   double qSide  = pair->qSidePf()/2.;
   double qLong  = pair->qLongPf()/2.;
   */
   double qOut = pair->KStarOut();
   double qSide = pair->KStarSide();
   double qLong = pair->KStarLong();

   // double mD=pair->fourMomentumDiff().m2();
   // double mS=pair->fourMomentumSum().m2();

   double qOut2 = qOut * qOut;
   double qSide2 = qSide * qSide;
   double qLong2 = qLong * qLong;
   double Qtot = TMath::Sqrt(qOut2 + qSide2 + qLong2);

   double cosTheta = 1.;
   if (Qtot != 0) cosTheta = qLong / Qtot;
   double phi = TMath::ATan2(qSide, qOut);
   if (phi < 0) phi = 2 * TMath::Pi() - TMath::Abs(phi);
   mNumerator->Fill(Qtot, cosTheta, phi);
}
//____________________________
void QtotCosThetaPhi3DcorrFctn::AddMixedPair(const StHbtPair* pair) {
   /*
   double qOut   = pair->qOutPf()/2.;
   double qSide  = pair->qSidePf()/2.;
   double qLong  = pair->qLongPf()/2.;
   */
   double qOut = pair->KStarOut();
   double qSide = pair->KStarSide();
   double qLong = pair->KStarLong();

   double qOut2 = qOut * qOut;
   double qSide2 = qSide * qSide;
   double qLong2 = qLong * qLong;
   double Qtot = TMath::Sqrt(qOut2 + qSide2 + qLong2);
   double cosTheta = 1.;
   if (Qtot != 0) cosTheta = qLong / Qtot;
   double phi = TMath::ATan2(qSide, qOut);
   if (phi < 0) phi = 2 * TMath::Pi() - TMath::Abs(phi);
   mDenominator->Fill(Qtot, cosTheta, phi);
}
