//====================================================================
//  ODMGoblinTest.cpp
//  created 6.12.18
//  written by odddd0
//
//  https://github.com/odddd0/ODWay
//====================================================================

#include <gtest/gtest.h>
#include <ODWayM/ODMGoblin.h>
#include <ODMBase/ODDBHandle.h>

StringTable tempGoblin_insert = {
    {"101", "103", "104", "105", "106", "107"},
    {"102", "203", "204", "205", "206", "207"},
    {"103", "303", "304", "305", "306", "307"}
};

StringTable tempGoblin_update = {
    {"101", "103", "104", "105123", "106", "107"},
    {"102", "20323", "201234", "212305", "206", "212307"},
    {"103", "31203", "313404", "305", "306123", "307"}
};

//TEST(ODMGoblin, insert)
//{
//    ODDBHandle::Instance()->Setup("test.db");
//    std::string errMsg;
//    ODMBaseList tmpList;
//    tmpList.push_back(std::make_shared<ODMGoblin>(tempGoblin_insert[0]));
//    tmpList.push_back(std::make_shared<ODMGoblin>(tempGoblin_insert[1]));
//    tmpList.push_back(std::make_shared<ODMGoblin>(tempGoblin_insert[2]));
//    EXPECT_TRUE(ODDBHandle::Instance()->Insert(tmpList, errMsg));
//    if (!errMsg.empty())
//    {
//        std::cout << errMsg << std::endl;
//    }
//}

//TEST(ODMGoblin, Update)
//{
//    ODMBaseList tmpList;
//    tmpList.push_back(std::make_shared<ODMGoblin>(tempGoblin_update[0]));
//    tmpList.push_back(std::make_shared<ODMGoblin>(tempGoblin_update[1]));
//    tmpList.push_back(std::make_shared<ODMGoblin>(tempGoblin_update[2]));
//    ODMGoblinPtr tmpPtr = std::static_pointer_cast<ODMGoblin>(tmpList[0]);
//    tmpPtr->_id = 122;
//    ODDBHandle::Instance()->Update(tmpList);
//}

//TEST(ODMGoblin, Select)
//{
//    ODMBaseList tmpList;
//    ODDBHandle::Instance()->Select<ODMGoblin>(tmpList);
//    ODMGoblinPtr tmpPtr = std::static_pointer_cast<ODMGoblin>(tmpList[0]);
//    tmpPtr = std::static_pointer_cast<ODMGoblin>(tmpList[1]);
//    tmpPtr = std::static_pointer_cast<ODMGoblin>(tmpList[2]);
//}

//TEST(ODDBHandle, Delete)
//{
//    IntList tmpList = {102, 103};
//    std::string tmpStr;
//    ODDBHandle::Instance()->Delete<ODMGoblin>(tmpList, tmpStr);
//}
