//====================================================================
//  ODPEfg.h
//  created 7.17.18
//  written by odddd0
//
//  https://github.com/odddd0/ODWay
//====================================================================

#ifndef _ODPEFG_H_DF512EA1A7A8DA7E8B7F0078DBC10725_
#define _ODPEFG_H_DF512EA1A7A8DA7E8B7F0078DBC10725_

#include <ODMBase/ODBaseTypes.h>
#include <ODWayM/ODMEfg.h>

class ODPEfg
{
    struct OneTip
    {
        int _id;
        int _state;
        std::string _name;
        std::string _classify;
        int _markTime;
    };
    typedef std::shared_ptr<OneTip> OneTipPtr;

    struct ExpandData
    {
        void clear()
        {
            _tipList.clear();
            _classifyList.clear();
            _classifyIsMap.clear();
            _lastEfgIdList.clear();
            _lastEfgAllColorList.clear();
            _markNum = 0;
            _totalNum = 0;
        }

        std::vector<OneTipPtr> _tipList;
        std::vector<std::string> _classifyList;
        std::map<std::string, int> _classifyIsMap;
        std::vector<int> _lastEfgIdList;
        std::vector<std::string> _lastEfgAllColorList;
        int _markNum;
        int _totalNum;
    };
public:
    static ODPEfg * Instance();

public:
    void GetEfgStrList(StringList &strList_);
    void GetEfgAllList(StringList &strList_);
    void GetProgressStr(std::string &str_);
    bool GetEfgAllColor(const int &index_, std::string &color_);

public:
    bool MarkIndex(const int &index_);
    bool UnMarkIndex(const int &index_);

private:
    struct Impl;
    Impl *_Impl;

private:
    ODPEfg();
    ~ODPEfg();
};

#endif // _ODPEFG_H_DF512EA1A7A8DA7E8B7F0078DBC10725_
