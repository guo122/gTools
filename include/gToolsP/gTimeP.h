//====================================================================
//  gTimeP.h
//  created 6.4.18
//  written by gzy
//
//  https://github.com/guo122
//====================================================================

#ifndef GTIMEP_H_E059E08A3569020BF0BF4ED7D07ADC10
#define GTIMEP_H_E059E08A3569020BF0BF4ED7D07ADC10

#include <gToolsM/gTimeM.h>

typedef gVector<gPair<gString, int>> SIMapList;

class gTimeP
{
    struct LastChart
    {
        LastChart(const gString &date_, const int &value_)
            : _date(date_)
            , _color("")
            , _value(value_)
        {}

        gString _date;
        gString _color;
        int _value;
    };
    typedef gSharedPtr<LastChart> LastChartPtr;
    struct LastChartList
    {
        void clear();
        void CalColor();

        gString _classify;
        gString _kindFirst;
        gString _kindSecond;
        gString _startDate;
        gString _endDate;
        int _totalValue;
        gVector<LastChartPtr> _list;
    };
    struct OneTip
    {
        int _time;
        int _durationSecond;
        gString _classify;
        gString _kindFirst;
        gString _kindSecond;
        gString _content;
    };
    typedef gSharedPtr<OneTip> OneTipPtr;

    struct OneDay
    {
        gVector<OneTipPtr> _tipList;
    };
    typedef gSharedPtr<OneDay> OneDayPtr;

    struct DaySum
    {
        void AddTip(const gString &classify_,
                    const gString &kindFirst_,
                    const gString &kindSecond_,
                    const int &second_);
        bool ToString(gzy::gStringList &strList_);
        bool ToString(const gString &classify_, gzy::gStringList &strList_);
        bool ToString(const gString &classify_, const gString &kindFirst_, gzy::gStringList &strList_);
        bool ToString(const gString &classify_, const gString &kindFirst_, const gString &kindSecond_, gzy::gStringList &strList_);

        // __SUM__ is sum.
        gMap<gString, int> _classifySum;
        gMap<gString, gMap<gString, int>> _kindFirstSum;
        gMap<gString, gMap<gString, gMap<gString, int>>> _kindSecondSum;
    };
    typedef gSharedPtr<DaySum> DaySumPtr;

    struct ExpandData
    {
        void clear();

        gzy::gStringList _dateList;
        gMap<gString, OneDayPtr> _dayList;
        gMap<gString, DaySumPtr> _sumList;
        gzy::gStringList _classifyList;
        gzy::gStringListPtrMap _kindFirstList;
        gMap<gString, gzy::gStringListPtrMap> _kindSecondList;
    };
public:
    static gTimeP * Instance();

public:
    // overview
    void GetRunningTimeStr(gString &str_);
    gString GetDate();

public:
    // TableTimeChart
    // first init lastChartData
    bool GetLastCKKSum(const gzy::gStringList &ckkList_, const int &lastCount, gzy::gIntList &IntList_);
    // second
    bool GetLastCKKSum(gzy::gStringList &strList_);
    bool GetLastCKKSumColor(const int &index_, gString &color_);
    bool SetDateByChartSum(const int &index_);
    gString GetStartDate();
    gString GetEndDate();
    bool IsChartSumCurrentDay(const int &index_);
    int getChartSumCurrentIndex();

public:
    // TableTimeSum
    gString GetCurSum();
    void GetCurSumList(
            gVector<gzy::gStringList> &classifyList_,
            gVector<gVector<gzy::gStringList>> &kindFirstList_,
            gVector<gVector<gVector<gzy::gStringList>>> &kindSecondList_);
    void GetAllSumList(
            gVector<gzy::gStringList> &classifyList_,
            gVector<gVector<gzy::gStringList>> &kindFirstList_,
            gVector<gVector<gVector<gzy::gStringList>>> &kindSecondList_);

public:
    // TableTimeList
    void GetCurList(gzy::gStringList &list);
    bool DelDurTime(const int &index_);
    bool CalDurTime(const int &index1_, const int &index2_, gString &str_);
    bool GetPopList(const gzy::gStringList &ckkList_, gzy::gIntList &indexList_);

public:
    // TableTimeAdd
    bool AddTime(const gTimeMPtr &curPtr_);
    bool FastIdle();
    void GetClassifyList(gzy::gStringList &list);
    void GetKindFirstList(gzy::gStringList &list, const gString &key_ = "");
    void GetKindSecondList(gzy::gStringList &list, const gString &classify_, const gString &key_);

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
    gTimeP();
    ~gTimeP();
};

#endif // GTIMEP_H_E059E08A3569020BF0BF4ED7D07ADC10
