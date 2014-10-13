/*
 *  $Id: DmpParameterBgo.h, 2014-08-21 16:33:13 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 06/08/2013
*/

#ifndef DmpParameterBgo_H
#define DmpParameterBgo_H

#include "TVector3.h"
class TXMLEngine;

class DmpParameterBgo_c{
public:
  static DmpParameterBgo_c* GetInstance(){
    static DmpParameterBgo_c instance;
    return &instance;
  }
  ~DmpParameterBgo_c();
  short PlaneNumber()const{return fPlaneNo;}
  short BarNumber()const{return fBarNo;}
  short ReferenceBarNumber()const{return fRefBarNo;}
  short SideNumber()const{return fSideNo;}
  short DynodeNumber()const{return fDyNo;}
  short FeeNumber()const{return fFeeNo;}
  TVector3 BarCenter(const short &GlobalBarID)const;
  TVector3 LayerCenter(const short &globalLayerID)const;

private:
  DmpParameterBgo_c();
  void LoadXMLFile();     // link to XML, update vectors

private:
  TXMLEngine   *fXMLEngine;
  short         fPlaneNo;
  short         fBarNo;
  short         fRefBarNo;
  short         fSideNo;
  short         fDyNo;
  short         fFeeNo;
};

//-------------------------------------------------------------------
namespace DmpParameterBgo{
// *
// *  TODO:  delete this namespace, use DmpParameterBgo_c
// *

  const short kPlaneNo = 7;
  const short kBarNo   = 22;
  const short kRefBarNo= 2;
  const short kSideNo  = 2;
  const short kDyNo    = 3;
  const short kFeeNo   = 16;
}

#endif

