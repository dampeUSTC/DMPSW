/*
 *  $Id: DmpElementManager.h, 2014-06-11 14:38:06 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 26/03/2014
*/

#ifndef DmpElementManager_H
#define DmpElementManager_H

#include <list>
#include <string>

template<typename DmpElement>       // DmpElement: DmpVAlgorithm, DmpVService

class DmpElementManager{
public:
  DmpElementManager(const std::string&);
  virtual ~DmpElementManager();

public:
  void Delete(const std::string&);
  void Append(DmpElement*);
  void ListAllElements();
  bool Initialize();
  bool Finalize();
  DmpElement* Get(const std::string&);

protected:
  const std::string& Name() const {return fName;}

protected:
  std::list<DmpElement*>    fElements;
  std::string               fName;

};


// define as below
//-------------------------------------------------------------------
#include <iostream>
template<typename DmpElement>
DmpElementManager<DmpElement>::DmpElementManager(const std::string &n)
 :fName(n)
{
  //std::cout<<"---> DmpCore:\tCreate "<<fName;
}

//-------------------------------------------------------------------
template<typename DmpElement>
DmpElementManager<DmpElement>::~DmpElementManager(){
        /*
  for(typename std::list<DmpElement*>::iterator it = fElements.begin();it != fElements.end();++it){
    std::cout<<"\tdelete "<<(*it)->Name()<<std::endl;;
    delete (*it);
  }
  */
  //std::cout<<"\t\tDone\n"<<std::endl;
}

//-------------------------------------------------------------------
template<typename DmpElement>
void DmpElementManager<DmpElement>::Delete(const std::string &name){
// *
// *  TODO: how to delete a element which was been created in python script
// *
  for(typename std::list<DmpElement*>::iterator it = fElements.begin();it != fElements.end();++it){
    if((*it)->Name() == name){
      std::cout<<"  ["<<fName<<"] Deleting element: "<<name<<std::endl;
      delete (*it);
      return;
    }
  }
}

//-------------------------------------------------------------------
template<typename DmpElement>
void DmpElementManager<DmpElement>::Append(DmpElement *aEle){
  std::cout<<"  ["<<fName<<"]\tAdding element: "<<aEle->Name()<<std::endl;
  fElements.push_back(aEle);
}

//-------------------------------------------------------------------
template<typename DmpElement>
void DmpElementManager<DmpElement>::ListAllElements(){
  std::cout<<"There are "<<fElements.size()<<" elements in "<<fName<<std::endl;;
  for(typename std::list<DmpElement*>::iterator it = fElements.begin();it != fElements.end();++it){
    std::cout<<"    name"<<(*it)->Name()<<std::endl;
  }
}

//-------------------------------------------------------------------
template<typename DmpElement>
bool DmpElementManager<DmpElement>::Initialize(){
  for(typename std::list<DmpElement*>::iterator it = fElements.begin();it != fElements.end();++it){
    if(not (*it)->Initialize()){
      std::cout<<"  ERROR:  ["<<fName<<"] Initialize "<<(*it)->Name()<<" failed"<<std::endl;
      return false;
    }
  }
  return true;
}

//-------------------------------------------------------------------
template<typename DmpElement>
bool DmpElementManager<DmpElement>::Finalize(){
  for(typename std::list<DmpElement*>::iterator it = fElements.begin();it != fElements.end();++it){
    if(not (*it)->Finalize()){
      std::cout<<"  ERROR:  ["<<fName<<"] Finalize "<<(*it)->Name()<<" failed"<<std::endl;
      // Do not need to return false
    }
  }
  return true;
}

//-------------------------------------------------------------------
template<typename DmpElement>
DmpElement* DmpElementManager<DmpElement>::Get(const std::string &n) {
  for(typename std::list<DmpElement*>::iterator it = fElements.begin();it != fElements.end();++it){
    if((*it)->Name() == n){
      return (*it);
    }
  }
  return 0;
}

#endif

