

#include "leventbus.h"

void LEventBus::subscribe(const QString & event, const LEventBus::Callback & callback)
{
    if (!m_callbacks.contains(event))
    {
        m_callbacks[event] = QList<Callback>();
    }
    m_callbacks[event].append(callback);
}

void LEventBus::publish(const QString & event, const QVariant & data)
{
    if (m_callbacks.contains(event))
    {
        for (const Callback & callback : m_callbacks[event])
        {
            callback(data);
        }
    }
}
