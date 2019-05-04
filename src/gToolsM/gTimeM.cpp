//====================================================================
//  gTimeM.cpp
//  created 6.4.18
//  written by gzy
//
//  https://github.com/guo122
//====================================================================

#include "gTimeM.h"

bool gTimeM::_init = true;

gTimeM::gTimeM()
    : gMBase("gTimeM")
    , _offsetMinute(0)
    , _classify("")
    , _kindFirst("")
    , _kindSecond("")
    , _content("")
{
}

gTimeM::gTimeM(const gzy::gStringList &stringList)
    : gMBase("gTimeM")
    , _offsetMinute(0)
    , _classify("")
    , _kindFirst("")
    , _kindSecond("")
    , _content("")
{
    if (stringList.size() == 6)
    {
        _preId = _id = gStoI(stringList[0]);
        _offsetMinute = gStoI(stringList[1]);
        _classify = stringList[2];
        _kindFirst = stringList[3];
        _kindSecond = stringList[4];
        _content = stringList[5];
    }
}

void gTimeM::GetSqlCreateTable(gString &sql_)
{
    if (_init)
    {
        sql_ = "CREATE TABLE IF NOT EXISTS 'TimeTable' ("
               "'Id' integer PRIMARY KEY NOT NULL,"
               "'OffsetMinute' integer NOT NULL DEFAULT(0),"
               "'Classify' varchar(128) NOT NULL,"
               "'KindFirst' varchar(128) NOT NULL,"
               "'KindSecond' varchar(128) NOT NULL,"
               "'Content' varchar(128) NOT NULL);";
        _init = false;
    }
}

void gTimeM::GetSqlSelect(gString &sql_)
{
    GetSqlCreateTable(sql_);
    sql_ += "SELECT * FROM TimeTable";
}

void gTimeM::GetSqlDelete(gString &sql_, const int &id_)
{
    GetSqlCreateTable(sql_);
    sql_ += "DELETE FROM TimeTable WHERE Id='" + gToString(id_) + "';";
}

void gTimeM::GetSqlUpdate(gString &sql_)
{
    GetSqlCreateTable(sql_);
    sql_ += "UPDATE TimeTable SET "
            "Id='" + gToString(_id) +
            "',OffsetMinute='" + gToString(_offsetMinute) +
            "',Classify='" + _classify +
            "',KindFirst='" + _kindFirst +
            "',KindSecond='" + _kindSecond +
            "',Content='" + _content +
            "' where Id='" + gToString(_preId) + "';";
}

void gTimeM::GetSqlInsert(gString &sql_)
{
    GetSqlCreateTable(sql_);
    sql_ += "INSERT INTO TimeTable VALUES('" +
            gToString(_id) + "','" +
            gToString(_offsetMinute) + "','" +
            _classify + "','" +
            _kindFirst + "','" +
            _kindSecond + "','" +
            _content + "');";
}
