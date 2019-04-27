//====================================================================
//  ODVTime.cpp
//  created 6.5.18
//  written by odddd0
//
//  https://github.com/odddd0/ODWay
//====================================================================

#include <ODWayP/ODPTime.h>

#include "ODNotification.h"

#include "ODVTime.h"

ODVTime::ODVTime(QObject *parent) : QObject(parent)
{
    updateClass();
}

QStringList ODVTime::curList()
{
    return m_curList;
}

QStringList ODVTime::classifyList() const
{
    return m_classifyList;
}

QStringList ODVTime::kindFirstList() const
{
    return m_kindFirstList;
}

QStringList ODVTime::kindSecondList() const
{
    return m_kindSecondList;
}

QString ODVTime::runningTimeStr()
{
    std::string tmpStr = "";
    ODPTime::Instance()->GetRunningTimeStr(tmpStr);
    m_runningTimeStr = tmpStr.c_str();
    return m_runningTimeStr;
}

void ODVTime::setCKKCur(const QStringList ckkList_)
{
    _ckkList.clear();
    for (int i = 0; i < ckkList_.size(); ++i)
    {
        _ckkList.push_back(ckkList_[i].toStdString());
    }
}

void ODVTime::clearCKKCur()
{
    _ckkList.clear();
}

QList<int> ODVTime::getLastCKKSum(const int &lastDay_)
{
    QList<int> Result;
    IntList tmpList;
    ODPTime::Instance()->GetLastCKKSum(_ckkList, lastDay_, tmpList);
    std::for_each(tmpList.begin(), tmpList.end(), [&Result](int &x){
        Result.push_back(x);
    });
    return Result;
}

QStringList ODVTime::getLastCKKSumStr()
{
    QStringList Result;
    StringList tmpList;
    ODPTime::Instance()->GetLastCKKSum(tmpList);
    std::for_each(tmpList.begin(), tmpList.end(), [&Result](std::string &x){
        Result.push_back(QString::fromStdString(x));
    });
    return Result;
}

QString ODVTime::getCKKStr(const QString &defaultStr_)
{
    QString Result = defaultStr_;
    if (_ckkList.size() == 3)
    {
        Result = "";
        if (_ckkList[0] != "")
        {
            Result = QString::fromStdString(_ckkList[0]);
        }
        if (_ckkList[1] != "")
        {
            Result += "_" + QString::fromStdString(_ckkList[1]);
        }
        if (_ckkList[2] != "")
        {
            Result += "_" + QString::fromStdString(_ckkList[2]);
        }
    }
    return Result;
}

QString ODVTime::getLastCKKSumStrColor(const int &index_, const QString &defaultColor_)
{
    std::string tmpStr;
    if (!ODPTime::Instance()->GetLastCKKSumColor(index_, tmpStr))
    {
        tmpStr = defaultColor_.toStdString();
    }
    return QString::fromStdString(tmpStr);
}

bool ODVTime::isChartSumCurrentDay(const int &index_)
{
    return ODPTime::Instance()->IsChartSumCurrentDay(index_);
}

int ODVTime::getChartSumCurrentDayIndex()
{
    return ODPTime::Instance()->getChartSumCurrentIndex();
}

void ODVTime::selectChartSum(const int &index_)
{
    ODPTime::Instance()->SetDateByChartSum(index_);
}

QString ODVTime::getStartDate()
{
    return QString::fromStdString(ODPTime::Instance()->GetStartDate());
}

QString ODVTime::getEndDate()
{
    return QString::fromStdString(ODPTime::Instance()->GetEndDate());
}

bool ODVTime::addTime(
        const int &year_,
        const int &month_,
        const int &day_,
        const int &hour_,
        const int &minute_,
        const int &second_,
        const bool &customTime_,
        const QString &classify_,
        const QString &kindFirst_,
        const QString &kindSecond_,
        const QString &content_)
{
    bool Result = false;
    ODMTimePtr tmpPtr = std::make_shared<ODMTime>();
    tmpPtr->_classify = classify_.toStdString();
    tmpPtr->_kindFirst = kindFirst_.toStdString();
    tmpPtr->_kindSecond = kindSecond_.toStdString();
    tmpPtr->_content = content_.toStdString();
    if (customTime_)
    {
        struct tm tmpTm;
        tmpTm.tm_year = year_ - 1900;
        tmpTm.tm_mon = month_ - 1;
        tmpTm.tm_mday = day_;
        tmpTm.tm_hour = hour_;
        tmpTm.tm_min = minute_;
        tmpTm.tm_sec = second_;
        tmpTm.tm_isdst = 0;
        time_t lt = mktime(&tmpTm);
        tmpPtr->_id = lt;
    }
    Result = ODPTime::Instance()->AddTime(tmpPtr);
    if (Result)
    {
#ifdef Q_OS_IOS
        ODNotification_iOS::cancelAllNotifictions();
        ODNotification_iOS::pushNotifiction("STOP!!!", QDateTime::currentDateTime().addSecs(3600));
#endif
        updateClass();
    }
    return Result;
}

