//====================================================================
//  ODMGoblinCoinTest.cpp
//  created 6.12.18
//  written by odddd0
//
//  https://github.com/odddd0/ODWay
//====================================================================

#include <gtest/gtest.h>
#include <ODWayM/ODMGoblinCoin.h>
#include <ODMBase/ODDBHandle.h>

StringTable tempGoblinCoin_insert = {
    {"101", "103", "N1", "103", "104", "105", "106"},
    {"102", "203", "N2", "204", "205", "206", "207"},
    {"103", "303", "N3", "304", "305", "306", "307"}
};

StringTable tempGoblinCoin_update = {
    {"101", "103", "N1", "104", "105123", "106", "107"},
    {"102", "20323", "N22", "201234", "212305", "206", "212307"},
    {"103", "31203", "N333", "313404", "305", "306123", "307"}
};

//TEST(ODMGoblinCoin, insert)
//{
//    ODDBHandle::Instance()->Setup("test.db");
//    std::string errMsg;
//    ODMBaseList tmpList;
//    tmpList.push_back(std::make_shared<ODMGoblinCoin>(tempGoblinCoin_insert[0]));
//    tmpList.push_back(std::make_shared<ODMGoblinCoin>(tempGoblinCoin_insert[1]));
//    tmpList.push_back(std::make_shared<ODMGoblinCoin>(tempGoblinCoin_insert[2]));
//    EXPECT_TRUE(ODDBHandle::Instance()->Insert(tmpList, errMsg));
//    if (!errMsg.empty())
//    {
//        std::cout << errMsg << std::endl;
//    }
//}

//TEST(ODMGoblinCoin, Update)
//{
//    ODMBaseList tmpList;
//    tmpList.push_back(std::make_shared<ODMGoblinCoin>(tempGoblinCoin_update[0]));
//    tmpList.push_back(std::make_shared<ODMGoblinCoin>(tempGoblinCoin_update[1]));
//    tmpList.push_back(std::make_shared<ODMGoblinCoin>(tempGoblinCoin_update[2]));
//    ODMGoblinCoinPtr tmpPtr = std::static_pointer_cast<ODMGoblinCoin>(tmpList[0]);
//    tmpPtr->_id = 122;
//    ODDBHandle::Instance()->Update(tmpList);
//}

//TEST(ODMGoblinCoin, Select)
//{
//    ODMBaseList tmpList;
//    ODDBHandle::Instance()->Select<ODMGoblinCoin>(tmpList);
//    ODMGoblinCoinPtr tmpPtr = std::static_pointer_cast<ODMGoblinCoin>(tmpList[0]);
//    tmpPtr = std::static_pointer_cast<ODMGoblinCoin>(tmpList[1]);
//    tmpPtr = std::static_pointer_cast<ODMGoblinCoin>(tmpList[2]);
//}

//TEST(ODMGoblinCoin, Delete)
//{
//    IntList tmpList = {102, 103};
//    std::string tmpStr;
//    ODDBHandle::Instance()->Delete<ODMGoblinCoin>(tmpList, tmpStr);
//}
