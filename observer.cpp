#include "observer.h"

void FilesObserver::subscribe(Adapter* adapter)
{
    if(adapter && !m_adapters.contains(adapter))
    {
        m_adapters.push_back(adapter);
    }
}

void FilesObserver::unsubscribe(Adapter* adapter)
{
    int index = m_adapters.indexOf(adapter);
    if(index >= 0)
    {
        m_adapters.remove(index);
    }
}

void FilesObserver::update(const QVector<QPair<QString, uint64_t>>& data)
{
    for(Adapter* adapter : m_adapters)
        adapter->updateData(data);
}

// оповестить конкретного подписчика
void FilesObserver::updateByIndex(const QVector<QPair<QString, uint64_t>>& data, int index)
{
    if(index >= 0 && index < m_adapters.size())
    {
        m_adapters[index]->updateData(data);
    }
}

// метод, чтобы получать по индексу подписчиков
// полезно, если нужно извне всех их удалить
Adapter* FilesObserver::getByIndex(int index)
{
    if(index >= 0 && index < m_adapters.size())
    {
        return m_adapters[index];
    }

}

int FilesObserver::count()
{
    return m_adapters.size();
}
