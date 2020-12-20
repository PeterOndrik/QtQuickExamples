#include "todolist.h"

ToDoList::ToDoList(QObject *parent) : QObject(parent)
{
    _items.append({ true, QStringLiteral("Wash the car")});
    _items.append({ false, QStringLiteral("Fix the sink")});
}

QVector<ToDoItem> ToDoList::items() const
{
    return _items;
}

bool ToDoList::setItemAt(int index, const ToDoItem &item)
{
    if (index < 0 || index >= _items.size())
        return false;

    const ToDoItem &oldItem = _items.at(index);
    if (item.done == oldItem.done && item.description == oldItem.description)
        return false;

    _items[index] = item;
}

void ToDoList::appendItem()
{
    emit preItemAppended();

    ToDoItem item;
    item.done = false;
    _items.append(item);

    emit postItemAppended();
}

void ToDoList::removeCompletedItems()
{
    for (int i = 0; i < _items.size(); ) {
        if (_items.at(i).done) {
            emit preItemRemoved(i);

            _items.removeAt(i);

            emit postItemRemoved();
        } else {
            ++i;
        }
    }
}
