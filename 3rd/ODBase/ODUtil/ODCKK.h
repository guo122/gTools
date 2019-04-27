//====================================================================
//  ODCKK.h
//  created 6.13.18
//  written by odddd0
//
//  https://github.com/odddd0/ODWay
//====================================================================

#ifndef _ODCKK_H_912C8E8C5AD8F6DFAE13002ED4214C6A_
#define _ODCKK_H_912C8E8C5AD8F6DFAE13002ED4214C6A_

#include <ODMBase/ODBaseTypes.h>

class ODCKK
{
public:
    ODCKK();
    ~ODCKK();

public:
    // ignore empty ckk
    bool appendData(const std::string &classify_, const std::string &kindFirst_, const std::string &kindSecond_);

public:
    bool classifyList(StringList &list);
    bool kindFirstList(StringList &list, const std::string &classify_ = "");
    bool kindSecondList(StringList &list, const std::string &classify_ = "", const std::string &kindFirst_ = "");

public:
    void clear();

private:
    struct Impl;
    Impl *_Impl;
};
typedef std::shared_ptr<ODCKK> CKKPtr;

#endif // _ODCKK_H_912C8E8C5AD8F6DFAE13002ED4214C6A_
