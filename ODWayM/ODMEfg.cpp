//====================================================================
//  ODMEfg.cpp
//  created 7.17.18
//  written by odddd0
//
//  https://github.com/odddd0/ODWay
//====================================================================

#include "ODMEfg.h"

bool ODMEfg::_init = true;

ODMEfg::ODMEfg()
    : ODMBase("ODMEfg")
    , _state(ODMEfg::EfgState::Normal)
    , _name("")
    , _classify("")
    , _markTime(-1)
{
}

ODMEfg::ODMEfg(const StringList &stringList)
    : ODMBase("ODMEfg")
    , _state(ODMEfg::EfgState::Normal)
    , _name("")
    , _classify("")
    , _markTime(-1)
{
    if (stringList.size() == 5)
    {
        _preId = _id = std::stoi(stringList[0]);
        _state = static_cast<ODMEfg::EfgState>(std::stoi(stringList[1]));
        _name = stringList[2];
        _classify = stringList[3];
        _markTime = std::stoi(stringList[4]);
    }
}

void ODMEfg::GetSqlCreateTable(std::string &sql_)
{
    if (_init)
    {
        sql_ = "CREATE TABLE IF NOT EXISTS 'EfgTable' ("
               "'Id' integer PRIMARY KEY NOT NULL,"
               "'State' integer DEFAULT(0),"
               "'Name' varchar(128),"
               "'Classify' varchar(128),"
               "'MarkTime' integer DEFAULT(-1));";
        _init = false;
    }
}

void ODMEfg::GetSqlSelect(std::string &sql_)
{
    GetSqlCreateTable(sql_);
    sql_ += "SELECT * FROM EfgTable";
}

void ODMEfg::GetSqlDelete(std::string &sql_, const int &id_)
{
    GetSqlCreateTable(sql_);
    sql_ += "DELETE FROM EfgTable WHERE Id='" + std::to_string(id_) + "';";
}

void ODMEfg::GetSqlUpdate(std::string &sql_)
{
    GetSqlCreateTable(sql_);
    sql_ += "UPDATE EfgTable SET "
            "Id='" + std::to_string(_id) +
            "',State='" + std::to_string(static_cast<int>(_state)) +
            "',Name='" + _name +
            "',Classify='" + _classify +
            "',MarkTime='" + std::to_string(_markTime) +
            "' where Id='" + std::to_string(_preId) + "';";
}

void ODMEfg::GetSqlInsert(std::string &sql_)
{
    GetSqlCreateTable(sql_);
    sql_ += "INSERT INTO EfgTable VALUES('" +
            std::to_string(_id) + "','" +
            std::to_string(static_cast<int>(_state)) + "','" +
            _name + "','" +
            _classify + "','" +
            std::to_string(static_cast<int>(_markTime)) + "');";
}
