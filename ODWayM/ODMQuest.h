//====================================================================
//  ODMQuest.h
//  created 11.8.18
//  written by odddd0
//
//  https://github.com/odddd0/ODWay
//====================================================================

#ifndef _ODMQUEST_H_0B4E966F39A3A16AA5EBA5613CF579A9_
#define _ODMQUEST_H_0B4E966F39A3A16AA5EBA5613CF579A9_

#include <ODMBase/ODMBase.h>
/**
 * @brief The ODMQuest struct
 */
struct ODMQuest : public ODMBase
{
    enum QuestState
    {
        Normal = 0,
        Done = 1,
        Fail = 2
    };

public:
    ODMQuest();
    ODMQuest(const StringList &stringList);

public:
    static void GetSqlCreateTable(std::string &sql_);
    static void GetSqlSelect(std::string &sql_);
    static void GetSqlDelete(std::string &sql_, const int &id_);
    void GetSqlUpdate(std::string &sql_);
    void GetSqlInsert(std::string &sql_);

public:
    QuestState _state;
    std::string _name;
    int _deadLine;

private:
    static bool _init;
};
typedef std::shared_ptr<ODMQuest> ODMQuestPtr;

#endif // _ODMQUEST_H_0B4E966F39A3A16AA5EBA5613CF579A9_
