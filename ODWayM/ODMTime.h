//====================================================================
//  ODMTime.h
//  created 6.4.18
//  written by odddd0
//
//  https://github.com/odddd0/ODWay
//====================================================================

#ifndef _ODMTIME_H_9BDC54BF1D2AE7E1C4FEB7E13176D8CC_
#define _ODMTIME_H_9BDC54BF1D2AE7E1C4FEB7E13176D8CC_

#include <ODMBase/ODMBase.h>

struct ODMTime : public ODMBase
{
public:
    ODMTime();
    ODMTime(const StringList &stringList);

public:
    static void GetSqlCreateTable(std::string &sql_);
    static void GetSqlSelect(std::string &sql_);
    static void GetSqlDelete(std::string &sql_, const int &id_);
    void GetSqlUpdate(std::string &sql_);
    void GetSqlInsert(std::string &sql_);

public:
    int _offsetMinute;
    std::string _classify;
    std::string _kindFirst;
    std::string _kindSecond;
    std::string _content;

private:
    static bool _init;
};
typedef std::shared_ptr<ODMTime> ODMTimePtr;

#endif // _ODMTIME_H_9BDC54BF1D2AE7E1C4FEB7E13176D8CC_
