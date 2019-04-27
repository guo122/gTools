//====================================================================
//  ODPTime.h
//  created 6.4.18
//  written by odddd0
//
//  https://github.com/odddd0/ODWay
//====================================================================

#ifndef _ODPTIME_H_E059E08A3569020BF0BF4ED7D07ADC10_
#define _ODPTIME_H_E059E08A3569020BF0BF4ED7D07ADC10_

#include <ODMBase/ODBaseTypes.h>
#include <ODWayM/ODMTime.h>

typedef std::vector<std::pair<std::string, int>> SIMapList;

class ODPTime
{
    struct LastChart
    {
        LastChart(const std::string &date_, const int &value_)
            : _date(date_)
            , _color("")
            , _value(value_)
        {}

        std::string _date;
        std::string _color;
        int _value;
    };
    typedef std::shared_ptr<LastChart> LastChartPtr;
    struct LastChartList
    {
        void clear();
        void CalColor();

        std::string _classify;
        std::string _kindFirst;
        std::string _kindSecond;
        std::string _startDate;
        std::string _endDate;
        int _totalValue;
        std::vector<LastChartPtr> _list;
    };
    struct OneTip
    {
        int _time;
        int _durationSecond;
        std::string _classify;
        std::string _kindFirst;
        std::string _kindSecond;
        std::string _content;
    };
    typedef std::shared_ptr<OneTip> OneTipPtr;

    struct OneDay
    {
        std::vector<OneTipPtr> _tipList;
    };
    typedef std::shared_ptr<OneDay> OneDayPtr;

    struct DaySum
    {
        void AddTip(const std::string &classify_,
                    const std::string &kindFirst_,
                    const std::string &kindSecond_,
                    const int &second_);
        bool ToString(StringList &strList_);
        bool ToString(const std::string &classify_, StringList &strList_);
        bool ToString(const std::string &classify_, const std::string &kindFirst_, StringList &strList_);
        bool ToString(const std::string &classify_, const std::string &kindFirst_, const std::string &kindSecond_, StringList &strList_);

        // __SUM__ is sum.
        std::map<std::string, int> _classifySum;
        std::map<std::string, std::map<std::string, int>> _kindFirstSum;
        std::map<std::string, std::map<std::string, std::map<std::string, int>>> _kindSecondSum;
    };
    typedef std::shared_ptr<DaySum> DaySumPtr;

    struct ExpandData
    {
        void clear();

        StringList _dateList;
        std::map<std::string, OneDayPtr> _dayList;
        std::map<std::string, DaySumPtr> _sumList;
        StringList _classifyList;
        StringListPtrMap _kindFirstList;
        std::map<std::string, StringListPtrMap> _kindSecondList;
    };
public:
    static ODPTime * Instance();

public:
    // overview
    void GetRunningTimeStr(std::string &str_);
    std::string GetDate();

public:
    // TableTimeChart
    // first init lastChartData
    bool GetLastCKKSum(const StringList &ckkList_, const int &lastCount, IntList &intList_);
    // second
    bool GetLastCKKSum(StringList &strList_);
    bool GetLastCKKSumColor(const int &index_, std::string &color_);
    bool SetDateByChartSum(const int &index_);
    std::string GetStartDate();
    std::string GetEndDate();
    bool IsChartSumCurrentDay(const int &index_);
    int getChartSumCurrentIndex();

public:
    // TableTimeSum
    std::string GetCurSum();
    void GetCurSumList(
            std::vector<StringList> &classifyList_,
            std::vector<std::vector<StringList>> &kindFirstList_,
            std::vector<std::vector<std::vector<StringList>>> &kindSecondList_);
    void GetAllSumList(
            std::vector<StringList> &classifyList_,
            std::vector<std::vector<StringList>> &kindFirstList_,
            std::vector<std::vector<std::vector<StringList>>> &kindSecondList_);

public:
    // TableTimeList
    void GetCurList(StringList &list);
    bool DelDurTime(const int &index_);
    bool CalDurTime(const int &index1_, const int &index2_, std::string &str_);
    bool GetPopList(const StringList &ckkList_, IntList &indexList_);

public:
    // TableTimeAdd
    bool AddTime(const ODMTimePtr &curPtr_);
    bool FastIdle();
    void GetClassifyList(StringList &list);
    void GetKindFirstList(StringList &list, const std::string &key_ = "");
    void GetKindSecondList(StringList &list, const std::string &classify_, const std::string &key_);

public:
    // turn day
    bool PrevCur();
    bool FirstCur();
    bool NextCur();
    bool LastCur();

private:
    struct Impl;
    Impl *_Impl;

private:
    ODPTime();
    ~ODPTime();
};

#endif // _ODPTIME_H_E059E08A3569020BF0BF4ED7D07ADC10_
