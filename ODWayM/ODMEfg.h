//====================================================================
//  ODMEfg.h
//  created 7.17.18
//  written by odddd0
//
//  https://github.com/odddd0/ODWay
//====================================================================

#ifndef _ODMEFG_H_7CB4FE6BD9DAF64AFE1667A7DBABC610_
#define _ODMEFG_H_7CB4FE6BD9DAF64AFE1667A7DBABC610_

#include <ODMBase/ODMBase.h>
/**
 * @brief The ODMEfg struct
 */
struct ODMEfg : public ODMBase
{
    enum EfgState
    {
        Normal = 0,
        Hiden = 1
    };

public:
    ODMEfg();
    ODMEfg(const StringList &stringList);

public:
    static void GetSqlCreateTable(std::string &sql_);
    static void GetSqlSelect(std::string &sql_);
    static void GetSqlDelete(std::string &sql_, const int &id_);
    void GetSqlUpdate(std::string &sql_);
    void GetSqlInsert(std::string &sql_);

public:
    EfgState _state;
    std::string _name;
    std::string _classify;
    int _markTime;

private:
    static bool _init;
};
typedef std::shared_ptr<ODMEfg> ODMEfgPtr;

#endif // _ODMEFG_H_7CB4FE6BD9DAF64AFE1667A7DBABC610_
