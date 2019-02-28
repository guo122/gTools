//====================================================================
//  GToolsM.cpp
//  created 2.20.19
//  written by gzy
//
//  https://github.com/guo122
//====================================================================

#include <QMap>
#include <QSet>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

#include "GToolsM.h"

struct GToolsM::Impl
{
    Impl()
        : _DBPath("")
    {}

    bool Exec(const QString &sql_)
    {
        bool Result = false;
        QSqlDatabase tmpDB = QSqlDatabase::addDatabase("QSQLITE");
        if (!_DBPath.isEmpty())
        {
            tmpDB.setDatabaseName(_DBPath);
            Result = tmpDB.open();
            if (!Result)
            {
                qDebug() << tmpDB.lastError();
            }
        }

        if (Result)
        {
            QSqlQuery tmpDBQuery;
            Result = tmpDBQuery.exec(sql_);
            if (!Result)
            {
                qDebug() << tmpDBQuery.lastError();
            }
        }
        tmpDB.close();

        return Result;
    }

    bool Exec(const QString &sql_, QVector<QVector<QVariant>> &list_)
    {
        bool Result = false;
        QSqlDatabase tmpDB = QSqlDatabase::addDatabase("QSQLITE");

        if (!_DBPath.isEmpty())
        {
            tmpDB.setDatabaseName(_DBPath);
            Result = tmpDB.open();
            if (!Result)
            {
                qDebug() << tmpDB.lastError();
            }
        }

        if (Result)
        {
            QSqlQuery tmpDBQuery;
            Result = tmpDBQuery.exec(sql_);
            if (Result)
            {
                while (tmpDBQuery.next())
                {
                    QVector<QVariant> tmpList;
                    // todo
                    // 长度判断
                    for (int i = 0; i < 5; ++i)
                    {
                        tmpList.push_back(tmpDBQuery.value(i));
                    }
                    list_.push_back(tmpList);
                }
            }
            else
            {
                qDebug() << tmpDBQuery.lastError();
            }
        }
        tmpDB.close();

        return Result;
    }


    QVector<GTMRandomListPtr> _randomList;
    QMap<QString, QSet<QString> > _randomMapSet;
    QSet<QString> _randomKind;

    QString _DBPath;
};

GToolsM *GToolsM::Instance()
{
    static GToolsM * obj = new GToolsM;
    return obj;
}

GToolsM::GToolsM()
    : _Impl(new Impl)
{
}

GToolsM::~GToolsM()
{
    delete _Impl;
    _Impl = nullptr;
}

bool GToolsM::Init(const QString &DBPath)
{
    bool Result = false;
    _Impl->_DBPath = DBPath;
    QString tmpStr = "";

    GTMRandomList::GetSqlCreateTable(tmpStr);
    Result = _Impl->Exec(tmpStr);
    return Result;
}

void GToolsM::ReadDB()
{
    QVector<QVector<QVariant>> queryList;
    QString tmpStr;
    _Impl->_randomMapSet.clear();

    GTMRandomListPtr tmpRandomListPtr = nullptr;
    _Impl->_randomList.clear();
    GTMRandomList::GetSqlSelect(tmpStr);
    _Impl->Exec(tmpStr, queryList);

    for (const auto &x: queryList)
    {
        tmpRandomListPtr = std::make_shared<GTMRandomList>(x);
        _Impl->_randomList.push_back(tmpRandomListPtr);
        _Impl->_randomKind.insert(x[2].toString());
        _Impl->_randomMapSet[x[2].toString()].insert(x[1].toString());
    }
}

bool GToolsM::AddData(const GTMRandomListPtr &ptr_)
{
    bool Result = false;
    auto tmpK = _Impl->_randomKind.find(ptr_->_kind);
    if (tmpK == _Impl->_randomKind.end())
    {
        // 新kind
        Result = true;
    }
    if (!Result)
    {
        // 旧kind，判断name是否存在
        auto tmpN = _Impl->_randomMapSet[ptr_->_kind].find(ptr_->_name);
        if (tmpN == _Impl->_randomMapSet[ptr_->_kind].end())
        {
            // 新name
            Result = true;
        }
    }
    if (Result)
    {
        _Impl->_randomList.push_back(ptr_);
        QString tmpStr;
        ptr_->GetSqlInsert(tmpStr);
        Result = _Impl->Exec(tmpStr);
    }

    if (Result)
    {
        _Impl->_randomKind.insert(ptr_->_kind);
        _Impl->_randomMapSet[ptr_->_kind].insert(ptr_->_name);
    }

    return Result;
}

void GToolsM::GetData(QVector<GTMRandomListPtr> &list_)
{
    for (const auto &x: _Impl->_randomList)
    {
        list_.push_back(x);
    }
}

bool GToolsM::GetRandomListByKind(const QString &kind_, QStringList &list_)
{
    bool Result = false;
    list_.clear();
    if (_Impl->_randomKind.find(kind_) != _Impl->_randomKind.end())
    {
        Result = true;
        for (const auto &x: _Impl->_randomMapSet[kind_])
        {
            list_.push_back(x);
        }
    }
    return Result;
}

bool GToolsM::GetRandomKind(QStringList &kindList_)
{
    kindList_.clear();
    for (const auto &x: _Impl->_randomKind)
    {
        kindList_.push_back(x);
    }
    return !kindList_.isEmpty();
}
