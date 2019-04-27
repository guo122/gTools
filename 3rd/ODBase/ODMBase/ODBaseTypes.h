//====================================================================
//  ODBaseTypes.h
//  created 6.3.18
//  written by odddd0
//
//  https://github.com/odddd0/ODWay
//====================================================================

#ifndef _ODBASETYPES_H_01FB28F8460F28622C3EDC8271E16576_
#define _ODBASETYPES_H_01FB28F8460F28622C3EDC8271E16576_

#include <string>
#include <vector>
#include <map>

typedef std::vector<std::string> StringList;
typedef std::vector<StringList> StringTable;

typedef std::shared_ptr<StringList> StringListPtr;

typedef std::map<std::string, StringList> StringListMap;
typedef std::map<std::string, StringListPtr> StringListPtrMap;

typedef std::vector<int> IntList;

#endif // _ODBASETYPES_H_01FB28F8460F28622C3EDC8271E16576_
