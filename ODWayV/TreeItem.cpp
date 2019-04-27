//====================================================================
//  TreeItem.cpp
//  created 6.7.18
//  written by odddd0
//
//  https://github.com/odddd0/ODWay
//====================================================================

#include "TreeItem.h"

TreeItem::TreeItem() :m_parentItem(NULL)
{
}
TreeItem::TreeItem(const StringList &data, TreeItem* parent) : m_parentItem(NULL)
{
    m_parentItem = parent;
    m_itemData = data;
}
TreeItem::~TreeItem()
{
    qDeleteAll(m_childItems);
}
void TreeItem::appendChild(TreeItem *item)
{
    item->setParent(this);
    m_childItems.append(item);
}
void TreeItem::deleteAllChild()
{
    for (int index = 0; index < m_childItems.size(); index++)
    {
        m_childItems[index]->deleteAllChild();
    }
    qDeleteAll(m_childItems);
    m_childItems.clear();
}
TreeItem *TreeItem::child(int row)
{
    return m_childItems.value(row);
}
int TreeItem::childCount() const
{
    return m_childItems.count();
}
int TreeItem::columnCount() const
{
    return m_itemData.size();
    //return 1;
}
QVariant TreeItem::data(int column) const
{
    QString tmpStr = m_itemData[column].c_str();
    return QVariant::fromValue<QString>(tmpStr);
}
TreeItem *TreeItem::parent()
{
    return m_parentItem;
}
void TreeItem::setParent(TreeItem *parent)
{
    m_parentItem = parent;
}
int TreeItem::row() const
{
    if (!m_parentItem) { return 0; }

    return m_parentItem->m_childItems.indexOf(const_cast<TreeItem*>(this));
}
