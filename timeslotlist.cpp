#include "timeslotlist.h"

timeSlotList::timeSlotList(QObject *parent) : QObject(parent), mCurrentIndex(0)
{

}


QVector<timeSlotItem> timeSlotList::items() const
{
    return mItems;
}


bool timeSlotList::setItemAt(int index, const timeSlotItem &item)
{
    if (index < 0 || index >= mItems.size())
        return false;

    mItems[index] = item;
    return true;
}


void timeSlotList::appendItem(const quint8 &group, const quint32 &fromMs, const quint32 &toMs)
{
    emit preItemAppended();
    timeSlotItem item;

    item.id = mCurrentIndex;
    item.fromMs = fromMs;
    item.toMs = toMs;
    item.ValveOnOff = false;
    item.LedOnOff = false;
    item.LedMode = 0;
    item.InverterLevel = 0;
    item.Inverter = false;
    switch(group)
    {
    case 0:
        item.Inverter = true;
        item.LedChannels = 1;
        item.ValveChannels = 1;

        break;
    case 1:
        item.LedChannels = 1;
        item.ValveChannels = 8;
        break;
    case 2:
        item.LedChannels = 1;
        item.ValveChannels = 16;
        break;
    case 3:
        item.LedChannels = 2;
        item.Inverter = true;
        item.ValveChannels = 1;
        break;
    case 4:
        item.LedChannels = 3;
        item.ValveChannels = 1;
        break;
    case 5:
        item.LedChannels = 12;
        item.Inverter = true;
        item.ValveChannels = 2;
        break;
    case 6:
        item.LedChannels = 6;
        item.ValveChannels = 2;
        break;
    case 7:
        item.LedChannels = 8;
        item.ValveChannels = 8;
        break;
    case 8:
        item.LedChannels = 2;
        item.ValveChannels = 2;
        break;

    }
    mItems.append(item);
    mCurrentIndex++;

    emit postItemAppended();
}

void timeSlotList::removeItems(const quint32 &id)
{
    for (int i = 0; i < mItems.size(); ) {
        if (mItems.at(i).id == id) {
            emit preItemRemoved(i);

            mItems.removeAt(i);

            emit postItemRemoved();

            return;
        } else {
            ++i;
        }
    }
}
