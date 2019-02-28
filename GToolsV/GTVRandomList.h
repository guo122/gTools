//====================================================================
//  GTVRandomList.h
//  created 2.20.19
//  written by gzy
//
//  https://github.com/guo122
//====================================================================

#ifndef _GTVRANDOMLIST_H_0A771846F866A63569EA88B1568B7781_
#define _GTVRANDOMLIST_H_0A771846F866A63569EA88B1568B7781_

#include <QObject>
#include <QVariant>

class GTVRandomList : public QObject
{
    Q_OBJECT

public:
    explicit GTVRandomList(QObject *parent = nullptr);

public slots:
    QString getDescription(const QString &name_);

public slots:
    bool initRandomList(const QString &kind_, const int &mode_);
    QString getRandom();
    int getRandomFontSize();
    int getRandomProgress();

public slots:
    bool addData(const QString &name_, const QString &kind_);
    QStringList getKindList();
    int getKindSize();
    QStringList getNameList(const QString &kind_);
};

#endif // _GTVRANDOMLIST_H_0A771846F866A63569EA88B1568B7781_
