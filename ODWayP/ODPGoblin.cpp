//====================================================================
//  ODPGoblin.cpp
//  created 6.12.18
//  written by odddd0
//
//  https://github.com/odddd0/ODWay
//====================================================================

#include <ODWayM/ODWayM.h>

#include <ODUtil/ODUtil.h>

#include "ODPGoblin.h"

struct ODPGoblin::Impl
{
    Impl(){}

    void ExpandData()
    {
        ResetExpanddata();
        ODMBaseList tmpList;

        // ODMGnome
        tmpList.clear();
        ODWayM::Instance()->GetList("ODMGnome", tmpList);
        std::for_each(tmpList.cbegin(), tmpList.cend(), [&](const ODMBasePtr &x){
            _expandData.appendGnome(x);
        });

        // ODMGoblinCoin
        tmpList.clear();
        ODWayM::Instance()->GetList("ODMGoblinCoin", tmpList);
        std::for_each(tmpList.cbegin(), tmpList.cend(), [&](const ODMBasePtr &x){
            _expandData.appendCoin(x);
        });
    }

    void ResetExpanddata()
    {
        _expandData.clear();
    }

    ODPGoblin::ExpandData _expandData;
};

ODPGoblin *ODPGoblin::Instance()
{
    static ODPGoblin * obj = new ODPGoblin;
    return obj;
}

bool ODPGoblin::AddGoblin(const ODMBasePtr &ptr_)
{
    bool Result = true;
    if (ptr_->_type == "ODMGnome")
    {
        // gnome name exist?
        ODMGnomePtr tmpPtr = std::static_pointer_cast<ODMGnome>(ptr_);
        auto pos = std::find(_Impl->_expandData._goldFromList.begin(), _Impl->_expandData._goldFromList.end(), tmpPtr->_name);
        tmpPtr->_id = _Impl->_expandData._goldFromList.size();
        if (pos != _Impl->_expandData._goldFromList.end())
        {
            Result = false;
        }
    }
    if (Result)
    {
        Result = false;
        if (ODWayM::Instance()->AddModel(ptr_))
        {
            if (ptr_->_type == "ODMGoblinCoin")
            {
                Result = _Impl->_expandData.appendCoin(ptr_);
            }
            else if (ptr_->_type == "ODMGnome")
            {
                Result = _Impl->_expandData.appendGnome(ptr_);
            }
        }
    }
    return Result;
}

void ODPGoblin::GetCKK(CKKPtr &ckk_)
{
    ckk_ = _Impl->_expandData._ckk;
}

void ODPGoblin::GetCoinList(StringList &list_, const std::string &goldType_)
{
    list_.clear();
    _Impl->_expandData._lastCoinNum.clear();
    std::string tmpStr;
    int daySumCount = 0;
    int dayTmpIndex = 0;
    bool dayIn = false;
    std::for_each(_Impl->_expandData._dateList.cbegin(), _Impl->_expandData._dateList.cend(), [&](const std::string &x){
        list_.push_back(x);
        _Impl->_expandData._lastCoinNum.push_back(-1);
        dayIn = false;
        dayTmpIndex = list_.size() - 1;
        daySumCount = 0;
        std::for_each(_Impl->_expandData._coinList[x].cbegin(), _Impl->_expandData._coinList[x].cend(), [&](const OneGoblinCoinPtr &y){
            tmpStr.clear();
            // transit
            if (y->_classify.empty())
            {
                if (y->_goldFrom == goldType_ || y->_goldTo == goldType_ || goldType_.empty())
                {
                    tmpStr = y->_goldFrom + " -> " + y->_goldTo + " (" + std::to_string(y->_count);
                    if (y->_count)
                    {
                        tmpStr.insert(tmpStr.end() - 2, '.');
                    }
                    tmpStr += ")";
                    if (y->_tips)
                    {
                        tmpStr += " Tips: " + std::to_string(y->_tips);
                        tmpStr.insert(tmpStr.end() - 2, '.');
                    }
                }
            }
            // others
            else
            {
                if (y->_goldFrom == goldType_ || goldType_.empty())
                {
                    // revoke
                    if (y->_state == static_cast<int>(ODMGoblinCoin::GoblinState::PayRevoke))
                    {
                        tmpStr += "-revokex-: ";
                    }
                    else if (y->_state == static_cast<int>(ODMGoblinCoin::GoblinState::InstallPay) ||
                             y->_state == static_cast<int>(ODMGoblinCoin::GoblinState::InstallPayReverse))
                    {
                        // instasll pay
                        tmpStr += "-install-: ";
                        daySumCount += y->_count;
                    }
                    else if (y->_state == static_cast<int>(ODMGoblinCoin::GoblinState::InstallBillSplit))
                    {
                        // instasll pay
                        tmpStr += "-split-: ";
                    }
                    else
                    {
                        daySumCount += y->_count;
                    }
                    tmpStr += y->_goldFrom + " (" + std::to_string(y->_count);
                    if (y->_count)
                    {
                        tmpStr.insert(tmpStr.end() - 2, '.');
                    }
                    tmpStr += "): " + y->_classify + "_" + y->_kindFirst + "_" + y->_kindSecond;
                }
            }
            if (!tmpStr.empty())
            {
                dayIn = true;
                _Impl->_expandData._lastCoinNum.push_back(y->_id);
                list_.push_back(tmpStr);
            }
        });
        if (!dayIn)
        {
            _Impl->_expandData._lastCoinNum.erase(_Impl->_expandData._lastCoinNum.end() - 1);
            list_.erase(list_.end() - 1);
        }
        else
        {
            _Impl->_expandData._lastCoinNum.push_back(-1);
            list_.push_back("");
            tmpStr = list_[dayTmpIndex];
            tmpStr += " (" + std::to_string(daySumCount);
            if (daySumCount)
            {
                tmpStr.insert(tmpStr.end() - 2, '.');
            }
            tmpStr += ")";
            list_[dayTmpIndex] = tmpStr;
        }
    });
    // todo
    //    StringList tmpList;
    GetGnomeBillList(list_, goldType_);
    //    tmpList.push_back("");
    //    list_.insert(list_.begin(), tmpList.begin(), tmpList.end());
}

