//====================================================================
//  gTimeP.cpp
//  created 6.4.18
//  written by gzy
//
//  https://github.com/guo122
//====================================================================

#include <gToolsM/gToolsM.h>

#include <gBase/gBase.h>

#include "gTimeP.h"

struct gTimeP::Impl
{
    Impl()
        : _curDate("")
        , _lastTip(NULL){}

    void InClassify(const gString classify_, const gString kindFirst_, const gString kindSecond_)
    {
        gzy::gStringListPtr tmpStrListPtr;
        // classify
        if (gzy::gList::RefreshInsert<gString>(_expandData._classifyList, classify_))
        {
            // classify first appearance
            tmpStrListPtr = gMakeShared<gzy::gStringList>();
            tmpStrListPtr->push_back(kindFirst_);
            _expandData._kindFirstList[classify_] = tmpStrListPtr;

            tmpStrListPtr = gMakeShared<gzy::gStringList>();
            tmpStrListPtr->push_back(kindSecond_);
            gzy::gStringListPtrMap tmpStrListPtrMap;
            tmpStrListPtrMap[kindFirst_] = tmpStrListPtr;
            _expandData._kindSecondList[classify_] = tmpStrListPtrMap;
        }
        else
        {
            tmpStrListPtr = _expandData._kindFirstList[classify_];
            if (gzy::gList::RefreshInsert<gString>(*tmpStrListPtr, kindFirst_))
            {
                tmpStrListPtr = gMakeShared<gzy::gStringList>();
                tmpStrListPtr->push_back(kindSecond_);
                _expandData._kindSecondList[classify_][kindFirst_] = tmpStrListPtr;
            }
            else
            {
                tmpStrListPtr = _expandData._kindSecondList[classify_][kindFirst_];
                gzy::gList::RefreshInsert<gString>(*tmpStrListPtr, kindSecond_);
            }
        }
    }

    void ExpandData()
    {
        ResetExpandData();

        OneTipPtr oneTipPtr = NULL;
        OneDayPtr oneDayPtr = NULL;
        DaySumPtr oneSumPtr = NULL;
        gzy::gMBaseList tmpList;
        gTimeMPtr cur;
        gToolsM::Instance()->GetList("gTimeM", tmpList);
        gForeach(tmpList.begin(), tmpList.end(), [&](gzy::gMBasePtr &x){
            cur = gStaticPointerCast<gTimeM>(x);

            // classify
            InClassify(cur->_classify, cur->_kindFirst, cur->_kindSecond);

            oneTipPtr = gMakeShared<OneTip>();
            oneTipPtr->_time = cur->_id;
            oneTipPtr->_classify = cur->_classify;
            oneTipPtr->_kindFirst = cur->_kindFirst;
            oneTipPtr->_kindSecond = cur->_kindSecond;
            oneTipPtr->_content = cur->_content;

            if (cur->_offsetMinute != 0)
            {
                oneTipPtr->_durationSecond = cur->_offsetMinute * 60;
            }
            else if (_lastTip)
            {
                oneTipPtr->_durationSecond = cur->_id - _lastTip->_time;
            }
            else
            {
                oneTipPtr->_durationSecond = 0;
            }

            if (_lastTip == NULL || !gzy::gTime::IsSameDay(_lastTip->_time, oneTipPtr->_time))
            {
                // new day
                oneDayPtr = gMakeShared<OneDay>();
                oneSumPtr = gMakeShared<DaySum>();
                _curDate = gzy::gTime::Timestamp2String(oneTipPtr->_time, "%y-%m-%d");
                _expandData._dateList.push_back(_curDate);
                _expandData._dayList[_curDate] = oneDayPtr;
                _expandData._sumList[_curDate] = oneSumPtr;
            }
            oneDayPtr->_tipList.push_back(oneTipPtr);

            _lastTip = oneTipPtr;

            oneSumPtr->AddTip(oneTipPtr->_classify, oneTipPtr->_kindFirst, oneTipPtr->_kindSecond, oneTipPtr->_durationSecond);
        });
    }

