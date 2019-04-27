#!/bin/bash

cd `dirname $0`

function cpLib() {
	cp -rf ../../ODBase/build-${1}-Desktop_Qt_5_11_0_clang_64bit-Debug/lib${1}.a ./ODBase/lib/clang64-Debug/ 2>/dev/null
	cp -rf ../../ODBase/build-${1}-Desktop_Qt_5_11_0_clang_64bit-Release/lib${1}.a ./ODBase/lib/clang64-Release/ 2>/dev/null
	cp -rf ../../ODBase/build-${1}-Qt_5_11_0_for_iOS-Debug/lib${1}.a ./ODBase/lib/iOS-Debug/ 2>/dev/null
	cp -rf ../../ODBase/build-${1}-Qt_5_11_0_for_iOS-Release/lib${1}.a ./ODBase/lib/iOS-Release/ 2>/dev/null
}

# clear old version
rm -rf ./ODBase/ODMBase/*
rm -rf ./ODBase/ODUtil/*
rm -rf ./ODBase/lib/clang64-Debug/*
rm -rf ./ODBase/lib/clang64-Release/*
rm -rf ./ODBase/lib/iOS-Debug/*
rm -rf ./ODBase/lib/iOS-Release/*

# copy header file
cp -rf ../../ODBase/ODMBase/*.h ./ODBase/ODMBase/
cp -rf ../../ODBase/ODUtil/*.h ./ODBase/ODUtil/

# copy library
# ODMBase
cpLib ODMBase
cpLib ODUtil
