/*
 *  $Id: DmpMetadata.h, 2014-10-03 20:03:20 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 01/10/2014
*/

#ifndef DmpMetadata_H
#define DmpMetadata_H

#include "TObject.h"
#include <map>

class DmpMetadata : public TObject{
/*
 *  Metadata for each Alg
 *
 */
public:
  DmpMetadata();
  ~DmpMetadata();
  DmpMetadata& operator=(const DmpMetadata &r);
  void Reset();
  void LoadFrom(DmpMetadata *r);

public:
  void PrintJobTime(const short &l=0)const;     // dd-mm-yy
  long JobTime()const{return Time;}
  short OptionSize()const{return CmdList.size();}
  void ListOptions()const;
  void SetOption(std::string path,const std::string &v);
  std::string GetCommand(const short &i)const{return CmdList.at(i);}
  bool HasCommand(std::string)const;      // whole command, or just a part of command
  std::string GetValue(const std::string&)const;
  std::string GetValue(const short &i)const;

private:
  long          Time;    // Time of this job
  std::map<std::string,std::string> Option;         // option map
  std::vector<std::string>          CmdList;        // order of command

  ClassDef(DmpMetadata,1)
};

#endif


