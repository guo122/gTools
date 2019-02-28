//====================================================================
//  GTMRandomList.cpp
//  created 2.20.19
//  written by gzy
//
//  https://github.com/guo122
//====================================================================

#include "GTMRandomList.h"

GTMRandomList::GTMRandomList()
    : _preId(-1)
    , _id(-1)
    , _name("")
    , _kind("")
    , _lastReadDate(0)
    , _lastReadState(0)
{
    time_t curTime = 0;
    _preId = _id = time(&curTime);
}

GTMRandomList::GTMRandomList(const QVector<QVariant> &list_)
    : _preId(-1)
    , _id(-1)
    , _name("")
    , _kind("")
    , _lastReadDate(0)
    , _lastReadState(0)
{
    if (list_.size() == 5)
    {
        _preId = _id = list_[0].toInt();
        _name = list_[1].toString();
        _kind = list_[2].toString();
        _lastReadDate = list_[3].toDouble();
        _lastReadState = list_[4].toInt();
    }
}

void GTMRandomList::GetSqlCreateTable(QString &sql_)
{
    sql_ = "CREATE TABLE IF NOT EXISTS 'RandomList' ("
           "'Id' integer PRIMARY KEY NOT NULL,"
           "'Name' varchar(128),"
           "'Kind' varchar(128),"
           "'LastReadDate' integer DEFAULT(0),"
           "'LastReadState' integer DEFAULT(0));";
}

void GTMRandomList::GetSqlSelect(QString &sql_)
{
    sql_ += "SELECT * FROM RandomList";
}

void GTMRandomList::GetSqlDelete(QString &sql_, const int &id_)
{
    sql_ += "DELETE FROM RandomList WHERE Id='" + QString::number(id_) + "';";
}

void GTMRandomList::GetSqlUpdate(QString &sql_)
{
    GetSqlCreateTable(sql_);
    sql_ += "UPDATE RandomList SET "
            "Id='" + QString::number(_id) +
            "',Name='" + _name +
            "',Kind='" + _kind +
            "',LastReadDate='" + QString::number(_lastReadDate) +
            "',LastReadState='" + QString::number(_lastReadState) +
            "' where Id='" + QString::number(_preId) + "';";
}

void GTMRandomList::GetSqlInsert(QString &sql_)
{
    sql_ += "INSERT INTO RandomList VALUES('" +
            QString::number(_id) + "','" +
            _name + "','" +
            _kind + "','" +
            QString::number(_lastReadDate) + "','" +
            QString::number(_lastReadState) + "');";
}
