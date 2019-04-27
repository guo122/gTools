//====================================================================
//  ODSqliteHandle.h
//  created 6.3.18
//  written by odddd0
//
//  https://github.com/odddd0/ODWay
//====================================================================

#ifndef _ODSQLITEHANDLE_H_6BC0E607E9DCA3298DCD458978C18C34_
#define _ODSQLITEHANDLE_H_6BC0E607E9DCA3298DCD458978C18C34_

#include "ODBaseTypes.h"

class ODSqliteHandle
{
public:
    ODSqliteHandle();

public:
    static bool Exec(
            const std::string &DBPath,
            const std::string &Sql,
            StringTable &ResStringTable,
            std::string &ErrMsg)
    {
        return ExecImpl(DBPath, Sql, ResStringTable, ErrMsg);
    }

    static bool Exec(
            const std::string &DBPath,
            const std::string &Sql,
            std::string &ErrMsg)
    {
        StringTable stringTable;
        return ExecImpl(DBPath, Sql, stringTable, ErrMsg);
    }

private:
    static bool ExecImpl(
            const std::string &DBPath,
            const std::string &Sql,
            StringTable &ResStringTable,
            std::string &ErrMsg);
};

#endif // _ODSQLITEHANDLE_H_6BC0E607E9DCA3298DCD458978C18C34_
