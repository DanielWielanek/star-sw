#ifndef PIOTRSTOFPIDDATAHOLDER_H
#define PIOTRSTOFPIDDATAHOLDER_H

#include <istream>

class piotrsToFPIDDataHolder {
  public:
   piotrsToFPIDDataHolder(std::istream &);
   piotrsToFPIDDataHolder();

   ~piotrsToFPIDDataHolder();
   bool getPionData(double, double &, double &);
   bool getKaonData(double, double &, double &);
   bool getProtonData(double, double &, double &);

   int getTrgId() const;
   int getSign() const;

   void printData() const;

  private:
   piotrsToFPIDDataHolder(piotrsToFPIDDataHolder &) {}

   void readData(std::istream &, double &, double &, double &, double **, double **);

   int trgId;
   int sign;
   double pionBoundaryLower;
   double pionBoundaryHigher;
   double pionStepSize;
   double *pionMassTable;
   double *pionSigmaTable;

   double kaonBoundaryLower;
   double kaonBoundaryHigher;
   double kaonStepSize;
   double *kaonMassTable;
   double *kaonSigmaTable;

   double protonBoundaryLower;
   double protonBoundaryHigher;
   double protonStepSize;
   double *protonMassTable;
   double *protonSigmaTable;
};

#endif
