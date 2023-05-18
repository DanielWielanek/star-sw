/***************************************************************************
 *
 * $Id: NonId3DCorrFctnMB.cxx,v 1.1 2001/04/03 21:02:50 kisiel Exp $
 *
 * Author: Adam Kisiel, Warsaw University of Technology
 ***************************************************************************
 *
 * Description: part of STAR HBT FRAMEWORK
 *   The correlation function for non-identical particle
 *   correlations. Uses selection on pair kinematics
 *   to perform a "3D-like" analysis.
 *
 ***************************************************************************
 *
 * $Log: NonId3DCorrFctnMB.cxx,v $
 * Revision 1.1  2001/04/03 21:02:50  kisiel
 *
 *
 *   The correlation function for non-identical particle
 *   correlations. Uses selection on pair kinematics
 *   to perform a "3D-like" analysis.
 *
 * Revision 1.4  2000/01/25 17:34:45  laue
 * I. In order to run the stand alone version of the StHbtMaker the following
 * changes have been done:
 * a) all ClassDefs and ClassImps have been put into #ifdef __ROOT__ statements
 * b) unnecessary includes of StMaker.h have been removed
 * c) the subdirectory StHbtMaker/doc/Make has been created including everything
 * needed for the stand alone version
 *
 * II. To reduce the amount of compiler warning
 * a) some variables have been type casted
 * b) some destructors have been declared as virtual
 *
 * Revision 1.3  1999/07/29 02:47:09  lisa
 * 1) add OpeningAngle correlation function 2) add StHbtMcEventReader 3) make histos in CorrFctns do errors correctly
 *
 * Revision 1.2  1999/07/06 22:33:20  lisa
 * Adjusted all to work in pro and new - dev itself is broken
 *
 * Revision 1.1.1.1  1999/06/29 16:02:57  lisa
 * Installation of StHbtMaker
 *
 **************************************************************************/

#include "StHbtMaker/CorrFctn/NonId3DCorrFctnMB.h"

#include <cstdio>

#ifdef __ROOT__
ClassImp(NonId3DCorrFctnMB)
#endif

    //____________________________
    NonId3DCorrFctnMB::NonId3DCorrFctnMB(char* title, const int& nbins, const float& QinvLo, const float& QinvHi,
                                         int nmixbins) {
   makeHistos(title, nbins, QinvLo, QinvHi, nmixbins);
}

