#pragma once
#include "adapter.h"
#include <QVector>
#include <QPair>

// наблюдатель
class FilesObserver
{
public:

   //добавить адаптер
   void subscribe(Adapter* adapter);
   //отписать
   void unsubscribe(Adapter* adapter);
   //Оповестить
   void update(const QVector<QPair<QString, uint64_t>>& data);
   // оповестить контрктный адаптер
   void updateByIndex(const QVector<QPair<QString, uint64_t>>& data, int index);
   Adapter* getByIndex(int index);
   int count();

private:

   //список адаптеров
   QVector<Adapter*> m_adapters;
};
