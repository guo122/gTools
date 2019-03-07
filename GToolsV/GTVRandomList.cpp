//====================================================================
//  GTVRandomList.cpp
//  created 2.20.19
//  written by gzy
//
//  https://github.com/guo122
//====================================================================

#include <GToolsP/GTPRandomList.h>

#include "GTVRandomList.h"

GTVRandomList::GTVRandomList(QObject *parent)
    : QObject(parent)
{
}

QString GTVRandomList::getDescription(const QString &name_)
{
    QString Result = "";
    if (name_ == "Random")
    {
        Result = GTPRandomList::Instance()->HomepageRandom();
    }
    return Result;
}

bool GTVRandomList::initRandomList(const QString &kind_, const int &mode_)
{
    return GTPRandomList::Instance()->InitRandomList(kind_, mode_);
}

QString GTVRandomList::getRandom()
{
    return GTPRandomList::Instance()->RandomData();
}

int GTVRandomList::getRandomFontSize()
{
    return GTPRandomList::Instance()->RandomDataFontSize();
}

int GTVRandomList::getRandomProgress()
{
    return GTPRandomList::Instance()->RandomDataProgress();
}

bool GTVRandomList::addData(const QString &name_, const QString &kind_)
{
    return GTPRandomList::Instance()->AddData(name_, kind_);
}

QStringList GTVRandomList::getKindList()
{
    QStringList Result;
    GTPRandomList::Instance()->GetKindList(Result);
    return Result;
}

int GTVRandomList::getKindSize()
{
    QStringList tmpList;
    GTPRandomList::Instance()->GetKindList(tmpList);
    return tmpList.size();
}

QStringList GTVRandomList::getNameList(const QString &kind_)
{
    QStringList Result;
    GTPRandomList::Instance()->GetNameList(kind_, Result);
    return Result;
}