//____________________________
void NonId3DCorrFctnMB::makeHistos(char* title, const int& nbins, const float& QinvLo, const float& QinvHi,
                                   int nmixbins) {
   NBins = nmixbins;

   char tbuf[100];

   mNumOutP = new StHbt1IHisto*[nmixbins];
   mDenOutP = new StHbt1IHisto*[nmixbins];
   mNumOutN = new StHbt1IHisto*[nmixbins];
   mDenOutN = new StHbt1IHisto*[nmixbins];
   for (int iter = 0; iter < nmixbins; iter++) {
      // set up numerators
      sprintf(tbuf, "NumOutP%s%i", title, iter);
      mNumOutP[iter] = new StHbt1IHisto(tbuf, title, nbins, QinvLo, QinvHi);
      // set up numerator
      sprintf(tbuf, "NumOutN%s%i", title, iter);
      mNumOutN[iter] = new StHbt1IHisto(tbuf, title, nbins, QinvLo, QinvHi);

      // set up denominators
      sprintf(tbuf, "DenOutP%s%i", title, iter);
      mDenOutP[iter] = new StHbt1IHisto(tbuf, title, nbins, QinvLo, QinvHi);
      // set up denominator
      sprintf(tbuf, "DenOutN%s%i", title, iter);
      mDenOutN[iter] = new StHbt1IHisto(tbuf, title, nbins, QinvLo, QinvHi);

      mNumOutP[iter]->Sumw2();
      mDenOutP[iter]->Sumw2();
      mNumOutN[iter]->Sumw2();
      mDenOutN[iter]->Sumw2();
   }

   sprintf(tbuf, "NumOutP%s", title);
   mNumOutPSum = new StHbt1IHisto(tbuf, title, nbins, QinvLo, QinvHi);
   sprintf(tbuf, "DenOutP%s", title);
   mDenOutPSum = new StHbt1IHisto(tbuf, title, nbins, QinvLo, QinvHi);
   sprintf(tbuf, "NumOutN%s", title);
   mNumOutNSum = new StHbt1IHisto(tbuf, title, nbins, QinvLo, QinvHi);
   sprintf(tbuf, "DenOutN%s", title);
   mDenOutNSum = new StHbt1IHisto(tbuf, title, nbins, QinvLo, QinvHi);

   mNumSideP = new StHbt1IHisto*[nmixbins];
   mDenSideP = new StHbt1IHisto*[nmixbins];
   mNumSideN = new StHbt1IHisto*[nmixbins];
   mDenSideN = new StHbt1IHisto*[nmixbins];
   for (int iter = 0; iter < nmixbins; iter++) {
      // set up numerators
      sprintf(tbuf, "NumSideP%s%i", title, iter);
      mNumSideP[iter] = new StHbt1IHisto(tbuf, title, nbins, QinvLo, QinvHi);
      // set up numerator
      sprintf(tbuf, "NumSideN%s%i", title, iter);
      mNumSideN[iter] = new StHbt1IHisto(tbuf, title, nbins, QinvLo, QinvHi);

      // set up denominators
      sprintf(tbuf, "DenSideP%s%i", title, iter);
      mDenSideP[iter] = new StHbt1IHisto(tbuf, title, nbins, QinvLo, QinvHi);
      // set up denominator
      sprintf(tbuf, "DenSideN%s%i", title, iter);
      mDenSideN[iter] = new StHbt1IHisto(tbuf, title, nbins, QinvLo, QinvHi);

      mNumSideP[iter]->Sumw2();
      mDenSideP[iter]->Sumw2();
      mNumSideN[iter]->Sumw2();
      mDenSideN[iter]->Sumw2();
   }

   sprintf(tbuf, "NumSideP%s", title);
   mNumSidePSum = new StHbt1IHisto(tbuf, title, nbins, QinvLo, QinvHi);
   sprintf(tbuf, "DenSideP%s", title);
   mDenSidePSum = new StHbt1IHisto(tbuf, title, nbins, QinvLo, QinvHi);
   sprintf(tbuf, "NumSideN%s", title);
   mNumSideNSum = new StHbt1IHisto(tbuf, title, nbins, QinvLo, QinvHi);
   sprintf(tbuf, "DenSideN%s", title);
   mDenSideNSum = new StHbt1IHisto(tbuf, title, nbins, QinvLo, QinvHi);

   mNumLongP = new StHbt1IHisto*[nmixbins];
   mDenLongP = new StHbt1IHisto*[nmixbins];
   mNumLongN = new StHbt1IHisto*[nmixbins];
   mDenLongN = new StHbt1IHisto*[nmixbins];
   for (int iter = 0; iter < nmixbins; iter++) {
      // set up numerators
      sprintf(tbuf, "NumLongP%s%i", title, iter);
      mNumLongP[iter] = new StHbt1IHisto(tbuf, title, nbins, QinvLo, QinvHi);
      // set up numerator
      sprintf(tbuf, "NumLongN%s%i", title, iter);
      mNumLongN[iter] = new StHbt1IHisto(tbuf, title, nbins, QinvLo, QinvHi);

      // set up denominators
      sprintf(tbuf, "DenLongP%s%i", title, iter);
      mDenLongP[iter] = new StHbt1IHisto(tbuf, title, nbins, QinvLo, QinvHi);
      // set up denominator
      sprintf(tbuf, "DenLongN%s%i", title, iter);
      mDenLongN[iter] = new StHbt1IHisto(tbuf, title, nbins, QinvLo, QinvHi);

      mNumLongP[iter]->Sumw2();
      mDenLongP[iter]->Sumw2();
      mNumLongN[iter]->Sumw2();
      mDenLongN[iter]->Sumw2();
   }

   sprintf(tbuf, "NumLongP%s", title);
   mNumLongPSum = new StHbt1IHisto(tbuf, title, nbins, QinvLo, QinvHi);
   sprintf(tbuf, "DenLongP%s", title);
   mDenLongPSum = new StHbt1IHisto(tbuf, title, nbins, QinvLo, QinvHi);
   sprintf(tbuf, "NumLongN%s", title);
   mNumLongNSum = new StHbt1IHisto(tbuf, title, nbins, QinvLo, QinvHi);
   sprintf(tbuf, "DenLongN%s", title);
   mDenLongNSum = new StHbt1IHisto(tbuf, title, nbins, QinvLo, QinvHi);

   // to enable error bar calculation...
   mNumOutPSum->Sumw2();
   mDenOutPSum->Sumw2();
   mNumOutNSum->Sumw2();
   mDenOutNSum->Sumw2();

   mNumSidePSum->Sumw2();
   mDenSidePSum->Sumw2();
   mNumSideNSum->Sumw2();
   mDenSideNSum->Sumw2();

   mNumLongPSum->Sumw2();
   mDenLongPSum->Sumw2();
   mNumLongNSum->Sumw2();
   mDenLongNSum->Sumw2();

   float kstarlim = 0.5;
   float klim = 0.6 * kstarlim;
   //  float klim2 = 0.3;
   //  double exitlim = 400.0;
   double ptlim = 1.0;

   char htitle[200];
   strcpy(htitle, "HOutKSame");
   mHOutKSame = new StHbt2IHisto(strcat(htitle, title), htitle, 100, -klim, klim, nbins, QinvLo, kstarlim);
   strcpy(htitle, "HOutKDiff");
   mHOutKDiff = new StHbt2IHisto(strcat(htitle, title), htitle, 100, -klim, klim, nbins, QinvLo, kstarlim);
   strcpy(htitle, "HSideKSame");
   mHSideKSame = new StHbt2IHisto(strcat(htitle, title), htitle, 100, -klim, klim, nbins, QinvLo, kstarlim);
   strcpy(htitle, "HSideKDiff");
   mHSideKDiff = new StHbt2IHisto(strcat(htitle, title), htitle, 100, -klim, klim, nbins, QinvLo, kstarlim);
   strcpy(htitle, "HLongKSame");
   mHLongKSame = new StHbt2IHisto(strcat(htitle, title), htitle, 100, -klim, klim, nbins, QinvLo, kstarlim);
   strcpy(htitle, "HLongKDiff");
   mHLongKDiff = new StHbt2IHisto(strcat(htitle, title), htitle, 100, -klim, klim, nbins, QinvLo, kstarlim);
   strcpy(htitle, "HPt1KStarOutNum");
   mHPt1KStarOutNum = new StHbt2IHisto(strcat(htitle, title), htitle, 100, 0.0, ptlim, nbins * 2, -QinvHi, QinvHi);
   strcpy(htitle, "HPt1KStarOutDen");
   mHPt1KStarOutDen = new StHbt2IHisto(strcat(htitle, title), htitle, 100, 0.0, ptlim, nbins * 2, -QinvHi, QinvHi);
   strcpy(htitle, "HPt2KStarOutNum");
   mHPt2KStarOutNum = new StHbt2IHisto(strcat(htitle, title), htitle, 100, 0.0, ptlim, nbins * 2, -QinvHi, QinvHi);
   strcpy(htitle, "HPt2KStarOutDen");
   mHPt2KStarOutDen = new StHbt2IHisto(strcat(htitle, title), htitle, 100, 0.0, ptlim, nbins * 2, -QinvHi, QinvHi);
   strcpy(htitle, "HPt1KStarSideNum");
   mHPt1KStarSideNum = new StHbt2IHisto(strcat(htitle, title), htitle, 100, 0.0, ptlim, nbins * 2, -QinvHi, QinvHi);
   strcpy(htitle, "HPt1KStarSideDen");
   mHPt1KStarSideDen = new StHbt2IHisto(strcat(htitle, title), htitle, 100, 0.0, ptlim, nbins * 2, -QinvHi, QinvHi);
   strcpy(htitle, "HPt2KStarSideNum");
   mHPt2KStarSideNum = new StHbt2IHisto(strcat(htitle, title), htitle, 100, 0.0, ptlim, nbins * 2, -QinvHi, QinvHi);
   strcpy(htitle, "HPt2KStarSideDen");
   mHPt2KStarSideDen = new StHbt2IHisto(strcat(htitle, title), htitle, 100, 0.0, ptlim, nbins * 2, -QinvHi, QinvHi);
   strcpy(htitle, "KStarRap1Num");
   strcat(htitle, title);
   mHKStarRap1OutNum = new StHbt2IHisto(htitle, htitle, nbins * 2, -QinvHi, QinvHi, 50, 0.0, 1.0);
   strcpy(htitle, "KStarRap2Num");
   strcat(htitle, title);
   mHKStarRap2OutNum = new StHbt2IHisto(htitle, htitle, nbins * 2, -QinvHi, QinvHi, 50, 0.0, 1.0);

   strcpy(htitle, "KStarRap1Den");
   strcat(htitle, title);
   mHKStarRap1OutDen = new StHbt2IHisto(htitle, htitle, nbins * 2, -QinvHi, QinvHi, 50, 0.0, 1.0);
   strcpy(htitle, "KStarRap2Den");
   strcat(htitle, title);
   mHKStarRap2OutDen = new StHbt2IHisto(htitle, htitle, nbins * 2, -QinvHi, QinvHi, 50, 0.0, 1.0);

   strcpy(htitle, "KStarPhi1Num");
   strcat(htitle, title);
   mHKStarPhi1OutNum = new StHbt2IHisto(htitle, htitle, nbins * 2, -QinvHi, QinvHi, 50, 0.0, 2 * TMath::Pi());
   strcpy(htitle, "KStarPhi2Num");
   strcat(htitle, title);
   mHKStarPhi2OutNum = new StHbt2IHisto(htitle, htitle, nbins * 2, -QinvHi, QinvHi, 50, 0.0, 2 * TMath::Pi());

   strcpy(htitle, "KStarPhi1Den");
   strcat(htitle, title);
   mHKStarPhi1OutDen = new StHbt2IHisto(htitle, htitle, nbins * 2, -QinvHi, QinvHi, 50, 0.0, 2 * TMath::Pi());
   strcpy(htitle, "KStarPhi2Den");
   strcat(htitle, title);
   mHKStarPhi2OutDen = new StHbt2IHisto(htitle, htitle, nbins * 2, -QinvHi, QinvHi, 50, 0.0, 2 * TMath::Pi());

   mKCompCut = -1000.0;
   mqSideSel = 0;
}

