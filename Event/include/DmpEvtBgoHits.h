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
  //void  AddG4Hit(const short &id,const double &e,const double &x,const double &y,const double &z);     // this is for simulation
  void Reset();
  void LoadFrom(const DmpEvtBgoHits &r);
  void LoadFrom(const DmpEvtBgoHits *r);
  short GetHittedBarNumber()const{return fGlobalBarID.size();}

public:
  std::vector <short>     fGlobalBarID;     // unique sensitive detector bar ID, using DmpBgoBase to construct it
  std::vector <double>    fEnergy;          // unit MeV
  std::vector <double>    fES0;             // unit MeV, from side 0
  std::vector <double>    fES1;             // unit MeV, from side 1
  std::vector <TVector3>  fPosition;        // unit mm, position x,y,z

  ClassDef(DmpEvtBgoHits,1)
};

#endif

