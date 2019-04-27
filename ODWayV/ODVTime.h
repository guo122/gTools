//====================================================================
//  ODVTime.h
//  created 6.5.18
//  written by odddd0
//
//  https://github.com/odddd0/ODWay
//====================================================================

#ifndef _ODVTIME_H_FD35CFBB6BDD4D77652D17F1D8BD8EF5_
#define _ODVTIME_H_FD35CFBB6BDD4D77652D17F1D8BD8EF5_

#include <QObject>

class ODVTime : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString runningTimeStr READ runningTimeStr WRITE setRunningTimeStr NOTIFY runningTimeStrChanged)
    Q_PROPERTY(QStringList curList READ curList WRITE setCurList NOTIFY curListChanged)
    Q_PROPERTY(QStringList classifyList READ classifyList WRITE setClassifyList NOTIFY classifyListChanged)
    Q_PROPERTY(QStringList kindFirstList READ kindFirstList WRITE setKindFirstList NOTIFY kindFirstListChanged)
    Q_PROPERTY(QStringList kindSecondList READ kindSecondList WRITE setKindSecondList NOTIFY kindSecondListChanged)

public:
    explicit ODVTime(QObject *parent = nullptr);

    QStringList curList();
    QStringList classifyList() const;
    QStringList kindFirstList() const;
    QStringList kindSecondList() const;
    QString runningTimeStr();

signals:
    void curListChanged(QStringList curList);
    void classifyListChanged(QStringList classifyList);
    void kindFirstListChanged(QStringList kindFirstList);
    void kindSecondListChanged(QStringList kindSecondList);
    void runningTimeStrChanged(QString runningTimeStr);

public slots:
    void setCurList(QStringList curList);
    void setClassifyList(QStringList classifyList);
    void setKindFirstList(QStringList kindFirstList);
    void setKindSecondList(QStringList kindSecondList);
    void setRunningTimeStr(QString runningTimeStr);

public slots:
    bool addTime(
            const int &year_,
            const int &month_,
            const int &day_,
            const int &hour_,
            const int &minute_,
            const int &second_,
            const bool &customTime_,
            const QString &classify_,
            const QString &kindFirst_,
            const QString &kindSecond_,
            const QString &content_);
    bool delTime(const int &index_);
    QString calDurTime(const int &index1_, const int &index2_);
    void setCKKCur(const QStringList ckkList_);
    void clearCKKCur();

public slots:
    // TableTimeChart
    QString getStartDate();
    QString getEndDate();
    QList<int> getLastCKKSum(const int &lastDay_);
    QStringList getLastCKKSumStr();
    QString getCKKStr(const QString &defaultStr_);
    QString getLastCKKSumStrColor(const int &index_, const QString &defaultColor_ = "black");
    bool isChartSumCurrentDay(const int &index_);
    int getChartSumCurrentDayIndex();
    void selectChartSum(const int &index_);

public slots:
    void updateList();
    bool fastIdle();
    bool prevDay();
    bool firstDay();
    bool nextDay();
    bool lastDay();
    bool isPop(const int &index_);

public slots:
    void updateClass();
    void updateKindFirst(QString classify_);
    void updateKindSecond(QString classify_, QString kind_);

private:
    QStringList m_curList;
    QStringList m_classifyList;
    QStringList m_kindFirstList;
    QStringList m_kindSecondList;
    QString m_runningTimeStr;
    std::vector<int> _popList;
    std::vector<std::string> _ckkList;
};

#endif // _ODVTIME_H_FD35CFBB6BDD4D77652D17F1D8BD8EF5_
