/*
 *  $Id: DmpTimeConvertor.h, 2014-10-27 19:39:09 DAMPE $
 *  Author(s):
 *    Zhiyong ZHANG (zhzhy@mail.ustc.edu.cn) 27/10/2014
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 28/10/2014
*/

#include <time.h>
#include <stdio.h>
#include <sstream>
#include "DmpTimeConvertor.h"

namespace DmpTimeConvertor{

std::string Second2Date(const int &second){
//  struct tm DatT0={0,0,0,1,0,113,1,0,-1};//{sec,min,hour,mday(1-31),mon(0-11),year(real-1900),wday(0-6),yday(0-365),isdst(+,0,-)}
  //conminder time zone
  struct tm DatT0={0,0,8,1,0,113,1,0,-1};//{sec,min,hour,mday(1-31),mon(0-11),year(real-1900),wday(0-6),yday(0-365),isdst(+,0,-)}
  time_t Astime0=mktime(&DatT0);
  time_t Astime1=Astime0+second;
  struct tm *DatT=gmtime(&Astime1);
  int year=DatT->tm_year+1900;
  int month=DatT->tm_mon+1;
  int day=DatT->tm_mday;
  int hour=DatT->tm_hour;
  int min=DatT->tm_min;
  int sec=DatT->tm_sec;
  //char* date=(char*)malloc(30);
  char date[50];
//  char* date=new char[30];
  snprintf(date,50,"%d/%02d/%02d %02d:%02d:%02d",year,month,day,hour,min,sec);
  return (std::string)date;
}

int Date2Second(const std::string &date){
  struct tm DatT;
//time YYYY-MM-DD HH:MM:SS
  std::string tmp = date.substr(0,4)+" "+date.substr(5,2)+" "+date.substr(8,2)+" "+date.substr(11,2)+" "+date.substr(14,2)+" "+date.substr(17,2);
  std::istringstream iss(tmp);
  int year,month,day,hour,min,sec;
  iss>>year>>month>>day>>hour>>min>>sec;
  DatT.tm_year=year-1900;
  DatT.tm_mon=month-1;
  DatT.tm_mday=day;
  DatT.tm_hour=hour;
  DatT.tm_min=min;
  DatT.tm_sec=sec;
  time_t Astime1=mktime(&DatT);
  struct tm DatT0={0,0,0,1,0,113,1,0,-1};//{sec,min,hour,mday(1-31),mon(0-11),year(real-1900),wday(0-6),yday(0-365),isdst(+,0,-)}
  time_t Astime0=mktime(&DatT0);
  int Astime=(int)difftime(Astime1,Astime0);

  return Astime;
}

}


