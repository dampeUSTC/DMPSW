/*
 *  $Id: DmpParameterPsd.cc, 2014-12-17 15:43:03 DAMPE/USTC $
 *  Author(s):
 *    Yifeng Wei (weiyf@mail.ustc.edu.cn) 17/12/2014
*/

#include "DmpParameterPsd.h"
#include "DmpPsdBase.h"
#include <iostream>
#include <stdlib.h>
//-------------------------------------------------------------------
DmpParameterPsd_c::DmpParameterPsd_c(){
  fXMLEngine = new TXMLEngine();
  LoadPsdParameter();
}
//-------------------------------------------------------------------
DmpParameterPsd_c::~DmpParameterPsd_c(){
  delete fXMLEngine;
}
//-------------------------------------------------------------------
TVector3 DmpParameterPsd_c::BarCenter(const short &globalBarID)const{
  short l = DmpPsdBase::GetLayerID(globalBarID);
  short s = DmpPsdBase::GetStripID(globalBarID);
  TVector3 tmp;

  if ((l<0)||(l>1)){
    std::cout<<"[BarCenter]:Wrong layer number!" << std::endl;
    throw;
  }

  if ((s<0)||(s>40)){
    std::cout<<"[BarCenter]:Wrong bar number!" << std::endl;
    throw;
  }

  //in this code, layer 0 is defined as the top layer(strip along X direction,far away from Bgo detector), layer 1 is the bottom layer(strip along Y direction,close to Bgo detector)
  //
  //there are two sub-layer in one Psd layer,two sub-layer have their own Z position.
  if (l==0){
    if ((s%2)==0){
      tmp.SetXYZ(0,m_PsdDetLayerBar_XY.at(s),m_PsdDetLayerBar_Z.at(0));
    }
    else {
      tmp.SetXYZ(0,m_PsdDetLayerBar_XY.at(s),m_PsdDetLayerBar_Z.at(1));
    }
  }
  else if (l==1){
    if ((s%2)==0){
      tmp.SetXYZ(m_PsdDetLayerBar_XY.at(s),0,m_PsdDetLayerBar_Z.at(2));
    }
    else {
      tmp.SetXYZ(m_PsdDetLayerBar_XY.at(s),0,m_PsdDetLayerBar_Z.at(3));
    }
  }
  return tmp;
}
//-------------------------------------------------------------------
TVector3 DmpParameterPsd_c::LayerCenter(const short &globalLayerID)const{
}
//-------------------------------------------------------------------
double DmpParameterPsd_c::GetXMLParameter(const char* parameter, XMLNodePointer_t node, TXMLEngine* xml){

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
    std::cout<< "[DmpParamterPsd::GetXMLParameter] ERROR: parameter "<< parameter << " is not found" <<std::endl;
    throw;
  }
}
//-------------------------------------------------------------------
void DmpParameterPsd_c::LoadXMLFile(){

  char *DMPSWSYS = NULL;
  DMPSWSYS = getenv ("DMPSWSYS");
  if (DMPSWSYS==NULL){
    std::cout<< "[DmpParameterPsd::LoadGeometryXML] ERROR:DMPSWSYSPath cannot be found!" << std::endl;
    throw;
  }
  // * reading xml geometry parameter files
  std::string DMPSWSYSPath = std::string(DMPSWSYS);

  //std::string GeometryPath = DMPSWSYSPath.erase((DMPSWSYSPath.size()-7),DMPSWSYSPath.size());//7 is size of "Install"
  std::string GeometryPath = DMPSWSYSPath + "/share/Geometry/";
  std::string DAMPEParamterPath = GeometryPath+"EQM/dampe_parameter.xml";
  std::string PsdParamterPath = GeometryPath+"EQM/psd_parameter.xml";
  XMLDocPointer_t xmldocDAMPEparameter = fXMLEngine->ParseFile(DAMPEParamterPath.c_str());
  XMLDocPointer_t xmldocBGOparameter = fXMLEngine->ParseFile(PsdParamterPath.c_str()); 
  nodeDAMPEparameter = fXMLEngine->DocGetRootElement(xmldocDAMPEparameter);
  nodePsdparameter = fXMLEngine->DocGetRootElement(xmldocBGOparameter);
}
//-------------------------------------------------------------------
void DmpParameterPsd_c::LoadPsdParameter(){

  LoadXMLFile();

  //reading parameters
  m_PsdDetOffsetZ = GetXMLParameter("psd_z_offset",nodeDAMPEparameter,fXMLEngine);
  
  m_PsdLayerNb = GetXMLParameter("PSD_NbofLayer",nodePsdparameter,fXMLEngine);
  m_PsdLayerBarNb = GetXMLParameter("PSD_NbofLayerBars",nodePsdparameter,fXMLEngine);
  m_PsdBarGap = GetXMLParameter("PSD_BarGap",nodePsdparameter,fXMLEngine);
  m_PsdFirstXofYLayer = GetXMLParameter("firstXofYLayer",nodePsdparameter,fXMLEngine);
  m_PsdFirstYofXLayer = GetXMLParameter("firstYofXLayer",nodePsdparameter,fXMLEngine);
  m_PsdUpZofXLayer = GetXMLParameter("upZofXLayer",nodePsdparameter,fXMLEngine);
  m_PsdUpZofYLayer = GetXMLParameter("upZofYLayer",nodePsdparameter,fXMLEngine);
  m_PsdBottomZofXLayer = GetXMLParameter("bottomZofXLayer",nodePsdparameter,fXMLEngine);
  m_PsdBottomZofYLayer = GetXMLParameter("bottomZofYLayer",nodePsdparameter,fXMLEngine);

  m_PsdDetSizeXY = GetXMLParameter("PSDdetectorX",nodePsdparameter,fXMLEngine);
  m_PsdDetSizeZ = GetXMLParameter("PSDdetectorZ",nodePsdparameter,fXMLEngine);
  m_PsdStripAX = GetXMLParameter("PSDStripAX",nodePsdparameter,fXMLEngine);
  m_PsdStripAY = GetXMLParameter("PSDStripAY",nodePsdparameter,fXMLEngine);
  m_PsdStripAZ = GetXMLParameter("PSDStripAZ",nodePsdparameter,fXMLEngine);
  m_PsdStripBX = GetXMLParameter("PSDStripBX",nodePsdparameter,fXMLEngine);
  m_PsdStripBY = GetXMLParameter("PSDStripBY",nodePsdparameter,fXMLEngine);
  m_PsdStripBZ = GetXMLParameter("PSDStripBZ",nodePsdparameter,fXMLEngine);


  //calculate bar position
  //Z direction
  //Psd detector has two Layer,there are two sub-layer in each layer of same direction(up sub-layer & bottom sub-layer)
  m_PsdDetLayerBar_Z.push_back(m_PsdUpZofXLayer+m_PsdDetOffsetZ);
  m_PsdDetLayerBar_Z.push_back(m_PsdBottomZofXLayer+m_PsdDetOffsetZ);
  m_PsdDetLayerBar_Z.push_back(m_PsdUpZofYLayer+m_PsdDetOffsetZ);
  m_PsdDetLayerBar_Z.push_back(m_PsdBottomZofYLayer+m_PsdDetOffsetZ);


  //x,y direction
  for (int i=0;i<m_PsdLayerBarNb;i++){
    double BarCenterXY = 0.;
    BarCenterXY = m_PsdFirstXofYLayer+i*m_PsdBarGap;
    m_PsdDetLayerBar_XY.push_back(BarCenterXY);
  }

}
//-------------------------------------------------------------------

