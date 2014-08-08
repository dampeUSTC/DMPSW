/*
 *  $Id: DmpVSvc.h, 2014-07-08 14:43:05 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 10/04/2014
*/

#ifndef DmpVSvc_H
#define DmpVSvc_H

#include <map>
#include <string>
#include "DmpLog.h"

class DmpVSvc{
/*
 *  DmpVSvc
 *
 *      all service derived from this class, and then
 *      append into Dmp Service Manager, in python
 *
 */
public:
  DmpVSvc(const std::string &n):fName(n){}
  virtual ~DmpVSvc(){}
  virtual bool Initialize()=0;
  virtual bool Finalize()=0;

public:
  virtual void Set(const std::string&,const std::string&){}    // for global options, binding me

public:
  const std::string& Name() const {return fName;}

protected:
  std::map<std::string,short>   OptMap; // a map of set options

private:
  std::string   fName;

};

#endif


