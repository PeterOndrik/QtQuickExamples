#include "todomodel.h"
#include "todolist.h"

ToDoModel::ToDoModel(QObject *parent)
    : QAbstractListModel(parent), _list(nullptr)
{
}

int ToDoModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid() || !_list)
        return 0;

    return _list->items().size();
}

QVariant ToDoModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || !_list)
        return QVariant();

    const ToDoItem item = _list->items().at(index.row());
    switch (role)
    {
    case DoneRole:
        return QVariant(item.done);
    case DescriptionRole:
        return QVariant(item.description);
    }

    return QVariant();
}

bool ToDoModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!_list)
        return false;

    ToDoItem item = _list->items().at(index.row());
    switch (role)
    {
    case DoneRole:
        item.done = value.toBool();
        break;
    case DescriptionRole:
        item.description = value.toString();
    }

    if (_list->setItemAt(index.row(), item))
    {
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }

    return false;
}

Qt::ItemFlags ToDoModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable;
}

QHash<int, QByteArray> ToDoModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[DoneRole] = "done";
    names[DescriptionRole] = "description";

    return names;
}

ToDoList *ToDoModel::list() const
{
    return _list;
}

void ToDoModel::setList(ToDoList *list)
{
    beginResetModel();

    if (_list)
        _list->disconnect(this);

    _list = list;

    if (_list)
    {
        connect(_list, &ToDoList::preItemAppended, this, [=](){
            const int index = _list->items().size();
            beginInsertRows(QModelIndex(), index, index);
        });
        connect(_list, &ToDoList::postItemAppended, this, [=](){
            endInsertRows();
        });

        connect(_list, &ToDoList::preItemRemoved, this, [=](int index){
            beginRemoveRows(QModelIndex(), index, index);
        });
        connect(_list, &ToDoList::postItemRemoved, this, [=](){
            endRemoveRows();
        });
    }

    endResetModel();
}
