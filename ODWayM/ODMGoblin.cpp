//====================================================================
//  ODMGoblin.cpp
//  created 6.12.18
//  written by odddd0
//
//  https://github.com/odddd0/ODWay
//====================================================================

#include "ODMGoblin.h"

bool ODMGoblin::_init = true;

ODMGoblin::ODMGoblin()
    : ODMBase("ODMGoblin")
    , _state(0)
    , _month(0)
    , _rate(0)
    , _tips(0)
    , _amount(0)
{
}

ODMGoblin::ODMGoblin(const StringList &stringList)
    : ODMBase("ODMGoblin")
    , _state(0)
    , _month(0)
    , _rate(0)
    , _tips(0)
    , _amount(0)
{
    if (stringList.size() == 6)
    {
        _preId = _id = std::stoi(stringList[0]);
        _state = std::stoi(stringList[1]);
        _month = std::stoi(stringList[2]);
        _rate = std::stoi(stringList[3]);
        _tips = std::stoi(stringList[4]);
        _amount = std::stoi(stringList[5]);
    }
}

void ODMGoblin::GetSqlCreateTable(std::string &sql_)
{
    if (_init)
    {
        sql_ = "CREATE TABLE IF NOT EXISTS 'GoblinTable' ("
               "'Id' integer PRIMARY KEY NOT NULL,"
               "'State' integer DEFAULT(0),"
               "'Month' integer DEFAULT(0),"
               "'Rate' integer DEFAULT(0),"
               "'Tips' integer DEFAULT(0),"
               "'Amount' integer DEFAULT(0));";
        _init = false;
    }
}

void ODMGoblin::GetSqlSelect(std::string &sql_)
{
    GetSqlCreateTable(sql_);
    sql_ += "SELECT * FROM GoblinTable";
}

void ODMGoblin::GetSqlDelete(std::string &sql_, const int &id_)
{
    GetSqlCreateTable(sql_);
    sql_ += "DELETE FROM GoblinTable WHERE Id='" + std::to_string(id_) + "';";
}

void ODMGoblin::GetSqlUpdate(std::string &sql_)
{
    GetSqlCreateTable(sql_);
    sql_ += "UPDATE GoblinTable SET "
            "Id='" + std::to_string(_id) +
            "',State='" + std::to_string(_state) +
            "',Month='" + std::to_string(_month) +
            "',Rate='" + std::to_string(_rate) +
            "',Tips='" + std::to_string(_tips) +
            "',Amount='" + std::to_string(_amount) +
            "' where Id='" + std::to_string(_preId) + "';";
}

void ODMGoblin::GetSqlInsert(std::string &sql_)
{
    GetSqlCreateTable(sql_);
    sql_ += "INSERT INTO GoblinTable VALUES('" +
            std::to_string(_id) + "','" +
            std::to_string(_state) + "','" +
            std::to_string(_month) + "','" +
            std::to_string(_rate) + "','" +
            std::to_string(_tips) + "','" +
            std::to_string(_amount) + "');";
}
