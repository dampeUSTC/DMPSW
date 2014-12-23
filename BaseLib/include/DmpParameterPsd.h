/*
 *  $Id: DmpParameterPsd.h, 2014-08-07 23:24:13 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 07/03/2014
*/

#ifndef DmpParameterPsd_H
#define DmpParameterPsd_H

#include "TVector3.h"
#include "TXMLEngine.h"

class DmpParameterPsd_c{
public:
  static DmpParameterPsd_c* GetInstance(){
    static DmpParameterPsd_c instance;
    return &instance;
  }
  ~DmpParameterPsd_c();
  TVector3 BarCenter(const short &globalBarID)const;
  TVector3 LayerCenter(const short &globalLayerID)const;
  int LayerNumber()const{return m_PsdLayerNb;}
  int LayerStripNumber()const{return m_PsdLayerBarNb;}
  TVector3 GetPsdStripParameter_TypeA(){TVector3 tmp;tmp.SetXYZ(m_PsdStripAX,m_PsdStripAY,m_PsdStripAZ);return tmp;}
  TVector3 GetPsdStripParameter_TypeB(){TVector3 tmp;tmp.SetXYZ(m_PsdStripBX,m_PsdStripBY,m_PsdStripBZ);return tmp;}

private:
  DmpParameterPsd_c();
  void LoadPsdParameter(); //update vectors
  void LoadXMLFile();     // link to XML
  double GetXMLParameter(const char *parameter,XMLNodePointer_t node,TXMLEngine *xml);

private:
  TXMLEngine   *fXMLEngine;
  XMLNodePointer_t nodeDAMPEparameter;
  XMLNodePointer_t nodePsdparameter;

  //geometry viriable
  int m_PsdLayerNb;
  int m_PsdLayerBarNb;
  double m_PsdDetOffsetZ;
  double m_PsdBarGap;
  double m_PsdFirstXofYLayer;
  double m_PsdFirstYofXLayer;
  double m_PsdUpZofXLayer;
  double m_PsdUpZofYLayer;
  double m_PsdBottomZofXLayer;
  double m_PsdBottomZofYLayer;
  std::vector<double> m_PsdDetLayerBar_Z;  //z pos of every layer
  std::vector<double> m_PsdDetLayerBar_XY;  //X,Y pos of every layer
 
  double m_PsdDetSizeXY;
  double m_PsdDetSizeZ;
  double m_PsdStripAX;
  double m_PsdStripAY;
  double m_PsdStripAZ;
  double m_PsdStripBX;
  double m_PsdStripBY;
  double m_PsdStripBZ;
};

namespace DmpParameterPsd{
  const short kPlaneNo = 1;
  const short kStripNo = 24;
  const short kSideNo  = 2;
  const short kFeeNo   = 4;
}

#endif

