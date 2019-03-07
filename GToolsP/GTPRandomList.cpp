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

int GTPRandomList::_StaticSeed = rand();

struct GTPRandomList::Impl
{
    Impl()
        : _lastRandom("")
    {}

    AutoRandomList _planAuto;
    AutoRandomList _homepageAuto;
    QString _lastRandom;
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
    if (GToolsM::Instance()->GetRandomListByKind(kind_, _Impl->_lastStringList))
    {
        Result = true;
        if (mode_ == 1)
        {
            _Impl->_planAuto.clear();
        }
        else
        {
            _Impl->_planAuto.init(_Impl->_lastStringList.size(), true);
        }
        _Impl->_homepageAuto.init(_Impl->_lastStringList.size(), true);
    }
    return Result;
}

QString GTPRandomList::RandomData(const bool &forceRand)
{
    QString Result = _Impl->_lastRandom;
    if (!_Impl->_planAuto.empty() && forceRand != true)
    {
        int i = _Impl->_planAuto.next();
        if (i >=0 && i < _Impl->_lastStringList.size())
        {
            Result = _Impl->_lastStringList[i];
            _Impl->_lastRandom = Result;
        }
    }
    else
    {
        if (_Impl->_lastStringList.size() > 0)
        {
            int curRand = 0;
            srand(int(time(nullptr)) + _StaticSeed);
            curRand = _StaticSeed = rand();
            curRand %= _Impl->_lastStringList.size();
            if (curRand >= 0 && curRand < _Impl->_lastStringList.size())
            {
                Result = _Impl->_lastStringList[curRand];
                if (!forceRand)
                {
                    _Impl->_lastRandom = Result;
                }
            }
        }
    }
    return Result;
}

QString GTPRandomList::HomepageRandom()
{
    QString Result = "";
    if (!_Impl->_homepageAuto.empty())
    {
        int i = _Impl->_homepageAuto.next();
        if (i >=0 && i < _Impl->_lastStringList.size())
        {
            Result = _Impl->_lastStringList[i];
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
    return _Impl->_planAuto.getProgress();
}

void GTPRandomList::AutoRandomList::init(const int &num_, const bool &unlimit_)
{
    if (num_ > 0)
    {
        _cur = -1;
        _unlimit = unlimit_;
        int curRand = 0;
        _list = QVector<int>(num_, -1);
        for (int i = 0; i < num_; ++i)
        {
            srand(int(time(nullptr)) + _StaticSeed);
            curRand = _StaticSeed = rand();
            curRand %= num_;

            if (curRand >= 0 && curRand < num_)
            {
                while (_list[curRand] != -1)
                {
                    curRand++;
                    if (curRand == num_)
                    {
                        curRand = 0;
                    }
                }
                _list[curRand] = i;
            }
        }
    }
}

void GTPRandomList::AutoRandomList::clear()
{
    _list.clear();
    _cur = -1;
    _unlimit = false;
}

int GTPRandomList::AutoRandomList::next()
{
    int Result = -1;
    if (!_list.empty() && _cur >= -1)
    {
        ++_cur;
        if (_cur >= _list.size())
        {
            if (_unlimit)
            {
                init(_list.size(), true);
                _cur = 0;
            }
            else
            {
                _cur = _list.size() - 1;
            }
        }
        Result = _list[_cur];
    }
    return Result;
}

bool GTPRandomList::AutoRandomList::empty()
{
    return _list.empty();
}

int GTPRandomList::AutoRandomList::getProgress()
{
    int Result = -1;
    if (!_list.empty() && _cur >= 0)
    {
        if (_list.size() == _cur + 1)
        {
            Result = 100;
        }
        else
        {
            Result = (double)(_cur) / (double)(_list.size() - 1) * 100;
        }
    }
    return Result;
}

int GTPRandomList::AutoRandomList::getIndex()
{
    int Result = -1;
    if (_cur >= 0 && _cur < _list.size())
    {
        Result = _list[_cur];
    }
    return Result;
}
