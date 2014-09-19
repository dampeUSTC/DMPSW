/*
 *  $Id: DmpRootIOSvc.cc, 2014-07-21 09:38:44 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 20/05/2014
*/

#include <boost/algorithm/string.hpp>
#include "TTree.h"
#include "TFile.h"

#include "DmpRootIOSvc.h"

//-------------------------------------------------------------------
DmpRootIOSvc::DmpRootIOSvc()
 :DmpVSvc("DmpRootIOSvc"),
  fInRootFile(0),
  fOutRootFile(0),
  fOutFileKey(""),
  fInPath("./"),
  fOutPath("./")
{
  fInFileName = "";
  fOutFileName = "";
  OptMap.insert(std::make_pair("InData/Path",   0));
  OptMap.insert(std::make_pair("InData/FileName", 1));
  OptMap.insert(std::make_pair("OutData/Path",  2));
  OptMap.insert(std::make_pair("OutData/FileName",  3));
  OptMap.insert(std::make_pair("OutData/WriteList", 4));
  OptMap.insert(std::make_pair("OutData/Key", 5));
}

//-------------------------------------------------------------------
DmpRootIOSvc::~DmpRootIOSvc(){
}

//-------------------------------------------------------------------
void DmpRootIOSvc::Set(const std::string &option,const std::string &argv){
  switch (OptMap[option]){
    case 0: // InData/Path
    {
      if('/' == argv[argv.length()-1]){
        fInPath = argv;
      }else{
        fInPath = argv+"/";
      }
      break;
    }
    case 1: // InData/FileName
    {
      boost::filesystem::path temp(argv);
      fInFileName = temp.filename().string();
      if((temp.parent_path().string()!="") && (fInPath=="./")){
        fInPath = temp.parent_path().string()+"/";
      }
      break;
    }
    case 2: // OutData/Path
    {
      if('/' == argv[argv.length()-1]){
        fOutPath = argv;
      }else{
        fOutPath = argv+"/";
      }
      break;
    }
    case 3: // OutData/FileName
    {
      boost::filesystem::path temp(argv);
      fOutFileName = temp.filename().string();
      if((temp.parent_path().string()!="") && (fOutPath=="./")){
        fOutPath = temp.parent_path().string()+"/";
      }
      break;
    }
    case 4: // OutData/WriteList
    {
      boost::split(fWriteList,argv,boost::is_any_of(";"));
      for(short i=0;i<fWriteList.size();++i){
        std::vector<std::string>  temp;
        boost::split(temp,fWriteList[i],boost::is_any_of("/"));
        if(3 != temp.size()){
          DmpLogError<<"Wrong path of writing data: "<<fWriteList[i]<<DmpLogEndl;
        }
      }
      break;
    }
    case 5: // OutData/Key
    {
      fOutFileKey = argv;
      break;
    }
    default:
    {
      DmpLogError<<"No argument type: "<<argv<<DmpLogEndl;
    }
  }
}

//-------------------------------------------------------------------
bool DmpRootIOSvc::Initialize(){
  DmpLogDebug<<"initialization... "<<DmpLogEndl;
  //-------------------------------------------------------------------
  if(fInFileName.string() != ""){   // has input file
    if(fInFileName.extension().string() == ".root"){
      fInFileName = fInPath+fInFileName.string();
      fInRootFile = new TFile(fInFileName.string().c_str(),"read");
      std::cout<<"\tInput data:\t"<<fInFileName.string()<<DmpLogEndl;
    }else{
      DmpLogError<<"input data is not a root file... "<<fInFileName.string()<<DmpLogEndl;
      return false;
    }
  }
  //-------------------------------------------------------------------
  if(not boost::filesystem::exists(fOutPath)){
    // create output directory at here, not in CreateOutRootFile()
    // since DmpVAlg::Initialize() need this directory is existing
    boost::filesystem::create_directories(fOutPath);
  }
  if(fOutFileName.string() == ""){
    Set("OutData/FileName",this->GetInputFileName());
  }
  //-------------------------------------------------------------------
  DmpLogDebug<<"... initialization done "<<DmpLogEndl;
  return true;
}

//-------------------------------------------------------------------
void DmpRootIOSvc::CreateOutRootFile(){
  if(0 != fWriteList.size()){
    // create root file at here, not in Initialize().
    // Becuase fOutFileKey may be setted in DmpVAlg::Initialize()
    std::string splitMark = "-";
    std::string output = fOutPath+fOutFileName.stem().string();
    unsigned found = output.find_last_of(splitMark);
    if(-1 == found){    // not found
      fOutFileName = output+splitMark+fOutFileKey+".root";
    }else{
      fOutFileName = output.substr(0,found)+splitMark+fOutFileKey+".root";
    }
    fOutRootFile = new TFile(fOutFileName.string().c_str(),"RECREATE");
    std::cout<<"\tOut file:\t"<<fOutFileName.string()<<DmpLogEndl;
  }
}

