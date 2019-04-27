//====================================================================
//  ODMGoblinCoin.cpp
//  created 6.12.18
//  written by odddd0
//
//  https://github.com/odddd0/ODWay
//====================================================================

#include "ODMGoblinCoin.h"

bool ODMGoblinCoin::_init = true;

ODMGoblinCoin::ODMGoblinCoin()
    : ODMBase("ODMGoblinCoin")
    , _state(ODMGoblinCoin::GoblinState::SimplePay)
    , _goldFrom("")
    , _bill(0)
    , _classify("")
    , _kindFirst("")
    , _kindSecond("")
    , _count(0)
    , _countSecond(0)
    , _revokeId(0)
    , _content("")
{
}

ODMGoblinCoin::ODMGoblinCoin(const StringList &stringList)
    : ODMBase("ODMGoblinCoin")
    , _state(ODMGoblinCoin::GoblinState::SimplePay)
    , _goldFrom("")
    , _bill(0)
    , _classify("")
    , _kindFirst("")
    , _kindSecond("")
    , _count(0)
    , _countSecond(0)
    , _revokeId(0)
    , _content("")
{
    if (stringList.size() == 11)
    {
        _preId = _id = std::stoi(stringList[0]);
        _state = static_cast<ODMGoblinCoin::GoblinState>(std::stoi(stringList[1]));
        _goldFrom = stringList[2];
        _bill = std::stoi(stringList[3]);
        _classify = stringList[4];
        _kindFirst = stringList[5];
        _kindSecond = stringList[6];
        _count = std::stoi(stringList[7]);
        _countSecond = std::stoi(stringList[8]);
        _revokeId = std::stoi(stringList[9]);
        _content = stringList[10];
    }
}

void ODMGoblinCoin::GetSqlCreateTable(std::string &sql_)
{
    if (_init)
    {
        sql_ = "CREATE TABLE IF NOT EXISTS 'GoblinCoinTable' ("
               "'Id' integer PRIMARY KEY NOT NULL,"
               "'State' integer DEFAULT(0),"
               "'GoldFrom' varchar(128),"
               "'Bill' integer DEFAULT(0),"
               "'Classify' varchar(128),"
               "'KindFirst' varchar(128),"
               "'KindSecond' varchar(128),"
               "'Count' integer DEFAULT(0),"
               "'CountSecond' integer DEFAULT(0),"
               "'RevokeID' integer DEFAULT(0),"
               "'Content' varchar(128));";
        _init = false;
    }
}

void ODMGoblinCoin::GetSqlSelect(std::string &sql_)
{
    GetSqlCreateTable(sql_);
    sql_ += "SELECT * FROM GoblinCoinTable";
}

void ODMGoblinCoin::GetSqlDelete(std::string &sql_, const int &id_)
{
    GetSqlCreateTable(sql_);
    sql_ += "DELETE FROM GoblinCoinTable WHERE Id='" + std::to_string(id_) + "';";
}

void ODMGoblinCoin::GetSqlUpdate(std::string &sql_)
{
    GetSqlCreateTable(sql_);
    sql_ += "UPDATE GoblinCoinTable SET "
            "Id='" + std::to_string(_id) +
            "',State='" + std::to_string(static_cast<int>(_state)) +
            "',GoldFrom='" + _goldFrom +
            "',Bill='" + std::to_string(_bill) +
            "',Classify='" + _classify +
            "',KindFirst='" + _kindFirst +
            "',KindSecond='" + _kindSecond +
            "',Count='" + std::to_string(_count) +
            "',CountSecond='" + std::to_string(_countSecond) +
            "',RevokeID='" + std::to_string(_revokeId) +
            "',Content='" + _content +
            "' where Id='" + std::to_string(_preId) + "';";
}

void ODMGoblinCoin::GetSqlInsert(std::string &sql_)
{
    GetSqlCreateTable(sql_);
    sql_ += "INSERT INTO GoblinCoinTable VALUES('" +
            std::to_string(_id) + "','" +
            std::to_string(static_cast<int>(_state)) + "','" +
            _goldFrom + "','" +
            std::to_string(_bill) + "','" +
            _classify + "','" +
            _kindFirst + "','" +
            _kindSecond + "','" +
            std::to_string(_count) + "','" +
            std::to_string(_countSecond) + "','" +
            std::to_string(_revokeId) + "','" +
            _content + "');";
}