    void AppendData(const gTimeMPtr &curPtr)
    {
        if (_expandData._dateList.empty() || _lastTip == NULL)
        {
            ExpandData();
        }
        else
        {
            // get last day's last tip
            OneDayPtr lastDayPtr = _expandData._dayList[_expandData._dateList[_expandData._dateList.size() - 1]];
            DaySumPtr lastSumPtr = _expandData._sumList[_expandData._dateList[_expandData._dateList.size() - 1]];
            if (curPtr->_id > _lastTip->_time)
            {
                InClassify(curPtr->_classify, curPtr->_kindFirst, curPtr->_kindSecond);
                OneTipPtr tmpPtr = gMakeShared<OneTip>();
                tmpPtr->_time = curPtr->_id;
                tmpPtr->_classify = curPtr->_classify;
                tmpPtr->_kindFirst = curPtr->_kindFirst;
                tmpPtr->_kindSecond = curPtr->_kindSecond;
                tmpPtr->_content = curPtr->_content;
                if (curPtr->_offsetMinute != 0)
                {
                    tmpPtr->_durationSecond = curPtr->_offsetMinute * 60;
                }
                else
                {
                    tmpPtr->_durationSecond = tmpPtr->_time - _lastTip->_time;
                }

                _curDate = gzy::gTime::Timestamp2String(tmpPtr->_time, "%y-%m-%d");
                if (!gzy::gTime::IsSameDay(tmpPtr->_time, _lastTip->_time))
                {
                    // new Day
                    lastDayPtr = gMakeShared<OneDay>();
                    lastSumPtr = gMakeShared<DaySum>();
                    _expandData._dateList.push_back(_curDate);
                    _expandData._dayList[_curDate] = lastDayPtr;
                    _expandData._sumList[_curDate] = lastSumPtr;
                }
                lastDayPtr->_tipList.push_back(tmpPtr);
                lastSumPtr->AddTip(tmpPtr->_classify, tmpPtr->_kindFirst, tmpPtr->_kindSecond, tmpPtr->_durationSecond);
                _lastTip = tmpPtr;
            }
            else
            {
                ExpandData();
            }
        }
    }

    void DeleteData(const int &id_)
    {
        // todo, swift delete
        ExpandData();
        _curDate = gzy::gTime::Timestamp2String(id_, "%y-%m-%d");
    }

    void ResetExpandData()
    {
        _expandData.clear();
        _curDate.clear();
        _lastTip = NULL;
        _lastCurList.clear();
        _lastChartList.clear();
    }

    gTimeP::ExpandData _expandData;
    gString _curDate;

    gTimeP::OneTipPtr _lastTip;
    gVector<gTimeP::OneTipPtr> _lastCurList;
    gTimeP::LastChartList _lastChartList;
};

gTimeP *gTimeP::Instance()
{
    static gTimeP * obj = new gTimeP;
    return obj;
}

gTimeP::gTimeP()
    : _Impl(new Impl)
{
    _Impl->ExpandData();
}

gTimeP::~gTimeP()
{
    delete _Impl;
    _Impl = NULL;
}

bool gTimeP::AddTime(const gTimeMPtr &curPtr_)
{
    bool Result = false;
    if (gToolsM::Instance()->AddModel(curPtr_))
    {
        Result = true;
        _Impl->AppendData(curPtr_);
    }
    return Result;
}

bool gTimeP::FastIdle()
{
    gTimeMPtr tmpPtr = gMakeShared<gTimeM>();
    tmpPtr->_classify = "Idle";
    tmpPtr->_kindFirst = "Idle";
    tmpPtr->_kindSecond = "Idle";
    tmpPtr->_content = "Fast Idle";
    return AddTime(tmpPtr);
}

bool gTimeP::DelDurTime(const int &index_)
{
    bool Result = false;
    if (index_ >= 0 && index_ < _Impl->_lastCurList.size())
    {
        if (_Impl->_lastCurList[index_])
        {
            int tmpTime = _Impl->_lastCurList[index_]->_time;

            if (gToolsM::Instance()->DeleteModel("ODMTime", tmpTime))
            {
                _Impl->DeleteData(tmpTime);
                Result = true;
            }
        }
    }
    return Result;
}

