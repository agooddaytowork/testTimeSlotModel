#include "timeslotmodel.h"

timeSlotModel::timeSlotModel(QObject *parent)
    : QAbstractListModel(parent), mList(nullptr)
{
}

int timeSlotModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid() || !mList)
        return 0;

    return mList->items().size();
}

QVariant timeSlotModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || !mList)
        return QVariant();


    const timeSlotItem item = mList->items().at(index.row());

    switch(role)
    {
    case IDRole:
        return QVariant(item.id);
    case GroupRole:
        return QVariant(item.group);
    case ValveOnOffRole:
        return QVariant(item.ValveOnOff);
    case LedOnOffRole:
        return QVariant(item.LedOnOff);
    case InverterRole:
        return QVariant(item.Inverter);
    case FromMsRole:
        return QVariant(item.fromMs);
    case ToMsRole:
        return QVariant(item.toMs);
    case LedModeRole:
        return QVariant(item.LedMode);
    case InverterLevelRole:
        return QVariant(item.InverterLevel);
    case FileBinPathRole:
        return QVariant(item.fileBinPath);
    case LEDValuesListRole:
        return QVariant(item.LedValuesList);
    case LEDChannelsRole:
        return QVariant(item.LedChannels);
    case ValveChannelsRole:
        return QVariant(item.ValveChannels);

    }

    return QVariant();
}

bool timeSlotModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!mList)
        return false;

    timeSlotItem item = mList->items().at(index.row());
    switch (role) {
    case IDRole:
        item.id = static_cast<quint32>(value.toUInt());
        break;
    case GroupRole:
        item.group = static_cast<quint8>(value.toUInt());
        break;
    case ValveOnOffRole:
        item.ValveOnOff = value.toBool();
        break;
    case LedOnOffRole:
        item.LedOnOff = value.toBool();
        break;
    case InverterRole:
        item.Inverter = value.toBool();
        break;
    case FromMsRole:
        item.fromMs = static_cast<quint32>(value.toUInt());
        break;
    case ToMsRole:
        item.toMs = static_cast<quint32>(value.toUInt());
    case LedModeRole:
        item.LedMode = static_cast<quint8>(value.toUInt());
        break;
    case InverterLevelRole:
        item.InverterLevel = static_cast<quint8>(value.toUInt());
        break;
    case FileBinPathRole:
        item.fileBinPath = value.toString();
        break;
    case LEDValuesListRole:
          item.LedValuesList = value.toString();
        break;
    case LEDChannelsRole:
        item.LedChannels = static_cast<quint8>(value.toUInt());
        break;
    case ValveChannelsRole:
        item.ValveChannels = static_cast<quint8>(value.toUInt());
    }

    if (mList->setItemAt(index.row(), item)) {
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags timeSlotModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable; // FIXME: Implement me!
}

QHash<int, QByteArray> timeSlotModel::roleNames() const
{
    QHash<int, QByteArray> names;

    names[IDRole] = "theId";
    names[ValveOnOffRole] = "ValveOnOff";
    names[LedOnOffRole] ="LedOnOff";
    names[InverterRole] = "Inverter";
    names[FromMsRole] = "FromMs";
    names[ToMsRole] = "ToMs";
    names[LedModeRole] = "LedMode";
    names[InverterLevelRole] = "InverterLevel";
    names[FileBinPathRole] = "FileBinPath";
    names[LEDValuesListRole] = "LEDValuesList";
    names[LEDChannelsRole] = "LEDChannels";
    names[ValveChannelsRole] = "ValveChannels";

    return names;

}


timeSlotList *timeSlotModel::list() const
{
    return mList;
}

void timeSlotModel::setList(timeSlotList *list)
{
    beginResetModel();

    if (mList)
        mList->disconnect(this);

    mList = list;

    if (mList) {
        connect(mList, &timeSlotList::preItemAppended, this, [=]() {
            const int index = mList->items().size();
            beginInsertRows(QModelIndex(), index, index);
        });
        connect(mList, &timeSlotList::postItemAppended, this, [=]() {
            endInsertRows();
        });

        connect(mList, &timeSlotList::preItemRemoved, this, [=](int index) {
            beginRemoveRows(QModelIndex(), index, index);
        });
        connect(mList, &timeSlotList::postItemRemoved, this, [=]() {
            endRemoveRows();
        });
    }

    endResetModel();
}
