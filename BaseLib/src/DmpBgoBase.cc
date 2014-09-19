/*
 *  $Id: DmpBgoBase.cc, 2014-08-20 19:39:25 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 20/08/2014
*/

#include "DmpBgoBase.h"

//-------------------------------------------------------------------
short DmpBgoBase::ConstructGlobalBarID(const short &l,const short &b){
  short i = 0;
  i = (l<<11) + (b<<6);
  return i;
}

//-------------------------------------------------------------------
short DmpBgoBase::ConstructGlobalPMTID(const short &l,const short &b,const short &s){
  short i = 0;
  i = (l<<11) + (b<<6) + (s<<4);
  return i;
}

//-------------------------------------------------------------------
short DmpBgoBase::ConstructGlobalDynodeID(const short &l,const short &b,const short &s,const short &d){
  short i = 0;
  i = (l<<11) + (b<<6) + (s<<4) + d;
  return i;
}

//-------------------------------------------------------------------
short DmpBgoBase::GetLayerID(const short &gid){
  return ((gid>>11) &0x000f);
}

//-------------------------------------------------------------------
short DmpBgoBase::GetBarID(const short &gid){
  return ((gid>>6) &0x001f);
}

//-------------------------------------------------------------------
short DmpBgoBase::GetSideID(const short &gid){
  return ((gid>>4) &0x0001);
}

//-------------------------------------------------------------------
short DmpBgoBase::GetDynodeID(const short &gid){
  return (gid&0x000f);
}

//-------------------------------------------------------------------
void DmpBgoBase::LoadLBSDID(const short &gid,short &l,short &b,short &s,short &d){
  l = DmpBgoBase::GetLayerID(gid);
  b = DmpBgoBase::GetBarID(gid);
  s = DmpBgoBase::GetSideID(gid);
  d = DmpBgoBase::GetDynodeID(gid);
}