bool gTimeP::CalDurTime(const int &index1_, const int &index2_, gString &str_)
{
    bool Result = false;
    if (index1_ >= 0 && index1_ < _Impl->_lastCurList.size() &&
            index2_ >= 0 && index2_ < _Impl->_lastCurList.size())
    {
        OneTipPtr tip1 = _Impl->_lastCurList[index1_];
        OneTipPtr tip2 = _Impl->_lastCurList[index2_];
        OneTipPtr tmpTip;
        if (tip1 && tip2)
        {
            Result = true;
            if (tip1->_time < tip2->_time)
            {
                tmpTip = tip1;
                tip1 = tip2;
                tip2 = tmpTip;
            }
            str_ = gzy::gTime::Duration2String(tip1->_time - tip2->_time + tip2->_durationSecond);
        }
    }
    return Result;
}

bool gTimeP::GetPopList(const gzy::gStringList &ckkList_, gzy::gIntList &indexList_)
{
    bool Result = false;
    indexList_.clear();
    if (ckkList_.size() == 3)
    {
        int i = 0;
        gForeach(_Impl->_lastCurList.begin(), _Impl->_lastCurList.end(), [&](OneTipPtr &x){
            if (x)
            {
                if (!(x->_classify != ckkList_[0] ||
                      (x->_kindFirst != ckkList_[1] && ckkList_[1] != "") ||
                      (x->_kindSecond != ckkList_[2] && ckkList_[2] != "")))
                {
                    indexList_.push_back(i);
                }
            }
            ++i;
        });
    }
    return Result;
}

bool gTimeP::GetLastCKKSum(const gzy::gStringList &ckkList_, const int &lastCount, gzy::gIntList &IntList_)
{
    bool Result = false;
    if (ckkList_.size() ==3 && ckkList_[0] != "" && _Impl->_lastTip)
    {
        gString tmpDate = gzy::gTime::Timestamp2String(_Impl->_lastTip->_time, "%y-%m-%d");
        gzy::gTime::DateJump(tmpDate, 1 - lastCount);
        int tmpValue = 0;
        _Impl->_lastChartList.clear();
        _Impl->_lastChartList._classify = ckkList_[0];
        _Impl->_lastChartList._kindFirst = ckkList_[1];
        _Impl->_lastChartList._kindSecond = ckkList_[2];
        _Impl->_lastChartList._startDate = tmpDate;
        Result = true;

        for (int i = 0; i < lastCount; ++i)
        {
            if (_Impl->_expandData._sumList[tmpDate])
            {

                if (ckkList_[1] == "")
                {
                    if (tmpValue = _Impl->_expandData._sumList[tmpDate]->_classifySum[ckkList_[0]])
                    {
                        tmpValue /= 60;
                    }
                    else
                    {
                        _Impl->_expandData._sumList[tmpDate]->_classifySum.erase(ckkList_[0]);
                    }
                }
                else if (ckkList_[2] == "")
                {
                    if (tmpValue = _Impl->_expandData._sumList[tmpDate]->_kindFirstSum[ckkList_[0]][ckkList_[1]])
                    {
                        tmpValue /= 60;
                    }
                    else
                    {
                        _Impl->_expandData._sumList[tmpDate]->_kindFirstSum[ckkList_[0]].erase(ckkList_[1]);
                    }
                }
                else
                {
                    if (tmpValue = _Impl->_expandData._sumList[tmpDate]->_kindSecondSum[ckkList_[0]][ckkList_[1]][ckkList_[2]])
                    {
                        tmpValue /= 60;
                    }
                    else
                    {
                        _Impl->_expandData._sumList[tmpDate]->_kindSecondSum[ckkList_[0]][ckkList_[1]].erase(ckkList_[2]);
                    }
                }
            }

            IntList_.push_back(tmpValue);
            _Impl->_lastChartList._endDate = tmpDate;
            _Impl->_lastChartList._totalValue += tmpValue;
            _Impl->_lastChartList._list.push_back(gMakeShared<LastChart>(tmpDate, tmpValue));
            gzy::gTime::DateJump(tmpDate);
        }
        _Impl->_lastChartList.CalColor();
    }
    return Result;
}

bool gTimeP::GetLastCKKSum(gzy::gStringList &strList_)
{
    strList_.clear();
    gForeach(_Impl->_lastChartList._list.crbegin(), _Impl->_lastChartList._list.crend(), [&strList_](const LastChartPtr &x){
        strList_.push_back(x->_date + ": " + gzy::gTime::Duration2String(x->_value * 60));
    });

    return !strList_.empty();
}