//____________________________
NonId3DCorrFctnMB::NonId3DCorrFctnMB(char* title, const int& nbins, const float& QinvLo, const float& QinvHi,
                                     const int aqSideSel, int nmixbins) {
   makeHistos(title, nbins, QinvLo, QinvHi, nmixbins);
   mKCompCut = -1000.0;
   mqSideSel = aqSideSel;
}

NonId3DCorrFctnMB::NonId3DCorrFctnMB(char* title, const int& nbins, const float& QinvLo, const float& QinvHi,
                                     const float KCompCut, int nmixbins) {
   makeHistos(title, nbins, QinvLo, QinvHi, nmixbins);
   mKCompCut = KCompCut;
   mqSideSel = 0;
}

//____________________________
NonId3DCorrFctnMB::~NonId3DCorrFctnMB() {
   delete mNumOutPSum;
   delete mDenOutPSum;
   delete mNumOutNSum;
   delete mDenOutNSum;

   for (int iter = 0; iter < NBins; iter++) {
      delete mNumOutP[iter];
      delete mDenOutP[iter];
      delete mNumOutN[iter];
      delete mDenOutN[iter];
   }
   delete[] mNumOutN;
   delete[] mNumOutP;
   delete[] mDenOutN;
   delete[] mDenOutP;

   delete mNumSidePSum;
   delete mDenSidePSum;
   delete mNumSideNSum;
   delete mDenSideNSum;

   for (int iter = 0; iter < NBins; iter++) {
      delete mNumSideP[iter];
      delete mDenSideP[iter];
      delete mNumSideN[iter];
      delete mDenSideN[iter];
   }
   delete[] mNumSideN;
   delete[] mNumSideP;
   delete[] mDenSideN;
   delete[] mDenSideP;

   delete mNumLongPSum;
   delete mDenLongPSum;
   delete mNumLongNSum;
   delete mDenLongNSum;

   for (int iter = 0; iter < NBins; iter++) {
      delete mNumLongP[iter];
      delete mDenLongP[iter];
      delete mNumLongN[iter];
      delete mDenLongN[iter];
   }
   delete[] mNumLongN;
   delete[] mNumLongP;
   delete[] mDenLongN;
   delete[] mDenLongP;

   delete mHOutKSame;
   delete mHOutKDiff;
   delete mHSideKSame;
   delete mHSideKDiff;
   delete mHLongKSame;
   delete mHLongKDiff;

   delete mHKStarRap1OutNum;
   delete mHKStarRap2OutNum;

   delete mHKStarRap1OutDen;
   delete mHKStarRap2OutDen;

   delete mHKStarPhi1OutNum;
   delete mHKStarPhi2OutNum;

   delete mHKStarPhi1OutDen;
   delete mHKStarPhi2OutDen;

   delete mHPt1KStarOutNum;
   delete mHPt1KStarOutDen;
   delete mHPt2KStarOutNum;
   delete mHPt2KStarOutDen;

   delete mHPt1KStarSideNum;
   delete mHPt1KStarSideDen;
   delete mHPt2KStarSideNum;
   delete mHPt2KStarSideDen;
}
//_________________________
void NonId3DCorrFctnMB::Finish() { return; }

