/***************************************************************************
 *
 * $Id: ptslopeEventCutMonitor.cxx,v 1.3 2003/01/22 16:05:11 mercedes Exp $
 *
 * Author: Mercedes Lopez Noriega , Ohio State, mercedes@pacific.mps.ohio-state.edu
 *
 ***************************************************************************
 *
 * Event Cut Monitor that plots just the tracks that passed
 * mercedesStarStandardEventCut in the multiplicity plot
 * Plots: EventMultiplicity (just # of tracks that passed the event cut),
 * ZVertexPosition, and 2D plot: EventMultiplicity vs Tracks (# of tracks that
 * passed the cuts vs # of tracks in the event)
 *
 ***************************************************************************
 *
 * $Log: ptslopeEventCutMonitor.cxx,v $
 * Revision 1.3  2003/01/22 16:05:11  mercedes
 * Minor changes
 *
 * Revision 1.2  2003/01/17 16:47:31  mercedes
 * Updated to get reference multiplicity
 *
 * Revision 1.1  2002/04/09 15:14:46  mercedes
 * Event Cut Monitor for mercedesStarStandardEventCut
 *
 *
 **************************************************************************/

#include "StHbtMaker/Cut/Event/ptslopeEventCutMonitor.h"

#include <cstdio>

#include "StHbtMaker/Infrastructure/StHbtEvent.hh"
#include "StHbtMaker/Infrastructure/StHbtTrack.hh"
#include "StHbtMaker/Infrastructure/StHbtTypes.hh"

#ifdef __ROOT__
ClassImp(ptslopeEventCutMonitor)
#endif

    ptslopeEventCutMonitor::ptslopeEventCutMonitor(int pid1, int pid2, char* suff) {
   double ptr1min, ptr1max, ptr2min, ptr2max;
   TString ssuff(suff);

   switch (pid1) {
      case 0:
         mass1 = 0.13957;
         probpi1 = 0.6;
         probk1 = -0.1;
         probp1 = -0.1;
         probe1 = -0.5;
         ptmin1 = 0.13;
         ptmax1 = 0.6;
         ptr1min = 0.25;
         ptr1max = 0.4;
         break;
      case 1:
         mass1 = 0.493677;
         probpi1 = -0.1;
         probk1 = 0.6;
         probp1 = -0.1;
         probe1 = -0.5;
         ptmin1 = 0.3;
         ptmax1 = 0.9;
         ptr1min = 0.35;
         ptr1max = 0.65;
         break;
      case 2:
         mass1 = 0.938272;
         probpi1 = -0.1;
         probk1 = -0.1;
         probp1 = 0.6;
         probe1 = -0.5;
         ptmin1 = 0.3;
         ptmax1 = 1.2;
         ptr1min = 0.55;
         ptr1max = 0.9;
         break;
      default:
         cout << "ptslopeEventCutMonitor::ptslopeEventCutMonitor: Unknown pid: " << pid1 << " Assuming 0 mass" << endl;
         mass1 = 0.0;
         probpi1 = 0.6;
         probk1 = -0.1;
         probp1 = -0.1;
         probe1 = -0.5;
         ptmin1 = 0.13;
         ptmax1 = 0.6;
         ptr1min = 0.25;
         ptr1max = 0.4;
   }

   switch (pid2) {
      case 0:
         mass2 = 0.13957;
         probpi2 = 0.6;
         probk2 = -0.1;
         probp2 = -0.1;
         probe2 = -0.5;
         ptmin2 = 0.13;
         ptmax2 = 0.6;
         ptr2min = 0.25;
         ptr2max = 0.4;
         break;
      case 1:
         mass2 = 0.493677;
         probpi2 = -0.1;
         probk2 = 0.6;
         probp2 = -0.1;
         probe2 = -0.5;
         ptmin2 = 0.3;
         ptmax2 = 0.9;
         ptr2min = 0.35;
         ptr2max = 0.65;
         break;
      case 2:
         mass2 = 0.938272;
         probpi2 = -0.1;
         probk2 = -0.1;
         probp2 = 0.6;
         probe2 = -0.5;
         ptmin2 = 0.3;
         ptmax2 = 1.2;
         ptr2min = 0.55;
         ptr2max = 0.9;
         break;
      default:
         cout << "ptslopeEventCutMonitor::ptslopeEventCutMonitor: Unknown pid: " << pid2 << " Assuming 0 mass" << endl;
         mass2 = 0.0;
         probpi2 = 0.6;
         probk2 = -0.1;
         probp2 = -0.1;
         probe2 = -0.5;
         ptmin2 = 0.13;
         ptmax2 = 0.6;
         ptr2min = 0.25;
         ptr2max = 0.4;
   }
   mtmin1 = hypot(ptmin1, mass1);
   mtmin2 = hypot(ptmin2, mass2);
   mtmax1 = hypot(ptmax1, mass1);
   mtmax2 = hypot(ptmax2, mass2);

   mMtSlope1 = new StHbt1IHisto((ssuff + "MtSlope1").Data(), "Mt Slope Particle 1", 200, 0., 1.5);
   mMtSlope2 = new StHbt1IHisto((ssuff + "MtSlope2").Data(), "Mt Slope Particle 2", 200, 0., 1.5);
   mMeanPt1 = new StHbt1IHisto((ssuff + "MeanPt1").Data(), "Mean Pt Particle 1", 200, ptr1min, ptr1max);
   mMeanPt2 = new StHbt1IHisto((ssuff + "MeanPt2").Data(), "Mean Pt Particle 2", 200, ptr2min, ptr2max);

   mMtvsPt1 = new StHbt2IHisto((ssuff + "MtSlopevsMeanPt1").Data(), "Mt Slope vs. Mean Pt Particle 1", 200, 0., 1.5,
                               200, ptr1min, ptr1max);
   mMtvsPt2 = new StHbt2IHisto((ssuff + "MtSlopevsMeanPt2").Data(), "Mt Slope vs. Mean Pt Particle 2", 200, 0., 1.5,
                               200, ptr2min, ptr2max);
   mMt1vsMt2 =
       new StHbt2IHisto((ssuff + "MtSlope1MtSlope2").Data(), "Mt Slope 1 vs. Mt Slope 2", 200, 0., 1.5, 200, 0.0, 1.5);
   mPt1vsPt2 = new StHbt2IHisto((ssuff + "MeanPt1MeanPt2").Data(), "Mean Pt 1 vs. Mean Pt 2", 200, ptr1min, ptr1max,
                                200, ptr2min, ptr2max);

   mMultvsMt1 = new StHbt2IHisto((ssuff + "MultMt1").Data(), "Mt Slope Particle 1 vs Event Multiplicity", 100, 100.,
                                 800., 200, 0., 1.5);
   mMultvsMt2 = new StHbt2IHisto((ssuff + "MultMt2").Data(), "Mt Slope Particle 2 vs Event Multiplicity", 100, 100.,
                                 800., 200, 0., 1.5);
   mMultvsPt1 = new StHbt2IHisto((ssuff + "MultPt1").Data(), "Mean Pt Particle 1 vs Event Multiplicity", 100, 100.,
                                 800., 200, ptr1min, ptr1max);
   mMultvsPt2 = new StHbt2IHisto((ssuff + "MultPt2").Data(), "Mean Pt Particle 2 vs Event Multiplicity", 100, 100.,
                                 800., 200, ptr2min, ptr2max);

   mMtDist1 = new StHbt1IHisto((ssuff + "MtDist1").Data(), "Mt Distribution 1", 200, 0., 2.0);
   mMtDist2 = new StHbt1IHisto((ssuff + "MtDist2").Data(), "Mt Distribution 2", 200, 0., 2.0);

   mOverallMeanPt = new StHbt1IHisto((ssuff + "OverallMeanPt").Data(), "Overall Mean Pt", 200, 0., 1.0);
   ;

   mMtSlope1->SetDirectory(0);
   mMtSlope2->SetDirectory(0);
   mMeanPt1->SetDirectory(0);
   mMeanPt2->SetDirectory(0);

   mMtvsPt1->SetDirectory(0);
   mMtvsPt2->SetDirectory(0);
   mMt1vsMt2->SetDirectory(0);
   mPt1vsPt2->SetDirectory(0);

   mMtDist1->SetDirectory(0);
   mMtDist2->SetDirectory(0);

   mOverallMeanPt->SetDirectory(0);

   mMtFun = new TF1("mtfun", "[0]*exp(-x/[1])", 0.0, 2.0);
   mMtFun->SetParameter(0, 100.0);
   mMtFun->SetParameter(1, 0.5);
}

