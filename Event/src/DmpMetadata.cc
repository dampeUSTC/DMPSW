/*
 *  $Id: DmpMetadata.cc, 2014-10-03 20:08:34 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 01/10/2014
*/

#include <iostream>
#include <time.h>   // time_t
#include "DmpMetadata.h"

ClassImp(DmpMetadata)

//-------------------------------------------------------------------
DmpMetadata::DmpMetadata()
 :JobTime(time((time_t*)NULL))
{
}

//-------------------------------------------------------------------
DmpMetadata::~DmpMetadata(){
}

//-------------------------------------------------------------------
void DmpMetadata::PrintJobTime(const short &level)const{
// *
// *  TODO: 
// *
  std::cout<<"Time: "<<JobTime<<std::endl;
}

//-------------------------------------------------------------------
void DmpMetadata::SetOption(const std::string &p,const std::string &v){
  std::string tmp = (p[0]!='/')?p:p.substr(1);
  Option[tmp] = v;
}

//-------------------------------------------------------------------
void DmpMetadata::ListOptions()const{
  for(std::map<std::string,std::string>::const_iterator it=Option.begin();it!=Option.end();it++){
    std::cout<<it->first<<":\t"<<it->second<<std::endl;
  }
}


