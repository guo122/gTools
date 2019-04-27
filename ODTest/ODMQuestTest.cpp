//====================================================================
//  ODMQuestTest.cpp
//  created 11.8.18
//  written by odddd0
//
//  https://github.com/odddd0/ODWay
//====================================================================

#include <gtest/gtest.h>
#include <ODWayM/ODMQuest.h>
#include <ODMBase/ODDBHandle.h>

StringTable tempQuest_insert = {
    {"101", "102", "103", "104"},
    {"201", "202", "203", "204"},
    {"301", "302", "303", "304"}
};

StringTable tempQuest_update = {
    {"101", "106", "107", "108"},
    {"201", "206", "207", "208"},
    {"301", "306", "307", "308"}
};

//TEST(ODMQuest, insert)
//{
//    ODDBHandle::Instance()->Setup("test.db");
//    std::string errMsg;
//    ODMBaseList tmpList;
//    tmpList.push_back(std::make_shared<ODMQuest>(tempQuest_insert[0]));
//    tmpList.push_back(std::make_shared<ODMQuest>(tempQuest_insert[1]));
//    tmpList.push_back(std::make_shared<ODMQuest>(tempQuest_insert[2]));
//    EXPECT_TRUE(ODDBHandle::Instance()->Insert(tmpList, errMsg));
//    if (!errMsg.empty())
//    {
//        std::cout << errMsg << std::endl;
//    }
//}

//TEST(ODMQuest, Update)
//{
//    ODMBaseList tmpList;
//    std::string errMsg;
//    tmpList.push_back(std::make_shared<ODMQuest>(tempQuest_update[0]));
//    tmpList.push_back(std::make_shared<ODMQuest>(tempQuest_update[1]));
//    tmpList.push_back(std::make_shared<ODMQuest>(tempQuest_update[2]));
//    ODMQuestPtr tmpPtr = std::static_pointer_cast<ODMQuest>(tmpList[0]);
//    tmpPtr->_id = 122;
//    EXPECT_TRUE(ODDBHandle::Instance()->Update(tmpList, errMsg));
//    std::cout << tmpPtr->_preId << std::endl;
//    std::cout << tmpPtr->_id << std::endl;
//    std::cout << tmpPtr->_state << std::endl;
//    std::cout << tmpPtr->_name << std::endl;
//    std::cout << tmpPtr->_deadLine << std::endl;
//}

//TEST(ODMQuest, Select)
//{
//    ODMBaseList tmpList;
//    ODDBHandle::Instance()->Select<ODMQuest>(tmpList);
//    ODMQuestPtr tmpPtr = std::static_pointer_cast<ODMQuest>(tmpList[0]);
//    tmpPtr = std::static_pointer_cast<ODMQuest>(tmpList[1]);
//    tmpPtr = std::static_pointer_cast<ODMQuest>(tmpList[2]);
//}

//TEST(ODDBHandle, Delete)
//{
//    IntList tmpList = {201, 301};
//    std::string tmpStr;
//    ODDBHandle::Instance()->Delete<ODMQuest>(tmpList, tmpStr);
//}
