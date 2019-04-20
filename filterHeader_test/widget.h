#ifndef WIDGET_H
#define WIDGET_H
#include <QTableView>

#include <QWidget>
#include <QStandardItemModel>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
private:
    QTableView* view;
    QStandardItemModel* model;
public slots:
    void onFilterTextChanged(int col, const QString& text);
};

#endif // WIDGET_H
