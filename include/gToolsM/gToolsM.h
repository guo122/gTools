//====================================================================
//  gToolsM.h
//  created 6.3.18
//  written by gzy
//
//  https://github.com/guo122
//====================================================================

#ifndef GTOOLSM_H_16EC2CC73F70B84A068EA4AB4E0606E4
#define GTOOLSM_H_16EC2CC73F70B84A068EA4AB4E0606E4

#include <gBase/gDB.h>

class gToolsM
{
public:
    static gToolsM *Instance(const gString &DBPath = "");

public:
    void ReadDB();

public:
    bool AddModel(const gzy::gMBasePtr &ptr_);

public:
    // only append
    void GetList(const gString &type_, gzy::gMBaseList &list);
    void GetPtr(const gString &type_, const int &id_, gzy::gMBasePtr &ptr_);

public:
    bool DeleteModel(const gString &type_, const int &id_);

public:
    bool UpdateModel(const gzy::gMBasePtr &ptr_);
    bool UpdateModel(const gzy::gMBaseList &list_);

private:
    struct Impl;
    Impl *_Impl;

private:
    gToolsM();
    ~gToolsM();
};

#endif // GTOOLSM_H_16EC2CC73F70B84A068EA4AB4E0606E4