bool ODPGoblin::DelCoin(const int &index_)
{
    bool Result = false;
    if (index_ >= 0 && index_ < _Impl->_expandData._lastCoinNum.size() && _Impl->_expandData._lastCoinNum[index_] >= 0)
    {
        Result = ODWayM::Instance()->DeleteModel("ODMGoblinCoin", _Impl->_expandData._lastCoinNum[index_]);
        if (Result)
        {
            _Impl->ExpandData();
        }
    }
    return Result;
}

bool ODPGoblin::RevokeCoin(const int &index_)
{
    bool Result = false;
    if (index_ >= 0 && index_ < _Impl->_expandData._lastCoinNum.size() && _Impl->_expandData._lastCoinNum[index_] >= 0)
    {
        ODMBasePtr tmpPtr;
        ODWayM::Instance()->GetPtr("ODMGoblinCoin", _Impl->_expandData._lastCoinNum[index_], tmpPtr);
        if (tmpPtr)
        {
            std::static_pointer_cast<ODMGoblinCoin>(tmpPtr)->_state = ODMGoblinCoin::GoblinState::PayRevoke;
            Result = ODWayM::Instance()->UpdateModel(tmpPtr);
            if (Result)
            {
                _Impl->ExpandData();
            }
        }
    }
    return Result;
}

bool ODPGoblin::SetEditCoin(const int &index_)
{
    bool Result = false;
    if (index_ >= 0 && index_ < _Impl->_expandData._lastCoinNum.size() && _Impl->_expandData._lastCoinNum[index_] >= 0)
    {
        _Impl->_expandData._editCoinId = _Impl->_expandData._lastCoinNum[index_];
        _Impl->_expandData._editCoinPtr = NULL;
        Result = true;
    }
    return Result;
}

bool ODPGoblin::DelEditCoin()
{
    bool Result = false;
    if (_Impl->_expandData._editCoinId >= 0)
    {

        Result = ODWayM::Instance()->DeleteModel("ODMGoblinCoin", _Impl->_expandData._editCoinId);
        if (Result)
        {
            _Impl->ExpandData();
        }
    }
    return Result;
}

