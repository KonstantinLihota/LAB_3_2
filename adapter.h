#pragma once

#include "filetablemodel.h"
#include <QtCharts>
/*Адаптер — это структурный паттерн проектирования, который позволяет объектам
 *  с несовместимыми интерфейсами работать вместе.
 * Наблюдатель — это поведенческий паттерн проектирования, который создаёт механизм подписки,
 *  позволяющий одним объектам следить и реагировать на события, происходящие в других объектах.
 *
 *  В данной задаче мы его используем  в паре с наблюдателем так как  диаграммы не являются частью системы MVC.
*/

class Adapter
{
public:

    virtual ~Adapter() = default;


    virtual void updateData(const QVector<QPair<QString, uint64_t>>& data) = 0;//чисто виртуалный метод отвечающий за обновление данных
};


class TableAdapter : public Adapter //аддаптер для представления в виде таблицы
{
public:

   TableAdapter(FileTableModel* model);
   void updateData(const QVector<QPair<QString, uint64_t>>& data) override;

private:

   FileTableModel* m_model;
};




class ChartAdapter : public Adapter//аддаптер для представления в диаграмм
{
public:

   ChartAdapter(QChart* chart, QChartView* view);
   virtual ~ChartAdapter();


   void updateData(const QVector<QPair<QString, uint64_t>>& data) override;//главный шаблонный метод для обновления графиков

protected:

   virtual QAbstractSeries* makeSeries() = 0;
   virtual void appendToSeries(QAbstractSeries* series, const QString& label, float percent) = 0;

   QChart* m_chart;
   QChartView* m_view;
};



class BarChartAdapter : public ChartAdapter//для столбчатой диаграммы
{
public:

   BarChartAdapter(QChartView* view);

private:

   QAbstractSeries* makeSeries() override;
   void appendToSeries(QAbstractSeries* series, const QString& label, float percent) override;
};



class PieChartAdapter : public ChartAdapter//для круговой диаграммы
{
public:

   PieChartAdapter(QChartView* view);

private:

   QAbstractSeries* makeSeries() override;
   void appendToSeries(QAbstractSeries* series, const QString& label, float percent) override;
};
