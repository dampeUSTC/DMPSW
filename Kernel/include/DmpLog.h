/*
 *  $Id: DmpLog.h, 2014-06-27 10:49:29 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 19/05/2014
 *    Andrii Tykhonov (Andrii.Tykhonov@cern.ch) 22/05/2014
*/

#ifndef DmpLog_H
#define DmpLog_H

#include <iostream>
#include <iomanip>

namespace DmpLog{
  enum{
    NONE    = 0, //
    ERROR   = 1, // ERROR
    WARNING = 2, // ERROR, WARNING
    INFO    = 3, // ERROR, WARNING, INFO
    DEBUG   = 4  // ERROR, WARNING, INFO, DEBUG
  };

//-------------------------------------------------------------------
  void SetLogLevel(const std::string&);

//-------------------------------------------------------------------
  extern short  logLevel;
}

#define DmpLogDebug   if(DmpLog::logLevel >= DmpLog::DEBUG) \
  std::cout<<"  DEBUG:   ["<<__PRETTY_FUNCTION__<<"("<<__LINE__<<")"<<"]  "

#define DmpLogInfo    if(DmpLog::logLevel >= DmpLog::INFO)\
  std::cout<<"  INFO:    "

#define DmpLogWarning if(DmpLog::logLevel >= DmpLog::WARNING)\
  std::cout<<"  WARNING: "

#define DmpLogError if(DmpLog::logLevel >= DmpLog::ERROR)\
  std::cout<<"  ERROR:   "

#define DmpLogEndl std::endl

#endif


