//====================================================================
//  ODVectorUtil.h
//  created 6.5.18
//  written by odddd0
//
//  https://github.com/odddd0/ODWay
//====================================================================

#ifndef _ODVECTORUTIL_H_79F5F3350B2857C60993735A97CE701C_
#define _ODVECTORUTIL_H_79F5F3350B2857C60993735A97CE701C_

#include <ODMBase/ODBaseTypes.h>

class ODVectorUtil
{
public:
    ODVectorUtil();

public:
    template<typename T>
    static bool RefreshInsert(std::vector<T> &list_, const T &val_)
    {
        bool Result = true;
        for (auto pos = list_.begin(); pos != list_.end(); ++pos)
        {
            if ((*pos) == val_)
            {
                list_.erase(pos);
                Result = false;
                break;
            }
        }
        list_.insert(list_.begin(), val_);
        return Result;
    }
};

#endif // _ODVECTORUTIL_H_79F5F3350B2857C60993735A97CE701C_
