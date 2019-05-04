//====================================================================
//  gToolsM.cpp
//  created 6.3.18
//  written by gzy
//
//  https://github.com/guo122
//====================================================================

#include "gTimeM.h"

#include "gToolsM.h"

struct gToolsM::Impl
{
    bool UpdateImpl(const gzy::gMBaseList &list_)
    {
        bool Result = false;
        
        if (gzy::gDB::Instance()->Update(list_))
        {
            Result = true;

            gForeach(list_.cbegin(), list_.cend(), [&](const gzy::gMBasePtr &x){
                auto pos = gFindIf(_DBList.cbegin(), _DBList.cend(), [&](const gzy::gMBasePtr &y){
                    return x->_id == y->_id && x->_type == y->_type;
                });
                if (pos != _DBList.end())
                {
                    _DBList.erase(pos);
                    _DBList.push_back(x);
                }
            });

            gSort(_DBList.begin(), _DBList.end(), [](gzy::gMBasePtr x, gzy::gMBasePtr y){
                return x->_id < y->_id;
            });
        }
        return Result;
    }

    gzy::gMBaseList _DBList;
};

gToolsM *gToolsM::Instance(const gString &DBPath)
{
    static gToolsM * obj = new gToolsM;
    if (!DBPath.empty())
    {
        gzy::gDB::Instance()->Setup(DBPath);
    }
    return obj;
}

gToolsM::gToolsM()
    : _Impl(new Impl)
{
}

gToolsM::~gToolsM()
{
    delete _Impl;
    _Impl = NULL;
}

void gToolsM::ReadDB()
{
    _Impl->_DBList.clear();
    gzy::gDB::Instance()->Select<gTimeM>(_Impl->_DBList);
}

bool gToolsM::AddModel(const gzy::gMBasePtr &ptr_)
{
    bool Result = false;
    gzy::gMBaseList tmpList;
    tmpList.push_back(ptr_);
    if (gzy::gDB::Instance()->Insert(tmpList))
    {
        Result = true;
        _Impl->_DBList.push_back(ptr_);
        gSort(_Impl->_DBList.begin(), _Impl->_DBList.end(), [](gzy::gMBasePtr x, gzy::gMBasePtr y){
            return x->_id < y->_id;
        });
    }
    return Result;
}

void gToolsM::GetList(const gString &type_, gzy::gMBaseList &list)
{
    gForeach(_Impl->_DBList.begin(), _Impl->_DBList.end(), [&list, type_](gzy::gMBasePtr &x){
        if (x->_type == type_)
        {
            list.push_back(x);
        }
    });
}

void gToolsM::GetPtr(const gString &type_, const int &id_, gzy::gMBasePtr &ptr_)
{
    auto pos = gFindIf(_Impl->_DBList.begin(), _Impl->_DBList.end(), [&](gzy::gMBasePtr &x){
        return x->_type == type_ && x->_id == id_;
    });
    if (pos != _Impl->_DBList.end())
    {
        ptr_ = *pos;
    }
    else
    {
        ptr_ = NULL;
    }
}

bool gToolsM::DeleteModel(const gString &type_, const int &id_)
{
    bool Result = false;
    gzy::gIntList tmpList;
    tmpList.push_back(id_);
    if (type_ == "gTimeM")
    {
        Result = gzy::gDB::Instance()->Delete<gTimeM>(tmpList);
    }
    if (Result)
    {
        auto pos = gFindIf(_Impl->_DBList.begin(), _Impl->_DBList.end(), [id_, type_](gzy::gMBasePtr &x){
            return x->_id == id_ && x->_type == type_;
        });
        if (pos != _Impl->_DBList.end())
        {
            _Impl->_DBList.erase(pos);
        }
    }
    return Result;
}

bool gToolsM::UpdateModel(const gzy::gMBasePtr &ptr_)
{
    gzy::gMBaseList tmpList;
    tmpList.push_back(ptr_);
    return _Impl->UpdateImpl(tmpList);
}

bool gToolsM::UpdateModel(const gzy::gMBaseList &list_)
{
    return _Impl->UpdateImpl(list_);
}
