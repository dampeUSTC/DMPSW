/*
 *  $Id: DmpParameterBgo.cc, 2014-10-11 19:29:14 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 11/10/2014
*/

#include "DmpParameterBgo.h"
#include "DmpBgoBase.h"
#include <iostream>

#include <stdlib.h>
//-------------------------------------------------------------------
DmpParameterBgo_c::DmpParameterBgo_c()
 :fXMLEngine(0),
  fPlaneNo(7),
  fLayerNo(14),
  fLayerBarNo(22),
  fRefBarNo(2),
  fSideNo(2),
  fDyNo(3),
  fFeeNo(16)
{
  fXMLEngine = new TXMLEngine();
  LoadBgoParameter();
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

  if ((l<0)||(l>14)){
    std::cout<<"[BarCenter]:Wrong layer number!" << std::endl;
    throw;
  }

  if ((b<0)||(b>22)){
    std::cout<<"[BarCenter]:Wrong bar number!" << std::endl;
    throw;
  }

  if ((l%2)==0){
    tmp.SetXYZ(0.,m_BgoDetLayerBar_XY[b],m_BgoDetLayerBar_Z[l]);
  }
  else {
    tmp.SetXYZ(m_BgoDetLayerBar_XY[b],0.,m_BgoDetLayerBar_Z[l]);
  }
  return tmp;
}

//-------------------------------------------------------------------
TVector3 DmpParameterBgo_c::LayerCenter(const short &globalLayerID)const{
  short l = DmpBgoBase::GetLayerID(globalLayerID);
  TVector3 tmp;

  if ((l<0)||(l>14)){
    std::cout<<"[LayerCenter]:Wrong layer number!" << std::endl;
    throw;
  }

  if ((l%2)==0){
    tmp.SetXYZ(0.,0.,m_BgoDetLayerBar_Z[l]);
  }
  else {

    tmp.SetXYZ(0.,0.,m_BgoDetLayerBar_Z[l]);
  }
 
  return tmp;
}

//-------------------------------------------------------------------
void DmpParameterBgo_c::LoadXMLFile(){

  char *DMPSWSYS = NULL;
  DMPSWSYS = getenv ("DMPSWSYS");
  if (DMPSWSYS==NULL){
    std::cout<< "[DmpBgoBase::LoadGeometryXML] ERROR:DMPSWSYSPath cannot be found!" << std::endl;
    throw;
  }
  // * reading xml geometry parameter files
  std::string DMPSWSYSPath = std::string(DMPSWSYS);

  //std::string GeometryPath = DMPSWSYSPath.erase((DMPSWSYSPath.size()-7),DMPSWSYSPath.size());//7 is size of "Install"
  std::string GeometryPath = DMPSWSYSPath + "/share/Geometry/";
  std::string DAMPEParamterPath = GeometryPath+"EQM/dampe_parameter.xml";
  std::string BgoParamterPath = GeometryPath+"EQM/bgo_parameter.xml";
  XMLDocPointer_t xmldocDAMPEparameter = fXMLEngine->ParseFile(DAMPEParamterPath.c_str());
  XMLDocPointer_t xmldocBGOparameter = fXMLEngine->ParseFile(BgoParamterPath.c_str()); 
  nodeDAMPEparameter = fXMLEngine->DocGetRootElement(xmldocDAMPEparameter);
  nodeBGOparameter = fXMLEngine->DocGetRootElement(xmldocBGOparameter);
}

//-------------------------------------------------------------------
double DmpParameterBgo_c::GetXMLParameter(const char* parameter, XMLNodePointer_t node, TXMLEngine* xml){

  XMLAttrPointer_t attr;
  XMLAttrPointer_t NextAttr;
  double result = -1;

  XMLNodePointer_t child = xml->GetChild(node);
  while(child!=0){
    attr = xml->GetFirstAttr(child);
    while(attr!=0){
      //char* value = xml->GetAttrValue(attr);
      if(strcmp(xml->GetAttrValue(attr),parameter)==0){
        NextAttr = xml->GetNextAttr(attr);
        result = atof(xml->GetAttrValue(NextAttr));
        return result;
      }
      attr = xml->GetNextAttr(attr);
    }
    child = xml->GetNext(child);
  }
  if (result==-1){
    std::cout<< "[DmpBgoBase::GetXMLParameter] ERROR: parameter "<< parameter << " is not found" <<std::endl;
    throw;
  }
}
//-------------------------------------------------------------------
void DmpParameterBgo_c::LoadBgoParameter(){

  LoadXMLFile();

  //reading parameters
  m_BgoDetOffsetZ = GetXMLParameter("bgo_z_offset",nodeDAMPEparameter,fXMLEngine);
  
  m_BgoLayerNb = GetXMLParameter("BGO_NbOfCALLayers",nodeBGOparameter,fXMLEngine);
  m_BgoLayerBarNb = GetXMLParameter("BGO_NbOfCALLayerBars",nodeBGOparameter,fXMLEngine);
  m_BgoDetSizeXY  = std::max(GetXMLParameter("BGOdetectorX",nodeBGOparameter,fXMLEngine), GetXMLParameter("BGOdetectorY",nodeBGOparameter,fXMLEngine));
  m_BgoDetSizeZ   = GetXMLParameter("BGOdetectorZ",nodeBGOparameter,fXMLEngine);
  m_BgoDetLayerSeparation = GetXMLParameter("BGO_CALLayerSeparation",nodeBGOparameter,fXMLEngine);
  m_BgoDetBarSeparation = GetXMLParameter("BGO_CALBarsSeparation",nodeBGOparameter,fXMLEngine);
  m_BgoBarX = GetXMLParameter("BGObarX",nodeBGOparameter,fXMLEngine);
  m_BgoBarY = GetXMLParameter("BGObarY",nodeBGOparameter,fXMLEngine);
  m_BgoBarZ = GetXMLParameter("BGObarZ",nodeBGOparameter,fXMLEngine);
  m_BgoDetTopLayerZ = GetXMLParameter("BGO_CALTopLayerZ",nodeBGOparameter,fXMLEngine);

  //calculate bar position
  //Z direction
  for (int i=0;i<m_BgoLayerNb;i++){
    double BarCenterZ = 0.;
    BarCenterZ = m_BgoDetTopLayerZ+i*(m_BgoBarZ+m_BgoDetLayerSeparation)+m_BgoDetOffsetZ;
    m_BgoDetLayerBar_Z.push_back(BarCenterZ);
  }

  //x,y direction
  double FirstBarCenterXY = 0.;
  FirstBarCenterXY = 0.-10.5*(m_BgoBarX+m_BgoDetBarSeparation);
  for (int i=0;i<m_BgoLayerBarNb;i++){
    double BarCenterXY = 0.;
    BarCenterXY = FirstBarCenterXY+i*(m_BgoBarX+m_BgoDetBarSeparation);
    m_BgoDetLayerBar_XY.push_back(BarCenterXY);
  }

  //update parameters
  fLayerNo = m_BgoLayerNb;
  fLayerBarNo = m_BgoLayerBarNb;
 
}
//-------------------------------------------------------------------