bool gTimeP::GetLastCKKSumColor(const int &index_, gString &color_)
{
    bool Result = false;
    if (index_ >= 0 && index_ < _Impl->_lastChartList._list.size())
    {
        color_ = _Impl->_lastChartList._list[_Impl->_lastChartList._list.size() - index_ - 1]->_color;
        Result = true;
    }
    return Result;
}

bool gTimeP::SetDateByChartSum(const int &index_)
{
    bool Result = false;
    if (index_ >= 0 && index_ < _Impl->_lastChartList._list.size())
    {
        _Impl->_curDate = _Impl->_lastChartList._list[_Impl->_lastChartList._list.size() - index_ - 1]->_date;
        Result = true;
    }
    return Result;
}

gString gTimeP::GetStartDate()
{
    return _Impl->_lastChartList._startDate;
}

gString gTimeP::GetEndDate()
{
    return _Impl->_lastChartList._endDate;
}

bool gTimeP::IsChartSumCurrentDay(const int &index_)
{
    bool Result = false;
    if (index_ >= 0 && index_ < _Impl->_lastChartList._list.size())
    {
        Result = _Impl->_lastChartList._list[_Impl->_lastChartList._list.size() - index_ - 1]->_date == _Impl->_curDate;
    }
    return Result;
}

int gTimeP::getChartSumCurrentIndex()
{
    int Result = -1;
    for (auto pos = _Impl->_lastChartList._list.crbegin(); pos != _Impl->_lastChartList._list.crend(); pos++)
    {
        Result++;
        if ((*pos)->_date == _Impl->_curDate)
        {
            return Result;
        }
    }
    return -1;
}

void gTimeP::GetCurList(gzy::gStringList &list)
{
    if (!_Impl->_expandData._dateList.empty())
    {
        _Impl->_lastCurList.clear();
        if (gFind(_Impl->_expandData._dateList.begin(), _Impl->_expandData._dateList.end(), _Impl->_curDate) ==
                _Impl->_expandData._dateList.end())
        {
            _Impl->_curDate = _Impl->_expandData._dateList[_Impl->_expandData._dateList.size() - 1];
        }
        gString tmpStr;
        list.clear();
        list.push_back(_Impl->_curDate);
        _Impl->_lastCurList.push_back(NULL);
        list.push_back("");
        _Impl->_lastCurList.push_back(NULL);
        gForeach(_Impl->_expandData._dayList[_Impl->_curDate]->_tipList.begin(), _Impl->_expandData._dayList[_Impl->_curDate]->_tipList.end(), [&](OneTipPtr &x){
            tmpStr = gzy::gTime::Timestamp2String(x->_time - x->_durationSecond, "%H:%M") + "-";
            tmpStr += gzy::gTime::Timestamp2String(x->_time, "%H:%M") + "(";
            tmpStr += gzy::gTime::Duration2String(x->_durationSecond) + "): ";
            tmpStr += x->_classify + "_" + x->_kindFirst + "_" + x->_kindSecond;
            list.push_back(tmpStr);
            _Impl->_lastCurList.push_back(x);
        });
    }
}

