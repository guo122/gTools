//====================================================================
//  ODPEfg.cpp
//  created 7.17.18
//  written by odddd0
//
//  https://github.com/odddd0/ODWay
//====================================================================

#include <ODWayM/ODWayM.h>

#include <ODUtil/ODUtil.h>

#include "ODPEfg.h"

struct ODPEfg::Impl
{
    Impl(){}

    void ExpandData()
    {
        _expandData.clear();

        ODMBaseList tmpList;
        ODWayM::Instance()->GetList("ODMEfg", tmpList);

        ODMEfgPtr cur = NULL;
        OneTipPtr tmpTip = NULL;

        std::for_each(tmpList.cbegin(), tmpList.cend(), [&](const ODMBasePtr &x){
            cur = std::static_pointer_cast<ODMEfg>(x);
            _expandData._totalNum++;

            if (ODVectorUtil::RefreshInsert<std::string>(_expandData._classifyList, cur->_classify))
            {
                _expandData._classifyIsMap[cur->_classify] = 0;
            }
            tmpTip = std::make_shared<OneTip>();
            _expandData._tipList.push_back(tmpTip);

            tmpTip->_id = cur->_id;
            tmpTip->_state = cur->_state;
            tmpTip->_name = cur->_name;
            tmpTip->_classify = cur->_classify;
            tmpTip->_markTime = cur->_markTime;

            time_t curTime = 0;
            time(&curTime);

            if (ODTimeUtil::IsSameDay(cur->_markTime, curTime))
            {
                _expandData._markNum++;
            }
            else
            {
                _expandData._classifyIsMap[cur->_classify] = 1;
            }
        });

        std::sort(_expandData._tipList.begin(), _expandData._tipList.end(), [](OneTipPtr &x, OneTipPtr &y){
            return x->_classify > y->_classify;
        });
    }

    ODPEfg::ExpandData _expandData;
};

ODPEfg *ODPEfg::Instance()
{
    static ODPEfg * obj = new ODPEfg;
    return obj;
}

void ODPEfg::GetEfgStrList(StringList &strList_)
{
    std::string lastClassify = "";

    strList_.clear();
    _Impl->_expandData._lastEfgIdList.clear();
    _Impl->_expandData._lastEfgAllColorList.clear();

    std::for_each(_Impl->_expandData._tipList.begin(), _Impl->_expandData._tipList.end(), [&](OneTipPtr &x){
        if (lastClassify != x->_classify && _Impl->_expandData._classifyIsMap[x->_classify] == 1)
        {
            if (!lastClassify.empty())
            {
                strList_.push_back("");
                _Impl->_expandData._lastEfgIdList.push_back(-1);
                _Impl->_expandData._lastEfgAllColorList.push_back("black");
            }
            lastClassify = x->_classify;
            strList_.push_back(" -" + lastClassify + "-");
            _Impl->_expandData._lastEfgIdList.push_back(-1);
            _Impl->_expandData._lastEfgAllColorList.push_back("black");
        }

        time_t curTime = 0;
        time(&curTime);

        if (!ODTimeUtil::IsSameDay(x->_markTime, curTime))
        {
            strList_.push_back(x->_name);
            _Impl->_expandData._lastEfgIdList.push_back(x->_id);
            _Impl->_expandData._lastEfgAllColorList.push_back("red");
        }
    });
}

void ODPEfg::GetEfgAllList(StringList &strList_)
{
    std::string lastClassify = "";

    strList_.clear();
    _Impl->_expandData._lastEfgIdList.clear();
    _Impl->_expandData._lastEfgAllColorList.clear();

    std::for_each(_Impl->_expandData._tipList.begin(), _Impl->_expandData._tipList.end(), [&](OneTipPtr &x){
        if (lastClassify != x->_classify)
        {
            if (!lastClassify.empty())
            {
                strList_.push_back("");
                _Impl->_expandData._lastEfgIdList.push_back(-1);
                _Impl->_expandData._lastEfgAllColorList.push_back("black");
            }
            lastClassify = x->_classify;
            strList_.push_back(" -" + lastClassify + "-");
            _Impl->_expandData._lastEfgIdList.push_back(-1);
            _Impl->_expandData._lastEfgAllColorList.push_back("black");
        }

        time_t curTime = 0;
        time(&curTime);

        if (!ODTimeUtil::IsSameDay(x->_markTime, curTime))
        {
            strList_.push_back(x->_name);
            _Impl->_expandData._lastEfgAllColorList.push_back("red");
        }
        else
        {
            strList_.push_back("(done)" + x->_name);
            _Impl->_expandData._lastEfgAllColorList.push_back("green");
        }
        _Impl->_expandData._lastEfgIdList.push_back(x->_id);
    });
}

void ODPEfg::GetProgressStr(std::string &str_)
{
    if (_Impl->_expandData._markNum == _Impl->_expandData._totalNum)
    {
        str_ = "done";
    }
    else
    {
        str_ = std::to_string(_Impl->_expandData._markNum) + "/" + std::to_string(_Impl->_expandData._totalNum);
    }
}

bool ODPEfg::GetEfgAllColor(const int &index_, std::string &color_)
{
    bool Result = false;
    color_ = "black";
    if (index_ >= 0 && index_ < _Impl->_expandData._lastEfgAllColorList.size())
    {
        color_ = _Impl->_expandData._lastEfgAllColorList[index_];
        Result = true;
    }
    return Result;
}

bool ODPEfg::MarkIndex(const int &index_)
{
    bool Result = false;
    if (index_ >= 0 && index_ < _Impl->_expandData._lastEfgIdList.size())
    {
        if (_Impl->_expandData._lastEfgIdList[index_] >= 0)
        {
            time_t curTime = 0;
            time(&curTime);

            ODMBasePtr tmpPtr;
            ODWayM::Instance()->GetPtr("ODMEfg", _Impl->_expandData._lastEfgIdList[index_], tmpPtr);
            if (tmpPtr)
            {
                std::static_pointer_cast<ODMEfg>(tmpPtr)->_markTime = curTime;
                Result = ODWayM::Instance()->UpdateModel(tmpPtr);
                if (Result)
                {
                    _Impl->ExpandData();
                }
            }
        }
    }
    return Result;
}

bool ODPEfg::UnMarkIndex(const int &index_)
{
    bool Result = false;
    if (index_ >= 0 && index_ < _Impl->_expandData._lastEfgIdList.size())
    {
        if (_Impl->_expandData._lastEfgIdList[index_] >= 0)
        {
            ODMBasePtr tmpPtr;
            ODWayM::Instance()->GetPtr("ODMEfg", _Impl->_expandData._lastEfgIdList[index_], tmpPtr);
            if (tmpPtr)
            {
                std::static_pointer_cast<ODMEfg>(tmpPtr)->_markTime = -1;
                Result = ODWayM::Instance()->UpdateModel(tmpPtr);
                if (Result)
                {
                    _Impl->ExpandData();
                }
            }
        }
    }
    return Result;
}

ODPEfg::ODPEfg()
    : _Impl(new Impl)
{
    _Impl->ExpandData();
}

ODPEfg::~ODPEfg()
{
    delete _Impl;
    _Impl = NULL;
}