bool ODVTime::delTime(const int &index_)
{
    if (ODPTime::Instance()->DelDurTime(index_))
    {
        return true;
    }
}

QString ODVTime::calDurTime(const int &index1_, const int &index2_)
{
    std::string tmpStr = "";
    ODPTime::Instance()->CalDurTime(index1_, index2_, tmpStr);
    return QString::fromStdString(tmpStr);
}

bool ODVTime::fastIdle()
{

    if (ODPTime::Instance()->FastIdle())
    {
#ifdef Q_OS_IOS
        ODNotification_iOS::cancelAllNotifictions();
        ODNotification_iOS::pushNotifiction("STOP!!!", QDateTime::currentDateTime().addSecs(3600));
#endif
        updateClass();
        return true;
    }
    return false;
}

void ODVTime::setCurList(QStringList curList)
{
    if (m_curList == curList)
        return;

    m_curList = curList;
    emit curListChanged(m_curList);
}

void ODVTime::updateList()
{
    StringList tmpList;
    ODPTime::Instance()->GetCurList(tmpList);
    m_curList.clear();
    std::for_each(tmpList.begin(), tmpList.end(), [&](std::string &x){
        m_curList.push_back(x.c_str());
    });

    ODPTime::Instance()->GetPopList(_ckkList, _popList);
}

void ODVTime::updateClass()
{
    m_classifyList.clear();
    StringList tmpList;
    ODPTime::Instance()->GetClassifyList(tmpList);
    std::for_each(tmpList.begin(), tmpList.end(), [&](std::string &x){
        m_classifyList.push_back(x.c_str());
    });
    if (!m_classifyList.empty())
    {
        updateKindFirst(m_classifyList[0]);
    }

    if (!m_kindFirstList.empty())
    {
        updateKindSecond(m_classifyList[0], m_kindFirstList[0]);
    }
}

bool ODVTime::prevDay()
{
    return ODPTime::Instance()->PrevCur();
}

bool ODVTime::firstDay()
{
    return ODPTime::Instance()->FirstCur();
}

bool ODVTime::nextDay()
{
    return ODPTime::Instance()->NextCur();
}

bool ODVTime::lastDay()
{
    return ODPTime::Instance()->LastCur();
}

bool ODVTime::isPop(const int &index_)
{
    bool Result = false;
    for (auto x: _popList)
    {
        if (x == index_)
        {
            Result = true;
            break;
        }
    }
    return Result;
}

void ODVTime::updateKindFirst(QString classify_)
{
    m_kindFirstList.clear();
    StringList tmpList;
    ODPTime::Instance()->GetKindFirstList(tmpList, classify_.toStdString());
    std::for_each(tmpList.begin(), tmpList.end(), [&](std::string &x){
        m_kindFirstList.push_back(x.c_str());
    });
}

void ODVTime::updateKindSecond(QString classify_, QString kind_)
{
    m_kindSecondList.clear();
    StringList tmpList;
    ODPTime::Instance()->GetKindSecondList(tmpList, classify_.toStdString(), kind_.toStdString());
    std::for_each(tmpList.begin(), tmpList.end(), [&](std::string &x){
        m_kindSecondList.push_back(x.c_str());
    });
}

void ODVTime::setClassifyList(QStringList classifyList)
{
    if (m_classifyList == classifyList)
        return;

    m_classifyList = classifyList;
    emit classifyListChanged(m_classifyList);
}

void ODVTime::setKindFirstList(QStringList kindFirstList)
{
    if (m_kindFirstList == kindFirstList)
        return;

    m_kindFirstList = kindFirstList;
    emit kindFirstListChanged(m_kindFirstList);
}

void ODVTime::setKindSecondList(QStringList kindSecondList)
{
    if (m_kindSecondList == kindSecondList)
        return;

    m_kindSecondList = kindSecondList;
    emit kindSecondListChanged(m_kindSecondList);
}

void ODVTime::setRunningTimeStr(QString runningTimeStr)
{
    if (m_runningTimeStr == runningTimeStr)
        return;

    m_runningTimeStr = runningTimeStr;
    emit runningTimeStrChanged(m_runningTimeStr);
}