void gTimeP::GetCurSumList(gVector<gzy::gStringList> &classifyList_,
                            gVector<gVector<gzy::gStringList> > &kindFirstList_,
                            gVector<gVector<gVector<gzy::gStringList> > > &kindSecondList_)
{
    if (!_Impl->_expandData._sumList.empty())
    {
        DaySumPtr oneSum = _Impl->_expandData._sumList[_Impl->_curDate];
        SIMapList listClassifySum, listKindFirstSum, listKindSecondSum;
        if (oneSum)
        {
            classifyList_.clear();
            kindFirstList_.clear();
            kindSecondList_.clear();

            gForeach(oneSum->_classifySum.begin(), oneSum->_classifySum.end(), [&listClassifySum](const gPair<gString, int> &x){
                listClassifySum.push_back(x);
            });
            gSort(listClassifySum.begin(), listClassifySum.end(), [](gPair<gString, int> &x, gPair<gString, int> &y){
                return x.second > y.second;
            });

            gForeach(listClassifySum.begin(), listClassifySum.end(), [&](gPair<gString, int> &x){
                gzy::gStringList metaClassify;
                gVector<gzy::gStringList> metaKindFirstClassify;
                gVector<gVector<gzy::gStringList>> metaKindSecondClassify;
                if (oneSum->ToString(x.first, metaClassify))
                {
                    classifyList_.push_back(metaClassify);

                    listKindFirstSum.clear();
                    gForeach(oneSum->_kindFirstSum[x.first].begin(), oneSum->_kindFirstSum[x.first].end(), [&listKindFirstSum](const gPair<gString, int> &x){
                        listKindFirstSum.push_back(x);
                    });
                    gSort(listKindFirstSum.begin(), listKindFirstSum.end(), [](gPair<gString, int> &x, gPair<gString, int> &y){
                        return x.second > y.second;
                    });

                    gForeach(listKindFirstSum.begin(), listKindFirstSum.end(), [&](gPair<gString, int> &y){
                        gzy::gStringList tmpKindFirst;
                        if (oneSum->ToString(x.first, y.first, tmpKindFirst))
                        {
                            metaKindFirstClassify.push_back(tmpKindFirst);
                            gVector<gzy::gStringList> metaKindSecondKind;

                            listKindSecondSum.clear();
                            gForeach(oneSum->_kindSecondSum[x.first][y.first].begin(), oneSum->_kindSecondSum[x.first][y.first].end(), [&listKindSecondSum](const gPair<gString, int> &x){
                                listKindSecondSum.push_back(x);
                            });
                            gSort(listKindSecondSum.begin(), listKindSecondSum.end(), [](gPair<gString, int> &x, gPair<gString, int> &y){
                                return x.second > y.second;
                            });

                            gForeach(listKindSecondSum.begin(), listKindSecondSum.end(), [&](gPair<gString, int> &z){
                                gzy::gStringList tmpKindSecond;
                                if (oneSum->ToString(x.first, y.first, z.first, tmpKindSecond))
                                {
                                    metaKindSecondKind.push_back(tmpKindSecond);
                                }
                            });
                            metaKindSecondClassify.push_back(metaKindSecondKind);
                        }
                    });
                    kindFirstList_.push_back(metaKindFirstClassify);
                    kindSecondList_.push_back(metaKindSecondClassify);
                }
            });
        }
    }
}

void gTimeP::GetAllSumList(gVector<gzy::gStringList> &classifyList_,
                            gVector<gVector<gzy::gStringList> > &kindFirstList_,
                            gVector<gVector<gVector<gzy::gStringList> > > &kindSecondList_)
{
    if (!_Impl->_expandData._sumList.empty())
    {
        DaySumPtr oneSum = _Impl->_expandData._sumList[_Impl->_curDate];
        SIMapList listClassifySum, listKindFirstSum, listKindSecondSum;
        if (oneSum)
        {
            classifyList_.clear();
            kindFirstList_.clear();
            kindSecondList_.clear();

            gForeach(_Impl->_expandData._classifyList.begin(), _Impl->_expandData._classifyList.end(), [&](gString &x){
                gzy::gStringList metaClassify;
                gVector<gzy::gStringList> metaKindFirstClassify;
                gVector<gVector<gzy::gStringList>> metaKindSecondClassify;

                metaClassify.push_back(x);
                metaClassify.push_back("0");
                metaClassify.push_back(x);
                metaClassify.push_back("");
                metaClassify.push_back("");

                classifyList_.push_back(metaClassify);

                gForeach(_Impl->_expandData._kindFirstList[x]->begin(), _Impl->_expandData._kindFirstList[x]->end(), [&](gString &y){
                    gzy::gStringList tmpKindFirst;

                    tmpKindFirst.push_back(y);
                    tmpKindFirst.push_back("0");
                    tmpKindFirst.push_back(x);
                    tmpKindFirst.push_back(y);
                    tmpKindFirst.push_back("");

                    metaKindFirstClassify.push_back(tmpKindFirst);
                    gVector<gzy::gStringList> metaKindSecondKind;

                    gForeach(_Impl->_expandData._kindSecondList[x][y]->begin(), _Impl->_expandData._kindSecondList[x][y]->end(), [&](gString &z){
                        gzy::gStringList tmpKindSecond;

                        tmpKindSecond.push_back(z);
                        tmpKindSecond.push_back("0");
                        tmpKindSecond.push_back(x);
                        tmpKindSecond.push_back(y);
                        tmpKindSecond.push_back(z);

                        metaKindSecondKind.push_back(tmpKindSecond);
                    });
                    metaKindSecondClassify.push_back(metaKindSecondKind);
                });
                kindFirstList_.push_back(metaKindFirstClassify);
                kindSecondList_.push_back(metaKindSecondClassify);
            });
        }
    }
}

