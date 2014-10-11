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
DmpEvtBgoHits& DmpEvtBgoHits::operator=(const DmpEvtBgoHits &r){
  Reset();
  fGlobalBarID = r.fGlobalBarID;
  fEnergy = r.fEnergy;
  fES0 = r.fES0;
  fES1 = r.fES1;
  fPosition = r.fPosition;
}

//-------------------------------------------------------------------
void DmpEvtBgoHits::Reset(){
  fGlobalBarID.clear();
  fEnergy.clear();
  fES0.clear();
  fES1.clear();
  fPosition.clear();
}

//-------------------------------------------------------------------
void DmpEvtBgoHits::LoadFrom(const DmpEvtBgoHits &r){
  fGlobalBarID = r.fGlobalBarID;
  fEnergy = r.fEnergy;
  fES0 = r.fES0;
  fES1 = r.fES1;
  fPosition = r.fPosition;
}

//-------------------------------------------------------------------
void DmpEvtBgoHits::LoadFrom(const DmpEvtBgoHits *r){
  fGlobalBarID = r->fGlobalBarID;
  fEnergy = r->fEnergy;
  fES0 = r->fES0;
  fES1 = r->fES1;
  fPosition = r->fPosition;
}


