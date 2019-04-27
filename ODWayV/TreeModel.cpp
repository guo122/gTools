//====================================================================
//  TreeModel.h
//  created 6.7.18
//  written by odddd0
//
//  https://github.com/odddd0/ODWay
//====================================================================

#include <ODWayP/ODPTime.h>

#include "TreeModel.h"

TreeModel::TreeModel(QObject *parent)
    : QAbstractItemModel(parent)
    , m_rootItem(NULL)
    , _CKKCur(3, "")
    , _isFirstExpand(false)
    , _isSecondExpand(false)
{
    updateSum();
}

TreeModel::~TreeModel()
{
    delete m_rootItem;
}

int TreeModel::columnCount(const QModelIndex &parent) const
{
    return 5;
    //返回实际的列数 (实际是他返回了0，因为根节点用的是无参的构造)，TreeView控件会认为表是空表，不获取数据
    if (parent.isValid())
    {
        return static_cast<TreeItem*>(parent.internalPointer())->columnCount();
    }
    else
    {
        return m_rootItem->columnCount();
    }
}

QHash<int, QByteArray> TreeModel::roleNames() const
{
    QHash<int, QByteArray> names(QAbstractItemModel::roleNames());
    names[NAME] = "name";
    names[SIMPLIFY] = "simplify";
    names[OD_CLASSIFY] = "classify";
    names[OD_KINDFIRST] = "kindFirst";
    names[OD_KINDSECOND] = "kindSecond";
    return names;
}

QString TreeModel::daySum() const
{
    return m_daySum;
}

void TreeModel::updateSum(const bool &allSum_)
{
    _classifyList.clear();
    _kindFirstList.clear();
    _kindSecondList.clear();
    m_rootItem = new TreeItem;

    int si = -1;
    int sj = -1;
    int sk = -1;

    if (allSum_)
    {
        ODPTime::Instance()->GetAllSumList(_classifyList, _kindFirstList, _kindSecondList);
    }
    else
    {
        ODPTime::Instance()->GetCurSumList(_classifyList, _kindFirstList, _kindSecondList);
    }
    m_daySum = ODPTime::Instance()->GetCurSum().c_str();

    for (int i = 0; i < _classifyList.size(); ++i)
    {
        auto item_I = new TreeItem(_classifyList[i], m_rootItem);
        m_rootItem->appendChild(item_I);
        if (_CKKCur.size() == 3 && _classifyList[i][0] == _CKKCur[0])
        {
            si = i;
        }

        for (int j = 0; j < _kindFirstList[i].size(); ++j)
        {
            auto item_J = new TreeItem(_kindFirstList[i][j], item_I);
            item_I->appendChild(item_J);
            if (_CKKCur.size() == 3 && _kindFirstList[i][j][0] == _CKKCur[1])
            {
                sj = j;
            }

            for (int k = 0; k < _kindSecondList[i][j].size(); ++k)
            {
                auto item_K = new TreeItem(_kindSecondList[i][j][k], item_J);
                item_J->appendChild(item_K);
                if (_CKKCur.size() == 3 && _kindSecondList[i][j][k][0] == _CKKCur[2])
                {
                    sk = k;
                }
            }
        }
    }

    if (si != -1 && sj != -1 && sk == -1)
    {
        // kindFirst level; expand classify
        _firstExpand = createIndex(si, 0, m_rootItem->child(si));
        _isFirstExpand = true;
        _isSecondExpand = false;
    }
    else if (si != -1 && sj != -1 && sk != -1)
    {
        // kindSecond level; expand classify, kindFirst
        _firstExpand = createIndex(si, 0, m_rootItem->child(si));
        _secondExpand = createIndex(sj, 0, m_rootItem->child(si)->child(sj));
        _isFirstExpand = true;
        _isSecondExpand = true;
    }
    else
    {
        _isFirstExpand = false;
        _isSecondExpand = false;
    }
}

