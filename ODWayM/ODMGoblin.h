//====================================================================
//  ODMGoblin.h
//  created 6.12.18
//  written by odddd0
//
//  https://github.com/odddd0/ODWay
//====================================================================

#ifndef _ODMGOBLIN_H_F9BD27BFA65BDF45C7B8F9C567C4DAA5_
#define _ODMGOBLIN_H_F9BD27BFA65BDF45C7B8F9C567C4DAA5_

#include <ODMBase/ODMBase.h>
/**
 * @brief The ODMGoblin struct
 *      !!! 12.22(double) -> 1222(int)
 */
struct ODMGoblin : public ODMBase
{
public:
    ODMGoblin();
    ODMGoblin(const StringList &stringList);

public:
    static void GetSqlCreateTable(std::string &sql_);
    static void GetSqlSelect(std::string &sql_);
    static void GetSqlDelete(std::string &sql_, const int &id_);
    void GetSqlUpdate(std::string &sql_);
    void GetSqlInsert(std::string &sql_);

public:
    int _state;
    int _month;
    int _rate;
    int _tips;
    int _amount;

private:
    static bool _init;
};
typedef std::shared_ptr<ODMGoblin> ODMGoblinPtr;

#endif // _ODMGOBLIN_H_F9BD27BFA65BDF45C7B8F9C567C4DAA5_
