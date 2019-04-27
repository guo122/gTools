//====================================================================
//  ODMGnomeTest.cpp
//  created 6.12.18
//  written by odddd0
//
//  https://github.com/odddd0/ODWay
//====================================================================

#include <gtest/gtest.h>
#include <ODWayM/ODMGnome.h>
#include <ODMBase/ODDBHandle.h>

StringTable tempGnome_insert = {
    {"101", "N1", "103", "104", "105", "106", "107"},
    {"102", "N2", "203", "204", "205", "206", "207"},
    {"103", "N3", "303", "304", "305", "306", "307"}
};

StringTable tempGnome_update = {
    {"101", "N1", "103", "104", "105123", "106", "107"},
    {"102", "N22", "20323", "201234", "212305", "206", "212307"},
    {"103", "N333", "31203", "313404", "305", "306123", "307"}
};

//TEST(ODMGnome, insert)
//{
//    ODDBHandle::Instance()->Setup("test.db");
//    std::string errMsg;
//    ODMBaseList tmpList;
//    tmpList.push_back(std::make_shared<ODMGnome>(tempGnome_insert[0]));
//    tmpList.push_back(std::make_shared<ODMGnome>(tempGnome_insert[1]));
//    tmpList.push_back(std::make_shared<ODMGnome>(tempGnome_insert[2]));
//    EXPECT_TRUE(ODDBHandle::Instance()->Insert(tmpList, errMsg));
//    if (!errMsg.empty())
//    {
//        std::cout << errMsg << std::endl;
//    }
//}

//TEST(ODMTime, Update)
//{
//    ODMBaseList tmpList;
//    tmpList.push_back(std::make_shared<ODMGnome>(tempGnome_update[0]));
//    tmpList.push_back(std::make_shared<ODMGnome>(tempGnome_update[1]));
//    tmpList.push_back(std::make_shared<ODMGnome>(tempGnome_update[2]));
//    ODMGnomePtr tmpPtr = std::static_pointer_cast<ODMGnome>(tmpList[0]);
//    tmpPtr->_id = 122;
//    ODDBHandle::Instance()->Update(tmpList);
//}

//TEST(ODMTime, Select)
//{
//    ODMBaseList tmpList;
//    ODDBHandle::Instance()->Select<ODMGnome>(tmpList);
//    ODMGnomePtr tmpPtr = std::static_pointer_cast<ODMGnome>(tmpList[0]);
//    tmpPtr = std::static_pointer_cast<ODMGnome>(tmpList[1]);
//    tmpPtr = std::static_pointer_cast<ODMGnome>(tmpList[2]);
//}

//TEST(ODDBHandle, Delete)
//{
//    IntList tmpList = {102, 103};
//    std::string tmpStr;
//    ODDBHandle::Instance()->Delete<ODMGnome>(tmpList, tmpStr);
//}