bool ODPGoblin::GetEditCoinText(std::string &str_, bool &revoke_, int &year_, int &month_, int &day_, int &hour_, int &minute_, int &second_, int &count_, int &countSecond_)
{
    bool Result = false;
    revoke_ = false;
    countSecond_ = 0;
    int tmpIndex = 0;
    if (_Impl->_expandData._editCoinId >= 0)
    {
        ODMBasePtr tmpPtr;
        ODWayM::Instance()->GetPtr("ODMGoblinCoin", _Impl->_expandData._editCoinId, tmpPtr);
        if (tmpPtr)
        {
            Result = true;
            _Impl->_expandData._editCoinPtr = tmpPtr;
            ODMGoblinCoinPtr cur = std::static_pointer_cast<ODMGoblinCoin>(tmpPtr);
            if (cur->_state == ODMGoblinCoin::GoblinState::InstallPay ||
                    cur->_state == ODMGoblinCoin::GoblinState::InstallBillSplit ||
                    cur->_state == ODMGoblinCoin::GoblinState::InstallWithdraw ||
                    cur->_state == ODMGoblinCoin::GoblinState::InstallPayReverse ||
                    cur->_state == ODMGoblinCoin::GoblinState::InstallWithdrawReverse)
            {
                // install pay edit coin
                if (cur->_revokeId)
                {
                    // earily payback
                }
                else
                {
                    // normal
                }
                str_ = ODTimeUtil::Timestamp2String(cur->_id, "%y%m%d_%H%M%S") + "\n";
                str_ += std::to_string(cur->_count);
                if (cur->_count)
                {
                    str_.insert(str_.end() - 2, '.');
                }
                str_ += "\nFuture: ";
                if (_Impl->_expandData._gnomeMap[cur->_goldFrom])
                {
                    ODTimeUtil::CalcuteBillList(cur->_id, _Impl->_expandData._gnomeMap[cur->_goldFrom]->_billDates, tmpIndex);
                }
                if (cur->_bill - tmpIndex - 1 > 0)
                {
                    str_ += std::to_string(cur->_bill - tmpIndex - 1) + " x " + std::to_string(cur->_countSecond);
                    if (cur->_countSecond / cur->_bill)
                    {
                        str_.insert(str_.end() - 2, '.');
                    }
                    str_ += " = " + std::to_string((cur->_countSecond) * (cur->_bill - tmpIndex - 1));
                    if (true)
                    {
                        str_.insert(str_.end() - 2, '.');
                    }
                }
                else
                {
                    str_ += " End";
                }
                str_ += "\nTotal: " + std::to_string((cur->_countSecond * (cur->_bill - 1)) + cur->_revokeId);
                if (true)
                {
                    str_.insert(str_.end() - 2, '.');
                }
            }
            else
            {
                // other type coin
                str_ = ODTimeUtil::Timestamp2String(cur->_id, "%y%m%d_%H%M%S") + "\n";
                str_ += std::to_string(cur->_count);
                if (cur->_count)
                {
                    str_.insert(str_.end() - 2, '.');
                }
                str_ += "\n";
                if (cur->_state == ODMGoblinCoin::GoblinState::NormalTransit)
                {
                    str_ += cur->_goldFrom + " -> " + cur->_classify;
                }
                else
                {
                    str_ += cur->_goldFrom + ": " + cur->_classify + "_" + cur->_kindFirst + "_" + cur->_kindSecond;
                    revoke_ = cur->_state == ODMGoblinCoin::GoblinState::PayRevoke;

                    time_t curTime = 0;
                    time(&curTime);

                    if (revoke_)
                    {
                        countSecond_ = cur->_countSecond;
                        curTime = cur->_revokeId;
                    }

                    struct tm *tmpTm;
                    tmpTm = localtime(&curTime);

                    year_ = tmpTm->tm_year + 1900;
                    month_ = tmpTm->tm_mon + 1;
                    day_ = tmpTm->tm_mday;
                    hour_ = tmpTm->tm_hour;
                    minute_ = tmpTm->tm_min;
                    second_ = tmpTm->tm_sec;
                }
                count_ = cur->_count;
            }
        }
    }
    return Result;
}

bool ODPGoblin::SaveEditCoin(
        const bool &revoke_,
        const int &year_,
        const int &month_,
        const int &day_,
        const int &hour_,
        const int &minute_,
        const int &second_,
        const int &countSecond_,
        const std::string &class_,
        const int &remainMonth_)
{
    bool Result = false;
    ODMGoblinCoinPtr cur = std::static_pointer_cast<ODMGoblinCoin>(_Impl->_expandData._editCoinPtr);
    if (cur)
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

        if (cur->_state == ODMGoblinCoin::GoblinState::SimplePay)
        {
            cur->_state = ODMGoblinCoin::GoblinState::SimplePay;
            if (revoke_)
            {
                cur->_state = ODMGoblinCoin::GoblinState::PayRevoke;
                cur->_countSecond = countSecond_;
                cur->_revokeId = lt;
            }
            Result = ODWayM::Instance()->UpdateModel(cur);
            if (Result)
            {
                _Impl->ExpandData();
            }
        }
        else if (cur->_state == ODMGoblinCoin::GoblinState::InstallBillSplit ||
                 cur->_state == ODMGoblinCoin::GoblinState::InstallPay ||
                 cur->_state == ODMGoblinCoin::GoblinState::InstallWithdraw && revoke_)
        {
            ODPGoblin::OneGnomePtr gnome = _Impl->_expandData._gnomeMap[cur->_goldFrom];
            if (gnome && gnome->_creditLimits)
            {
                ODMGoblinCoinPtr newCur = std::make_shared<ODMGoblinCoin>();
                newCur->_id = lt;
                newCur->_goldFrom = class_;
                newCur->_classify = cur->_goldFrom;
                newCur->_countSecond = cur->_countSecond;
                newCur->_revokeId = cur->_revokeId;

                newCur->_count = countSecond_;
                newCur->_bill = remainMonth_;

                if (cur->_state == ODMGoblinCoin::GoblinState::InstallPay ||
                        cur->_state == ODMGoblinCoin::GoblinState::InstallWithdraw ||
                        cur->_state == ODMGoblinCoin::GoblinState::InstallBillSplit)
                {
                    newCur->_state = ODMGoblinCoin::GoblinState::PrePaybackInstall;
                    if (newCur->_bill != cur->_bill)
                    {
                        newCur->_revokeId = newCur->_countSecond;
                    }
                }
                else
                {
                    newCur->_state = ODMGoblinCoin::GoblinState::PrePaybackInstallReverse;
                }

                // calculate offset
                int tmpIndex = -1;
                int tmpNewIndex = -1;
                ODTimeUtil::CalcuteBillList(cur->_id, gnome->_billDates, tmpIndex);
                ODTimeUtil::CalcuteBillList(newCur->_id, gnome->_billDates, tmpNewIndex);
                newCur->_content = std::to_string(tmpIndex - cur->_bill + remainMonth_ - tmpNewIndex);

                Result = ODWayM::Instance()->AddModel(newCur);
                if (Result)
                {
                    _Impl->ExpandData();
                }
            }
        }
    }
    return Result;
}

