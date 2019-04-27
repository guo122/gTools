//====================================================================
//  ODVGoblin.h
//  created 6.13.18
//  written by odddd0
//
//  https://github.com/odddd0/ODWay
//====================================================================

#ifndef _ODVGOBLIN_H_7E454649C08C0A706DA13FA21129A632_
#define _ODVGOBLIN_H_7E454649C08C0A706DA13FA21129A632_

#include <QObject>
#include <QVariant>
#include <ODUtil/ODCKK.h>

class ODVGoblin : public QObject
{
    Q_OBJECT

public:
    explicit ODVGoblin(QObject *parent = nullptr);

public:

signals:

public slots:
    // add
    QVariant getCKK();
    QStringList getGoldFromList();
    bool addSimplePay(
            const int &year_,
            const int &month_,
            const int &day_,
            const int &hour_,
            const int &minute_,
            const int &second_,
            const bool &customTime_,
            const QString &goldFrom_,
            const QString &classify_,
            const QString &kindFirst_,
            const QString &kindSecond_,
            const double &count_,
            const QString &content_);
    bool addTransit(
            const int &year_,
            const int &month_,
            const int &day_,
            const int &hour_,
            const int &minute_,
            const int &second_,
            const bool &customTime_,
            const QString &goldFrom_,
            const QString &goldTo_,
            const double &count_,
            const double &tips_,
            const QString &content_,
            const int &offsetBill_,
            const double &lessCount);
    bool addBill(
            const int &year_,
            const int &month_,
            const int &day_,
            const int &hour_,
            const int &minute_,
            const int &second_,
            const bool &customTime_,
            const QString &goldFrom_,
            const QString &classify_,
            const QString &kindFirst_,
            const QString &kindSecond_,
            const double &count_,
            const int &billMonth_,
            const double &firstMonthCount_,
            const double &othersMonthCount_,
            const QString &content_,
            const bool &isBillSplit_,
            const bool &withDraw_,
            const bool &isReverse_,
            const QString &withDrawGoldTo_);

    QStringList getCoinList();
    bool delCoin(const int &index_);
    bool delCoin();
    bool revokeCoin(const int &index_);
    bool setEditCoin(const int &index_);
    bool saveEditCoin(
            const bool &revoke_,
            const int &year_,
            const int &month_,
            const int &day_,
            const int &hour_,
            const int &minute_,
            const int &second_,
            const double &countSecond_,
            const QString &class_,
            const int &offset);
    QString getCurGnomeStr(const QString &defaultStr = "");

public slots:
    // editCoinStr
    void updateEditCoin();
    QString getEditCoinStrText();
    bool getEditCoinStrRevoke();
    int getEditCoinStrYear();
    int getEditCoinStrMonth();
    int getEditCoinStrDay();
    int getEditCoinStrHour();
    int getEditCoinStrMinute();
    int getEditCoinStrSecond();
    double getEditCoinStrCount();
    double getEditCoinStrCountSecond();

public slots:
    // gnome
    QStringList getGnomeList();
    bool addGnome(
            const QString &name_,
            const int &CreditLimits_,
            const int &BillDates_,
            const int &DueDay_,
            const int &GnomeType_,
            const int &GnomeState_);
    bool upGnome(const int &index_);
    void setGnomeIndex(const int &index_);

private:
    std::string _curGnome;
    std::string _editCoinStr;
    bool _revoke;
    int _year;
    int _month;
    int _day;
    int _hour;
    int _minute;
    int _second;
    int _count;
    int _countSecond;
};

#endif // _ODVGOBLIN_H_7E454649C08C0A706DA13FA21129A632_
