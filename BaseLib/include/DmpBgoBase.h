/*
 *  $Id: DmpBgoBase.h, 2014-08-20 19:39:09 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 20/08/2014
*/

#ifndef DmpBgoBase_H
#define DmpBgoBase_H

#include "DmpParameterBgo.h"

namespace DmpBgoBase{
  /*
   *    gid for bgo signal: short: bit 15~0
   *
   *    layer(0~13):    bits 14,13,12,11
   *        = (fGlobalID >> 11) & 0x000f
   *    bar(0~23):      bits 10,9,8,7,6
   *         = (fGlobalID >> 6) & 0x001f
   *    side(0,1):      bits 4
   *        = (fGlobal >> 4) & 0x0001
   *    dynode(2,5,8):  bits 3,2,1,0
   *        = fGlobal & 0x000f
   */
  short ConstructGlobalBarID(const short &l,const short &b);
  short ConstructGlobalPMTID(const short &l,const short &b,const short &s);
  short ConstructGlobalDynodeID(const short &l,const short &b,const short &s,const short &d);
  short GetLayerID(const short &gid);
  short GetBarID(const short &gid);
  short GetSideID(const short &gid);
  short GetDynodeID(const short &gid);
  void  LoadLBSDID(const short &gid,short &l,short &b,short &s,short &d);
  DmpParameterBgo_c*  Parameter();
}

#endif

