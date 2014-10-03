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
  DmpMetadata(std::string whichAlgorithm);
  ~DmpMetadata();
  void PrintJobTime(const short &l=0)const;     // dd-mm-yy
  void SetOption(const std::string &path,const std::string &v);

public:
  std::string   AlgName;    // which algorithm created me
  long          JobTime;    // Time of this job
  std::map<std::string,std::string> Option;         // option map

  ClassDef(DmpMetadata,1)
};

#endif


