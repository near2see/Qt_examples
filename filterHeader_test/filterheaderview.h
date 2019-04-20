#ifndef FILTERHEADERVIEW_H
#define FILTERHEADERVIEW_H

#include <QHeaderView>
#include <QTableView>
#include <QLineEdit>

class FilterHeaderView : public QHeaderView
{
    Q_OBJECT
public:
    explicit FilterHeaderView(QTableView* parent = nullptr);
    ~FilterHeaderView() = default;
    void generateFilters(int number, bool showFirst);
    QSize sizeHint() const;
    void updateGeometries();
    void setFilter(int column, const QString& value);
    void clearFilters();
public slots:
    void adjustPositions();
signals:
    void filterTextChanged(int col, const QString& text);
private:
    QList<QLineEdit*> filters;
};

#endif // FILTERHEADERVIEW_H
