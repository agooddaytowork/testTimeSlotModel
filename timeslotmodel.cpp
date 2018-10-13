#include "timeslotmodel.h"

timeSlotModel::timeSlotModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

int timeSlotModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    // FIXME: Implement me!
}

QVariant timeSlotModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch(role)
    {
    case IDRole:
        return QVariant(0);
    case GroupRole:
        return QVariant(0);
    case ValveOnOffRole:
        return QVariant(false);
    case LedOnOffRole:
        return QVariant(false);
    case InverterRole:
        return QVariant(false);
    case FromMsRole:
        return QVariant(0);
    case ToMsRole:
        return QVariant(5000);
    case LedModeRole:
        return QVariant(0);
    case InverterLevelRole:
        return QVariant(0);
    case FileBinPathRole:
        return QVariant("some link here I don't know ");
    case LEDValuesListRole:
        return QVariant("A String maybe?");


    }
    // FIXME: Implement me!
    return QVariant();
}

bool timeSlotModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        // FIXME: Implement me!
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

    return names;

}
