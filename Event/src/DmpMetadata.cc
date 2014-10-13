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
 :Time(time((time_t*)NULL))
{
}

//-------------------------------------------------------------------
DmpMetadata::~DmpMetadata(){
}

//-------------------------------------------------------------------
DmpMetadata& DmpMetadata::operator=(const DmpMetadata &r){
  Reset();
  Time = r.Time;
  Option =r.Option;
  CmdList = r.CmdList;
}

//-------------------------------------------------------------------
void DmpMetadata::LoadFrom(DmpMetadata *r){
  Reset();
  Time = r->Time;
  Option = r->Option;
  CmdList = r->CmdList;
}

//-------------------------------------------------------------------
void DmpMetadata::PrintJobTime(const short &level)const{
// *
// *  TODO: 
// *
  std::cout<<"Time: "<<Time<<std::endl;
}

//-------------------------------------------------------------------
void DmpMetadata::SetOption(std::string tmp,const std::string &v){
  tmp = (tmp[0]!='/')?tmp:tmp.substr(1);
  if(HasCommand(tmp)){
    std::cout<<"Resetting "<<tmp<<":\t\""<<Option[tmp]<<"\" ---> \""<<v<<"\""<<std::endl;
    Option[tmp] = v;
  }else{
    Option.insert(std::make_pair(tmp,v));
    CmdList.push_back(tmp);
  }
}

//-------------------------------------------------------------------
void DmpMetadata::ListOptions()const{
  for(std::map<std::string,std::string>::const_iterator it=Option.begin();it!=Option.end();it++){
    std::cout<<it->first<<":\t"<<it->second<<std::endl;
  }
}

//-------------------------------------------------------------------
bool DmpMetadata::HasCommand(std::string o)const{
  o = (o[0]!='/') ? o : o.substr(1);
  bool status = (Option.find(o) != Option.end()) ? true : false;
  if(not status){
    for(size_t i=0;i<CmdList.size();++i){
      if(CmdList[i].find(o) != std::string::npos){
        return true;
      }
    }
  }
  return status;
}

//-------------------------------------------------------------------
std::string DmpMetadata::GetValue(const std::string &tmp)const{
  if(HasCommand(tmp)){
    return Option.at(tmp);
  }
  return "";
}

//-------------------------------------------------------------------
std::string DmpMetadata::GetValue(const short &i)const{
  return Option.at(CmdList.at(i));
}

//-------------------------------------------------------------------
void DmpMetadata::Reset(){
  Option.clear();
  CmdList.clear();
}

