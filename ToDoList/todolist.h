#ifndef TODOLIST_H
#define TODOLIST_H

#include <QObject>
#include <QVector>

struct ToDoItem
{
    bool done;
    QString description;
};

// a data storage for a model
// the back-end type
class ToDoList : public QObject
{
    Q_OBJECT
public:
    explicit ToDoList(QObject *parent = nullptr);

    QVector<ToDoItem> items() const;
    bool setItemAt(int index, const ToDoItem &item);

signals:
    void preItemAppended();
    void postItemAppended();
    void preItemRemoved(int index);
    void postItemRemoved();

public slots:
    // functions called by QML code
    void appendItem();
    void removeCompletedItems();

private:
    QVector<ToDoItem> _items;
};

#endif // TODOLIST_H
