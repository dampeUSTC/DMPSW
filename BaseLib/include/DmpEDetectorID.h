/*
 *  $Id: DmpEDetectorID.h, 2014-08-07 23:19:42 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 07/03/2014
*/

#ifndef DmpEDetectorID_H
#define DmpEDetectorID_H

namespace DmpEDetectorID{
  const short gSubDetNo=4;
  enum Type{
    kWhole = -1,
    kStk = 0,
    kBgo = 1,
    kPsd = 2,
    kNud = 3
  };
}

#endif


