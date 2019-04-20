#include "filterheaderview.h"
#include <QApplication>
#include <QScrollBar>
#include <QDebug>

FilterHeaderView::FilterHeaderView(QTableView* parent) :
    QHeaderView (Qt::Horizontal, parent)
{
    setSectionsClickable(true);
    setSortIndicatorShown(true);

    connect(this, SIGNAL(sectionResized(int,int,int)), this, SLOT(adjustPositions()));
    connect(parent->horizontalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(adjustPositions()));
    connect(parent->verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(adjustPositions()));
    connect(this, &FilterHeaderView::sectionCountChanged, [this](int oldCount, int newCount)
    {
        Q_UNUSED(oldCount);
        this->generateFilters(newCount, true);
    });
}
/**
 * @brief 构造初始化过滤QLineEdit对象
 * @param number 过滤QLineEdit个数
 * @param showFirst 第一个过滤QLineEdit显示与否
 */
void FilterHeaderView::generateFilters(int number, bool showFirst)
{
    qDeleteAll(filters);
    filters.clear();

    for(int i=0;i < number; ++i)
    {
        QLineEdit* l = new QLineEdit(this);
        l->setPlaceholderText("过滤");
        l->setClearButtonEnabled(true);
        if(!showFirst && i == 0)
            l->setVisible(false);
        else
            l->setVisible(true);
        filters.push_back(l);
        connect(l, &QLineEdit::textChanged, [this, i](const QString& text)
        {
            emit filterTextChanged(i, text);
        });
    }
    adjustPositions();
}
/**
 * @brief 重载QHeaderView::sizeHint 加上QLineEdit的sizeHint()
 * @return 新的sizeHint()
 */
QSize FilterHeaderView::sizeHint() const
{
    QSize s = QHeaderView::sizeHint();
    if(filters.size())
        s.setHeight(s.height() + filters.at(0)->sizeHint().height() + 4);
    return s;
}

/**
 * @brief 设置FilterHeaderView与table的距离(外边距)，即QLineEdit的高度
 */
void FilterHeaderView::updateGeometries()
{
    if(filters.size())
        setViewportMargins(0, 0, 0, filters.at(0)->sizeHint().height());
    else
        setViewportMargins(0, 0, 0, 0);
    QHeaderView::updateGeometries();
    adjustPositions();
}

/**
 * @brief 让QLineEdit与QHeaderView的宽度绑定
 */
void FilterHeaderView::adjustPositions()
{
    for(int i=0;i < filters.size(); ++i)
    {
        QWidget* w = filters.at(i);
        int y = QHeaderView::sizeHint().height() + 2;
        if (QApplication::layoutDirection() == Qt::RightToLeft)
            w->move(width() - (sectionPosition(i) + sectionSize(i) - offset()), y);
        else
            w->move(sectionPosition(i) - offset(), y);
        w->resize(sectionSize(i), w->sizeHint().height());
    }
}
/**
 * @brief 设置单个QLineEdit的text
 * @param column
 * @param value
 */
void FilterHeaderView::setFilter(int column, const QString& value)
{
    if(column < filters.size())
        filters.at(column)->setText(value);
}
/**
 * @brief 清除空过滤QLineEdit
 */
void FilterHeaderView::clearFilters()
{
    for(QLineEdit* filterLineEdit : filters)
        filterLineEdit->clear();
}