bool ODPGoblin::UpGnome(const int &index_)
{
    bool Result = false;
    if (index_ > 0 && index_ < _Impl->_expandData._lastGnomeNum.size())
    {
        int tmpId = _Impl->_expandData._lastGnomeNum[index_];
        if (tmpId)
        {
            std::string upStr = _Impl->_expandData._goldFromList[tmpId];
            std::string downStr = _Impl->_expandData._goldFromList[tmpId - 1];
            _Impl->_expandData._goldFromList.erase(_Impl->_expandData._goldFromList.begin() + tmpId);
            _Impl->_expandData._goldFromList.insert(_Impl->_expandData._goldFromList.begin() + tmpId - 1, upStr);

            Result = _Impl->_expandData.chgGnome(upStr, downStr);
        }
    }
    return Result;
}

void ODPGoblin::GetGoldFromList(StringList &list_)
{
    list_ = _Impl->_expandData._goldFromList;
}

void ODPGoblin::GetGnomeList(StringList &list_)
{
    list_.clear();
    _Impl->_expandData._lastGnomeNum.clear();
    _Impl->_expandData._lastGnomeNum.push_back(-1);
    OneGnomePtr cur;
    std::string tmpStr;
    int totalLastBill = 0;
    int totalCurrentBill = 0;
    int totalBalance = 0;
    std::for_each(_Impl->_expandData._goldFromList.cbegin(), _Impl->_expandData._goldFromList.cend(), [&](const std::string &x){
        cur = _Impl->_expandData._gnomeMap[x];
        tmpStr.clear();

        tmpStr = x;
        // credit
        if (cur->_creditLimits)
        {
            if (cur->_gnomeState != ODMGnome::GnomeState::HidenInTotal)
            {
                totalLastBill += cur->_billList[1];
                totalCurrentBill += cur->_billList[0];
            }
            else
            {
                tmpStr = "--- " + tmpStr;
            }

            tmpStr += "\n(" + std::to_string(cur->_billDates) + ")  ";

            tmpStr += std::to_string(cur->_creditLimits + cur->_balance);
            if (cur->_creditLimits + cur->_balance)
            {
                tmpStr.insert(tmpStr.end() - 2, '.');
            }

            tmpStr += " / " + std::to_string(cur->_billList[1]);
            if (cur->_billList[1])
            {
                tmpStr.insert(tmpStr.end() - 2, '.');
            }

            tmpStr += " / " + std::to_string(cur->_billList[0]);
            if (cur->_billList[0])
            {
                tmpStr.insert(tmpStr.end() - 2, '.');
            }
        }
        else
        {
            if (cur->_gnomeState != ODMGnome::GnomeState::HidenInTotal)
            {
                totalBalance += cur->_balance;
            }
            else
            {
                tmpStr = "--- " + tmpStr;
            }
            tmpStr += "\nBalance:  " + std::to_string(cur->_balance);
            if (cur->_balance)
            {
                tmpStr.insert(tmpStr.end() - 2, '.');
            }
        }

        list_.push_back(tmpStr);
        _Impl->_expandData._lastGnomeNum.push_back(cur->_id);
    });
    tmpStr = "Total\n";
    std::string tmpIntStr = "";
    _Impl->_expandData._totalDescription.clear();
    tmpStr += "LastBill:  ";
    tmpIntStr = std::to_string(totalLastBill);
    if (totalLastBill)
    {
        tmpIntStr.insert(tmpIntStr.end() - 2, '.');
    }
    tmpStr += tmpIntStr;
    _Impl->_expandData._totalDescription += tmpIntStr + " / ";

    tmpStr += "\nCurrentBill:  ";
    tmpIntStr = std::to_string(totalCurrentBill);
    if (totalCurrentBill)
    {
        tmpIntStr.insert(tmpIntStr.end() - 2, '.');
    }
    tmpStr += tmpIntStr;
    _Impl->_expandData._totalDescription += tmpIntStr + " / ";

    tmpStr += "\nBalance:  ";
    tmpIntStr = std::to_string(totalBalance);
    if (totalBalance)
    {
        tmpIntStr.insert(tmpIntStr.end() - 2, '.');
    }
    tmpStr += tmpIntStr;
    _Impl->_expandData._totalDescription += tmpIntStr;

    tmpStr += "\n";
    list_.insert(list_.begin(), tmpStr);

    _Impl->_expandData._totalDescription = std::to_string(totalBalance - totalLastBill - totalCurrentBill);
    if (totalBalance - totalLastBill - totalCurrentBill)
    {
        _Impl->_expandData._totalDescription.insert(_Impl->_expandData._totalDescription.end() - 2, '.');
    }
}

