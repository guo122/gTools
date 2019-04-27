//====================================================================
//  ODMBase.h
//  created 6.3.18
//  written by odddd0
//
//  https://github.com/odddd0/ODWay
//====================================================================

#ifndef _ODMBASE_H_2ECF0B1817956EF0747B103CD8300A09_
#define _ODMBASE_H_2ECF0B1817956EF0747B103CD8300A09_

#include "ODBaseTypes.h"

struct ODMBase
{
public:
    ODMBase(const int &id_);
    ODMBase(const std::string &type_);
    ODMBase(const std::string &type_, const int &id_);

public:
    // The following 5 function must implementation.
    static void GetSqlCreateTable(std::string &sql_){};
    static void GetSqlSelect(std::string &sql_){};
    static void GetSqlDelete(std::string &sql_, const int &id_){};
    virtual void GetSqlInsert(std::string &sql_) = 0;
    virtual void GetSqlUpdate(std::string &sql_) = 0;

public:
    int _preId;
    int _id;
    std::string _type;
};
typedef std::shared_ptr<ODMBase> ODMBasePtr;
typedef std::vector<ODMBasePtr> ODMBaseList;

#endif // _ODMBASE_H_2ECF0B1817956EF0747B103CD8300A09_
