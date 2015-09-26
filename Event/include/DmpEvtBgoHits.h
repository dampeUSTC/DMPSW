/*
 *  $Id: DmpEvtBgoHits.h, 2014-10-06 17:08:29 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 24/19/2014
*/

#ifndef DmpEvtBgoHits_H
#define DmpEvtBgoHits_H

#include "TVector3.h"

class DmpEvtBgoHits : public TObject{
/*
 *  DmpEvtBgoHits
 *  
 *  One DmpEvtBgoHits is a response of one Event.
*/
public:
  DmpEvtBgoHits();
  ~DmpEvtBgoHits();
  DmpEvtBgoHits &operator=(const DmpEvtBgoHits &r);
  void Reset();
  void LoadFrom(DmpEvtBgoHits *r);

public:
  int GetFiredBarNumber()const;
  int GetFiredBarNumber(double eLow,double eHigh)const;
  double GetTotalE(double noise=2.5)const;
  double GetMaxE()const;
  double GetERMS()const;

public:
  std::vector <short>     fGlobalBarID;     // unique sensitive detector bar ID, using DmpBgoBase to construct it
  std::vector <double>    fEnergy;          // unit MeV
  std::vector <double>    fES0;             // unit MeV, from side 0
  std::vector <double>    fES1;             // unit MeV, from side 1
  std::vector <TVector3>  fPosition;        // unit mm, position x,y,z

  ClassDef(DmpEvtBgoHits,1)
};

#endif