//-------------------------------------------------------------------
bool DmpRootIOSvc::Finalize(){
  // save trees
  if(fOutRootFile){
    DmpLogInfo<<"+--Writing "<<fOutFileName<<DmpLogEndl;
    for(DmpRootIOFolderMap::iterator aFolderMap=fOutTreeSet.begin();aFolderMap != fOutTreeSet.end();++aFolderMap){
      if(aFolderMap->first != "Event"){
        FillData(aFolderMap->first);
      }
      DmpRootIOTreeMap aTreeMap = aFolderMap->second;
      DmpLogInfo<<"|  +--folder: "<<aFolderMap->first<<DmpLogEndl;
      fOutRootFile->mkdir((aFolderMap->first).c_str());
      fOutRootFile->cd((aFolderMap->first).c_str());
      for(DmpRootIOTreeMap::iterator it= aTreeMap.begin();it!=aTreeMap.end();++it){
        DmpLogInfo<<"|  |  +--tree: "<<it->first<<", entries = "<<it->second->GetEntries()<<DmpLogEndl;
        it->second->Write();
        delete it->second;
      }
    }
    DmpLogInfo<<"+--Done"<<DmpLogEndl;
  }
  // delete root files
  if(fInRootFile){
    fInRootFile->Close();
    delete fInRootFile;
  }
  if(fOutRootFile){
    fOutRootFile->Close();
    delete fOutRootFile;
  }
  return true;
}

//-------------------------------------------------------------------
bool DmpRootIOSvc::WriteValid(const std::string &folderName,const std::string &treeName, const std::string &branchName){
  // check write list
  bool inWriteList=false, noBranch=false;
  std::string path = folderName+"/"+treeName+"/"+branchName;
  for(short i=0;i<fWriteList.size();++i){
    if(path == fWriteList[i]){
      inWriteList = true;
      break;
    }
  }
  // check branch
  TTree *theTree = GetOutputTree(folderName,treeName);
  if(0 == theTree->GetListOfBranches()->FindObject(branchName.c_str())){
    noBranch = true;
  }else{
    DmpLogError<<"path existed... "<<path<<DmpLogEndl;
  }
  return (inWriteList && noBranch);
}

//-------------------------------------------------------------------
TTree* DmpRootIOSvc::GetOutputTree(const std::string &folderName,const std::string &treeName){
  TTree *tree = 0;
  if(fOutTreeSet.find(folderName) != fOutTreeSet.end()){
    if(fOutTreeSet[folderName].find(treeName) != fOutTreeSet[folderName].end()){
      tree = fOutTreeSet[folderName][treeName];
    }
  }else{
    DmpRootIOTreeMap aNewFolder;
    fOutTreeSet.insert(std::make_pair(folderName,aNewFolder));
  }
  if(0 == tree){
    tree = new TTree(treeName.c_str(),treeName.c_str());
    tree->SetAutoSave(50000000);    //50MBytes
    fOutTreeSet[folderName].insert(std::make_pair(treeName,tree));
  }
  return tree;
}

//-------------------------------------------------------------------
TTree* DmpRootIOSvc::GetInputTree(const std::string &folderName,const std::string &treeName){
  TTree *theTree = 0;
  if(fInTreeSet.find(folderName) != fInTreeSet.end()){
    if(fInTreeSet[folderName].find(treeName) != fInTreeSet[folderName].end()){
      theTree = fInTreeSet[folderName][treeName];
    }
  }else{
    DmpRootIOTreeMap  aNewFolder;
    fInTreeSet.insert(std::make_pair(folderName,aNewFolder));
  }
  if(0 == theTree){
    std::string foldrAndTreeName = folderName+"/"+treeName;
    theTree = dynamic_cast<TTree*>(fInRootFile->Get(foldrAndTreeName.c_str()));
    if(theTree){
      fInTreeSet[folderName].insert(std::make_pair(treeName,theTree));
      fEntriesOfTree.insert(std::make_pair(foldrAndTreeName,theTree->GetEntries()));
    }
  }
  return theTree;
}

//-------------------------------------------------------------------
void DmpRootIOSvc::PrepareMetaData(){
  for(DmpRootIOFolderMap::iterator aFolder=fInTreeSet.begin();aFolder!=fInTreeSet.end();++aFolder){
    if("Event" != aFolder->first){
      for(DmpRootIOTreeMap::iterator it=fInTreeSet[aFolder->first].begin();it!=fInTreeSet[aFolder->first].end();++it){
        it->second->GetEntry();
      }
    }
  }
}

//-------------------------------------------------------------------
bool DmpRootIOSvc::PrepareEvent(const long &evtID){
  if(0 == fInTreeSet.size()){
    // some algorithm not use input root file, like Sim and Rdc
    return true;
  }
  DmpLogDebug<<"reading event ID = "<<evtID<<DmpLogEndl;
  bool atLeastONeTree = false;
  for(DmpRootIOTreeMap::iterator it=fInTreeSet["Event"].begin();it!=fInTreeSet["Event"].end();++it){
    if(evtID < fEntriesOfTree["Event/"+it->first]){
      it->second->GetEntry(evtID);
      atLeastONeTree = true;
    }
  }
  return atLeastONeTree;
}

//-------------------------------------------------------------------
void DmpRootIOSvc::FillData(const std::string &floder){
  for(DmpRootIOTreeMap::iterator it=fOutTreeSet[floder].begin();it!=fOutTreeSet[floder].end();++it){
    DmpLogDebug<<it->first<<"\tFill "<<floder<<" data "<<it->second->GetEntries()<<DmpLogEndl;
    it->second->Fill();
  }
}

//-------------------------------------------------------------------
DmpRootIOSvc *gRootIOSvc = DmpRootIOSvc::GetInstance();