void ODPGoblin::GetGnomeNameByIndex(const int &index_, std::string &name_)
{
    name_.clear();
    if (index_ > 0 && index_ < _Impl->_expandData._lastGnomeNum.size())
    {
        int tmpId = _Impl->_expandData._lastGnomeNum[index_];
        if (tmpId >= 0)
        {
            name_ = _Impl->_expandData._goldFromList[tmpId];
        }
    }
}

void ODPGoblin::GetGnomeBillList(StringList &list_, const std::string &gnome_)
{
    StringList tmpList;
    OneGnomePtr cur = _Impl->_expandData._gnomeMap[gnome_];
    std::string tmpStr = "";

    struct tm curTm;
    time_t curTime;
    time(&curTime);
    curTm = *localtime(&curTime);

    int tmpInt = 0;

    if (cur && cur->_creditLimits)
    {
        if (curTm.tm_mday >= cur->_billDates);
        {
            curTm.tm_mon++;
        }
        std::for_each(cur->_futureBillList.cbegin(), cur->_futureBillList.cend(), [&tmpList, &tmpStr, &curTm, &tmpInt](const int &x){
            curTm.tm_mon++;
            mktime(&curTm);
            tmpStr = std::to_string(curTm.tm_year - 100) + "-" + std::to_string(curTm.tm_mon + 1) + ": ";
            tmpStr += std::to_string(x);
            if (x)
            {
                tmpStr.insert(tmpStr.end() - 2, '.');
                tmpInt = 0;
            }
            else
            {
                tmpInt++;
            }
            tmpList.insert(tmpList.begin(), tmpStr);
        });
        if (tmpInt)
        {
            tmpList.erase(tmpList.begin(), tmpList.begin() + tmpInt - 1);
        }
        time(&curTime);
        curTm = *localtime(&curTime);
        if (curTm.tm_mday >= cur->_billDates);
        {
            curTm.tm_mon++;
            mktime(&curTm);
        }
        tmpInt = 0;
        std::for_each(cur->_billList.cbegin(), cur->_billList.cend(), [&tmpList, &tmpStr, &curTm, &tmpInt](const int &x){
            tmpStr = std::to_string(curTm.tm_year - 100) + "-" + std::to_string(curTm.tm_mon + 1) + ": ";
            tmpStr += std::to_string(x);
            if (x)
            {
                tmpInt = 0;
                tmpStr.insert(tmpStr.end() - 2, '.');
            }
            else
            {
                tmpInt++;
            }
            tmpList.push_back(tmpStr);
            curTm.tm_mon--;
            mktime(&curTm);
        });
        if (tmpInt)
        {
            tmpList.erase(tmpList.end() - tmpInt, tmpList.end());
        }
        list_.insert(list_.end(), tmpList.begin(), tmpList.end());
    }
}

void ODPGoblin::GetTotalDescription(std::string &str_)
{
    if (_Impl->_expandData._totalDescription.empty())
    {
        StringList tmpList;
        GetGnomeList(tmpList);
    }
    str_ = _Impl->_expandData._totalDescription;
}

ODPGoblin::ODPGoblin()
    : _Impl(new Impl)
{
    _Impl->ExpandData();
}

ODPGoblin::~ODPGoblin()
{
    delete _Impl;
    _Impl = NULL;
}

ODPGoblin::ExpandData::ExpandData()
{
    _ckk = std::make_shared<ODCKK>();
}

void ODPGoblin::ExpandData::clear()
{
    _goldFromList.clear();
    _ckk.reset();
    _ckk = std::make_shared<ODCKK>();
    _gnomeMap.clear();
    _coinList.clear();
    _dateList.clear();
    _lastCoinNum.clear();
    _lastGnomeNum.clear();
    _totalDescription.clear();
    _editCoinId = -1;
    _editCoinPtr = NULL;
}

