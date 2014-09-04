/*
 *  $Id: DmpDataBuffer.h, 2014-08-08 20:05:53 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 20/07/2014
*/

#ifndef DmpDataBuffer_H
#define DmpDataBuffer_H

#include "TTree.h"
#include "DmpRootIOSvc.h"

class TObject;

class DmpDataBuffer{
/*
 *  DmpDataBuffer
 *
 *      it's a singleton for eanch job
 *      it manages all data pointers.
 */
public:
  static DmpDataBuffer* GetInstance(){
    static DmpDataBuffer instance;
    return &instance;
  }
  ~DmpDataBuffer();
  template<typename T> bool RegisterObject(const std::string &path,T *&dataPtr,const std::string &className);   // path = Folder/Tree/Branch
  template<typename T> bool ReadObject(const std::string &path,T *&dataPtr);  // if path/dataPtr not in any data buffer, use dataPtr to read a branch from input rootfile;

private:
  DmpDataBuffer();
  bool PathCheck(const std::string &checkMe,std::string &folderName, std::string &treeName, std::string &branchName);

private:
typedef std::map<std::string, TObject*>                 DmpDataBufBranchMap;    // key is "Branch"
typedef std::map<std::string, DmpDataBufBranchMap>      DmpDataBufTreeMap;      // key is "Tree"
typedef std::map<std::string, DmpDataBufTreeMap>        DmpDataBufFolderMap;    // key is "Folder"

  DmpDataBufFolderMap    fDataBufPool;           // new created data pointers in pool. 3-level path: Folder, Tree, Branch
  DmpDataBufFolderMap    fInputDataBufPool;      // inputed data pointers in pool. 3-level path: Folder, Tree, Branch

};

//-------------------------------------------------------------------
template<typename T> bool DmpDataBuffer::RegisterObject(const std::string &path,T *&dataPtr,const std::string &className){
  // path check
  std::string folderName, treeName, branchName;
  if(not PathCheck(path,folderName,treeName,branchName)){
    return false;
  }
  // insert data buffer
  if(fDataBufPool.find(folderName) == fDataBufPool.end()){
    DmpDataBufTreeMap aNewTreeMap;
    fDataBufPool.insert(std::make_pair(folderName,aNewTreeMap));
  }
  if(fDataBufPool[folderName].find(treeName) == fDataBufPool[folderName].end()){
    DmpDataBufBranchMap aNewBranchMap;
    fDataBufPool[folderName].insert(std::make_pair(treeName,aNewBranchMap));
  }
  if(fDataBufPool[folderName][treeName].find(branchName) == fDataBufPool[folderName][treeName].end()){
    fDataBufPool[folderName][treeName].insert(std::make_pair(branchName,dataPtr));
  }else{
    DmpLogError<<path<<" is existing in data buffer"<<DmpLogEndl;
    return false;
  }
  // input arguments into root IOSvc, to create a branch (IOSvc check whether need to create branch)
  if(gRootIOSvc->WriteValid(folderName,treeName,branchName)){
    gRootIOSvc->GetOutputTree(folderName,treeName)->Branch(branchName.c_str(),className.c_str(),&dataPtr,32000,2);
  }
  return true;
}

//-------------------------------------------------------------------
template<typename T> bool DmpDataBuffer::ReadObject(const std::string &path,T *&dataPtr){
  // check path
  std::string folderName, treeName, branchName;
  if(not PathCheck(path,folderName,treeName,branchName)){
    return false;
  }
  // find it in fDataBufPool
  if(fDataBufPool.find(folderName) != fDataBufPool.end()){
    if(fDataBufPool[folderName].find(treeName) != fDataBufPool[folderName].end()){
      if(fDataBufPool[folderName][treeName].find(branchName) != fDataBufPool[folderName][treeName].end()){
        delete dataPtr;
        dataPtr = dynamic_cast<T*>(fDataBufPool[folderName][treeName][branchName]);
        return true;
      }
    }
  }// create buffer map in input data buffer pool, not here
  // find it in fInputDataBufPool
  if(fInputDataBufPool.find(folderName) != fInputDataBufPool.end()){
    if(fInputDataBufPool[folderName].find(treeName) != fInputDataBufPool[folderName].end()){
      if(fInputDataBufPool[folderName][treeName].find(branchName) != fInputDataBufPool[folderName][treeName].end()){
        delete dataPtr;
        dataPtr = dynamic_cast<T*>(fInputDataBufPool[folderName][treeName][branchName]);
        return true;
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
  // find it in input root file
  TTree *findTree = gRootIOSvc->GetInputTree(folderName,treeName);
  if(findTree){
    findTree->SetBranchAddress(branchName.c_str(),&dataPtr);
    fInputDataBufPool[folderName][treeName].insert(std::make_pair(branchName,dataPtr));
    return true;
  }
  DmpLogError<<"[DmpDataBuffer::ReadObject] didn't find data: "<<path<<DmpLogEndl;
  return false;
}

//-------------------------------------------------------------------
extern DmpDataBuffer  *gDataBuffer;

#endif


