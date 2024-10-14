#ifndef LEVENTBUS_H
#define LEVENTBUS_H

#include <QObject>
#include <QMap>
#include <QList>
#include <QVariant>
#include <functional>
#include <include_common/TSingleton.hpp>

#include "leventbus_global.h"

class LEVENTBUS_EXPORT LEventBus : public QObject,
                                   public TSingleton<LEventBus>
{
    friend class TSingleton<LEventBus>;
    Q_OBJECT

public:
    using Callback = std::function<void(const QVariant &)>;

    void subscribe(const QString & event, const Callback & callback);

    void publish(const QString & event, const QVariant & data);

private:
    LEventBus() {}
    QMap<QString, QList<Callback>> m_callbacks;
};

#endif // LEVENTBUS_H
