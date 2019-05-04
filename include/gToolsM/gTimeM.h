//====================================================================
//  gTimeM.h
//  created 6.4.18
//  written by gzy
//
//  https://github.com/guo122
//====================================================================

#ifndef GTIMEM_H_9BDC54BF1D2AE7E1C4FEB7E13176D8CC
#define GTIMEM_H_9BDC54BF1D2AE7E1C4FEB7E13176D8CC

#include <gBase/gDB.h>

struct gTimeM : public gzy::gMBase
{
public:
    gTimeM();
    gTimeM(const gzy::gStringList &stringList);

public:
    static void GetSqlCreateTable(gString &sql_);
    static void GetSqlSelect(gString &sql_);
    static void GetSqlDelete(gString &sql_, const int &id_);
    void GetSqlUpdate(gString &sql_);
    void GetSqlInsert(gString &sql_);

public:
    int _offsetMinute;
    gString _classify;
    gString _kindFirst;
    gString _kindSecond;
    gString _content;

private:
    static bool _init;
};
typedef gSharedPtr<gTimeM> gTimeMPtr;

#endif // GTIMEM_H_9BDC54BF1D2AE7E1C4FEB7E13176D8CC
