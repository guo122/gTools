//====================================================================
//  ODVEfg.cpp
//  created 7.17.18
//  written by odddd0
//
//  https://github.com/odddd0/ODWay
//====================================================================

#include <ODWayP/ODPEfg.h>
#include <ODWayM/ODMEfg.h>

#include "ODVEfg.h"

ODVEfg::ODVEfg(QObject *parent)
    : QObject(parent)
{
}

QStringList ODVEfg::getEfgStrList()
{
    QStringList Result;
    StringList tmpList;
    ODPEfg::Instance()->GetEfgStrList(tmpList);
    std::for_each(tmpList.begin(), tmpList.end(), [&Result](std::string &x){
        Result.push_back(QString::fromStdString(x));
    });
    return Result;
}

QStringList ODVEfg::getEfgAllList()
{
    QStringList Result;
    StringList tmpList;
    ODPEfg::Instance()->GetEfgAllList(tmpList);
    std::for_each(tmpList.begin(), tmpList.end(), [&Result](std::string &x){
        Result.push_back(QString::fromStdString(x));
    });
    return Result;
}

bool ODVEfg::markIndex(const int &index_)
{
    return ODPEfg::Instance()->MarkIndex(index_);
}

bool ODVEfg::unMarkIndex(const int &index_)
{
        return ODPEfg::Instance()->UnMarkIndex(index_);
}

QString ODVEfg::getEfgColor(const int &index_, const QString &defaultColor_)
{
    std::string tmpStr;
    if (!ODPEfg::Instance()->GetEfgAllColor(index_, tmpStr))
    {
        tmpStr = defaultColor_.toStdString();
    }
    return QString::fromStdString(tmpStr);
}

QString ODVEfg::getProgressStr()
{
    std::string tmpStr = "";
    ODPEfg::Instance()->GetProgressStr(tmpStr);
    return QString::fromStdString(tmpStr);
}

