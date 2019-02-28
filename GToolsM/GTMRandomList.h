//====================================================================
//  GTMRandomList.h
//  created 2.20.19
//  written by gzy
//
//  https://github.com/guo122
//====================================================================

#ifndef _GTMRANDOMLIST_H_02AC5B7D1A35F703B7A279596AA968EC_
#define _GTMRANDOMLIST_H_02AC5B7D1A35F703B7A279596AA968EC_

#include <QVector>
#include <QVariant>
#include <QString>

struct GTMRandomList
{
public:
    GTMRandomList();
    GTMRandomList(const QVector<QVariant> &list_);

public:
    static void GetSqlCreateTable(QString &sql_);
    static void GetSqlSelect(QString &sql_);
    static void GetSqlDelete(QString &sql_, const int &id_);
    void GetSqlUpdate(QString &sql_);
    void GetSqlInsert(QString &sql_);

public:
    int _preId;
    int _id;
    QString _name;
    QString _kind;
    double _lastReadDate;
    int _lastReadState;
};
typedef std::shared_ptr<GTMRandomList> GTMRandomListPtr;

#endif // _GTMRANDOMLIST_H_02AC5B7D1A35F703B7A279596AA968EC_