ptslopeEventCutMonitor::ptslopeEventCutMonitor() {
   ptslopeEventCutMonitor(0, 0, "");  // ptslopeEventCutMonitor::ptslopeEventCutMonitor(0,0,"");
}

//------------------------------
ptslopeEventCutMonitor::~ptslopeEventCutMonitor() {
   delete mMtSlope1;
   delete mMtSlope2;
   delete mMeanPt1;
   delete mMeanPt2;

   delete mMtvsPt1;
   delete mMtvsPt2;
   delete mMt1vsMt2;
   delete mPt1vsPt2;

   delete mMultvsPt1;
   delete mMultvsPt2;
   delete mMultvsMt1;
   delete mMultvsMt2;

   delete mOverallMeanPt;

   delete mMtDist1;
   delete mMtDist2;
   delete mMtFun;
}

//------------------------------
void ptslopeEventCutMonitor::Fill(const StHbtEvent* event) {
   int is1, is2;
   double mt;
   int p1count, p2count, overcount;
   double pt1sum, pt2sum;
   double mts1, mts2, mpt1, mpt2;
   double moverpt = 0;

   StHbtTrack* pParticle;
   StHbtTrackIterator pIter;
   StHbtTrackIterator startLoop = event->TrackCollection()->begin();
   StHbtTrackIterator endLoop = event->TrackCollection()->end();

   mMtDist1->Reset("ICE");
   mMtDist2->Reset("ICE");
   p1count = p2count = overcount = 0;
   pt1sum = pt2sum = moverpt = 0.0;

   for (pIter = startLoop; pIter != endLoop; pIter++) {
      pParticle = *pIter;
      is1 = is2 = 0;

      if ((pParticle->NHits() > 10.0) && (pParticle->DCAxyGlobal() < 3.0)) {
         if (probpi1 > 0) {
            if ((pParticle->PidProbPion() > probp1) && (pParticle->PidProbKaon() < -probk1) &&
                (pParticle->PidProbProton() < -probp1) && (pParticle->PidProbElectron() < -probe1))
               is1 = 1;
         } else if (probk1 > 0) {
            if ((pParticle->PidProbPion() < -probp1) && (pParticle->PidProbKaon() > probk1) &&
                (pParticle->PidProbProton() < -probp1) && (pParticle->PidProbElectron() < -probe1))
               is1 = 1;
         } else if (probp1 > 0) {
            if ((pParticle->PidProbPion() < -probp1) && (pParticle->PidProbKaon() < -probk1) &&
                (pParticle->PidProbProton() > probp1) && (pParticle->PidProbElectron() < -probe1))
               is1 = 1;
         }
         if (!is1) {
            if (probpi2 > 0) {
               if ((pParticle->PidProbPion() > probp2) && (pParticle->PidProbKaon() < -probk2) &&
                   (pParticle->PidProbProton() < -probp2) && (pParticle->PidProbElectron() < -probe2))
                  is2 = 1;
            } else if (probk2 > 0) {
               if ((pParticle->PidProbPion() < -probp2) && (pParticle->PidProbKaon() > probk2) &&
                   (pParticle->PidProbProton() < -probp2) && (pParticle->PidProbElectron() < -probe2))
                  is2 = 1;
            } else if (probp2 > 0) {
               if ((pParticle->PidProbPion() < -probp2) && (pParticle->PidProbKaon() < -probk2) &&
                   (pParticle->PidProbProton() > probp2) && (pParticle->PidProbElectron() < -probe2))
                  is2 = 1;
            }
         }
         if ((is1) && (pParticle->Pt() > ptmin1) && (pParticle->Pt() < ptmax1)) {
            mt = hypot(pParticle->Pt(), mass1);
            mMtDist1->Fill(mt, 1.0 / mt);
            pt1sum += pParticle->Pt();
            p1count++;
         }
         if ((is2) && (pParticle->Pt() > ptmin2) && (pParticle->Pt() < ptmax2)) {
            mt = hypot(pParticle->Pt(), mass2);
            mMtDist2->Fill(mt, 1.0 / mt);
            pt2sum += pParticle->Pt();
            p2count++;
         }
         moverpt += pParticle->Pt();
         overcount++;
      }
   }

   mMtDist1->Fit(mMtFun, "QN0", "", mtmin1, mtmax1);
   mts1 = mMtFun->GetParameter(1);
   mpt1 = pt1sum / p1count;

   mMtDist2->Fit(mMtFun, "QN0", "", mtmin2, mtmax2);
   mts2 = mMtFun->GetParameter(1);
   mpt2 = pt2sum / p2count;

   mMtSlope1->Fill(mts1);
   mMtSlope2->Fill(mts2);
   mMeanPt1->Fill(mpt1);
   mMeanPt2->Fill(mpt2);

   mMtvsPt1->Fill(mts1, mpt1);
   mMtvsPt2->Fill(mts2, mpt2);
   mMt1vsMt2->Fill(mts1, mts2);
   mPt1vsPt2->Fill(mpt1, mpt2);

   mMultvsMt1->Fill(event->UncorrectedNumberOfPrimaries(), mts1);
   mMultvsMt2->Fill(event->UncorrectedNumberOfPrimaries(), mts2);
   mMultvsPt1->Fill(event->UncorrectedNumberOfPrimaries(), mpt1);
   mMultvsPt2->Fill(event->UncorrectedNumberOfPrimaries(), mpt2);

   mOverallMeanPt->Fill(moverpt / overcount);
}

//------------------------------
void ptslopeEventCutMonitor::Finish() {
   cout << " entries in mPt1  histogram : " << mMtSlope1->Integral() << endl;
   cout << " entries in mPt2  histogram : " << mMtSlope2->Integral() << endl;
}

//------------------------------
StHbtString ptslopeEventCutMonitor::Report() {
   string Stemp;
   char Ctemp[100];
   sprintf(Ctemp, " ptslopeEventCutMonitor");
   Stemp = Ctemp;
   StHbtString returnThis = Stemp;
   return returnThis;
}

void ptslopeEventCutMonitor::Write() {
   mMtSlope1->Write();
   mMtSlope2->Write();
   mMeanPt1->Write();
   mMeanPt2->Write();

   mMtvsPt1->Write();
   mMtvsPt2->Write();
   mMt1vsMt2->Write();
   mPt1vsPt2->Write();

   mMultvsMt1->Write();
   mMultvsMt2->Write();
   mMultvsPt1->Write();
   mMultvsPt2->Write();

   mMtDist1->Write();
   mMtDist2->Write();

   mOverallMeanPt->Write();
}
