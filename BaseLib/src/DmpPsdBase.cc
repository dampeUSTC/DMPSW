/*
 *  $Id: DmpPsdBase.cc, 2014-08-20 20:58:43 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 20/08/2014
*/

#include "DmpPsdBase.h"

//-------------------------------------------------------------------
short DmpPsdBase::ConstructGlobalStripID(const short &l,const short &s){
  short i = 0;
  i = (l<<12) + (s<<6);
  return i;
}

//-------------------------------------------------------------------
short DmpPsdBase::ConstructGlobalPMTID(const short &l,const short &b,const short &s){
  short i = 0;
  i = (l<<12) + (b<<6) + (s<<4);
  return i;
}

//-------------------------------------------------------------------
short DmpPsdBase::ConstructGlobalDynodeID(const short &l,const short &b,const short &s,const short &d){
  short i = 0;
  i = (l<<12) + (b<<6) + (s<<4) + d;
  return i;
}

//-------------------------------------------------------------------
short DmpPsdBase::GetLayerID(const short &gid){
  return ((gid>>12) &0x0007);
}

//-------------------------------------------------------------------
short DmpPsdBase::GetStripID(const short &gid){
  return ((gid>>6) &0x003f);
}

//-------------------------------------------------------------------
short DmpPsdBase::GetSideID(const short &gid){
  return ((gid>>4) &0x0001);
}

//-------------------------------------------------------------------
short DmpPsdBase::GetDynodeID(const short &gid){
  return (gid&0x000f);
}

//-------------------------------------------------------------------
void DmpPsdBase::LoadLBSDID(const short &gid,short &l,short &b,short &s,short &d){
  l = DmpPsdBase::GetLayerID(gid);
  b = DmpPsdBase::GetStripID(gid);
  s = DmpPsdBase::GetSideID(gid);
  d = DmpPsdBase::GetDynodeID(gid);
}

//-------------------------------------------------------------------
DmpParameterPsd_c* DmpPsdBase::Parameter(){
  return DmpParameterPsd_c::GetInstance();
}
