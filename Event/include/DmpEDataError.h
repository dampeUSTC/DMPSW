/*
 *  $Id: DmpEDataError.h, 2014-08-07 19:59:08 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 31/07/2014
*/

#ifndef DmpEDataError_H
#define DmpEDataError_H

namespace DmpEDataError{
  enum Type{
    Good = 0,
    NotFind_0xeb = 1,
    NotFind_0x90 = 2,
    DataLength_Wrong = 3,
    //Trigger_NotMatch = 4,
    //Trigger_Skip = 5,        // TODO how to check?
    CRC_Wrong = 6
  };
}

#endif