QStringList TreeModel::setSelectIndex(const QModelIndex &index_)
{
    QStringList Result;
    if (_CKKCur.size() == 3)
    {
        _CKKCur[0] = index_.data(OD_CLASSIFY).toString().toStdString();
        _CKKCur[1] = index_.data(OD_KINDFIRST).toString().toStdString();
        _CKKCur[2] = index_.data(OD_KINDSECOND).toString().toStdString();
    }
    else
    {
        _CKKCur.clear();
        _CKKCur.push_back(index_.data(OD_CLASSIFY).toString().toStdString());
        _CKKCur.push_back(index_.data(OD_KINDFIRST).toString().toStdString());
        _CKKCur.push_back(index_.data(OD_KINDSECOND).toString().toStdString());
    }
    Result.push_back(index_.data(OD_CLASSIFY).toString());
    Result.push_back(index_.data(OD_KINDFIRST).toString());
    Result.push_back(index_.data(OD_KINDSECOND).toString());
    return Result;
}

bool TreeModel::isFirstExpand()
{
    return _isFirstExpand;
}

bool TreeModel::isSecondExpand()
{
    return _isSecondExpand;
}

QModelIndex TreeModel::getFirstExpand()
{
    return _firstExpand;
}

QModelIndex TreeModel::getSecondExpand()
{
    return _secondExpand;
}

void TreeModel::setDaySum(QString daySum)
{
    if (m_daySum == daySum)
        return;

    m_daySum = daySum;
    emit daySumChanged(m_daySum);
}

void TreeModel::clearCKK()
{
    _CKKCur.clear();
    _isFirstExpand = false;
    _isSecondExpand = false;
}

bool TreeModel::isSelectHighlight(const QString &classify_, const QString &kindFirst_, const QString &kindSecond_)
{
    bool Result = true;
    if (_CKKCur.size() != 3 ||
            kindSecond_ != QString::fromStdString(_CKKCur[2]) ||
            kindFirst_ != QString::fromStdString(_CKKCur[1]) ||
            classify_ != QString::fromStdString(_CKKCur[0]))
    {
        Result = false;
    }
    return Result;
}

QVariant TreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    switch (role)
    {
    case NAME:
    {
        return static_cast<TreeItem*>(index.internalPointer())->data(0);
    }
    case SIMPLIFY:
    {
        return static_cast<TreeItem*>(index.internalPointer())->data(1);
    }
    case OD_CLASSIFY:
    {
        return static_cast<TreeItem*>(index.internalPointer())->data(2);
    }
    case OD_KINDFIRST:
    {
        return static_cast<TreeItem*>(index.internalPointer())->data(3);
    }
    case OD_KINDSECOND:
    {
        return static_cast<TreeItem*>(index.internalPointer())->data(4);
    }
    }
}

Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
    {
        return 0;
    }

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
    {
        return QModelIndex();
    }

    TreeItem *parentItem;
    if (!parent.isValid())
    {
        parentItem = m_rootItem;
    }
    else
    {
        parentItem = static_cast<TreeItem*>(parent.internalPointer());
    }

    TreeItem *childItem = parentItem->child(row);
    if (childItem)
    {
        return createIndex(row, column, childItem);
    }
    else
    {
        return QModelIndex();
    }
}

QModelIndex TreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
    {
        return QModelIndex();
    }

    TreeItem *childItem = static_cast<TreeItem*>(index.internalPointer());
    TreeItem *parentItem = childItem->parent();

    if (parentItem == m_rootItem)
    {
        return QModelIndex();
    }

    return createIndex(parentItem->row(), 0, parentItem);
}

int TreeModel::rowCount(const QModelIndex &parent) const
{
    TreeItem *parentItem;
    if (parent.column() > 0)
    {
        return 0;
    }

    if (!parent.isValid())
    {
        parentItem = m_rootItem;
    }
    else
    {
        parentItem = static_cast<TreeItem*>(parent.internalPointer());
    }

    return parentItem->childCount();
}
