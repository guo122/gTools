//====================================================================
//  GToolsM.h
//  created 2.20.19
//  written by gzy
//
//  https://github.com/guo122
//====================================================================

#ifndef _GTOOLSM_H_56B31F0D66E6380D47665546CCC3201A_
#define _GTOOLSM_H_56B31F0D66E6380D47665546CCC3201A_

#include <QVector>
#include <QVariant>
#include <QString>

#include "GTMRandomList.h"

class GToolsM
{
public:
    static GToolsM *Instance();

public:
    bool Init(const QString &DBPath);
    void ReadDB();

public:
    bool AddData(const GTMRandomListPtr &ptr_);
    void GetData(QVector<GTMRandomListPtr> &list_);
    bool GetRandomListByKind(const QString &kind_, QStringList &list_);
    bool GetRandomKind(QStringList &kindList_);

private:
    struct Impl;
    Impl *_Impl;

private:
    GToolsM();
    ~GToolsM();
};

#endif // _GTOOLSM_H_56B31F0D66E6380D47665546CCC3201A_
