/*
 *  $Id: DmpLog.h, 2014-09-27 11:15:18 DAMPE $
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
  void SetLogHeader(const std::string&);

//-------------------------------------------------------------------
  extern short  logLevel;
  extern bool   logHeader;
}

#define DmpLogCout std::cout<<"  "

#define DmpLogDebug   if(DmpLog::logLevel >= DmpLog::DEBUG) \
  std::cout<<"\033[37m  DEBUG:   \033[0m["<<__PRETTY_FUNCTION__<<"("<<__LINE__<<")"<<"]  "

#define DmpLogInfo    if(DmpLog::logLevel >= DmpLog::INFO)\
  std::cout<<"  INFO:    ["<<(DmpLog::logHeader? __PRETTY_FUNCTION__:"")<<"]  "

#define DmpLogWarning if(DmpLog::logLevel >= DmpLog::WARNING)\
  std::cout<<"  WARNING: ["<<(DmpLog::logHeader? __PRETTY_FUNCTION__:"")<<"]  "

#define DmpLogError if(DmpLog::logLevel >= DmpLog::ERROR)\
  std::cout<<"\033[31m  ERROR:   \033[0m["<<(DmpLog::logHeader? __PRETTY_FUNCTION__:"")<<"]  "

#define DmpLogEndl std::endl

#endif


