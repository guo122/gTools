//====================================================================
//  ODMTest.h
//  created 6.3.18
//  written by odddd0
//
//  https://github.com/odddd0/ODWay
//====================================================================

#ifndef _ODMTEST_H_DFBE097664D21A52ED9E1AFF37C5B121_
#define _ODMTEST_H_DFBE097664D21A52ED9E1AFF37C5B121_

#include "ODMBase.h"

struct ODMTest : public ODMBase
{
public:
    ODMTest();
    ODMTest(const StringList &stringList);

public:
    static void GetSqlCreateTable(std::string &sql_);
    static void GetSqlSelect(std::string &sql_);
    static void GetSqlDelete(std::string &sql_, const int &id_);
    void GetSqlUpdate(std::string &sql_);
    void GetSqlInsert(std::string &sql_);

public:
    std::string _name;
    int _score;

private:
    static bool _init;
};
typedef std::shared_ptr<ODMTest> ODMTestPtr;

#endif // _ODMTEST_H_DFBE097664D21A52ED9E1AFF37C5B121_
