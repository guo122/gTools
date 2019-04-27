//====================================================================
//  ODMTimeTest.cpp
//  created 6.4.18
//  written by odddd0
//
//  https://github.com/odddd0/ODWay
//====================================================================

#include <gtest/gtest.h>
#include <ODWayM/ODMTime.h>
#include <ODMBase/ODDBHandle.h>

StringTable tempTable_insert = {
    {"101", "201", "CC1", "KF1", "KS1", "C1"},
    {"102", "202", "CC2", "KF2", "KS2", "C2"},
    {"103", "203", "CC3", "KF3", "KS3", "C3"}
};

StringTable tempTable_update = {
    {"101", "201", "CC1", "KF1", "KS5", "C1"},
    {"102", "212", "CB2", "KCD2", "KAD2", "CGF2"},
    {"103", "203", "CC4", "KF3", "KS3", "C3"}
};

//TEST(ODMTime, insert)
//{
//    ODDBHandle::Instance()->Setup("test.db");
//    std::string errMsg;
//    ODMBaseList tmpList;
//    tmpList.push_back(std::make_shared<ODMTime>(tempTable_insert[0]));
//    tmpList.push_back(std::make_shared<ODMTime>(tempTable_insert[1]));
//    tmpList.push_back(std::make_shared<ODMTime>(tempTable_insert[2]));
//    EXPECT_TRUE(ODDBHandle::Instance()->Insert(tmpList, errMsg));
//    if (!errMsg.empty())
//    {
//        std::cout << errMsg << std::endl;
//    }
//}

//TEST(ODMTime, Update)
//{
//    ODMBaseList tmpList;
//    tmpList.push_back(std::make_shared<ODMTime>(tempTable_update[0]));
//    tmpList.push_back(std::make_shared<ODMTime>(tempTable_update[1]));
//    tmpList.push_back(std::make_shared<ODMTime>(tempTable_update[2]));
//    ODMTimePtr tmpPtr = std::static_pointer_cast<ODMTime>(tmpList[0]);
//    tmpPtr->_id = 122;
//    ODDBHandle::Instance()->Update(tmpList);
//}

//TEST(ODMTime, Select)
//{
//    ODMBaseList tmpList;
//    ODDBHandle::Instance()->Select<ODMTime>(tmpList);
//    ODMTimePtr tmpPtr = std::static_pointer_cast<ODMTime>(tmpList[0]);
//    tmpPtr = std::static_pointer_cast<ODMTime>(tmpList[1]);
//    tmpPtr = std::static_pointer_cast<ODMTime>(tmpList[2]);
//}

//TEST(ODDBHandle, Delete)
//{
//    IntList tmpList = {102, 103};
//    std::string tmpStr;
//    ODDBHandle::Instance()->Delete<ODMTime>(tmpList, tmpStr);
//}
