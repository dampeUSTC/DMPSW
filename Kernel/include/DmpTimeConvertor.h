/*
 *  $Id: DmpTimeConvertor.h, 2014-10-27 19:39:09 DAMPE $
 *  Author(s):
 *    Zhiyong ZHANG (zhzhy@mail.ustc.edu.cn) 27/10/2014
*/

#ifndef DmpTimeConvertor_H
#define DmpTimeConvertor_H
#include <string>

namespace DmpTimeConvertor{

std::string Second2Date(const int &second);

int Date2Second(const std::string &date);

}

#endif

