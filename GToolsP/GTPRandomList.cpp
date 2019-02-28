//====================================================================
//  GTPRandomList.cpp
//  created 2.20.18
//  written by gzy
//
//  https://github.com/guo122
//====================================================================

#include <QSet>
#include <QtDebug>

#include "GTPRandomList.h"

struct GTPRandomList::Impl
{
    Impl()
        : _lastSeed(0)
        , _lastI(-1)
        , _lastRandom("")
    {}

    int _lastSeed;
    int _lastI;
    QString _lastRandom;
    QVector<int> _randomMap;
    QStringList _lastStringList;
};

GTPRandomList *GTPRandomList::Instance()
{
    static GTPRandomList * obj = new GTPRandomList;
    return obj;
}

GTPRandomList::GTPRandomList()
    : _Impl(new Impl)
{
}

GTPRandomList::~GTPRandomList()
{
    delete _Impl;
    _Impl = nullptr;
}

bool GTPRandomList::AddData(const QString &name_, const QString &kind_)
{
    bool Result = false;
    if (!name_.isEmpty() && !kind_.isEmpty())
    {
        GTMRandomListPtr tmpPtr = std::make_shared<GTMRandomList>();
        tmpPtr->_name = name_;
        tmpPtr->_kind = kind_;
        Result = GToolsM::Instance()->AddData(tmpPtr);
    }
    return Result;
}

void GTPRandomList::GetKindList(QStringList &list_)
{
    GToolsM::Instance()->GetRandomKind(list_);
}

void GTPRandomList::GetNameList(const QString &kind_, QStringList &list_)
{
    GToolsM::Instance()->GetRandomListByKind(kind_, list_);
}

bool GTPRandomList::InitRandomList(const QString &kind_, const int &mode_)
{
    bool Result = false;
    _Impl->_lastStringList.clear();
    _Impl->_lastI = -1;
    _Impl->_randomMap.clear();
    if (GToolsM::Instance()->GetRandomListByKind(kind_, _Impl->_lastStringList))
    {
        Result = true;
        if (mode_ == 2)
        {
            _Impl->_lastI = 0;
            _Impl->_randomMap = QVector<int>(_Impl->_lastStringList.size(), -1);
            for (int i = 0; i < _Impl->_randomMap.size(); ++i)
            {
                srand(int(time(nullptr)) + _Impl->_lastSeed);
                // 生成randMap
                _Impl->_lastSeed = rand() % _Impl->_randomMap.size();

                if (_Impl->_lastSeed >= 0 && _Impl->_lastSeed < _Impl->_randomMap.size())
                {
                    while (_Impl->_randomMap[_Impl->_lastSeed] != -1)
                    {
                        _Impl->_lastSeed++;
                        if (_Impl->_lastSeed == _Impl->_randomMap.size())
                        {
                            _Impl->_lastSeed = 0;
                        }
                    }
                    _Impl->_randomMap[_Impl->_lastSeed] = i;
                }
            }
        }
    }
    return Result;
}

QString GTPRandomList::RandomData(const bool &forceRand)
{
    QString Result = _Impl->_lastRandom;
    if (_Impl->_lastI != -1 && forceRand != true)
    {
        int i;
        if (_Impl->_lastI >=0 && _Impl->_lastI < _Impl->_randomMap.size())
        {
            i = _Impl->_randomMap[_Impl->_lastI];
            if (i >= 0 && i < _Impl->_lastStringList.size())
            {
                Result = _Impl->_lastStringList[i];
                _Impl->_lastRandom = Result;
                _Impl->_lastI++;
            }
        }
    }
    else
    {
        if (_Impl->_lastStringList.size() > 0)
        {
            srand(int(time(nullptr)) + _Impl->_lastSeed);
            _Impl->_lastSeed = rand() % _Impl->_lastStringList.size();
            if (_Impl->_lastSeed >= 0 && _Impl->_lastSeed < _Impl->_lastStringList.size())
            {
                Result = _Impl->_lastStringList[_Impl->_lastSeed];
                if (!forceRand)
                {
                    _Impl->_lastRandom = Result;
                }
            }
        }
    }
    return Result;
}

int GTPRandomList::RandomDataFontSize()
{
    int Result = 0;
    if (_Impl->_lastRandom.size() <= 3)
    {
        Result = 150;
    }
    else if (_Impl->_lastRandom.size() > 3 && _Impl->_lastRandom.size() <= 10)
    {
        Result = 50;
    }
    else if (_Impl->_lastRandom.size() > 10 && _Impl->_lastRandom.size() <= 20)
    {
        Result = 30;
    }
    else if (_Impl->_lastRandom.size() > 20 && _Impl->_lastRandom.size() <= 30)
    {
        Result = 22;
    }
    else
    {
        Result = 22;
    }
    return Result;
}

int GTPRandomList::RandomDataProgress()
{
    int Result = 0;
    if (_Impl->_lastI == -1)
    {
        Result = -1;
    }
    else
    {
        if (_Impl->_lastStringList.size() == _Impl->_lastI)
        {
            Result = 100;
        }
        else
        {
            Result = (double)(_Impl->_lastI - 1) / (double)(_Impl->_lastStringList.size() - 1) * 100;
        }
    }
    return Result;
}
