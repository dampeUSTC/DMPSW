/*
 *  $Id: DmpEvtBgoHits.cc, 2014-10-06 17:06:59 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 16/12/2013
*/

#include "DmpEvtBgoHits.h"

ClassImp(DmpEvtBgoHits)

//------------------------------------------------------------------------------
DmpEvtBgoHits::DmpEvtBgoHits(){
}

//------------------------------------------------------------------------------
DmpEvtBgoHits::~DmpEvtBgoHits(){
  Reset();
}

//-------------------------------------------------------------------
void DmpEvtBgoHits::Reset(){
  fGlobalBarID.clear();
  fEnergy.clear();
  fE0.clear();
  fE1.clear();
  fPosition.clear();
}

//-------------------------------------------------------------------
void DmpEvtBgoHits::LoadFrom(const DmpEvtBgoHits &r){
  fGlobalBarID = r.fGlobalBarID;
  fEnergy = r.fEnergy;
  fE0 = r.fE0;
  fE1 = r.fE1;
  fPosition = r.fPosition;
}

//-------------------------------------------------------------------
void DmpEvtBgoHits::LoadFrom(const DmpEvtBgoHits *r){
  fGlobalBarID = r->fGlobalBarID;
  fEnergy = r->fEnergy;
  fE0 = r->fE0;
  fE1 = r->fE1;
  fPosition = r->fPosition;
}


