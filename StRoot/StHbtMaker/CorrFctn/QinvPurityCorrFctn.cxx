#include "StHbtMaker/CorrFctn/QinvPurityCorrFctn.h"

#include <cstdio>

#ifdef __ROOT__
ClassImp(QinvPurityCorrFctn)
#endif

    //____________________________
    QinvPurityCorrFctn::QinvPurityCorrFctn(char* title, const int& nbins, const float& QinvLo, const float& QinvHi,
                                           int pType) {
   // set up numerator
   char TitNum[100] = "Num";
   strcat(TitNum, title);
   mNum = new StHbt1DHisto(TitNum, title, nbins, QinvLo, QinvHi);
   // set up denominator
   char TitDen[100] = "Den";
   strcat(TitDen, title);
   mDen = new StHbt1DHisto(TitDen, title, nbins, QinvLo, QinvHi);
   // set up ratio
   char TitRat[100] = "Rat";
   strcat(TitRat, title);
   mRat = new StHbt1DHisto(TitRat, title, nbins, QinvLo, QinvHi);

   mpType = pType;
   char TitPairPurity[100];
   strcpy(TitPairPurity, "PairPurity");
   strcat(TitPairPurity, title);
   mPairPurity = new TProfile(TitPairPurity, title, nbins, QinvLo, QinvHi);

   // to enable error bar calculation...
   mNum->Sumw2();
   mDen->Sumw2();
   mRat->Sumw2();
}

QinvPurityCorrFctn::~QinvPurityCorrFctn() {
   delete mNum;
   delete mDen;
   delete mRat;

   delete mPairPurity;
}
//_________________________
void QinvPurityCorrFctn::Finish() {
   double tScale;
   int tLastNormBin = mNum->GetNbinsX();
   int tFirstNormBin = tLastNormBin / 2 + 1;
   // Make cvk dependant correlation function
   mRat->Divide(mNum, mDen, 1.0, 1.0);
   tScale = mRat->Integral(tFirstNormBin, tLastNormBin);
   tScale /= (tLastNormBin - tFirstNormBin + 1);
   mRat->Scale(1. / tScale);
}

void QinvPurityCorrFctn::Write() {
   mNum->Write();
   mDen->Write();
   mRat->Write();

   mPairPurity->Write();
}

//____________________________
StHbtString QinvPurityCorrFctn::Report() {
   string stemp = "Qinv Correlation Function Report:\n";
   char ctemp[100];
   sprintf(ctemp, "Number of entries in numerator:\t%E\n", mNum->GetEntries());
   stemp += ctemp;
   sprintf(ctemp, "Number of entries in denominator:\t%E\n", mDen->GetEntries());
   stemp += ctemp;
   sprintf(ctemp, "Number of entries in ratio:\t%E\n", mRat->GetEntries());
   stemp += ctemp;
   StHbtString returnThis = stemp;
   return returnThis;
}
//____________________________
void QinvPurityCorrFctn::AddRealPair(const StHbtPair* pair) {
   double tKStar = fabs(pair->KStar());
   // double tPStar = 2*fabs(pair->KStarFlipped());
   double pPurity = 0.0;
   mNum->Fill(tKStar);

   switch (mpType) {
      case 1:
         pPurity = (pair->track1()->GetPionPurity()) * (pair->track2()->GetPionPurity());
         break;
      case 2:
         pPurity = (pair->track1()->GetKaonPurity()) * (pair->track2()->GetKaonPurity());
         break;
      case 3:
         pPurity = (pair->track1()->GetProtonPurity()) * (pair->track2()->GetProtonPurity());
         break;
      case 4:
         pPurity = (pair->track1()->Track()->PidProbElectron()) * (pair->track2()->Track()->PidProbElectron());
         break;
   }

   mPairPurity->Fill(tKStar, pPurity);
}
//____________________________
void QinvPurityCorrFctn::AddMixedPair(const StHbtPair* pair) {
   double tKStar = 2 * fabs(pair->KStar());
   // double tPStar = 2*fabs(pair->KStarFlipped());
   mDen->Fill(tKStar);
}
