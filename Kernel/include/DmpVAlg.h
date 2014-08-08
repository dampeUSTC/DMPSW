/*
 *  $Id: DmpVAlg.h, 2014-07-08 14:42:53 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 22/03/2014
*/

#ifndef DmpVAlg_H
#define DmpVAlg_H

#include <map>
#include <string>
#include "DmpLog.h"

class DmpVAlg{
/*
 * DmpVAlg
 *
 *  drive yourself algorithm from this class, and then
 *  register your algorithm into Dmp Alorithm Manager, in python
 *
 */
public:
  DmpVAlg(const std::string &n):fName(n){}
  virtual ~DmpVAlg(){}
  virtual bool Initialize()=0;
  virtual bool ProcessThisEvent()=0;
  virtual bool Finalize()=0;
  virtual void Set(const std::string&,const std::string&){}    // for options, binding me

public:
  const std::string& Name() const {return fName;}

protected:
  std::map<std::string,short>   OptMap; // a map of set options

private:
  std::string   fName;

};

#endif

