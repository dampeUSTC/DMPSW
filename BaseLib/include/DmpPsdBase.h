/*
 *  $Id: DmpPsdBase.h, 2014-08-20 19:39:09 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 20/08/2014
*/

namespace DmpPsdBase{
//-------------------------------------------------------------------
  /*
   *    gid for bgo signal: short: bit 15~0
   *
   *    layer(0~1):     bits 14,13,12
   *        = (fGlobalID >> 12) & 0x0007
   *    strip(0~41):    bits 11,10,9,8,7,6
   *         = (fGlobalID >> 6) & 0x003f
   *    side(0,1):      bits 4
   *        = (fGlobal >> 4) & 0x0001
   *    dynode(5,8):  bits 3,2,1,0
   *        = fGlobal & 0x000f
   */
  short ConstructGlobalStripID(const short &l,const short &s);
  short ConstructGlobalPMTID(const short &l,const short &strip,const short &side);
  short ConstructGlobalDynodeID(const short &l,const short &strip,const short &side,const short &d);
  short GetLayerID(const short &gid);
  short GetStripID(const short &gid);
  short GetSideID(const short &gid);
  short GetDynodeID(const short &gid);

}

