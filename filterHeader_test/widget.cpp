#include "widget.h"
#include "filterheaderview.h"
#include <QStandardItemModel>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    view = new QTableView(this);
    FilterHeaderView* headView = new FilterHeaderView(view);
    view->setHorizontalHeader(headView);
    connect(headView, &FilterHeaderView::filterTextChanged, this, &Widget::onFilterTextChanged);
    model = new QStandardItemModel(view);
    QStringList headlist = QStringList();
    for(int i=0; i<9; i++)
    {
        QStandardItem* item = new QStandardItem(QString("hello%1").arg(i));
        headlist << QString("head %1").arg(i);
        model->setItem(0, i, item);
    }
    model->setHorizontalHeaderLabels(headlist);
    view->setModel(model);

}

Widget::~Widget()
{

}
void Widget::onFilterTextChanged(int col, const QString& text)
{
    qDebug() << "col:" << col ;
    qDebug() << "text:" << text;
}