bool ODPGoblin::ExpandData::appendGnome(const ODMBasePtr &ptr_)
{
    bool Result = false;
    ODMGnomePtr cur = std::static_pointer_cast<ODMGnome>(ptr_);
    if (cur)
    {
        Result = true;
        // Gnome
        if (_goldFromList.end() == std::find(_goldFromList.begin(), _goldFromList.end(), cur->_name))
        {
            // new gnome
            _goldFromList.push_back(cur->_name);
            _gnomeMap[cur->_name] = std::make_shared<ODPGoblin::OneGnome>();
            _gnomeMap[cur->_name]->_creditLimits = cur->_creditLimits;
            _gnomeMap[cur->_name]->_billDates = cur->_billDates;
            _gnomeMap[cur->_name]->_dueDay = cur->_dueDay;
            _gnomeMap[cur->_name]->_id = cur->_id;
            _gnomeMap[cur->_name]->_gnomeType = static_cast<int>(cur->_gnomeType);
            _gnomeMap[cur->_name]->_gnomeState = static_cast<int>(cur->_gnomeState);
        }
    }
    return Result;
}

bool ODPGoblin::ExpandData::chgGnome(const std::string &name1_, const std::string &name2_)
{
    bool Result = false;
    OneGnomePtr tmpPtr1 = _gnomeMap[name1_];
    OneGnomePtr tmpPtr2 = _gnomeMap[name2_];
    if (tmpPtr1 && tmpPtr2)
    {
        ODMBaseList tmpList;
        ODMGnomePtr gnomePtr1 = std::make_shared<ODMGnome>();
        ODMGnomePtr gnomePtr2 = std::make_shared<ODMGnome>();
        tmpList.push_back(gnomePtr1);
        tmpList.push_back(gnomePtr2);

        gnomePtr1->_preId = tmpPtr1->_id;
        gnomePtr1->_id = (tmpPtr1->_id + 122) * 12200;
        gnomePtr1->_name = name1_;
        gnomePtr1->_creditLimits = tmpPtr1->_creditLimits;
        gnomePtr1->_billDates = tmpPtr1->_billDates;
        gnomePtr1->_dueDay = tmpPtr1->_dueDay;
        gnomePtr1->_gnomeType = static_cast<ODMGnome::GnomeType>(tmpPtr1->_gnomeType);
        gnomePtr1->_gnomeState = static_cast<ODMGnome::GnomeState>(tmpPtr1->_gnomeState);

        gnomePtr2->_preId = tmpPtr2->_id;
        gnomePtr2->_id = (tmpPtr2->_id + 122) * 12200;
        gnomePtr2->_name = name2_;
        gnomePtr2->_creditLimits = tmpPtr2->_creditLimits;
        gnomePtr2->_billDates = tmpPtr2->_billDates;
        gnomePtr2->_dueDay = tmpPtr2->_dueDay;
        gnomePtr2->_gnomeType = static_cast<ODMGnome::GnomeType>(tmpPtr2->_gnomeType);
        gnomePtr2->_gnomeState = static_cast<ODMGnome::GnomeState>(tmpPtr2->_gnomeState);

        if (ODWayM::Instance()->UpdateModel(tmpList))
        {
            gnomePtr1->_preId = (tmpPtr1->_id + 122) * 12200;
            gnomePtr1->_id = tmpPtr2->_id;
            gnomePtr2->_preId = (tmpPtr2->_id + 122) * 12200;
            gnomePtr2->_id = tmpPtr1->_id;


            tmpPtr1->_id = gnomePtr1->_id;
            tmpPtr2->_id = gnomePtr2->_id;
            Result = ODWayM::Instance()->UpdateModel(tmpList);
        }
    }
    return Result;
}

