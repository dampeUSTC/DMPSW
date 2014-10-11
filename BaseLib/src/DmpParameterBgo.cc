/*
 *  $Id: DmpParameterBgo.cc, 2014-10-11 19:29:14 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 11/10/2014
*/

#include "DmpParameterBgo.h"
#include "TXMLEngine.h"
#include "DmpBgoBase.h"

//-------------------------------------------------------------------
DmpParameterBgo_c::DmpParameterBgo_c()
 :fXMLEngine(0),
  fPlaneNo(7),
  fBarNo(22),
  fRefBarNo(2),
  fSideNo(2),
  fDyNo(3),
  fFeeNo(16)
{
  fXMLEngine = new TXMLEngine();
  LoadXMLFile();
}

//-------------------------------------------------------------------
DmpParameterBgo_c::~DmpParameterBgo_c(){
  delete fXMLEngine;
}

//-------------------------------------------------------------------
TVector3 DmpParameterBgo_c::BarCenter(const short &GlobalBarID)const{
  short l = DmpBgoBase::GetLayerID(GlobalBarID);
  short b = DmpBgoBase::GetBarID(GlobalBarID);
  TVector3 tmp;
// *
// *  TODO: update tmp
// *
  return tmp;
}

//-------------------------------------------------------------------
TVector3 DmpParameterBgo_c::LayerCenter(const short &globalLayerID)const{
  short l = DmpBgoBase::GetLayerID(globalLayerID);
  TVector3 tmp;
// *
// *  TODO: update tmp
// *
  return tmp;
}

//-------------------------------------------------------------------
void DmpParameterBgo_c::LoadXMLFile(){
// *
// *  TODO: read xml file, update data members
// *
}


