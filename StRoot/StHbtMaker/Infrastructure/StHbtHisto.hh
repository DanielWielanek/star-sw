#ifndef StHbtHisto
#define StHbtHisto

#ifdef __ROOT__

#ifndef ROOT_TH1
#include "TF1.h"
#include "TH1.h"
#endif

#ifndef ROOT_TH2
#include "TF2.h"
#include "TH2.h"
#endif

#ifndef ROOT_TH3
#include "TF3.h"
#include "TH3.h"
#endif

#include "StHbtMaker/Infrastructure/CTH.hh"
#include "TF1.h"
#include "TF2.h"
#include "TF3.h"

typedef TH1D StHbt1DHisto;
typedef TH2D StHbt2DHisto;
typedef TH3D StHbt3DHisto;

typedef TH1I StHbt1IHisto;
typedef TH2I StHbt2IHisto;
typedef TH3I StHbt3IHisto;

typedef TH1F StHbt1FHisto;
typedef TH2F StHbt2FHisto;
typedef TH3F StHbt3FHisto;

typedef TF1 StHbtTF1;
typedef TF2 StHbtTF2;
typedef TF3 StHbtTF3;

#else  // __ROOT__

#include "StHbtMaker/Infrastructure/franks1HistoD.hh"
#include "StHbtMaker/Infrastructure/franks2HistoD.hh"
typedef franks1HistoD StHbt1DHisto;
typedef franks2HistoD StHbt2DHisto;

#endif  // __ROOT__

#endif
