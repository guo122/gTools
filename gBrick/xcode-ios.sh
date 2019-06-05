#!/bin/bash

if [ "$1" == "-h" ] ; then
	echo "t[team]"
	echo "ti[team, ident]"
else
	if [ "$1" == "t" ] ; then
		ios_team="$2"
		extra_d="$3"
	elif [ "$1" == "ti" ] ; then
		ios_team="$2"
		ios_ident="$3"
		extra_d="$4"
	else
		ios_team=`cat ~/etc/env_default_ios_testteam 2>/dev/null`
		ios_ident=`cat ~/etc/env_default_ios_testapp 2>/dev/null`
		extra_d="$1"
	fi

	if [ "$ios_team" != "" ] ; then
		extra_d=$extra_d" -DCMAKE_XCODE_ATTRIBUTE_DEVELOPMENT_TEAM="$ios_team
	fi
	if [ "$ios_ident" != "" ] ; then
		extra_d=$extra_d" -DBUNDLE_IDENT="$ios_ident
	fi

	cmake -E make_directory "build-ios" && cmake -E chdir "build-ios" cmake -G "Xcode" ../ -DCMAKE_TOOLCHAIN_FILE=../../BuildScript/cmake/ios-toolchain/ios.toolchain.cmake -DPLATFORM=OS64COMBINED $extra_d

	if [ "$?" == 0 ] ; then
		open build-ios/*.xcodeproj
	fi
fi
