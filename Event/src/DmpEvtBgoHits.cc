/*
 *  $Id: DmpEvtBgoHits.cc, 2014-10-06 17:06:59 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 16/12/2013
*/

#include "DmpEvtBgoHits.h"
#include "TMath.h"

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
void DmpEvtBgoHits::LoadFrom(DmpEvtBgoHits *r){
  Reset();
  fGlobalBarID = r->fGlobalBarID;
  fEnergy = r->fEnergy;
  fES0 = r->fES0;
  fES1 = r->fES1;
  fPosition = r->fPosition;
}

double DmpEvtBgoHits::GetTotalE(double noise)const
{
  double et = 0;
  for(size_t i=0;i<fEnergy.size();++i){
    if(fEnergy.at(i) > noise) {
      et += fEnergy.at(i);
    }
  }
  return et;
}

int DmpEvtBgoHits::GetFiredBarNumber(double eL,double eH)const
{
  int n =0;
  for(size_t i=0;i<fEnergy.size();++i){
    if(fEnergy[i] > eL && fEnergy[i] < eH){
      ++n;
    }
  }
  return n;
}


double DmpEvtBgoHits::GetMaxE()const
{
  int x = fEnergy.size();
  return x ? TMath::MaxElement(x,&fEnergy[0]) : 0;
}

int DmpEvtBgoHits::GetFiredBarNumber()const
{
  return fGlobalBarID.size();
}


double DmpEvtBgoHits::GetERMS()const
{
  return TMath::RMS(fEnergy.size(),&fEnergy[0]);
}