void NonId3DCorrFctnMB::Write() {
   mNumOutPSum->Write();
   mDenOutPSum->Write();
   mNumOutNSum->Write();
   mDenOutNSum->Write();

   for (int iter = 0; iter < NBins; iter++) {
      mNumOutP[iter]->Write();
      mDenOutP[iter]->Write();
      mNumOutN[iter]->Write();
      mDenOutN[iter]->Write();
   }

   mNumSidePSum->Write();
   mDenSidePSum->Write();
   mNumSideNSum->Write();
   mDenSideNSum->Write();

   for (int iter = 0; iter < NBins; iter++) {
      mNumSideP[iter]->Write();
      mDenSideP[iter]->Write();
      mNumSideN[iter]->Write();
      mDenSideN[iter]->Write();
   }

   mNumLongPSum->Write();
   mDenLongPSum->Write();
   mNumLongNSum->Write();
   mDenLongNSum->Write();

   for (int iter = 0; iter < NBins; iter++) {
      mNumLongP[iter]->Write();
      mDenLongP[iter]->Write();
      mNumLongN[iter]->Write();
      mDenLongN[iter]->Write();
   }

   mHOutKSame->Write();
   mHOutKDiff->Write();
   mHSideKSame->Write();
   mHSideKDiff->Write();
   mHLongKSame->Write();
   mHLongKDiff->Write();

   mHPt1KStarOutNum->Write();
   mHPt1KStarOutDen->Write();
   mHPt2KStarOutNum->Write();
   mHPt2KStarOutDen->Write();

   mHPt1KStarSideNum->Write();
   mHPt1KStarSideDen->Write();
   mHPt2KStarSideNum->Write();
   mHPt2KStarSideDen->Write();

   mHKStarRap1OutNum->Write();
   mHKStarRap2OutNum->Write();

   mHKStarRap1OutDen->Write();
   mHKStarRap2OutDen->Write();

   mHKStarPhi1OutNum->Write();
   mHKStarPhi2OutNum->Write();

   mHKStarPhi1OutDen->Write();
   mHKStarPhi2OutDen->Write();
}

