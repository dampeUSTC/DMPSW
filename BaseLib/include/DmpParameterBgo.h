/*
 *  $Id: DmpParameterBgo.h, 2014-08-21 16:33:13 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 06/08/2013
*/

#ifndef DmpParameterBgo_H
#define DmpParameterBgo_H

#include "TVector3.h"
#include "TXMLEngine.h"

class DmpParameterBgo_c{
public:
  static DmpParameterBgo_c* GetInstance(){
    static DmpParameterBgo_c instance;
    return &instance;
  }
  ~DmpParameterBgo_c();
  short PlaneNumber()const{return fPlaneNo;}
  short LayerNumber()const{return fLayerNo;}
  short LayerBarNumber()const{return fLayerBarNo;}
  short ReferenceBarNumber()const{return fRefBarNo;}
  short SideNumber()const{return fSideNo;}
  short DynodeNumber()const{return fDyNo;}
  short FeeNumber()const{return fFeeNo;}
  TVector3 BarCenter(const short &GlobalBarID)const;
  TVector3 LayerCenter(const short &globalLayerID)const;

private:
  DmpParameterBgo_c();
  void LoadBgoParameter(); //update vectors
  void LoadXMLFile();     // link to XML
  double GetXMLParameter(const char *parameter,XMLNodePointer_t node,TXMLEngine *xml);

private:
  TXMLEngine   *fXMLEngine;
  XMLNodePointer_t nodeDAMPEparameter;
  XMLNodePointer_t nodeBGOparameter;

  //geometry viriable
  int m_BgoLayerNb;
  int m_BgoLayerBarNb;
  double m_BgoDetSizeXY;
  double m_BgoDetSizeZ;
  double m_BgoDetOffsetZ;
  std::vector<double> m_BgoDetLayerBar_Z;  //z pos of every layer
  std::vector<double> m_BgoDetLayerBar_XY;  //X,Y pos of every layer
  double m_BgoDetLayerSeparation;
  double m_BgoDetBarSeparation;
  double m_BgoBarX;
  double m_BgoBarY;
  double m_BgoBarZ;
  double m_BgoDetTopLayerZ;


  short         fPlaneNo;
  short         fLayerNo;
  short         fLayerBarNo;
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

