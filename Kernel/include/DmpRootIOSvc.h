/*
 *  $Id: DmpRootIOSvc.h, 2014-07-21 09:38:42 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 20/05/2014
*/

#ifndef DmpRootIOSvc_H
#define DmpRootIOSvc_H

#ifndef __CINT__
#include <boost/filesystem.hpp>     // path
#endif
#include <vector>
#include "DmpVSvc.h"

class TFile;
class TTree;

class DmpRootIOSvc : public DmpVSvc{
/* 
 *  DmpRootIOSvc
 *
 *      it's the first element in DmpServiceManager
 *      it's a singleton for eanch job
 *      only one input and one output root file
 *      input of Simulation and Rdc is not compatible.
 */
public:
  static DmpRootIOSvc* GetInstance(){
    static DmpRootIOSvc instance;
    return &instance;
  }
  ~DmpRootIOSvc();
  void Set(const std::string &option,const std::string &v);
  /*
   * Options:
   *    +--Input
   *    |  |--Path
   *    |  `--FileName
   *    +--Output
   *    |  |--Path
   *    |  |--FileName
   *    |  |--WriteList
   *    |  `--Key
   */
  bool Initialize();
  bool Finalize();

public:
  bool WriteValid(const std::string &treeName); // in write list, no branch
  TTree* GetOutputTree(const std::string &folderName,const std::string &treeName);
  TTree* GetInputTree(const std::string &folderName,const std::string &treeName);
  void PrepareMetaData();
  bool PrepareEvent(const long &evtID); //only read fInTreeSet["Event"]
  void FillData(const std::string &floderName);
 /*
  *  invoke FillData("Event") in DmpCore::Run(), if fAlgMgr->ProcessThisEvent() return true
  *
  *  invoke FillData("Calibration") in the begin of DmpRootIOSvc::Finalize()
  *
  */

public:
  std::string GetInputPath()const{return fInPath;}
  std::string GetOutputPath()const{return fOutPath;}
  std::string GetInputFileName()const{return fInFileName.string();}//return full input file name
  std::string GetOutputFileName()const{return fOutFileName.string();}
  std::string GetInputStem()const{return fInFileName.stem().string();}//return input filename without suffix and path
  std::string GetOutputStem()const{return fOutFileName.stem().string();}
  std::string GetInputExtension()const{return fInFileName.extension().string();}
  std::string GetOutputExtension()const{return fOutFileName.extension().string();}
  std::string GetOutFileKey()const{return fOutFileKey;}
  long  GetEntries(std::string TreePath)const;

private:
  DmpRootIOSvc();
  void CreateOutRootFile();

private:
typedef std::map<std::string, TTree*>  DmpRootIOTreeMap;                // key is "Tree"
typedef std::map<std::string, DmpRootIOTreeMap>  DmpRootIOFolderMap;    // key is "Folder"
#ifndef __CINT__
  boost::filesystem::path   fInFileName;        // include path
  boost::filesystem::path   fOutFileName;       // include path
#endif
  std::string               fOutFileKey;        // key word for the name of output root file
  std::string               fInPath;            // input file path
  std::string               fOutPath;           // output file path
  std::vector<std::string>  fWriteList;         // folderName/treeName
  TFile         *fInRootFile;
  TFile         *fOutRootFile;
  std::map<std::string,long>    fEntriesOfTree; // entries of each input event tree. key is "Folder/Tree"
  DmpRootIOFolderMap    fInTreeSet;     // input trees
  DmpRootIOFolderMap    fOutTreeSet;    // output trees
};

//-------------------------------------------------------------------
extern DmpRootIOSvc  *gRootIOSvc;

#endif