//____________________________
StHbtString NonId3DCorrFctnMB::Report() {
   string stemp = "Non-Identical 3D Correlation Function Report:\n";
   char ctemp[1000];
   sprintf(ctemp, "Number of entries in out numerator:\t%E\n", mHOutKSame->GetEntries());
   stemp += ctemp;
   sprintf(ctemp, "Number of entries in out denominator:\t%E\n", mHOutKDiff->GetEntries());
   stemp += ctemp;
   sprintf(ctemp, "Number of entries in side numerator:\t%E\n", mHSideKSame->GetEntries());
   stemp += ctemp;
   sprintf(ctemp, "Number of entries in side denominator:\t%E\n", mHSideKDiff->GetEntries());
   stemp += ctemp;
   sprintf(ctemp, "Number of entries in long numerator:\t%E\n", mHLongKSame->GetEntries());
   stemp += ctemp;
   sprintf(ctemp, "Number of entries in long denominator:\t%E\n", mHLongKDiff->GetEntries());
   stemp += ctemp;
   StHbtString returnThis = stemp;
   return returnThis;
}
//____________________________
void NonId3DCorrFctnMB::AddRealPair(const StHbtPair* pair) {
   double tKStar = fabs(pair->KStar());
   double tKOut = pair->dKOut();
   double tKSide = pair->dKSide();
   double tKLong = pair->dKLong();

   if (mKCompCut <= 0.0) {
      if ((!mqSideSel) || (mqSideSel * tKSide > 0)) {
         if (tKOut > 0.) {
            mNumOutP[0]->Fill(tKStar);
         } else {
            mNumOutN[0]->Fill(tKStar);
         }
         if (tKSide > 0.) {
            mNumSideP[0]->Fill(tKStar);
         } else {
            mNumSideN[0]->Fill(tKStar);
         }
         if (tKLong > 0.) {
            mNumLongP[0]->Fill(tKStar);
         } else {
            mNumLongN[0]->Fill(tKStar);
         }
      }
   } else {
      if ((fabs(tKLong) < mKCompCut) && (fabs(tKSide) < mKCompCut)) {
         if (tKOut > 0.) {
            mNumOutP[0]->Fill(tKStar);
         } else {
            mNumOutN[0]->Fill(tKStar);
         }
      }
      if ((fabs(tKOut) < mKCompCut) && (fabs(tKLong) < mKCompCut)) {
         if (tKSide > 0.) {
            mNumSideP[0]->Fill(tKStar);
         } else {
            mNumSideN[0]->Fill(tKStar);
         }
      }
      if ((fabs(tKOut) < mKCompCut) && (fabs(tKSide) < mKCompCut)) {
         if (tKLong > 0.) {
            mNumLongP[0]->Fill(tKStar);
         } else {
            mNumLongN[0]->Fill(tKStar);
         }
      }
   }
   mHOutKSame->Fill(tKOut, tKStar, 1.);
   mHSideKSame->Fill(tKSide, tKStar, 1.);
   mHLongKSame->Fill(tKLong, tKStar, 1.);

   mHPt1KStarOutNum->Fill(pair->track1()->FourMomentum().perp(), tKStar * ((tKOut > 0) * 2 - 1), 1.0);
   mHPt2KStarOutNum->Fill(pair->track2()->FourMomentum().perp(), tKStar * ((tKOut > 0) * 2 - 1), 1.0);

   mHPt1KStarSideNum->Fill(pair->track1()->FourMomentum().perp(), tKStar * ((tKSide > 0) * 2 - 1), 1.0);
   mHPt2KStarSideNum->Fill(pair->track2()->FourMomentum().perp(), tKStar * ((tKSide > 0) * 2 - 1), 1.0);

   int mSignKOut = tKOut > 0 ? 1 : -1;
   mHKStarRap1OutNum->Fill(tKStar * mSignKOut, pair->track1()->FourMomentum().rapidity());
   mHKStarRap2OutNum->Fill(tKStar * mSignKOut, pair->track2()->FourMomentum().rapidity());
   mHKStarPhi1OutNum->Fill(tKStar * mSignKOut,
                           TMath::ATan2(pair->track1()->FourMomentum().y(), pair->track1()->FourMomentum().x()));
   mHKStarPhi2OutNum->Fill(tKStar * mSignKOut,
                           TMath::ATan2(pair->track2()->FourMomentum().y(), pair->track2()->FourMomentum().x()));
   //   mHQSideExitNum->Fill(tKSide,exitsep,1.0);
   //   mHQOutExitNum->Fill(tKOut,exitsep,1.0);
}
//____________________________
void NonId3DCorrFctnMB::AddMixedPair(const StHbtPair* pair) {
   double tKStar = fabs(pair->KStar());
   double tKOut = pair->dKOut();
   double tKSide = pair->dKSide();
   double tKLong = pair->dKLong();
   //  double exitsep = pair->NominalTpcExitSeparation();

   if (mKCompCut <= 0.0) {
      if ((!mqSideSel) || (mqSideSel * tKSide > 0)) {
         if (tKOut > 0.) {
            mDenOutP[0]->Fill(tKStar);
         } else {
            mDenOutN[0]->Fill(tKStar);
         }
         if (tKSide > 0.) {
            mDenSideP[0]->Fill(tKStar);
         } else {
            mDenSideN[0]->Fill(tKStar);
         }
         if (tKLong > 0.) {
            mDenLongP[0]->Fill(tKStar);
         } else {
            mDenLongN[0]->Fill(tKStar);
         }
      }
   } else {
      if ((fabs(tKLong) < mKCompCut) && (fabs(tKSide) < mKCompCut)) {
         if (tKOut > 0.) {
            mDenOutP[0]->Fill(tKStar);
         } else {
            mDenOutN[0]->Fill(tKStar);
         }
      }
      if ((fabs(tKOut) < mKCompCut) && (fabs(tKLong) < mKCompCut)) {
         if (tKSide > 0.) {
            mDenSideP[0]->Fill(tKStar);
         } else {
            mDenSideN[0]->Fill(tKStar);
         }
      }
      if ((fabs(tKOut) < mKCompCut) && (fabs(tKSide) < mKCompCut)) {
         if (tKLong > 0.) {
            mDenLongP[0]->Fill(tKStar);
         } else {
            mDenLongN[0]->Fill(tKStar);
         }
      }
   }

   mHOutKDiff->Fill(tKOut, tKStar, 1.);
   mHSideKDiff->Fill(tKSide, tKStar, 1.);
   mHLongKDiff->Fill(tKLong, tKStar, 1.);

   int mSignKOut = tKOut > 0 ? 1 : -1;
   mHKStarRap1OutDen->Fill(tKStar * mSignKOut, pair->track1()->FourMomentum().rapidity());
   mHKStarRap2OutDen->Fill(tKStar * mSignKOut, pair->track2()->FourMomentum().rapidity());
   mHKStarPhi1OutDen->Fill(tKStar * mSignKOut,
                           TMath::ATan2(pair->track1()->FourMomentum().y(), pair->track1()->FourMomentum().x()));
   mHKStarPhi2OutDen->Fill(tKStar * mSignKOut,
                           TMath::ATan2(pair->track2()->FourMomentum().y(), pair->track2()->FourMomentum().x()));

   //   mHQSideExitDen->Fill(tKSide,exitsep,1.0);
   //   mHQOutExitDen->Fill(tKOut,exitsep,1.0);
   mHPt1KStarOutDen->Fill(pair->track1()->FourMomentum().perp(), tKStar * ((tKOut > 0) * 2 - 1), 1.0);
   mHPt2KStarOutDen->Fill(pair->track2()->FourMomentum().perp(), tKStar * ((tKOut > 0) * 2 - 1), 1.0);

   mHPt1KStarSideDen->Fill(pair->track1()->FourMomentum().perp(), tKStar * ((tKSide > 0) * 2 - 1), 1.0);
   mHPt2KStarSideDen->Fill(pair->track2()->FourMomentum().perp(), tKStar * ((tKSide > 0) * 2 - 1), 1.0);
}