gString gTimeP::GetCurSum()
{
    gString Result = "Sum";
    if (!_Impl->_expandData._sumList.empty())
    {
        DaySumPtr oneSum = _Impl->_expandData._sumList[_Impl->_curDate];
        if (oneSum)
        {
            gzy::gStringList tmpList;
            oneSum->ToString(tmpList);
            Result = _Impl->_curDate + ": " + tmpList[1];
        }
    }
    return Result;
}

void gTimeP::GetRunningTimeStr(gString &str_)
{
    if (_Impl->_lastTip)
    {
        time_t curTime = 0;
        int curTimestamp = time(&curTime);
        str_ = gzy::gTime::Duration2String(curTimestamp - _Impl->_lastTip->_time, "__DIGITAL__");
    }
    else
    {
        str_ = "--:--:--";
    }
}

gString gTimeP::GetDate()
{
    return _Impl->_curDate;
}

bool gTimeP::PrevCur()
{
    gString tmpStr = _Impl->_curDate;
    for (int i = 0; i < _Impl->_expandData._dateList.size(); ++i)
    {
        if (_Impl->_expandData._dateList[i] == _Impl->_curDate && i != 0)
        {
            _Impl->_curDate = _Impl->_expandData._dateList[i - 1];
            break;
        }
    }
    return tmpStr != _Impl->_curDate;
}

bool gTimeP::FirstCur()
{
    gString tmpStr = _Impl->_curDate;
    if (!_Impl->_expandData._dateList.empty())
    {
        _Impl->_curDate = _Impl->_expandData._dateList[0];
    }
    return tmpStr != _Impl->_curDate;
}

bool gTimeP::NextCur()
{
    gString tmpStr = _Impl->_curDate;
    for (int i = 0; i < _Impl->_expandData._dateList.size(); ++i)
    {
        if (_Impl->_expandData._dateList[i] == _Impl->_curDate && i != _Impl->_expandData._dateList.size() - 1)
        {
            _Impl->_curDate = _Impl->_expandData._dateList[i + 1];
            break;
        }
    }
    return tmpStr != _Impl->_curDate;
}

bool gTimeP::LastCur()
{
    gString tmpStr = _Impl->_curDate;
    if (!_Impl->_expandData._dateList.empty())
    {
        _Impl->_curDate = _Impl->_expandData._dateList[_Impl->_expandData._dateList.size() - 1];
    }
    return tmpStr != _Impl->_curDate;
}

void gTimeP::GetClassifyList(gzy::gStringList &list)
{
    list = _Impl->_expandData._classifyList;
}

void gTimeP::GetKindFirstList(gzy::gStringList &list, const gString &key_)
{
    if (key_.empty() && !_Impl->_expandData._classifyList.empty())
    {
        list = *(_Impl->_expandData._kindFirstList[_Impl->_expandData._classifyList[0]]);
    }
    else
    {
        list = *(_Impl->_expandData._kindFirstList[key_]);
    }
}

void gTimeP::GetKindSecondList(gzy::gStringList &list, const gString &classify_, const gString &key_)
{
    list = *(_Impl->_expandData._kindSecondList[classify_][key_]);
    //    _Impl->_expandData._kindFirstList[classify_][""];
    //    list = *(_Impl->_expandData._kindSecondList[""]);
}

void gTimeP::DaySum::AddTip(const gString &classify_, const gString &kindFirst_, const gString &kindSecond_, const int &second_)
{
    _kindSecondSum[classify_][kindFirst_][kindSecond_] += second_;
    _kindSecondSum[classify_][kindFirst_]["__SUM__"] += second_;
    _kindFirstSum[classify_][kindFirst_] += second_;
    _kindFirstSum[classify_]["__SUM__"] += second_;
    _classifySum[classify_] += second_;
    _classifySum["__SUM__"] += second_;
}

