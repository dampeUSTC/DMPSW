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

class DmpDataBuffer : public DmpVSvc{
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
  bool Initialize();
  bool Finalize();
  TObject* ReadObject(const std::string &path);  // if path/dataPtr not in any data buffer, return 0
  template<typename T> void RegisterObject(const std::string &path,T *&dataPtr,const std::string &className="TClonesArray");   // path = Folder/Tree/Branch
  template<typename T> void LinkRootFile(const std::string &path,T *&dataPtr);  // use dataPtr to read a branch from input rootfile, if not find branch, break job;

private:
  DmpDataBuffer();
  void PathCheck(const std::string &checkMe,std::string &folderName, std::string &treeName, std::string &branchName);

private:
typedef std::map<std::string, TObject*>                 DmpDataBufBranchMap;    // key is "Branch"
typedef std::map<std::string, DmpDataBufBranchMap>      DmpDataBufTreeMap;      // key is "Tree"
typedef std::map<std::string, DmpDataBufTreeMap>        DmpDataBufFolderMap;    // key is "Folder"

  DmpDataBufFolderMap    fDataBufPool;           // new created data pointers in pool. 3-level path: Folder, Tree, Branch
  DmpDataBufFolderMap    fInputDataBufPool;      // inputed data pointers in pool. 3-level path: Folder, Tree, Branch

};

//-------------------------------------------------------------------
template<typename T> void DmpDataBuffer::RegisterObject(const std::string &path,T *&dataPtr,const std::string &className){
  // path check
  std::string folderName, treeName, branchName;
  PathCheck(path,folderName,treeName,branchName);
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
    throw;
  }
  // input arguments into root IOSvc, to create a branch (IOSvc check whether need to create branch)
  if(gRootIOSvc->WriteValid(folderName,treeName,branchName)){
    TTree *tree = gRootIOSvc->GetOutputTree(folderName,treeName);
    if("TClonesArray" == className){
      tree->Branch(branchName.c_str(),dataPtr,32000,2);
    }else{
      tree->Branch(branchName.c_str(),className.c_str(),&dataPtr,32000,2);
    }
  }
}

//-------------------------------------------------------------------
template<typename T> void DmpDataBuffer::LinkRootFile(const std::string &path,T *&dataPtr){
  // check path
  std::string folderName, treeName, branchName;
  PathCheck(path,folderName,treeName,branchName);
  TTree *findTree = gRootIOSvc->GetInputTree(folderName,treeName);
  if(findTree){
    findTree->SetBranchAddress(branchName.c_str(),&dataPtr);
    fInputDataBufPool[folderName][treeName].insert(std::make_pair(branchName,dataPtr));
  }else{
    DmpLogError<<"[DmpDataBuffer::LinkRootFile] not find the branch "<<branchName<<" in tree "<<folderName<<"/"<<treeName<<DmpLogEndl;
  }
}

//-------------------------------------------------------------------
extern DmpDataBuffer  *gDataBuffer;

#endif


