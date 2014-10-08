/*
 *  $Id: DmpDataBuffer.cc, 2014-07-24 15:11:16 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 20/07/2014
*/

#include <boost/algorithm/string.hpp>
#include "DmpDataBuffer.h"

//-------------------------------------------------------------------
DmpDataBuffer::DmpDataBuffer()
 :DmpVSvc("DmpDataBuffer")
{
}

//-------------------------------------------------------------------
DmpDataBuffer::~DmpDataBuffer(){
}

//-------------------------------------------------------------------
bool DmpDataBuffer::Initialize(){
  return true;
}

//-------------------------------------------------------------------
bool DmpDataBuffer::Finalize(){
  DmpLogInfo<<"+-Deleting input data..."<<DmpLogEndl;
  for(DmpDataBufFolderMap::iterator aFolder=fInputDataBufPool.begin();aFolder!=fInputDataBufPool.end();++aFolder){
    DmpDataBufTreeMap aTreeMap = aFolder->second;
    DmpLogInfo<<"| |-"<<aFolder->first<<std::endl;
    for(DmpDataBufTreeMap::iterator aTree=aTreeMap.begin();aTree!=aTreeMap.end();++aTree){
      DmpDataBufBranchMap aBranchMap = aTree->second;
    DmpLogInfo<<"| | |-"<<aTree->first<<std::endl;
      for(DmpDataBufBranchMap::iterator it=aBranchMap.begin();it!=aBranchMap.end();++it){
    DmpLogInfo<<"| | | |-"<<it->first<<std::endl;
        delete it->second;
      }
    }
  }
  DmpLogInfo<<"`-Done"<<DmpLogEndl;
    //-------------------------------------------------------------------
  DmpLogInfo<<"+-Deleting output data..."<<DmpLogEndl;
  for(DmpDataBufFolderMap::iterator aFolder=fDataBufPool.begin();aFolder!=fDataBufPool.end();++aFolder){
    DmpDataBufTreeMap aTreeMap = aFolder->second;
    DmpLogInfo<<"| |-"<<aFolder->first<<std::endl;
    for(DmpDataBufTreeMap::iterator aTree=aTreeMap.begin();aTree!=aTreeMap.end();++aTree){
      DmpDataBufBranchMap aBranchMap = aTree->second;
    DmpLogInfo<<"| | |-"<<aTree->first<<std::endl;
      for(DmpDataBufBranchMap::iterator it=aBranchMap.begin();it!=aBranchMap.end();++it){
    DmpLogInfo<<"| | | |-"<<it->first<<std::endl;
        delete it->second;
      }
    }
  }
  DmpLogInfo<<"`-Done"<<DmpLogEndl;
  return true;
}

//-------------------------------------------------------------------
TObject* DmpDataBuffer::ReadObject(const std::string &path){
  // check path
  std::string folderName, treeName, branchName;
  PathCheck(path,folderName,treeName,branchName);
  // find it in fDataBufPool
  if(fDataBufPool.find(folderName) != fDataBufPool.end()){
    if(fDataBufPool[folderName].find(treeName) != fDataBufPool[folderName].end()){
      if(fDataBufPool[folderName][treeName].find(branchName) != fDataBufPool[folderName][treeName].end()){
        TObject *dataPtr = fDataBufPool[folderName][treeName][branchName];
        return dataPtr;
      }
    }
  }// create buffer map in input data buffer pool, not here
  // find it in fInputDataBufPool
  if(fInputDataBufPool.find(folderName) != fInputDataBufPool.end()){
    if(fInputDataBufPool[folderName].find(treeName) != fInputDataBufPool[folderName].end()){
      if(fInputDataBufPool[folderName][treeName].find(branchName) != fInputDataBufPool[folderName][treeName].end()){
        TObject *dataPtr = fInputDataBufPool[folderName][treeName][branchName];
        return dataPtr;
      }
    }else{
      DmpDataBufBranchMap aNewBranchMap;
      fInputDataBufPool[folderName].insert(std::make_pair(treeName,aNewBranchMap));
    }
  }else{
    DmpDataBufTreeMap aNewTreeMap;
    fInputDataBufPool.insert(std::make_pair(folderName,aNewTreeMap));
    DmpDataBufBranchMap aNewBranchMap;
    fInputDataBufPool[folderName].insert(std::make_pair(treeName,aNewBranchMap));
  }
  return 0;
}

//-------------------------------------------------------------------
void DmpDataBuffer::PathCheck(const std::string &checkMe,std::string &folderName,std::string &treeName,std::string &branchName){
  std::vector<std::string> temp;
  boost::split(temp,checkMe,boost::is_any_of("/"));
  if(3 != temp.size()){
    DmpLogError<<"Wrong path: "<<checkMe<<DmpLogEndl;
    throw;
  }else{
    folderName = temp[0];
    treeName = temp[1];
    branchName = temp[2];
  }
}

//-------------------------------------------------------------------
DmpDataBuffer *gDataBuffer = DmpDataBuffer::GetInstance();


