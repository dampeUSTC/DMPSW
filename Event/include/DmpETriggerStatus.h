/*
 *  $Id: DmpETriggerStatus.h, 2014-08-07 20:00:23 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 07/08/2014
*/

#ifndef DmpETriggerStatus_H
#define DmpETriggerStatus_H

namespace DmpETriggerStatus{
  enum Type{
    kNoCheck = 0,       // did not receive check signal
    kCheckRight = 1,    // received check signal, and checked right
    kCheckWrong = 2,    // received check signal, and checked, but wrong
    kUnknow = 3         // unknow
  };
}

#endif

