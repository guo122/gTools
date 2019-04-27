//====================================================================
//  ODMTime.cpp
//  created 6.4.18
//  written by odddd0
//
//  https://github.com/odddd0/ODWay
//====================================================================

#include "ODMTime.h"

bool ODMTime::_init = true;

ODMTime::ODMTime()
    : ODMBase("ODMTime")
    , _offsetMinute(0)
    , _classify("")
    , _kindFirst("")
    , _kindSecond("")
    , _content("")
{
}

ODMTime::ODMTime(const StringList &stringList)
    : ODMBase("ODMTime")
    , _offsetMinute(0)
    , _classify("")
    , _kindFirst("")
    , _kindSecond("")
    , _content("")
{
    if (stringList.size() == 6)
    {
        _preId = _id = std::stoi(stringList[0]);
        _offsetMinute = std::stoi(stringList[1]);
        _classify = stringList[2];
        _kindFirst = stringList[3];
        _kindSecond = stringList[4];
        _content = stringList[5];
    }
}

void ODMTime::GetSqlCreateTable(std::string &sql_)
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

void ODMTime::GetSqlSelect(std::string &sql_)
{
    GetSqlCreateTable(sql_);
    sql_ += "SELECT * FROM TimeTable";
}

void ODMTime::GetSqlDelete(std::string &sql_, const int &id_)
{
    GetSqlCreateTable(sql_);
    sql_ += "DELETE FROM TimeTable WHERE Id='" + std::to_string(id_) + "';";
}

void ODMTime::GetSqlUpdate(std::string &sql_)
{
    GetSqlCreateTable(sql_);
    sql_ += "UPDATE TimeTable SET "
            "Id='" + std::to_string(_id) +
            "',OffsetMinute='" + std::to_string(_offsetMinute) +
            "',Classify='" + _classify +
            "',KindFirst='" + _kindFirst +
            "',KindSecond='" + _kindSecond +
            "',Content='" + _content +
            "' where Id='" + std::to_string(_preId) + "';";
}

void ODMTime::GetSqlInsert(std::string &sql_)
{
    GetSqlCreateTable(sql_);
    sql_ += "INSERT INTO TimeTable VALUES('" +
            std::to_string(_id) + "','" +
            std::to_string(_offsetMinute) + "','" +
            _classify + "','" +
            _kindFirst + "','" +
            _kindSecond + "','" +
            _content + "');";
}
