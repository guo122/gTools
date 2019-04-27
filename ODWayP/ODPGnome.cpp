//====================================================================
//  ODPGnome.cpp
//  created 6.12.18
//  written by odddd0
//
//  https://github.com/odddd0/ODWay
//====================================================================

#include <ODWayM/ODWayM.h>

#include <ODUtil/ODUtil.h>

#include "ODPGnome.h"

struct ODPGnome::Impl
{
    Impl(){}

    void ExpandData()
    {

    }
};

ODPGnome *ODPGnome::Instance()
{
    static ODPGnome * obj = new ODPGnome;
    return obj;
}

ODPGnome::ODPGnome()
    : _Impl(new Impl)
{
    _Impl->ExpandData();
}

ODPGnome::~ODPGnome()
{
    delete _Impl;
    _Impl = NULL;
}