bool ODPGoblin::ExpandData::appendCoin(const ODMBasePtr &ptr_)
{
    bool Result = false;
    ODMGoblinCoinPtr cur = std::static_pointer_cast<ODMGoblinCoin>(ptr_);
    OneGoblinCoinPtr tmpCoinPtr = NULL;
    int tmpIndex = -1;
    int tmpOffset = 0;
    int tmpInt = 0;
    int tmpFirstIndex = -1;
    int tmpEndIndex = -1;

    ODPGoblin::OneGnomePtr gnome = NULL;
    if (cur)
    {
        Result = true;
        // CKK
        _ckk->appendData(cur->_classify, cur->_kindFirst, cur->_kindSecond);

        // Compute Gnome
        // Pay
        if (cur->_state == ODMGoblinCoin::GoblinState::SimplePay ||
                cur->_state == ODMGoblinCoin::GoblinState::PayRevoke)
        {
            if (gnome = _gnomeMap[cur->_goldFrom])
            {
                tmpInt = cur->_count;
                // revoke
                if (cur->_state == ODMGoblinCoin::GoblinState::PayRevoke)
                {
                    tmpInt -= cur->_countSecond;
                }
                // CreditPay
                if (gnome->_creditLimits)
                {
                    if (ODTimeUtil::CalcuteBillList(cur->_id, gnome->_billDates, tmpIndex))
                    {
                        while (gnome->_billList.size() <= tmpIndex)
                        {
                            gnome->_billList.push_back(0);
                        }
                        gnome->_billList[tmpIndex] += tmpInt;
                    }
                }
                gnome->_balance -= tmpInt;
            }
        }
        // Installment pay
        else if (cur->_state == ODMGoblinCoin::GoblinState::InstallPay ||
                 cur->_state == ODMGoblinCoin::GoblinState::InstallWithdraw ||
                 cur->_state == ODMGoblinCoin::GoblinState::InstallBillSplit ||
                 cur->_state == ODMGoblinCoin::GoblinState::InstallPayReverse ||
                 cur->_state == ODMGoblinCoin::GoblinState::PrePaybackInstall ||
                 cur->_state == ODMGoblinCoin::GoblinState::PrePaybackInstallReverse ||
                 cur->_state == ODMGoblinCoin::GoblinState::InstallWithdrawReverse)
        {
            if (cur->_state == ODMGoblinCoin::GoblinState::InstallPay ||
                    cur->_state == ODMGoblinCoin::GoblinState::InstallWithdraw ||
                    cur->_state == ODMGoblinCoin::GoblinState::InstallBillSplit ||
                    cur->_state == ODMGoblinCoin::GoblinState::InstallPayReverse ||
                    cur->_state == ODMGoblinCoin::GoblinState::InstallWithdrawReverse)
            {
                gnome = _gnomeMap[cur->_goldFrom];
            }
            else
            {
                gnome = _gnomeMap[cur->_classify];
                cur->_countSecond = - cur->_countSecond;
                cur->_revokeId = - cur->_revokeId;
                cur->_count = - cur->_count;
            }
            if (gnome)
            {
                // CreditPay
                if (gnome->_creditLimits)
                {
                    // total pay     // revokeId is first month, countSecond are others
                    tmpInt = cur->_countSecond * (cur->_bill - 1) + cur->_revokeId;

                    if (ODTimeUtil::CalcuteBillList(cur->_id, gnome->_billDates, tmpIndex))
                    {
                        while (gnome->_billList.size() <= tmpIndex + 1)
                        {
                            gnome->_billList.push_back(0);
                        }

                        if (cur->_state == ODMGoblinCoin::GoblinState::InstallBillSplit)
                        {
                            gnome->_billList[tmpIndex + 1] -= cur->_count;
                        }

                        if (cur->_state == ODMGoblinCoin::GoblinState::PrePaybackInstall ||
                                cur->_state == ODMGoblinCoin::GoblinState::PrePaybackInstallReverse)
                        {
                            tmpOffset = std::stoi(cur->_content);
                        }
                        tmpIndex += tmpOffset;

                        // generate first bill
                        gnome->_billList[tmpIndex] += cur->_revokeId;
                        tmpFirstIndex = tmpIndex;
                        --tmpIndex;

                        // generate others bill list
                        int i = 1;
                        // before bill
                        for (; tmpIndex >= 0 && i < cur->_bill; --tmpIndex, ++i)
                        {
                            gnome->_billList[tmpIndex] += cur->_countSecond;
                        }
                        // future bill
                        for (int j = 0; i < cur->_bill; ++i, ++j)
                        {
                            while (gnome->_futureBillList.size() <= j)
                            {
                                gnome->_futureBillList.push_back(0);
                            }
                            gnome->_futureBillList[j] += cur->_countSecond;
                            tmpEndIndex = j;
                        }

                        // reverse
                        if (cur->_state == ODMGoblinCoin::GoblinState::InstallPayReverse ||
                                cur->_state == ODMGoblinCoin::GoblinState::PrePaybackInstallReverse ||
                                cur->_state == ODMGoblinCoin::GoblinState::InstallWithdrawReverse)
                        {
                            if (tmpEndIndex != -1)
                            {
                                gnome->_futureBillList[tmpEndIndex] -= cur->_countSecond - cur->_revokeId;
                            }
                            else
                            {
                                gnome->_billList[tmpIndex + 1] -= cur->_countSecond - cur->_revokeId;
                            }
                            gnome->_billList[tmpFirstIndex] -= cur->_revokeId - cur->_countSecond;
                        }
                    }
                }

                // Install Withdraw
                if (cur->_state == ODMGoblinCoin::GoblinState::InstallWithdraw && _gnomeMap[cur->_classify])
                {
                    _gnomeMap[cur->_classify]->_balance += cur->_count;
                }
                // Install Prepayback
                if (cur->_state == ODMGoblinCoin::GoblinState::PrePaybackInstall ||
                        cur->_state == ODMGoblinCoin::GoblinState::PrePaybackInstallReverse)
                {
                    _gnomeMap[cur->_goldFrom]->_balance += cur->_count;
                }

                if (cur->_state == ODMGoblinCoin::GoblinState::InstallBillSplit)
                {
                    // calculate addition tips
                    gnome->_balance -= tmpInt - cur->_count;
                }
                else
                {
                    gnome->_balance -= tmpInt;
                }
            }
        }
        // NormalTransit
        else if (cur->_state == ODMGoblinCoin::GoblinState::NormalTransit)
        {
            if (_gnomeMap[cur->_classify] && _gnomeMap[cur->_goldFrom])
            {
                // exchange rate
                bool isExchangeRate = _gnomeMap[cur->_classify]->_gnomeType != _gnomeMap[cur->_goldFrom]->_gnomeType;

                // gold to
                gnome = _gnomeMap[cur->_classify];
                if (gnome->_creditLimits)
                {
                    // repay credit
                    if (ODTimeUtil::CalcuteBillList(cur->_id, gnome->_billDates, tmpIndex))
                    {
                        // ready
                        while (gnome->_billList.size() <= tmpIndex + 1)
                        {
                            gnome->_billList.push_back(0);
                        }
                        if (tmpIndex + 1 + cur->_bill > 0)
                        {
                            while (gnome->_billList.size() <= tmpIndex + 1 + cur->_bill)
                            {
                                gnome->_billList.push_back(0);
                            }
                        }
                        // payback installment month
                        // countSecond is less
                        if (tmpIndex + 1 + cur->_bill >= 0)
                        {
                            gnome->_billList[tmpIndex + 1 + cur->_bill] -= cur->_count + cur->_countSecond;
                        }
                    }
                }
                if (isExchangeRate)
                {
                    gnome->_balance += cur->_countSecond;
                }
                else
                {
                    gnome->_balance += cur->_count + cur->_countSecond;
                }

                // gold from
                gnome = _gnomeMap[cur->_goldFrom];
                if (!cur->_kindSecond.empty())
                {
                    tmpInt = std::stoi(cur->_kindSecond);
                }
                if (gnome->_creditLimits)
                {
                    // credit withdraw
                    if (ODTimeUtil::CalcuteBillList(cur->_id, gnome->_billDates, tmpIndex))
                    {
                        // ready
                        while (gnome->_billList.size() <= tmpIndex)
                        {
                            gnome->_billList.push_back(0);
                        }
                        gnome->_billList[tmpIndex] += cur->_count + tmpInt;
                    }
                }
                // tmpInt is tips
                gnome->_balance -= cur->_count + tmpInt;
            }
        }

        // add to coinList
        tmpCoinPtr = std::make_shared<OneGoblinCoin>();
        if (cur->_state == ODMGoblinCoin::GoblinState::SimplePay ||
                cur->_state == ODMGoblinCoin::GoblinState::PayRevoke ||
                cur->_state == ODMGoblinCoin::GoblinState::InstallPay ||
                cur->_state == ODMGoblinCoin::GoblinState::InstallBillSplit ||
                cur->_state == ODMGoblinCoin::GoblinState::InstallPayReverse)
        {
            tmpCoinPtr->_classify = cur->_classify;
            tmpCoinPtr->_kindFirst = cur->_kindFirst;
            tmpCoinPtr->_kindSecond = cur->_kindSecond;
        }
        else
        {
            tmpCoinPtr->_goldTo = cur->_classify;
            if (!cur->_kindSecond.empty())
            {
                tmpCoinPtr->_tips = std::stoi(cur->_kindSecond);
            }
        }
        tmpCoinPtr->_state = static_cast<int>(cur->_state);
        tmpCoinPtr->_goldFrom = cur->_goldFrom;
        tmpCoinPtr->_count = cur->_count;
        tmpCoinPtr->_content = cur->_content;
        tmpCoinPtr->_id = cur->_id;

        ODVectorUtil::RefreshInsert<std::string>(_dateList, ODTimeUtil::Timestamp2String(cur->_id, "%y-%m-%d"));
        _coinList[_dateList[0]].push_back(tmpCoinPtr);
    }
    return Result;
}

ODPGoblin::OneGnome::OneGnome()
{
    _id = 0;
    _balance = 0;
    _creditLimits = 0;
    _billDates = 1;
    _dueDay = 1;
    _gnomeType = 0;
    _gnomeState = 0;
    _billList.push_back(0);
    _billList.push_back(0);
}

ODPGoblin::OneGoblinCoin::OneGoblinCoin()
{
    _id = -1;
    _goldFrom = "";
    _goldTo = "";

    _classify = "";
    _kindFirst = "";
    _kindSecond = "";

    _content = "";

    _state = 0;

    _tips = 0;
    _count = 0;
}
