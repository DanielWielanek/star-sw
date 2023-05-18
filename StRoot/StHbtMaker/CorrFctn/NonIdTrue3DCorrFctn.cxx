#include "StHbtMaker/CorrFctn/NonIdTrue3DCorrFctn.h"

#include <cstdio>

#include "StHbtMaker/Infrastructure/StHbtAnalysis.h"

#ifdef __ROOT__
ClassImp(NonIdTrue3DCorrFctn)
#endif

    void NonIdTrue3DCorrFctn::makeHistos(char* title, const int& nbins, const float& QinvLo, const float& QinvHi,
                                         int nmixbins) {
   NBins = nmixbins;
   char tbuf[100];

   mNums = new StHbt3IHisto*[nmixbins];
   mDens = new StHbt3IHisto*[nmixbins];
   for (int iter = 0; iter < nmixbins; iter++) {
      // set up numerators
      sprintf(tbuf, "NumTrue3D%s%i", title, iter);
      mNums[iter] =
          new StHbt3IHisto(tbuf, title, nbins, -QinvHi, QinvHi, nbins, -QinvHi, QinvHi, nbins, -QinvHi, QinvHi);

      // set up denominators
      sprintf(tbuf, "DenTrue3D%s%i", title, iter);
      mDens[iter] =
          new StHbt3IHisto(tbuf, title, nbins, -QinvHi, QinvHi, nbins, -QinvHi, QinvHi, nbins, -QinvHi, QinvHi);

      mNums[iter]->Sumw2();
      mDens[iter]->Sumw2();
   }

   sprintf(tbuf, "NumTrue3DSum%s", title);
   mNumSum = new StHbt3IHisto(tbuf, title, nbins, -QinvHi, QinvHi, nbins, -QinvHi, QinvHi, nbins, -QinvHi, QinvHi);
   sprintf(tbuf, "DenTrue3DSum%s", title);
   mDenSum = new StHbt3IHisto(tbuf, title, nbins, -QinvHi, QinvHi, nbins, -QinvHi, QinvHi, nbins, -QinvHi, QinvHi);

   // to enable error bar calculation...
   mNumSum->Sumw2();
   mDenSum->Sumw2();
}

//____________________________
NonIdTrue3DCorrFctn::NonIdTrue3DCorrFctn(char* title, const int& nbins, const float& QLo, const float& QHi,
                                         int nmixbin) {
   makeHistos(title, nbins, QLo, QHi, nmixbin);
}

//____________________________
NonIdTrue3DCorrFctn::~NonIdTrue3DCorrFctn() {
   delete mNumSum;
   delete mDenSum;

   for (int iter = 0; iter < NBins; iter++) {
      delete mNums[iter];
      delete mDens[iter];
   }
   delete[] mNums;
   delete[] mDens;
}
//_________________________
void NonIdTrue3DCorrFctn::Finish() {
   double tScale;
   int tFirstExclude = mNums[0]->GetNbinsX() * 1 / 6;
   int tLastExclude = mNums[0]->GetNbinsX() * 5 / 6;
   int tCountBins = mNums[0]->GetNbinsX();

   mNumSum->Reset("ICE");
   mDenSum->Reset("ICE");

   Double_t scalen;
   Double_t scaled;

   for (int iter = 0; iter < NBins; iter++) {
      if (mNums[iter]->GetEntries() && mDens[iter]->GetEntries()) {
         mNumSum->Add(mNums[iter]);
         scalen = mNums[iter]->Integral(1, tCountBins, 1, tCountBins, 1, tCountBins);
         scalen -= mNums[iter]->Integral(tFirstExclude, tLastExclude, tFirstExclude, tLastExclude, tFirstExclude,
                                         tLastExclude);
         scaled = mDens[iter]->Integral(1, tCountBins, 1, tCountBins, 1, tCountBins);
         scaled -= mDens[iter]->Integral(tFirstExclude, tLastExclude, tFirstExclude, tLastExclude, tFirstExclude,
                                         tLastExclude);
         mDenSum->Add(mDens[iter], scalen / scaled);
      }
   }
}

//____________________________
StHbtString NonIdTrue3DCorrFctn::Report() {
   string stemp = "KStar True 3D Non-identical Correlation Function Report:\n";
   char ctemp[100];
   ctemp[0] = 0;
   stemp += ctemp;
   //
   StHbtString returnThis = stemp;
   return returnThis;
}
//____________________________
void NonIdTrue3DCorrFctn::AddRealPair(const StHbtPair* pair) {
   double tKOut = pair->dKOut();
   double tKSide = pair->dKSide();
   double tKLong = pair->dKLong();

   mNumSum->Fill(tKOut, tKSide, tKLong);
}

//____________________________
void NonIdTrue3DCorrFctn::AddMixedPair(const StHbtPair* pair) {
   double tKOut = pair->dKOut();
   double tKSide = pair->dKSide();
   double tKLong = pair->dKLong();

   int nbin;
   StHbtAnalysis* curan = dynamic_cast<StHbtAnalysis*>(HbtAnalysis());
   nbin = curan->GetMixingBinNumber();

   mDens[nbin]->Fill(tKOut, tKSide, tKLong);
}

void NonIdTrue3DCorrFctn::Write() {
   mNumSum->Write();
   mDenSum->Write();

   for (int iter = 0; iter < NBins; iter++) {
      mNums[iter]->Write();
      mDens[iter]->Write();
   }
}

void NonIdTrue3DCorrFctn::EventBegin(const StHbtEvent* event) {}
//____________________________
void NonIdTrue3DCorrFctn::EventEnd(const StHbtEvent* event) {
   StHbtAnalysis* curan = dynamic_cast<StHbtAnalysis*>(HbtAnalysis());
   cout << "Got analysis " << curan << endl;
   int tMixingBinNumber = curan->GetMixingBinNumber();
   cout << "Got mixing buffer number " << tMixingBinNumber << endl;
   int nbin = tMixingBinNumber;

   mNums[nbin]->Add(mNumSum);

   mNumSum->Reset("ICE");
}
