
#ifndef StHbtResultsWriter_hh
#define StHbtResultsWriter_hh

class TFile;

class ResultsWriter {
  public:
   virtual void Write(TFile *) = 0;
};

#endif