bool gTimeP::DaySum::ToString(gzy::gStringList &strList_)
{
    bool Result = false;
    if (!_classifySum.empty())
    {
        strList_.clear();
        strList_.push_back("_SUM_");
        strList_.push_back(gzy::gTime::Duration2String(_classifySum["__SUM__"]));
        strList_.push_back(gToString(_classifySum["__SUM__"]));
        Result = true;
    }
    return Result;
}

bool gTimeP::DaySum::ToString(const gString &classify_, gzy::gStringList &strList_)
{
    bool Result = false;
    if (!_classifySum.empty() && classify_ != "__SUM__")
    {
        char tmpChar[20];
        double tmpPercentage;
        strList_.clear();
        strList_.push_back(classify_);

        tmpPercentage = (double)_classifySum[classify_] / (double)_classifySum["__SUM__"] * 100;
        sprintf(tmpChar, "%.2f", tmpPercentage);

        strList_.push_back(gzy::gTime::Duration2String(_classifySum[classify_]) + " (" + tmpChar + "%)");
        strList_.push_back(classify_);
        strList_.push_back("");
        strList_.push_back("");

        Result = true;
    }
    return Result;
}

bool gTimeP::DaySum::ToString(const gString &classify_, const gString &kindFirst_, gzy::gStringList &strList_)
{
    bool Result = false;
    if (!_classifySum.empty() && classify_ != "__SUM__" && kindFirst_ != "__SUM__")
    {
        char tmpChar[20];
        double tmpPercentage;
        strList_.clear();
        strList_.push_back(kindFirst_);

        tmpPercentage = (double)_kindFirstSum[classify_][kindFirst_] / (double)_kindFirstSum[classify_]["__SUM__"] * 100;
        sprintf(tmpChar, "%.2f", tmpPercentage);

        strList_.push_back(gzy::gTime::Duration2String(_kindFirstSum[classify_][kindFirst_]) + " (" + tmpChar + "%)");
        strList_.push_back(classify_);
        strList_.push_back(kindFirst_);
        strList_.push_back("");

        Result = true;
    }
    return Result;
}

bool gTimeP::DaySum::ToString(const gString &classify_, const gString &kindFirst_, const gString &kindSecond_, gzy::gStringList &strList_)
{
    bool Result = false;
    if (!_classifySum.empty() && classify_ != "__SUM__" && kindFirst_ != "__SUM__" && kindSecond_ != "__SUM__")
    {
        char tmpChar[20];
        double tmpPercentage;
        strList_.clear();
        strList_.push_back(kindSecond_);

        tmpPercentage = (double)_kindSecondSum[classify_][kindFirst_][kindSecond_] / (double)_kindSecondSum[classify_][kindFirst_]["__SUM__"] * 100;
        sprintf(tmpChar, "%.2f", tmpPercentage);

        strList_.push_back(gzy::gTime::Duration2String(_kindSecondSum[classify_][kindFirst_][kindSecond_]) + " (" + tmpChar + "%)");
        strList_.push_back(classify_);
        strList_.push_back(kindFirst_);
        strList_.push_back(kindSecond_);

        Result = true;
    }
    return Result;
}

void gTimeP::ExpandData::clear()
{
    _dateList.clear();
    _dayList.clear();
    _sumList.clear();
    _classifyList.clear();
    _kindFirstList.clear();
    _kindSecondList.clear();
}

void gTimeP::LastChartList::clear()
{
    _classify.clear();
    _kindFirst.clear();
    _kindSecond.clear();
    _startDate.clear();
    _endDate.clear();
    _totalValue = 0;
    _list.clear();
}

void gTimeP::LastChartList::CalColor()
{
    int tmpAverage = _totalValue / _list.size();
    gForeach(_list.begin(), _list.end(), [tmpAverage](LastChartPtr &x){
        if (x->_value == 0)
        {
            x->_color = "grey";
        }
        else if (x->_value < tmpAverage)
        {
            x->_color = "red";
        }
        else if (x->_value > tmpAverage)
        {
            x->_color = "green";
        }
        else
        {
            x->_color = "black";
        }
    });
}
