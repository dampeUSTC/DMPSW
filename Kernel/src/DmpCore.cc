/*
 *  $Id: DmpCore.cc, 2014-09-21 14:58:08 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 22/04/2014
*/

#include <time.h>

#include "DmpCore.h"
#include "DmpRootIOSvc.h"
#include "DmpDataBuffer.h"
#include "DmpTimeConvertor.h"

//-------------------------------------------------------------------
DmpCore::DmpCore()
 :fAlgMgr(0),
  fSvcMgr(0),
  fLaunchTime("20130101-0000"),
  fMaxEventNo(-1),
  fStartTime(DmpTimeConvertor::Date2Second("2013-01-01 00:00:00")),
  fStopTime(DmpTimeConvertor::Date2Second("2113-01-01 00:00:00")),
  fInitializeDone(false),
  fTerminateRun(false),
  fCurrentEventID(0)    // must == 0
{
  std::cout<<"**************************************************"<<std::endl;
  std::cout<<"      Offline software of DAMPE (DMPSW)"<<std::endl;
  std::cout<<"      version:  1.1.0(dampeustc)"<<std::endl;
  std::cout<<"**************************************************"<<std::endl;
  fAlgMgr = DmpAlgorithmManager::GetInstance();
  fSvcMgr = DmpServiceManager::GetInstance();
  fSvcMgr->Append(DmpRootIOSvc::GetInstance());     // must use GetInstance instead of global variable, since, Mac create global variable later than DmpCore::DmpCore()
  fSvcMgr->Append(DmpDataBuffer::GetInstance());
  OptMap.insert(std::make_pair("LogLevel",  0));    // value: None, Error, Warning, Info, Debug
  OptMap.insert(std::make_pair("LogHeader", 1));    // value: On, Off 
  OptMap.insert(std::make_pair("EventNumber",2));   // value: any number
  OptMap.insert(std::make_pair("StartTime", 3));    // value: format 20131231-1430
  OptMap.insert(std::make_pair("StopTime",  4));    // value: format 20131231-1430
  OptMap.insert(std::make_pair("FromEvent",5));     // value: any number
}

//-------------------------------------------------------------------
DmpCore::~DmpCore(){
}

//-------------------------------------------------------------------
bool DmpCore::Initialize(){
  //*
  //* Important! First, initialize servises, then algorithms
  //*
  std::cout<<"\n  [DmpCore::Initialize] Initialize..."<<std::endl;
  if(not fSvcMgr->Initialize()) return false;
  if(not fAlgMgr->Initialize()) return false;
  gRootIOSvc->PrepareMetaData();
  std::cout<<"  [DmpCore::Initialize] ... initialized successfully"<<std::endl;
  fInitializeDone = true;
  return true;
}

//-------------------------------------------------------------------
bool DmpCore::Run(){
  if(not fInitializeDone){
    return false;
  }
  std::cout<<"\n  [DmpCore::Run] Running..."<<std::endl;
// *
// *  TODO: use cut of time range??
// *
  while(not (fTerminateRun||(fCurrentEventID==fMaxEventNo))){
    if(gRootIOSvc->PrepareEvent(fCurrentEventID)){
      if(fAlgMgr->ProcessOneEvent()){
        gRootIOSvc->FillData("Event");
      }
      ++fCurrentEventID;
    }else{
      fTerminateRun = true;
      break;
    }
  }
  std::cout<<"  [DmpCore::Run] Done"<<std::endl;
  return true;
}

//-------------------------------------------------------------------
bool DmpCore::Finalize(){
  std::cout<<"\n  [DmpCore::Finalize] Finalize..."<<std::endl;
  //*
  //* Important! First, finalize algorithms, then services!
  //*
  fAlgMgr->Finalize();
  fSvcMgr->Finalize();
  std::cout<<"  [DmpCore::Finalize] ... finalized successfully"<<std::endl;
  return true;
}

//-------------------------------------------------------------------
#include <boost/lexical_cast.hpp>
void DmpCore::Set(const std::string &type,const std::string &value){
  if(OptMap.find(type) == OptMap.end()){
    DmpLogError<<"[DmpCore::Set] No argument type: "<<type<<DmpLogEndl;
    std::cout<<"\tPossible options are:"<<DmpLogEndl;
    for(std::map<std::string,short>::iterator anOpt= OptMap.begin();anOpt!=OptMap.end();anOpt++){
      std::cout<<"\t\t"<<anOpt->first<<DmpLogEndl;
    }
    throw;
  }
  switch(OptMap[type]){
    case 0: // LogLevel
    {
      DmpLog::SetLogLevel(value);
      break;
    }
    case 1: // LogHeader
    {
      DmpLog::SetLogHeader(value);
      break;
    }
    case 2: // EventNumber
    {
      fMaxEventNo = boost::lexical_cast<long>(value);
      break;
    }
    case 3: // StartTime
    {
      fStartTime = DmpTimeConvertor::Date2Second(value);
      break;
    }
    case 4: // StopTime
    {
      fStopTime = DmpTimeConvertor::Date2Second(value);
      break;
    }
    case 5: // FromEvent
    {
      fCurrentEventID = boost::lexical_cast<long>(value);
      break;
    }
  }
}

//-------------------------------------------------------------------
DmpCore *gCore = DmpCore::GetInstance();


