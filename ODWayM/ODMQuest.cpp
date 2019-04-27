//====================================================================
//  ODMQuest.cpp
//  created 11.8.18
//  written by odddd0
//
//  https://github.com/odddd0/ODWay
//====================================================================

#include "ODMQuest.h"

bool ODMQuest::_init = true;

ODMQuest::ODMQuest()
    : ODMBase("ODMQuest")
    , _state(ODMQuest::QuestState::Normal)
    , _name("")
    , _deadLine(-1)
{
}

ODMQuest::ODMQuest(const StringList &stringList)
    : ODMBase("ODMQuest")
    , _state(ODMQuest::QuestState::Normal)
    , _name("")
    , _deadLine(-1)
{
    if (stringList.size() == 4)
    {
        _preId = _id = std::stoi(stringList[0]);
        _state = static_cast<ODMQuest::QuestState>(std::stoi(stringList[1]));
        _name = stringList[2];
        _deadLine = std::stoi(stringList[3]);
    }
}

void ODMQuest::GetSqlCreateTable(std::string &sql_)
{
    if (_init)
    {
        sql_ = "CREATE TABLE IF NOT EXISTS 'QuestTable' ("
               "'Id' integer PRIMARY KEY NOT NULL,"
               "'State' integer DEFAULT(0),"
               "'Name' varchar(128),"
               "'DeadLine' integer DEFAULT(-1));";
        _init = false;
    }
}

void ODMQuest::GetSqlSelect(std::string &sql_)
{
    GetSqlCreateTable(sql_);
    sql_ += "SELECT * FROM QuestTable";
}

void ODMQuest::GetSqlDelete(std::string &sql_, const int &id_)
{
    GetSqlCreateTable(sql_);
    sql_ += "DELETE FROM QuestTable WHERE Id='" + std::to_string(id_) + "';";
}

void ODMQuest::GetSqlUpdate(std::string &sql_)
{
    GetSqlCreateTable(sql_);
    sql_ += "UPDATE QuestTable SET "
            "Id='" + std::to_string(_id) +
            "',State='" + std::to_string(static_cast<int>(_state)) +
            "',Name='" + _name +
            "',DeadLine='" + std::to_string(_deadLine) +
            "' where Id='" + std::to_string(_preId) + "';";
}

void ODMQuest::GetSqlInsert(std::string &sql_)
{
    GetSqlCreateTable(sql_);
    sql_ += "INSERT INTO QuestTable VALUES('" +
            std::to_string(_id) + "','" +
            std::to_string(static_cast<int>(_state)) + "','" +
            _name + "','" +
            std::to_string(static_cast<int>(_deadLine)) + "');";
}
