//====================================================================
//  GTPRandomList.h
//  created 2.20.18
//  written by gzy
//
//  https://github.com/guo122
//====================================================================

#ifndef _GTPRANDOMLIST_H_B2682FAF9255B6AD3B7038F046E05EAC_
#define _GTPRANDOMLIST_H_B2682FAF9255B6AD3B7038F046E05EAC_

#include <GToolsM/GTMRandomList.h>
#include <GToolsM/GToolsM.h>

class GTPRandomList
{
    struct AutoRandomList
    {
        AutoRandomList(const int &num_, const bool &unlimit_ = false)
            : _cur(-1)
            , _unlimit(unlimit_)
        {
            init(num_);
        }
        AutoRandomList()
            : _cur(-1), _unlimit(false) {}

        void init(const int &num_, const bool &unlimit_ = false);
        void clear();
        int next();
        bool empty();

        int getProgress();
        int getIndex();

        QVector<int> _list;
        int _cur;
        bool _unlimit;
    };
    typedef std::shared_ptr<AutoRandomList> AutoRandomListPtr;

public:
    static GTPRandomList * Instance();

public:
    bool AddData(const QString &name_, const QString &kind_);

public:
    void GetKindList(QStringList &list_);
    void GetNameList(const QString &kind_, QStringList &list_);

public:
    // mode 1: rand; 2: plan
    bool InitRandomList(const QString &kind_, const int &mode_);
    QString RandomData(const bool &forceRand = false);
    QString HomepageRandom();
    int RandomDataFontSize();
    int RandomDataProgress();

private:
    static int _StaticSeed;

private:
    struct Impl;
    Impl *_Impl;

private:
    GTPRandomList();
    ~GTPRandomList();
};

#endif // _GTPRANDOMLIST_H_B2682FAF9255B6AD3B7038F046E05EAC_
