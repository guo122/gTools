//====================================================================
//  ODPGoblin.h
//  created 6.12.18
//  written by odddd0
//
//  https://github.com/odddd0/ODWay
//====================================================================

#ifndef _ODPGOBLIN_H_6B74E5D188DF431726ACC138C35490AD_
#define _ODPGOBLIN_H_6B74E5D188DF431726ACC138C35490AD_

#include <ODMBase/ODBaseTypes.h>
#include <ODUtil/ODCKK.h>
#include <ODWayM/ODMGoblin.h>
#include <ODWayM/ODMGoblinCoin.h>
#include <ODWayM/ODMGnome.h>

class ODPGoblin
{
    struct OneGnome
    {
        OneGnome();

        int _id;

        int _balance;
        int _creditLimits;
        int _billDates;
        int _dueDay;
        int _gnomeType;
        int _gnomeState;
        std::vector<int> _billList;
        std::vector<int> _futureBillList;
    };
    typedef std::shared_ptr<OneGnome> OneGnomePtr;

    struct OneGoblinCoin
    {
        OneGoblinCoin();
        int _id;
        std::string _goldFrom;
        std::string _goldTo;

        std::string _classify;
        std::string _kindFirst;
        std::string _kindSecond;

        std::string _content;

        int _state;

        int _tips;
        int _count;
    };
    typedef std::shared_ptr<OneGoblinCoin> OneGoblinCoinPtr;

    struct ExpandData
    {
        ExpandData();
        void clear();
        bool appendGnome(const ODMBasePtr &ptr_);
        bool chgGnome(const std::string &name1_, const std::string &name2_);
        bool appendCoin(const ODMBasePtr &ptr_);

        std::map<std::string, std::vector<OneGoblinCoinPtr>> _coinList;
        StringList _goldFromList;
        StringList _dateList;
        std::map<std::string, OneGnomePtr> _gnomeMap;
        CKKPtr _ckk;
        IntList _lastCoinNum;
        IntList _lastGnomeNum;
        std::string _totalDescription;
        int _editCoinId;
        ODMBasePtr _editCoinPtr;
    };
public:
    static ODPGoblin * Instance();

public:
    // add
    bool AddGoblin(const ODMBasePtr &ptr_);
    void GetCKK(CKKPtr &ckk_);

    // get
    void GetCoinList(StringList &list_, const std::string &goldType_ = "");
    bool DelCoin(const int &index_);
    bool RevokeCoin(const int &index_);
    bool SetEditCoin(const int &index_);
    bool DelEditCoin();
    bool GetEditCoinText(std::string &str_, bool &revoke_, int &year_, int &month_, int &day_, int &hour_, int &minute_, int &second_, int &count_, int &countSecond_);
    bool SaveEditCoin(
            const bool &revoke_,
            const int &year_,
            const int &month_,
            const int &day_,
            const int &hour_,
            const int &minute_,
            const int &second_,
            const int &countSecond_,
            const std::string &class_,
            const int &remainMonth_);

public:
    // Gnome
    // get
    bool UpGnome(const int &index_);
    void GetGoldFromList(StringList &list_);
    void GetGnomeList(StringList &list_);
    void GetGnomeNameByIndex(const int &index_, std::string &name_);

    // todo not clear
    void GetGnomeBillList(StringList &list_, const std::string &gnome_);

public:
    //
    void GetTotalDescription(std::string &str_);

private:
    struct Impl;
    Impl *_Impl;

private:
    ODPGoblin();
    ~ODPGoblin();
};

#endif // _ODPGOBLIN_H_6B74E5D188DF431726ACC138C35490AD_
