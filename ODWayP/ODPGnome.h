//====================================================================
//  ODPGnome.h
//  created 6.12.18
//  written by odddd0
//
//  https://github.com/odddd0/ODWay
//====================================================================

#ifndef _ODPGNOME_H_47E200D3EE43F043E3D3F45DCFAB1E07_
#define _ODPGNOME_H_47E200D3EE43F043E3D3F45DCFAB1E07_

#include <ODMBase/ODBaseTypes.h>
#include <ODWayM/ODMGnome.h>

class ODPGnome
{
public:
    static ODPGnome * Instance();

private:
    struct Impl;
    Impl *_Impl;

private:
    ODPGnome();
    ~ODPGnome();
};

#endif // _ODPGNOME_H_47E200D3EE43F043E3D3F45DCFAB1E07_
