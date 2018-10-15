#ifndef TIMESLOTLIST_H
#define TIMESLOTLIST_H

#include <QObject>
#include <QVector>

struct timeSlotItem{
    quint32 id;
    quint32 fromMs;
    quint32 toMs;
    quint8 group;
    bool ValveOnOff;
    bool LedOnOff;
    bool Inverter;
    quint8 LedMode;
    quint8 InverterLevel;
    QString fileBinPath;
    QString LedValuesList;
    quint8 LedChannels;
    quint8 ValveChannels;
};

class timeSlotList : public QObject
{
    Q_OBJECT

    QVector<timeSlotItem> mItems;
    quint32 mCurrentIndex;
public:
    explicit timeSlotList(QObject *parent = nullptr);
    QVector<timeSlotItem> items() const;
    bool setItemAt(int index, const timeSlotItem &item);
signals:
    void preItemAppended();
    void postItemAppended();

    void preItemRemoved(int index);
    void postItemRemoved();

public slots:

    void appendItem(const quint8 &group,const quint32 &fromMs, const quint32 &toMs);
    void removeItems(const quint32 &id);

};

#endif // TIMESLOTLIST_H