//____________________________
void NonId3DCorrFctnMB::AddRealPairMB(const StHbtPair* pair, int nbin) {
   double tKStar = fabs(pair->KStar());
   double tKOut = pair->dKOut();
   double tKSide = pair->dKSide();
   double tKLong = pair->dKLong();

   if (nbin > NBins) {
      cout << "Real NBin " << nbin << " larger than number of bins! " << NBins << endl;
      return;
   }

   if (mKCompCut <= 0.0) {
      if ((!mqSideSel) || (mqSideSel * tKSide > 0)) {
         if (tKOut > 0.) {
            mNumOutP[nbin]->Fill(tKStar);
         } else {
            mNumOutN[nbin]->Fill(tKStar);
         }
         if (tKSide > 0.) {
            mNumSideP[nbin]->Fill(tKStar);
         } else {
            mNumSideN[nbin]->Fill(tKStar);
         }
         if (tKLong > 0.) {
            mNumLongP[nbin]->Fill(tKStar);
         } else {
            mNumLongN[nbin]->Fill(tKStar);
         }
      }
   } else {
      if ((fabs(tKLong) < mKCompCut) && (fabs(tKSide) < mKCompCut)) {
         if (tKOut > 0.) {
            mNumOutP[nbin]->Fill(tKStar);
         } else {
            mNumOutN[nbin]->Fill(tKStar);
         }
      }
      if ((fabs(tKOut) < mKCompCut) && (fabs(tKLong) < mKCompCut)) {
         if (tKSide > 0.) {
            mNumSideP[nbin]->Fill(tKStar);
         } else {
            mNumSideN[nbin]->Fill(tKStar);
         }
      }
      if ((fabs(tKOut) < mKCompCut) && (fabs(tKSide) < mKCompCut)) {
         if (tKLong > 0.) {
            mNumLongP[nbin]->Fill(tKStar);
         } else {
            mNumLongN[nbin]->Fill(tKStar);
         }
      }
   }
   mHOutKSame->Fill(tKOut, tKStar, 1.);
   mHSideKSame->Fill(tKSide, tKStar, 1.);
   mHLongKSame->Fill(tKLong, tKStar, 1.);

   mHPt1KStarOutNum->Fill(pair->track1()->FourMomentum().perp(), tKStar * ((tKOut > 0) * 2 - 1), 1.0);
   mHPt2KStarOutNum->Fill(pair->track2()->FourMomentum().perp(), tKStar * ((tKOut > 0) * 2 - 1), 1.0);

   mHPt1KStarSideNum->Fill(pair->track1()->FourMomentum().perp(), tKStar * ((tKSide > 0) * 2 - 1), 1.0);
   mHPt2KStarSideNum->Fill(pair->track2()->FourMomentum().perp(), tKStar * ((tKSide > 0) * 2 - 1), 1.0);

   int mSignKOut = tKOut > 0 ? 1 : -1;
   mHKStarRap1OutNum->Fill(tKStar * mSignKOut, pair->track1()->FourMomentum().rapidity());
   mHKStarRap2OutNum->Fill(tKStar * mSignKOut, pair->track2()->FourMomentum().rapidity());
   mHKStarPhi1OutNum->Fill(tKStar * mSignKOut,
                           TMath::ATan2(pair->track1()->FourMomentum().y(), pair->track1()->FourMomentum().x()));
   mHKStarPhi2OutNum->Fill(tKStar * mSignKOut,
                           TMath::ATan2(pair->track2()->FourMomentum().y(), pair->track2()->FourMomentum().x()));
}
//____________________________
void NonId3DCorrFctnMB::AddMixedPairMB(const StHbtPair* pair, int nbin) {
   double tKStar = fabs(pair->KStar());
   double tKOut = pair->dKOut();
   double tKSide = pair->dKSide();
   double tKLong = pair->dKLong();

   if (nbin > NBins) {
      cout << "Mixed NBin " << nbin << " larger than number of bins! " << NBins << endl;
      return;
   }

   if (mKCompCut <= 0.0) {
      if ((!mqSideSel) || (mqSideSel * tKSide > 0)) {
         if (tKOut > 0.) {
            mDenOutP[nbin]->Fill(tKStar);
         } else {
            mDenOutN[nbin]->Fill(tKStar);
         }
         if (tKSide > 0.) {
            mDenSideP[nbin]->Fill(tKStar);
         } else {
            mDenSideN[nbin]->Fill(tKStar);
         }
         if (tKLong > 0.) {
            mDenLongP[nbin]->Fill(tKStar);
         } else {
            mDenLongN[nbin]->Fill(tKStar);
         }
      }
   } else {
      if ((fabs(tKLong) < mKCompCut) && (fabs(tKSide) < mKCompCut)) {
         if (tKOut > 0.) {
            mDenOutP[nbin]->Fill(tKStar);
         } else {
            mDenOutN[nbin]->Fill(tKStar);
         }
      }
      if ((fabs(tKOut) < mKCompCut) && (fabs(tKLong) < mKCompCut)) {
         if (tKSide > 0.) {
            mDenSideP[nbin]->Fill(tKStar);
         } else {
            mDenSideN[nbin]->Fill(tKStar);
         }
      }
      if ((fabs(tKOut) < mKCompCut) && (fabs(tKSide) < mKCompCut)) {
         if (tKLong > 0.) {
            mDenLongP[nbin]->Fill(tKStar);
         } else {
            mDenLongN[nbin]->Fill(tKStar);
         }
      }
   }

   mHOutKDiff->Fill(tKOut, tKStar, 1.);
   mHSideKDiff->Fill(tKSide, tKStar, 1.);
   mHLongKDiff->Fill(tKLong, tKStar, 1.);

   int mSignKOut = tKOut > 0 ? 1 : -1;
   mHKStarRap1OutDen->Fill(tKStar * mSignKOut, pair->track1()->FourMomentum().rapidity());
   mHKStarRap2OutDen->Fill(tKStar * mSignKOut, pair->track2()->FourMomentum().rapidity());
   mHKStarPhi1OutDen->Fill(tKStar * mSignKOut,
                           TMath::ATan2(pair->track1()->FourMomentum().y(), pair->track1()->FourMomentum().x()));
   mHKStarPhi2OutDen->Fill(tKStar * mSignKOut,
                           TMath::ATan2(pair->track2()->FourMomentum().y(), pair->track2()->FourMomentum().x()));

   //   mHQSideExitDen->Fill(tKSide,exitsep,1.0);
   //   mHQOutExitDen->Fill(tKOut,exitsep,1.0);
   mHPt1KStarOutDen->Fill(pair->track1()->FourMomentum().perp(), tKStar * ((tKOut > 0) * 2 - 1), 1.0);
   mHPt2KStarOutDen->Fill(pair->track2()->FourMomentum().perp(), tKStar * ((tKOut > 0) * 2 - 1), 1.0);

   mHPt1KStarSideDen->Fill(pair->track1()->FourMomentum().perp(), tKStar * ((tKSide > 0) * 2 - 1), 1.0);
   mHPt2KStarSideDen->Fill(pair->track2()->FourMomentum().perp(), tKStar * ((tKSide > 0) * 2 - 1), 1.0);
}
