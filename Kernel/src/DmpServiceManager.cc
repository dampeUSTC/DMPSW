/*
 *  $Id: DmpServiceManager.cc, 2014-06-27 10:52:28 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 15/03/2014
*/

#include "DmpServiceManager.h"

//-------------------------------------------------------------------
DmpServiceManager::DmpServiceManager()
 :DmpElementManager<DmpVSvc>("Service manager")
{
  std::cout<<"===>  "<<Name()<<" created"<<std::endl;
}

//-------------------------------------------------------------------
DmpServiceManager::~DmpServiceManager(){
  std::cout<<"===>  "<<Name()<<" deleted"<<std::endl;
}

